// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include "../bnode/bitmap_bnode.h"
#include <QObject>

namespace mina {

class SolidColorINode : public BitmapBNode {
    Q_OBJECT
public:
    SolidColorINode(QObject *parent = nullptr);
    ~SolidColorINode();

    void main() override;
    
    int nodeType() override;
};

} // namespace