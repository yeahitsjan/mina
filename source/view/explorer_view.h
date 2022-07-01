// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QWidget>
#include <QObject>

#include <QPointer>

#include "../project.h"

#include <QToolBar>
#include <QTreeWidget>

namespace mina {

class ExplorerView : public QWidget {
    Q_OBJECT
public:
    explicit ExplorerView(QWidget *parent = nullptr);
    ~ExplorerView();

    // Sets the project so the explorer can load project resources.
    void setProject(Project *_project);
    Project* currentProject();

protected:
    QPointer<QToolBar> m_toolBar;
    QPointer<QTreeWidget> m_projectTree;
    
    QPointer<Project> m_currentProject;
};

} // namespace