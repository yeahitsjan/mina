// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "easylogging++.h"
#include "abstract_material.h"

namespace mina {

AbstractMaterial::AbstractMaterial(QObject *parent) : QObject(parent) {
    if (!m_material)
        m_material = new Qt3DRender::QMaterial;
}

AbstractMaterial::~AbstractMaterial() {
}

Qt3DRender::QMaterial* AbstractMaterial::material() {
    return m_material;
}

QList<MaterialBNode*> AbstractMaterial::nodesForMaterial() {
    return m_lNodesForMaterial;
}

void AbstractMaterial::addNodeToMaterial(MaterialBNode *_node) {
    m_lNodesForMaterial.append(_node);
    connect(_node, &MaterialBNode::dataChanged, this, &AbstractMaterial::onDataChange);
}

void AbstractMaterial::onDataChange(int _nodeType, QVariant _data) {
    // Each material should reimplement this slot, so the material is filled with the right properties.
}

} // namespace