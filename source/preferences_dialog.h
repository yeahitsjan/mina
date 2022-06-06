// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include <QDialog>
#include <QObject>
#include <QWidget>

#include <QPointer>

#include <QVBoxLayout>
#include <QTabWidget>

#include <QPushButton>
#include <QCheckBox>

namespace mina {

class PreferencesDialog : public QDialog {
    Q_OBJECT
public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog();

    QPointer<QTabWidget> m_pagesTabWidget;
    QPointer<QWidget> m_pageNodeGraph;

protected:
    QVBoxLayout* createUi();
    QPointer<QVBoxLayout> m_dialogLayout;

    QPushButton *m_restoreBtn;

    QPushButton *m_okBtn;
    QPushButton *m_cancelBtn;

    // PageNodeGraph
    QCheckBox *m_ng_aaBox;
    QCheckBox *m_ng_glAccelBox;

private:
    QWidget* createTabNodeGraph();

signals:
    void graphReconfigured(bool _aa, bool _glAccel);

public slots:
    void on_okBtn_clicked();
};

} // namespace