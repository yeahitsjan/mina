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

// ---DEPRECATED DUE TO PROJECT MANAGER CLASS---
void CustomTabWidget::addDocument() {
    NodeGraphView *newNodeGraph = new NodeGraphView(this);
    newNodeGraph->setAA(MApp->ngConfiguredAA());
    newNodeGraph->setGlAcceleration(MApp->ngConfiguredGLAcceleration());
    newNodeGraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_graphsInSession.append(newNodeGraph);
    connect(this, &CustomTabWidget::graphConfigRefreshRequested, newNodeGraph, &NodeGraphView::onGraphReconfigured);
    this->addTab(newNodeGraph, "Node Graph " + QString::number(m_graphsInSession.count()));
}

void CustomTabWidget::refreshGraphConfig(bool _aa, bool _glAccel) {
    // TODO: a strange bug appear on refresh of graph =>
    // anytime the GL viewport is changed all viewports except the currently displayed one
    // are getting squared. Probably this has something to do with the NodeGraphView being the
    // only widget inside the tab widgets page? Need to further look into this...
    emit graphConfigRefreshRequested(_aa, _glAccel);
#if 0
    foreach (NodeGraphView *_graph, m_graphsInSession) {
        _graph->onGraphReconfigured(_aa, _glAccel);
    }
#endif
}
// ---DEPRECATED DUE TO PROJECT MANAGER CLASS---

} // namespace