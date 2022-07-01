// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QWidget>
#include <QObject>

#include <QPointer>

#include <QToolBar>
#include <QLineEdit>

namespace mina {

class LibraryView : public QWidget {
    Q_OBJECT
public:
    explicit LibraryView(QWidget *parent = nullptr);
    ~LibraryView();

protected:
    QPointer<QToolBar> m_toolBar;
    QLineEdit *m_searchBox;
};

} // namespace