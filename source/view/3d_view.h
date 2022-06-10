// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QWidget>
#include <QObject>

#include <QPointer>

#include <QMenuBar>
#include <QMenu>

#include <Qt3DRender>
#include <Qt3DCore>
#include <Qt3DExtras>

namespace mina {

class Q3dView : public QWidget {
    Q_OBJECT
public:
    explicit Q3dView(QWidget *parent = nullptr);
    ~Q3dView();

    // Set the input (material) to be applied to the 3d object in view.
    void setInput(/*GeneratedMaterial*/);

protected:
    QPointer<QMenuBar> m_viewMenuBar;
    QMenu *m_sceneMenu;
    QMenu *m_lightMenu;
    QMenu *m_cameraMenu;
    QMenu *m_envMenu;

    QPointer<Qt3DExtras::Qt3DWindow> m_view;
    QPointer<QWidget> m_viewContainer;

    QPointer<Qt3DCore::QEntity> m_root;
    QPointer<Qt3DRender::QCamera> m_camera;
    QPointer<Qt3DExtras::QFirstPersonCameraController> m_cameraController;
};

} // namespace