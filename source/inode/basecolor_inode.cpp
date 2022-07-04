// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "basecolor_inode.h"

namespace mina {

BaseColorINode::BaseColorINode(QObject *parent) : MaterialBNode(parent) {
}

BaseColorINode::~BaseColorINode() {
}

void BaseColorINode::main() {
    // Normally we just would wait for input; TODO: default value?
    emit dataChanged(this->nodeType(), m_vProperty); // testing
}

int BaseColorINode::nodeType() {
    return 905;
}

} // namespace