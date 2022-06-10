// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QWidget>
#include <QObject>

#include <QPointer>
#include <QString>

#include <QVBoxLayout>

#include "node_graph.h"

namespace mina {

class Project : public QWidget {
    Q_OBJECT
public:
    Project(QWidget *parent = nullptr);
    Project(const QString &_fromPath, QWidget *parent = nullptr);
    ~Project();

    // TODO
    //void save
    //void read

    // Set a project name (doesn't needs to be unique).
    void setProjectName(const QString &_projectName);
    // Return the project's name.
    QString projectName();

    // Return the project's unique id.
    QString projectUniqueId();

    // Refresh the node graph's configuration (mainly called). TODO: slot?
    void refreshGraphConfig(bool _aa, bool _glAccel);
    // Return the project's node graph.
    NodeGraphView* nodeGraph();

protected:
    QPointer<NodeGraphView> m_projectNodeGraph;

    // Internal. Just a setter for m_projectUniqueId (is generated in constructor).
    void setProjectUniqueId(const QString &_id);

    QVBoxLayout* createGraphUi();

private:
    QString m_mprFilePath;
    QString m_temporaryProjectPath;
    QString m_projectName;
    QString m_projectUniqueId;

    // Help function for unique id generation.
    QString textToMd5(const QString &_t);
};

} // namespace