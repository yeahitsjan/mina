// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "material_bnode.h"

namespace mina {

MaterialBNode::MaterialBNode(QObject *parent) : AbstractNode(parent) {
}

MaterialBNode::~MaterialBNode() {
}

QVariant MaterialBNode::vProperty() {
    return m_vProperty;
}

int MaterialBNode::nodeType() {
    return 10;
}

} // namespace