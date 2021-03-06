// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "node_graph.h"
#include "easylogging++.h"
#include "application.h"

#include <QGraphicsScene>

#include "inode/read_inode.h"
#include "inode/solidcolor_inode.h"

namespace mina {

QPixmap GridBuilder_p::drawPattern(int _step, const QColor &_col) {
    QPixmap px(_step, _step);
    QPainter p;
    
    int pxwidth = px.width() - 1;
    px.fill(QColor(47, 47, 47));

    p.begin(&px);
    drawSq(&p, pxwidth, _col);
    return px;
}

void GridBuilder_p::drawSq(QPainter *_painter, int _w, const QColor &_col) {
    _painter->setPen(_col);
    _painter->drawLine(0, 0, _w, 0);
    _painter->drawLine(0, 0, 0, _w);
}

void ControllerRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem::mousePressEvent(event);
        event->accept();
    }
}

void ControllerRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
    // pos change
}

NodeGraphView::NodeGraphView(QWidget *parent) : QGraphicsView(parent) {
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setCacheMode(QGraphicsView::CacheBackground);

    connect(this, &NodeGraphView::glAccelerationChanged, this, &NodeGraphView::glAcceleration);
    connect(this, &NodeGraphView::aaModeChanged, this, &NodeGraphView::aaMode);

    this->setBackgroundBrush(QBrush(GridBuilder_p::drawPattern(25, QColor(51, 51, 51)))); // darker so it can be differentiated
    this->setScene(new QGraphicsScene(this));
}

NodeGraphView::~NodeGraphView() {
}

void NodeGraphView::setGlAcceleration(bool en) {
    emit glAccelerationChanged(en);
}

void NodeGraphView::setAA(bool en) {
    emit aaModeChanged(en);
}

void NodeGraphView::addNode(AbstractNode *_node) {
    connect(_node, &AbstractNode::readyForDisplay, this, &NodeGraphView::nodeReadyForDisplay);
    _node->main();
}

void NodeGraphView::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        const qreal det = QStyleOptionGraphicsItem::levelOfDetailFromTransform( this->transform() );
        const qreal fac = 1.1;
        if ( (det < 3.5) && (event->angleDelta().y() > 0) )
            this->scale(fac, fac);
        if ( (det > 1.0) && (event->angleDelta().y() < 0) )
            this->scale( (1 / fac), (1 / fac) );
    } else {
        QGraphicsView::wheelEvent(event);
    }
}

void NodeGraphView::contextMenuEvent(QContextMenuEvent *event) {
    if (!m_nodesMenu) {
        m_nodesMenu = new QMenu;

        m_bitmapNodesMenu = new QMenu("Bitmap");
        m_bitmapNodesMenu->addActions(this->entriesFromCategory("1"));
        m_nodesMenu->addMenu(m_bitmapNodesMenu);

        if (!m_scriptNodesMenu)
            m_scriptNodesMenu = new QMenu("Script");
        m_scriptNodesMenu->addActions(this->entriesFromCategory("2"));
        m_nodesMenu->addMenu(m_scriptNodesMenu);
        if (!m_pluginNodesMenu)
            m_pluginNodesMenu = new QMenu("Plugin");
        m_pluginNodesMenu->addActions(this->entriesFromCategory("3"));
        m_nodesMenu->addMenu(m_pluginNodesMenu);

        m_nodesMenu->addSeparator();

        m_materialNodesMenu = new QMenu("Material");
        m_materialNodesMenu->addActions(this->entriesFromCategory("0"));
        m_nodesMenu->addMenu(m_materialNodesMenu);
    }

    m_nodesMenu->exec(event->globalPos());
}

QList<QAction*> NodeGraphView::entriesFromCategory(const QString &_category) {
    QList<QAction*> r;
    QStringList entries = MApp->nodeEntriesForCategory(_category);
    if (entries.isEmpty())
        return r;
    foreach (QString _e, entries) {
        QAction *_action = new QAction;
        _action->setText(_e);
        //todo: assign uniqueid somewhere, probably moving into own class inherting from QAction
        r.append(_action);
    }
    return r;
}

void NodeGraphView::onGraphReconfigured(bool _aa, bool _glAccel) {
    this->setAA(_aa);
    this->setGlAcceleration(_glAccel);
}

void NodeGraphView::glAcceleration(bool en) {
    if (!m_glViewport)
        m_glViewport = new QGLWidget(QGLFormat(QGL::SampleBuffers));

    if (en) {
        this->setViewport(m_glViewport);
        LOG(INFO) << "node_graph: Enabled GL acceleration in current session";
        MApp->ngConfigureGLAcceleration(true);
    } else {
        this->setViewport(new QWidget);
        LOG(INFO) << "node_graph: Disabled GL acceleration in current session";
        MApp->ngConfigureGLAcceleration(false);
    }
}

void NodeGraphView::aaMode(bool en) {
    if (en) {
        this->setRenderHint(QPainter::Antialiasing, true);
        LOG(INFO) << "node_graph: Enabled anti-aliasing in current session";
        MApp->ngConfigureAA(true);
    } else {
        this->setRenderHint(QPainter::Antialiasing, false);
        LOG(INFO) << "node_graph: Disabled anti-aliasing in current session";
        MApp->ngConfigureAA(false);
    }
}

void NodeGraphView::nodeReadyForDisplay(AbstractNode *_node) {
    QPoint __tmpPoint(0, 0); // temporary

    ControllerRectItem *_proxyController = new ControllerRectItem;
    _proxyController->setRect(QRectF(__tmpPoint.x(), __tmpPoint.y(), _node->graphWidget()->width(), 10));
    _proxyController->setPen(QPen(Qt::gray));
    _proxyController->setBrush(QBrush(QColor(230, 8, 70))); // TODO: based on node type
    _proxyController->setFlag(QGraphicsItem::ItemIsMovable, true);
    _proxyController->setFlag(QGraphicsItem::ItemIsSelectable, true);
    _proxyController->setCursor(Qt::SizeAllCursor);
    this->scene()->addItem(_proxyController);

    QGraphicsProxyWidget* const _proxy = this->scene()->addWidget(_node->graphWidget());
    _proxy->setPos(__tmpPoint.x(), __tmpPoint.y() + _proxyController->rect().height());
    _proxy->setParentItem(_proxyController);

    m_lNodesInGraph.append(_node);
}

} // namespace