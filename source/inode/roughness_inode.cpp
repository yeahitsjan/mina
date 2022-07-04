// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "roughness_inode.h"

namespace mina {

RoughnessINode::RoughnessINode(QObject *parent) : MaterialBNode(parent) {
}

RoughnessINode::~RoughnessINode() {
}

void RoughnessINode::main() {
    // Normally we just would wait for input; TODO: default value?
    emit dataChanged(this->nodeType(), m_vProperty); // testing
}

int RoughnessINode::nodeType() {
    return 904;
}

} // namespace