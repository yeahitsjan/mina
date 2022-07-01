// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "easylogging++.h"
#include "metalrough_material.h"

namespace mina {

MetalRoughMaterial::MetalRoughMaterial(QObject *parent) : AbstractMaterial(parent) {
    if (!m_metalRoughMaterial)
        m_metalRoughMaterial = new Qt3DExtras::QMetalRoughMaterial;
}

MetalRoughMaterial::~MetalRoughMaterial() {
}

Qt3DRender::QMaterial* MetalRoughMaterial::material() {
    return m_metalRoughMaterial;
}

void MetalRoughMaterial::onDataChange(int _nodeType, QVariant _data) {
    //todo
    LOG(DEBUG) << "Material: Data change registered";
}

} // namespace