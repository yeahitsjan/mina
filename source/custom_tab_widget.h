// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QTabWidget>
#include <QObject>
#include <QWidget>

#include <QList>

#include "project.h"

namespace mina {

class CustomTabWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit CustomTabWidget(QWidget *parent = nullptr);
    ~CustomTabWidget();

protected:
    QList<Project*> m_openProjects;

signals:
    void projectChanged(Project *_project);

public slots:
    void addProjectTab(Project *_project);
    void on_Project_changed(int index);
};

} // namespace