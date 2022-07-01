// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "library_view.h"

#include <QVBoxLayout>

namespace mina {

LibraryView::LibraryView(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *_viewLayout = new QVBoxLayout;
    _viewLayout->setMargin(0);
    _viewLayout->setSpacing(0);

    if (!m_toolBar)
        m_toolBar = new QToolBar;
    m_toolBar->setFloatable(false);
    m_toolBar->setMovable(false);
    _viewLayout->addWidget(m_toolBar);

    //todo: actions to toolbar with space to searchbox

    m_searchBox = new QLineEdit;
    m_searchBox->setPlaceholderText("Search");
    m_toolBar->addWidget(m_searchBox);

    QWidget *__p = new QWidget;
    __p->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _viewLayout->addWidget(__p);

    this->setLayout(_viewLayout);
}

LibraryView::~LibraryView() {
}

} // namespace