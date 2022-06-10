// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "3d_view.h"

#include <QVBoxLayout>

namespace mina {

Q3dView::Q3dView(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *_viewLayout = new QVBoxLayout;
    _viewLayout->setSpacing(0);
    _viewLayout->setMargin(0);

    if (!m_viewMenuBar)
        m_viewMenuBar = new QMenuBar;
    m_sceneMenu = m_viewMenuBar->addMenu("Scene");
    m_lightMenu = m_viewMenuBar->addMenu("Light");
    m_cameraMenu = m_viewMenuBar->addMenu("Camera");
    m_envMenu = m_viewMenuBar->addMenu("Environment");
    _viewLayout->addWidget(m_viewMenuBar);

    if (!m_view)
        m_view = new Qt3DExtras::Qt3DWindow;
    m_view->defaultFrameGraph()->setClearColor(QColor(38, 38, 38));
    if (!m_viewContainer)
        m_viewContainer = QWidget::createWindowContainer(m_view);
    m_viewContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_viewContainer->setMinimumSize(QSize(200, 100));
    m_viewContainer->setMaximumSize(m_view->screen()->size());
    _viewLayout->addWidget(m_viewContainer);

    if (!m_root)
        m_root = new Qt3DCore::QEntity;
    if (!m_camera)
        m_camera = m_view->camera();
    // todo: this is testing around, taken from basic shapes example
    m_camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0, 0, 20.0f));
    m_camera->setUpVector(QVector3D(0, 1, 0));
    m_camera->setViewCenter(QVector3D(0, 0, 0));

    if (!m_cameraController)
        m_cameraController = new Qt3DExtras::QFirstPersonCameraController(m_root);
    m_cameraController->setCamera(m_camera);

    m_view->setRootEntity(m_root);

    this->setLayout(_viewLayout);
}

Q3dView::~Q3dView() {
}

void Q3dView::setInput() {
    //todo
}

} // namespace