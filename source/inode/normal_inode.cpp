// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "normal_inode.h"

namespace mina {

NormalINode::NormalINode(QObject *parent) : MaterialBNode(parent) {
}

NormalINode::~NormalINode() {
}

void NormalINode::main() {
    // Normally we just would wait for input; TODO: default value?
    emit dataChanged(this->nodeType(), m_vProperty); // testing
}

int NormalINode::nodeType() {
    // Material fixed node types have a different number.
    // BNode - 1x
    // INode - 2x +x
    // Material:INode - 9xx
    return 901;
}

} // namespace