// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "custom_tab_widget.h"
#include "application.h"

namespace mina {

CustomTabWidget::CustomTabWidget(QWidget *parent) : QTabWidget(parent) {
    this->setMovable(true);
    this->setTabsClosable(true);
}

CustomTabWidget::~CustomTabWidget() {
}

void CustomTabWidget::addProjectTab(Project *_project) {
    m_openProjects.append(_project);
    this->addTab(_project->nodeGraph(), "Node Graph - [" + _project->projectName() + "]");
}

} // namespace