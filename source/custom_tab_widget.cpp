// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "custom_tab_widget.h"
#include "application.h"

namespace mina {

CustomTabWidget::CustomTabWidget(QWidget *parent) : QTabWidget(parent) {
    this->setMovable(true);
    this->setTabsClosable(true);

    connect(this, &CustomTabWidget::currentChanged, this, &CustomTabWidget::on_Project_changed);
}

CustomTabWidget::~CustomTabWidget() {
}

void CustomTabWidget::addProjectTab(Project *_project) {
    m_openProjects.append(_project);
    this->addTab(_project, "Node Graph - [" + _project->projectName() + "]");
    LOG(DEBUG) << "Added project " + _project->projectUniqueId() + " to CustomTabWidget";
}

void CustomTabWidget::on_Project_changed(int index) {
    // This could be heavily unsafe if we have something different than a Project as a widget.
    Project *_newProject = qobject_cast<Project*>(this->currentWidget());
    emit projectChanged(_newProject);
}

} // namespace