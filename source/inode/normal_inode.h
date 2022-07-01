// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "../bnode/material_bnode.h"
#include <QObject>

namespace mina {

class NormalINode : public MaterialBNode {
    Q_OBJECT
public:
    NormalINode(QObject *parent = nullptr);
    ~NormalINode();

    void main() override;

    int nodeType() override;
};

} // namespace