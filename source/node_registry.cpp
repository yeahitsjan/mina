// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "node_registry.h"
#include "easylogging++.h"

#include <QFileInfo>
#include <QDirIterator>
#include <QStandardPaths>

#include <QFile>
#include <QByteArray>

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

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

    foreach (QString _jsonFile, _jsonFiles) {
        bool err = false;
        //node?

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
            //todo: parse json
        }
    }
}

} // namespace