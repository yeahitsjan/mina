// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "bitmap_bnode.h"

namespace mina {

BitmapBNode::BitmapBNode(QObject *parent) : AbstractNode(parent) {
}

BitmapBNode::~BitmapBNode() {
}

QImage* BitmapBNode::bitmap() {
    return m_bitmap;
}

bool BitmapBNode::loadFromPath(const QString &_path) {
    // todo
}

int BitmapBNode::nodeType() {
    // BNode - 1x
    // INode - 2x +x
    return 11; 
}

} // namespace