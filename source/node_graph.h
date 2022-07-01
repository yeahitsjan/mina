// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QGraphicsView>
#include <QObject>
#include <QWidget>

#include <QtOpenGL>
#include <QPointer>
#include <QList>

#include <QMenu>
#include <QAction>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include <QWheelEvent>
#include <QContextMenuEvent>

#include "abstract_node.h"

namespace mina {

class GridBuilder_p {
public:
    static QPixmap drawPattern(int _step, const QColor &_col);

private:
    static void drawSq(QPainter *_painter, int _w, const QColor &_col);
};

class ControllerRectItem : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    int type() const override {
        return Type;
    }
};

class NodeGraphView : public QGraphicsView {
    Q_OBJECT
public:
    explicit NodeGraphView(QWidget *parent = nullptr);
    ~NodeGraphView();

    QPointer<QGLWidget> m_glViewport;

    // Set GL acceleration of the node graphs viewport.
    void setGlAcceleration(bool en);
    // Set anti-aliasing of the node graph's viewport.
    void setAA(bool en);
    // Add a node to the current scene (calls main function of node).
    void addNode(AbstractNode *_node);

    QPointer<QMenu> m_scriptNodesMenu;
    QPointer<QMenu> m_pluginNodesMenu;

protected:
    void wheelEvent(QWheelEvent *event) override; // zoom
    void contextMenuEvent(QContextMenuEvent *event) override; // right-click

    QPointer<QMenu> m_nodesMenu;

    QMenu *m_bitmapNodesMenu;
    // todo: subject to change due to load from registry

    QMenu *m_materialNodesMenu;

    QList<AbstractNode*> m_lNodesInGraph;

signals:
    void glAccelerationChanged(bool en);
    void aaModeChanged(bool en);

public slots:
    void onGraphReconfigured(bool _aa, bool _glAccel);
    void glAcceleration(bool en);
    void aaMode(bool en);
    void nodeReadyForDisplay(AbstractNode *_node); // fired from AbstractNode::readyForDisplay
};

} // namespace