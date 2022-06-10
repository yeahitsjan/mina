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

void ProjectManager::on_graphConfig_refreshed(bool _aa, bool _glAccel) {
    foreach (Project *_p, m_lProjects) {
        // There is still a strange bug here...
        // After enable/disable of GL acceleration of all open graphs, the graphs
        // not in focus (display) are getting resized as a square.
        // QGLWidget is deprecated, QOpenGLWidget throws errors related to QProxyWidget
        // ---BIG TODO---
        _p->refreshGraphConfig(_aa, _glAccel);
    }
}

} // namespace