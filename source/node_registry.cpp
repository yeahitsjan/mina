// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "node_registry.h"
#include "easylogging++.h"

#include <QFileInfo>
#include <QDirIterator>
#include <QStandardPaths>

#include <QVariant>

#include <QFile>
#include <QByteArray>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QCryptographicHash>

namespace mina {

NodeRegistry::NodeRegistry(QObject *parent) : QObject(parent) {
    connect(this, &NodeRegistry::indexingFinished, this, &NodeRegistry::fillRegistry);
}

NodeRegistry::~NodeRegistry() {
}

void NodeRegistry::setNodeSearchPath(const QString &_searchPath) {
    const QFileInfo dir(_searchPath);
    if ( (!dir.exists()) || (!dir.isDir()) ) {
        LOG(ERROR) << "Given search path for node database does not exists or is not a directory.";
        return;
    }
    m_searchPath = _searchPath;
}

QString NodeRegistry::nodeSearchPath() {
    if (m_searchPath.isEmpty()) {
        // fallback to default search path
        QString _fallback = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.mina/cnode/";
    }
    return m_searchPath;
}

QStringList NodeRegistry::nodesFromCategory(const QString &_category) {
    QStringList r;
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.mina/n.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * FROM nodes WHERE category = :cat");
    q.bindValue(":cat", QVariant(_category));
    if (q.exec()) {
        while (q.next()) {
            QString cc = q.value(0).toString() + ";" + q.value(1).toString();
            r.append(cc);
        }
    }
    db.close();
    return r;
}

void NodeRegistry::index(const QString &_path, QStringList &_list) {
    QDirIterator it(_path, QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        it.next();
        if ( QFileInfo( it.filePath() ).isFile() ) {
            if ( QFileInfo( it.filePath() ).suffix() == "json" )
                _list.append(it.filePath());
        }
    }
    LOG(INFO) << "Finished indexing; Found " + QString::number(_list.count()) + " files";
}

QString NodeRegistry::generateUniqueId(const QString &_name, const QString &_verStr) {
    QString identifier = "__NODE__" + _name + "**" + _verStr;
    QString hash = QString("%1").arg(QString(QCryptographicHash::hash(identifier.toUtf8(), QCryptographicHash::Sha1).toHex()));
    return hash;
}

void NodeRegistry::clearPack(SqlPack _pack) {
    _pack.uniqueid = "";
    _pack.name = "";
    _pack.category = "";
    _pack.versionstring = "";
    _pack.author = "";
    _pack.description = "";
}

bool NodeRegistry::existsInRegistry(const QString &_uniqueId) {
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.mina/n.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    db.open();
    QSqlQuery q;
    q.prepare("SELECT * FROM nodes WHERE uniqueid = :uniqueId");
    q.bindValue(":uniqueId", QVariant(_uniqueId));
    if (q.exec()) {
        bool res = q.next();
        if (res) {
            LOG(INFO) << "Node with id " + _uniqueId + " already exists in registry.";
            return true;
        } else {
            return false;
        }   
    }
    db.close();
}

void NodeRegistry::addToRegistry(SqlPack _pack) {
    if (!this->existsInRegistry(_pack.uniqueid)) {
        QString dbPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.mina/n.db";
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);
        db.open();
        QSqlQuery q;
        q.prepare("INSERT INTO nodes (uniqueid, name, category, versionstring, author, description) "
                                "VALUES (:uniqueid, :name, :category, :versionstring, :author, :description)");
        q.bindValue(":uniqueid", QVariant(_pack.uniqueid));
        q.bindValue(":name", QVariant(_pack.name));
        q.bindValue(":category", QVariant(_pack.category));
        q.bindValue(":versionstring", QVariant(_pack.versionstring));
        q.bindValue(":author", QVariant(_pack.author));
        q.bindValue(":description", QVariant(_pack.description));
        if (q.exec())
            LOG(INFO) << "Added node '" + _pack.name + " (" + _pack.uniqueid + ")' to registry.";
        else
            LOG(ERROR) << "Could not add node to database. SQLITE_ERR: " + q.lastError().text();
        db.close();
    }
}

bool NodeRegistry::initializeLocalDb() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.mina/n.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    QSqlQuery q;
    return q.exec("CREATE TABLE nodes "
                "(uniqueid varchar(200), "
                "name varchar(200), "
                "category varchar(200), "
                "versionstring varchar(200), "
                "author varchar(200), "
                "description varchar(200))");
}

void NodeRegistry::indexResourcePath() {
    LOG(INFO) << "Loading INodes from resources";
    this->index(":/NODE_REGISTRY/source/inode/", m_lINodes);
    emit indexingFinished(m_lINodes);
}

void NodeRegistry::indexSearchPath(const QString &_searchPath) {
    LOG(INFO) << "Start indexing search path";
    this->index(_searchPath, m_lJsonFiles);
    emit indexingFinished(m_lJsonFiles);
}

void NodeRegistry::fillRegistry(const QStringList &_jsonFiles) {
    if (_jsonFiles.isEmpty()) {
        LOG(INFO) << "No nodes to be added";
        return;
    }

    SqlPack p;

    foreach (QString _jsonFile, _jsonFiles) {
        bool err = false;
        this->clearPack(p);

        QFile f(_jsonFile);
        if (!f.open( QIODevice::ReadOnly )) {
            LOG(ERROR) << "Could not read JSON!";
            err = true;
        }

        QByteArray ba;
        ba = f.readAll();
        f.close();

        QJsonParseError jErr;
        QJsonDocument jDoc;
        jDoc = QJsonDocument::fromJson(ba, &jErr);
        if (jErr.error != QJsonParseError::NoError) {
            LOG(ERROR) << "Could not parse JSON in file " + f.fileName() + ". Error string: <" + jErr.errorString() + ">";
            err = true;
        }

        if (err == false) {
            QJsonObject jObj;
            jObj = jDoc.object();

            QJsonValue jVal;

            jVal = jObj.value("name");
            p.name = jVal.toString();
            jVal = jObj.value("category");
            p.category = jVal.toString();
            jVal = jObj.value("version");
            p.versionstring = jVal.toString();
            jVal = jObj.value("author");
            p.author = jVal.toString();
            jVal = jObj.value("description");
            p.description = jVal.toString();

            p.uniqueid = this->generateUniqueId(p.name, p.versionstring);
            this->addToRegistry(p);
        }
    }
    // Clearup.
    this->clearPack(p);
}

} // namespace
