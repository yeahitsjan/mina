// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include "../abstract_node.h"
#include <QObject>

#include <QImage>

namespace mina {

class BitmapBNode : public AbstractNode {
    Q_OBJECT
public:
    BitmapBNode(QObject *parent = nullptr);
    virtual ~BitmapBNode();

    QImage* bitmap();

    // Load bitmap from path.
    bool loadFromSourceFile(const QString &_path);
    QString sourceFile();

    // todo: load from data (probably input from another node)

    int nodeType() override;

protected:
    QString m_sourceFile;
    QImage *m_bitmap;
};

} // namespace