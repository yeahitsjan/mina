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

    void addProject(Project *_project);
    QList<Project*> projectsInManager();

    Project* activeProject();

protected:
    QList<Project*> m_lProjects;

    void setAsActiveProject(Project *_project);

private:
    Project *m_activeProject;

signals:
    void activeProjectChanged();
};

} // namespace