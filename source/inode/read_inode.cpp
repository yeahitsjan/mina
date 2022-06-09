// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "easylogging++.h"
#include "read_inode.h"

#include <QFileDialog>

namespace mina {

ReadINode::ReadINode(QObject *parent) : BitmapBNode(parent) {
}

ReadINode::~ReadINode() {
}

void ReadINode::main() {
    LOG(DEBUG) << "Read inode called";
    QString _sourceFilePath = QFileDialog::getOpenFileName(
        nullptr, /* is this even safe? */
        "Select source file",
        QDir::currentPath(),
        "All files (*.*) ;; Bitmap (*.bmp)"
    );
    if (!_sourceFilePath.isNull())
        this->loadFromSourceFile(_sourceFilePath);
    emit mainFinished();
}

int ReadINode::nodeType() {
    // BNode - 1x
    // INode - 2x +x
    return 21;
}

} // namespace