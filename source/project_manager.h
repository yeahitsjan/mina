// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QObject>

#include <QList>

#include "project.h"

namespace mina {

class ProjectManager : public QObject {
    Q_OBJECT
public:
    explicit ProjectManager(QObject *parent = nullptr);
    ~ProjectManager();

    // Add a project to the manager.
    void addProject(Project *_project);
    // Return all projects of the manager in the current session.
    QList<Project*> projectsInManager();

protected:
    QList<Project*> m_lProjects;

private:
    Project *m_activeProject;

signals:
    void projectAdded(Project *_project);

public slots:
    void on_graphConfig_refreshed(bool _aa, bool _glAccel);
};

} // namespace