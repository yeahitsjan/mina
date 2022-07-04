// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "ao_inode.h"

namespace mina {

AoINode::AoINode(QObject *parent) : MaterialBNode(parent) {
}

AoINode::~AoINode() {
}

void AoINode::main() {
    // Normally we just would wait for input; TODO: default value?
    emit dataChanged(this->nodeType(), m_vProperty); // testing
}

int AoINode::nodeType() {
    return 902;
}

} // namespace