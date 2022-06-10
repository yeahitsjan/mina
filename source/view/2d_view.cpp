// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "2d_view.h"

#include <QVBoxLayout>

namespace mina {

Q2dView::Q2dView(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *_viewLayout = new QVBoxLayout;

    if (!m_toolBar)
        m_toolBar = new QToolBar;
    // disable toolbar like behavior
    m_toolBar->setFloatable(false);
    m_toolBar->setMovable(false);
    _viewLayout->addWidget(m_toolBar);

    QWidget *__p = new QWidget;
    __p->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _viewLayout->addWidget(__p);

    this->setLayout(_viewLayout);
}

Q2dView::~Q2dView() {
}

void Q2dView::setInput() {
    //todo
}

} // namespace