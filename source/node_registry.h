// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QObject>

#include <QString>
#include <QStringList>
#include <QList>

namespace mina {

class NodeRegistry : public QObject {
    Q_OBJECT
public:
    struct SqlPack {
        QString uniqueId;
        QString name;
        QString category;
        QString verStr;
        QString author;
        QString description;
    };
    explicit NodeRegistry(QObject *parent = nullptr);
    ~NodeRegistry();

    void setNodeSearchPath(const QString &_searchPath);
    QString nodeSearchPath();

protected:
    QString m_searchPath;

    QStringList m_lINodes;
    QStringList m_lJsonFiles;

private:
    void index(const QString &_path, QStringList &_list);

public slots:
    bool initializeLocalDb(); // todo: load a backup?
    void indexResourcePath();
    void indexSearchPath(const QString &_searchPath);
    void fillRegistry(const QStringList &_jsonFiles);

signals:
    void indexingFinished(const QStringList &_files);
};

} // namespace