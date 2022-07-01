// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QObject>
#include <QPointer>
#include <QList>

#include <Qt3DRender>

#include "bnode/material_bnode.h"

namespace mina {

class AbstractMaterial : public QObject {
    Q_OBJECT
public:
    AbstractMaterial(QObject *parent = nullptr);
    virtual ~AbstractMaterial();

    virtual Qt3DRender::QMaterial* material();

    // Returns all nodes needed to fullfill this material.
    QList<MaterialBNode*> nodesForMaterial();

    // Add a node to the material. 
    void addNodeToMaterial(MaterialBNode *_node);

protected:
    QList<MaterialBNode*> m_lNodesForMaterial;
    QPointer<Qt3DRender::QMaterial> m_material;

public slots:
    virtual void onDataChange(int _nodeType, QVariant _data);
};

} // namespace