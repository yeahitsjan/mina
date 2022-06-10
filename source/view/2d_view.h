// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QWidget>
#include <QObject>

#include <QPointer>

#include <QToolBar>

namespace mina {

class Q2dView : public QWidget {
    Q_OBJECT
public:
    explicit Q2dView(QWidget *parent = nullptr);
    ~Q2dView();

    // Set the input (material) to be applied to the 3d object in view.
    void setInput(/*GeneratedMaterial*/);

protected:
    QPointer<QToolBar> m_toolBar;
};

} // namespace