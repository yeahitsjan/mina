// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QTabWidget>
#include <QObject>
#include <QWidget>

#include <QList>

#include "node_graph.h"

namespace mina {

class CustomTabWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit CustomTabWidget(QWidget *parent = nullptr);
    ~CustomTabWidget();

    // ---DEPRECATED DUE TO PROJECT MANAGER CLASS---
    void addDocument(); // TODO: currently empty; adds a document (new project or whatever)

protected:
    QList<NodeGraphView*> m_graphsInSession;

signals:
    void graphConfigRefreshRequested(bool _aa, bool _glAccel);

public slots:
    void refreshGraphConfig(bool _aa, bool _glAccel);
};

} // namespace