// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "easylogging++.h"
#include "read_inode.h"

namespace mina {

ReadINode::ReadINode(QObject *parent) : BitmapBNode(parent) {
}

ReadINode::~ReadINode() {
}

void ReadINode::main() {
    // todo
    // call loadFromPath by using a QFileDialog
    LOG(INFO) << "Read inode called";
    emit mainFinished();
}

int ReadINode::nodeType() {
    // BNode - 1x
    // INode - 2x +x
    return 21;
}

} // namespace