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

#include "project_manager.h"

#include <QToolBar>
#include "custom_tab_widget.h"
#include <QStatusBar>

#include <QDockWidget>
#include "view/3d_view.h"
#include "view/2d_view.h"
#include "view/explorer_view.h"
#include "view/library_view.h"

#include "preferences_dialog.h"

#include "project.h"

namespace mina {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showStatusBarMsg(const QString &_msg, int _lengthInSecs);

    QPointer<QToolBar> m_toolsBar; // node-graph tools
    QPointer<QToolBar> m_docBar; // document-related tools
    QPointer<CustomTabWidget> m_tabWidget;

    QPointer<ProjectManager> m_projectManager;
    QPointer<Q3dView> m_3dView;
    QPointer<Q2dView> m_2dView;
    QPointer<ExplorerView> m_explorerView;
    QPointer<LibraryView> m_libraryView;

protected:
    QPointer<QMenuBar> m_menuBar;
    QPointer<QStatusBar> m_statusBar;

    QPointer<PreferencesDialog> m_preferencesDlg;
    QPointer<QDockWidget> m_3dViewDock;
    QPointer<QDockWidget> m_2dViewDock;
    QPointer<QDockWidget> m_explorerDock;
    QPointer<QDockWidget> m_libraryDock;

private:
    QMenu *m_fileMenu;
    
    QMenu *m_editMenu;
    QAction *m_edit_preferencesAction;
    
    QMenu *m_viewMenu;

    QMenu *m_helpMenu;
    QAction *m_help_aboutAction;

    QList<QMenu*> m_lMenus;

signals:
    void newProjectAdded(Project *_project);

public slots:
    void on_editPreferencesAction_clicked();
    void on_Project_added(Project *_project);
    void on_Project_changed(Project *_project);
};

} // namespace