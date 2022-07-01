// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "../abstract_node.h"
#include <QObject>

#include <QVariant>

namespace mina {

class MaterialBNode : public AbstractNode {
    Q_OBJECT
public:
    MaterialBNode(QObject *parent = nullptr);
    virtual ~MaterialBNode();

    QVariant vProperty();

    int nodeType() override;

protected:
    QVariant m_vProperty;
};

} // namespace