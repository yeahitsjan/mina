// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "easylogging++.h"
#include "abstract_node.h"

#include <QSize>
#include <QVBoxLayout>

namespace mina {

AbstractNodeWidget::AbstractNodeWidget(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(QSize(100, 28));

    m_mainBtn = new QPushButton;
    QVBoxLayout *_layout = new QVBoxLayout;
    _layout->setSpacing(0);
    _layout->setMargin(0);
    _layout->addWidget(m_mainBtn);
    m_mainBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setLayout(_layout);
}

AbstractNodeWidget::~AbstractNodeWidget() {
}

AbstractNode::AbstractNode(QObject *parent) : QObject(parent) {
    if (!m_graphWidget)
        m_graphWidget = new AbstractNodeWidget;
    connect(this, &AbstractNode::mainFinished, this, &AbstractNode::onMainFinished);
}

AbstractNode::~AbstractNode() {
}

void AbstractNode::main() {
    // Each node type reimplements this function(, should not be reached).
    LOG(INFO) << "I am an abstract node. Do something with me!";
    // Function (in-theory) executed successfully.
    emit mainFinished();
}

int AbstractNode::nodeType() {
    return 1; // AbstractNode always has node type 1.
}

AbstractNodeWidget* AbstractNode::graphWidget() {
    return m_graphWidget;
}

void AbstractNode::onMainFinished() {
    // Each node type can reimplement this slot.
    LOG(DEBUG) << "The node did it's stuff. Amazing! ---END---";
    emit readyForDisplay(this);
}

} // namespace