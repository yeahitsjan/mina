// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "preferences_dialog.h"

#include "application.h"

#include <QHBoxLayout>
#include <QLabel>

namespace mina {

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("Preferences");
    this->resize(QSize(960, 720)); // always the initial size
    this->setMinimumSize(QSize(640, 480));
    this->setLayout( this->createUi() );
}

PreferencesDialog::~PreferencesDialog() {
}

QVBoxLayout* PreferencesDialog::createUi() {
    if (!m_dialogLayout)
        m_dialogLayout = new QVBoxLayout;
    m_dialogLayout->setSpacing(2);
    m_dialogLayout->setMargin(4);
    
    if (!m_pagesTabWidget)
        m_pagesTabWidget = new QTabWidget;
    m_pagesTabWidget->setMovable(false);
    m_pagesTabWidget->setTabsClosable(false);

    m_dialogLayout->addWidget(m_pagesTabWidget);

    // add pages to tab widget
    m_pagesTabWidget->addTab(this->createTabNodeGraph(), "Node Graph");

    QHBoxLayout *_btnLayout = new QHBoxLayout;
    _btnLayout->setSpacing(2);
    _btnLayout->setMargin(2);

    m_restoreBtn = new QPushButton("Restore Defaults", this);
    
    QWidget *_spacer = new QWidget;
    _spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_okBtn = new QPushButton("OK", this);
    m_cancelBtn = new QPushButton("Cancel", this);

    _btnLayout->addWidget(m_restoreBtn);
    _btnLayout->addWidget(_spacer);
    _btnLayout->addWidget(m_okBtn);
    _btnLayout->addWidget(m_cancelBtn);
    m_dialogLayout->addLayout(_btnLayout);

    return m_dialogLayout;
}

QWidget* PreferencesDialog::createTabNodeGraph() {
    if (!m_pageNodeGraph)
        m_pageNodeGraph = new QWidget;
    
    QVBoxLayout *_pageLayout = new QVBoxLayout;
    _pageLayout->setSpacing(4);
    _pageLayout->setMargin(16);

    QLabel *_aaDescrLbl = new QLabel(MApp->INIvalueFromKey("preferences_dlg", "ng_configure_aa"), m_pageNodeGraph);
    _aaDescrLbl->setWordWrap(true);
    m_ng_aaBox = new QCheckBox("Enable AA", m_pageNodeGraph);
    _pageLayout->addWidget(_aaDescrLbl);
    _pageLayout->addWidget(m_ng_aaBox);
    {
        m_ng_aaBox->setChecked(MApp->ngConfiguredAA());
    }

    QLabel *_glDescrLbl = new QLabel(MApp->INIvalueFromKey("preferences_dlg", "ng_configure_gl"), m_pageNodeGraph);
    _glDescrLbl->setWordWrap(true);
    m_ng_glAccelBox = new QCheckBox("Enable GL acceleration", m_pageNodeGraph);
    _pageLayout->addWidget(_glDescrLbl);
    _pageLayout->addWidget(m_ng_glAccelBox);
    {
        m_ng_glAccelBox->setChecked(MApp->ngConfiguredGLAcceleration());
    }

    QWidget *_endSpacer = new QWidget;
    _endSpacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    _pageLayout->addWidget(_endSpacer);

    m_pageNodeGraph->setLayout(_pageLayout);
    return m_pageNodeGraph;
}

void PreferencesDialog::on_okBtn_clicked() {
    emit graphReconfigured(m_ng_aaBox->isChecked(), m_ng_glAccelBox->isChecked());
    this->close();
}

} // namespace