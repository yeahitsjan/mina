// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "project_manager.h"

namespace mina {

ProjectManager::ProjectManager(QObject *parent) : QObject(parent) {
}

ProjectManager::~ProjectManager() {
}

void ProjectManager::addProject(Project *_project) {
    m_lProjects.append(_project);
    this->setAsActiveProject(_project);
}

QList<Project*> ProjectManager::projectsInManager() {
    return m_lProjects;
}

Project* ProjectManager::activeProject() {
    return m_activeProject;
}

void ProjectManager::setAsActiveProject(Project *_project) {
    m_activeProject = _project;
    emit activeProjectChanged();
}

} // namespace