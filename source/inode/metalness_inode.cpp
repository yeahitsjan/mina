// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "metalness_inode.h"

namespace mina {

MetalnessINode::MetalnessINode(QObject *parent) : MaterialBNode(parent) {
}

MetalnessINode::~MetalnessINode() {
}

void MetalnessINode::main() {
    // Normally we just would wait for input; TODO: default value?
    emit dataChanged(this->nodeType(), m_vProperty); // testing
}

int MetalnessINode::nodeType() {
    return 903;
}

} // namespace