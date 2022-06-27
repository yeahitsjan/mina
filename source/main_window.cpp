// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "main_window.h"
#include "application.h"

namespace mina {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    if (!m_menuBar)
        m_menuBar = new QMenuBar;
    m_menuBar->setFont(MApp->platformFont(12));
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
    m_edit_preferencesAction = new QAction("Preferences", m_editMenu);
    connect(m_edit_preferencesAction, &QAction::triggered, this, &MainWindow::on_editPreferencesAction_clicked);
    m_editMenu->addAction(m_edit_preferencesAction);
    
    m_lMenus.append( m_viewMenu = m_menuBar->addMenu("View") );

    m_lMenus.append( m_helpMenu = m_menuBar->addMenu("Help") );
    m_help_aboutAction = new QAction("About Mina", m_helpMenu);
    m_helpMenu->addAction(m_help_aboutAction);

    foreach (QMenu *_m, m_lMenus) {
        _m->setFont(MApp->platformFont(12));
    }

    this->setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);

    if (!m_tabWidget)
        m_tabWidget = new CustomTabWidget;
    this->setCentralWidget(m_tabWidget);
    connect(this, &MainWindow::newProjectAdded, m_tabWidget, &CustomTabWidget::addProjectTab);
    connect(m_tabWidget, &CustomTabWidget::projectChanged, this, &MainWindow::on_Project_changed);

    if (!m_statusBar)
        m_statusBar = new QStatusBar;
    this->setStatusBar(m_statusBar);

    if (!m_projectManager)
        m_projectManager = new ProjectManager;
    connect(m_projectManager, &ProjectManager::projectAdded, this, &MainWindow::on_Project_added);

    if (!m_3dView)
        m_3dView = new Q3dView;
    if (!m_3dViewDock)
        m_3dViewDock = new QDockWidget;
    m_3dViewDock->setWidget(m_3dView);
    this->addDockWidget(Qt::BottomDockWidgetArea, m_3dViewDock);

    if (!m_2dView)
        m_2dView = new Q2dView;
    if (!m_2dViewDock)
        m_2dViewDock = new QDockWidget;
    m_2dViewDock->setWidget(m_2dView);
    this->addDockWidget(Qt::BottomDockWidgetArea, m_2dViewDock);

    if (m_projectManager->projectsInManager().isEmpty()) {
        m_tabWidget->hide();
        m_3dViewDock->hide();
    }

    // test
    Project *_proj1 = new Project;
    _proj1->setProjectName("Autobahn Old tarmac");
    m_projectManager->addProject(_proj1);
    Project *_proj2 = new Project;
    _proj2->setProjectName("MyCoolMaterial");
    m_projectManager->addProject(_proj2);

    this->showStatusBarMsg("OpenGL version " + MApp->currentGpuInfo().openGlVer + " on " + MApp->currentGpuInfo().devName, 10);
}

MainWindow::~MainWindow() {
}

void MainWindow::showStatusBarMsg(const QString &_msg, int _lengthInSecs) {
    if (m_statusBar)
        m_statusBar->showMessage(_msg, _lengthInSecs * 1000);
}

void MainWindow::on_editPreferencesAction_clicked() {
    if (!m_preferencesDlg)
        m_preferencesDlg = new PreferencesDialog(this);
    connect(m_preferencesDlg, &PreferencesDialog::graphReconfigured, m_projectManager, &ProjectManager::on_graphConfig_refreshed);
    m_preferencesDlg->exec();
}

void MainWindow::on_Project_added(Project *_project) {
    if (!m_tabWidget->isVisible())
        m_tabWidget->show();
    if (!m_3dViewDock->isVisible())
        m_3dViewDock->show();
    emit newProjectAdded(_project);
}

void MainWindow::on_Project_changed(Project *_project) {
    // todo: redirect input for 3d/2d view, assets (lib / explorer)
    LOG(DEBUG) << "Changed to project " + _project->projectUniqueId();
    if (m_3dViewDock) {
        m_3dViewDock->setWindowTitle("3D VIEW - [" + _project->projectName() + "]");
    }
    if (m_2dViewDock) {
        m_2dViewDock->setWindowTitle("2D VIEW - [" + _project->projectName() + "]");
    }
    // todo: 2d + 3d view needs to get new input
}

} // namespace