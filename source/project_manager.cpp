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
    emit projectAdded(_project);
}

QList<Project*> ProjectManager::projectsInManager() {
    return m_lProjects;
}

} // namespace