// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "easylogging++.h"
#include "solidcolor_inode.h"

#include <QColorDialog>

namespace mina {

SolidColorINode::SolidColorINode(QObject *parent) : BitmapBNode(parent) {
}

SolidColorINode::~SolidColorINode() {
}

void SolidColorINode::main() {
    LOG(DEBUG) << "SolidColor inode called";
    QColor _color = QColorDialog::getColor(Qt::white, nullptr /* safe? */, "Select color", QColorDialog::DontUseNativeDialog);
    if (_color.isValid()) {
        //todo: create bitmap
    }
    emit mainFinished();
}

int SolidColorINode::nodeType() {
    return 22;
}

} // namespace