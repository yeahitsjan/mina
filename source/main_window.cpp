// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "main_window.h"
#include "application.h"

namespace mina {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    if (!m_menuBar)
        m_menuBar = new QMenuBar;
    m_menuBar->setFont(MApp->platformFont(11));
    this->setMenuBar(m_menuBar);

    if (!m_toolsBar)
        m_toolsBar = new QToolBar;
    m_toolsBar->setFloatable(false);
    this->addToolBar(Qt::LeftToolBarArea, m_toolsBar);

    if (!m_docBar)
        m_docBar = new QToolBar;
    m_docBar->setFloatable(false);
    this->addToolBar(Qt::TopToolBarArea, m_docBar);

    m_lMenus.append( m_fileMenu = m_menuBar->addMenu("File") );
    m_lMenus.append( m_editMenu = m_menuBar->addMenu("Edit") );
    m_lMenus.append( m_viewMenu = m_menuBar->addMenu("View") );

    m_lMenus.append( m_helpMenu = m_menuBar->addMenu("Help") );
    m_help_aboutAction = new QAction("About Mina", m_helpMenu);
    m_helpMenu->addAction(m_help_aboutAction);

    foreach (QMenu *_m, m_lMenus) {
        _m->setFont(MApp->platformFont(11));
    }

    this->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

    if (!m_tabWidget)
        m_tabWidget = new QTabWidget;
    m_tabWidget->setMovable(true);
    m_tabWidget->setTabsClosable(true);
    this->setCentralWidget(m_tabWidget);

    m_tabWidget->addTab(new NodeGraphView, "Node Graph 1");

    if (!m_statusBar)
        m_statusBar = new QStatusBar;
    this->setStatusBar(m_statusBar);

    this->showStatusBarMsg("OpenGL version " + MApp->currentGpuInfo().openGlVer + " on " + MApp->currentGpuInfo().devName, 10);
}

MainWindow::~MainWindow() {
}

void MainWindow::showStatusBarMsg(const QString &_msg, int _lengthInSecs) {
    if (m_statusBar)
        m_statusBar->showMessage(_msg, _lengthInSecs * 1000);
}

} // namespace