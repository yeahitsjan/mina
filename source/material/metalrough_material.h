// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include "../abstract_material.h"
#include <QObject>

#include <Qt3DRender>
#include <Qt3DExtras>

namespace mina {

class MetalRoughMaterial : public AbstractMaterial {
    Q_OBJECT
public:
    explicit MetalRoughMaterial(QObject *parent = nullptr);
    virtual ~MetalRoughMaterial();

    Qt3DRender::QMaterial* material() override;
protected:
    QPointer<Qt3DExtras::QMetalRoughMaterial> m_metalRoughMaterial;

public slots:
    void onDataChange(int _nodeType, QVariant _data);
};

} // namespace