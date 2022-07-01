// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "explorer_view.h"

#include <QVBoxLayout>

namespace mina {

ExplorerView::ExplorerView(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *_viewLayout = new QVBoxLayout;
    _viewLayout->setMargin(0);
    _viewLayout->setSpacing(0);
    
    if (!m_toolBar)
        m_toolBar = new QToolBar;
    m_toolBar->setFloatable(false);
    m_toolBar->setMovable(false);
    _viewLayout->addWidget(m_toolBar);

    if (!m_projectTree)
        m_projectTree = new QTreeWidget;
    m_projectTree->setHeaderHidden(true);
    m_projectTree->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _viewLayout->addWidget(m_projectTree);

    this->setLayout(_viewLayout);
}

ExplorerView::~ExplorerView() {
}

void ExplorerView::setProject(Project *_project) {
    //todo
}

Project* ExplorerView::currentProject() {
    return m_currentProject;
}

} // namespace