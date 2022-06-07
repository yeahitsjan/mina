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

#include "preferences_dialog.h"
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
    QPointer<CustomTabWidget> m_tabWidget;

    QPointer<ProjectManager> m_projectManager;

protected:
    QPointer<QMenuBar> m_menuBar;
    QPointer<QStatusBar> m_statusBar;

    QPointer<PreferencesDialog> m_preferencesDlg;

private:
    QMenu *m_fileMenu;
    
    QMenu *m_editMenu;
    QAction *m_edit_preferencesAction;
    
    QMenu *m_viewMenu;

    QMenu *m_helpMenu;
    QAction *m_help_aboutAction;

    QList<QMenu*> m_lMenus;

public slots:
    void on_editPreferencesAction_clicked();
    void on_activeProject_changed();
};

} // namespace