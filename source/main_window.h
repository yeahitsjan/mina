// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <QPointer>
#include <QList>

#include <QMenuBar>
#include <QMenu>

#include <QToolBar>
#include <QTabWidget>
#include <QStatusBar>

#include "node_graph.h"

namespace mina {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showStatusBarMsg(const QString &_msg, int _lengthInSecs);

    QPointer<QToolBar> m_toolsBar; // node-graph tools
    QPointer<QToolBar> m_docBar; // document-related tools
    QPointer<QTabWidget> m_tabWidget;

protected:
    QPointer<QMenuBar> m_menuBar;
    QPointer<QStatusBar> m_statusBar;

private:
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_viewMenu;

    QMenu *m_helpMenu;
    QAction *m_help_aboutAction;

    QList<QMenu*> m_lMenus;
};

} // namespace