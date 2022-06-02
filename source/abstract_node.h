// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QWidget>
#include <QObject>

#include <QPointer>

#include <QPushButton>

namespace mina {

class AbstractNodeWidget : public QWidget {
    Q_OBJECT
public:
    AbstractNodeWidget(QWidget *parent = nullptr);
    ~AbstractNodeWidget();

    void setButtonTitle(const QString &_title);

protected:
    QPushButton *m_mainBtn;
};

class AbstractNode : public QObject {
    Q_OBJECT
public:
    AbstractNode(QObject *parent = nullptr);
    virtual ~AbstractNode();

    virtual void main();

    virtual int nodeType();

    AbstractNodeWidget* graphWidget();

protected:
    QPointer<AbstractNodeWidget> m_graphWidget;

signals:
    void mainFinished();
    void readyForDisplay(AbstractNode *_node);

public slots:
    virtual void onMainFinished();
};

} // namespace