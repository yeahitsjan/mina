// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "application.h"

#include <QtGlobal>

#include <QIcon>
#include <QFontDatabase>

#include <QFileInfo>
#include <QFile>
#include <QTextStream>

#include <QStandardPaths>
#include <QDir>

MinaApp::MinaApp(int &argc, char **argv) : QApplication(argc, argv) {
    MApp = this;
    this->setWindowIcon(QIcon(":/resources/icons/app/logo_default_512px.png"));
    LOG(INFO) << "Mina version " << MINA_VERSION << " - build date: " << MINA_BDATE;
    LOG(INFO) << "Copyright (c) 2022 Jan Kowalewicz -  Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.";
    m_gpuInfo = gpuInfo();

    if (!m_globalRegistry)
        m_globalRegistry = new mina::NodeRegistry;
    connect(this, &MinaApp::preparationDone, this, &MinaApp::indexNodes);

    // TODO: force for now
    this->ngConfigureAA(false);
    this->ngConfigureGLAcceleration(false);

    m_fontInstalled = this->installApplicationFont();    
}

MinaApp::~MinaApp() {
}

void MinaApp::prepareHomeDirectory() {
    QString sdir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.mina/";
    QDir dir(sdir);
    if (!dir.exists()) {
        if (dir.mkpath("."))
            LOG(INFO) << "Prepare phase: Created [~/.mina]";
        //todo
    } else {
        LOG(INFO) << "Prepare phase: Found the main directory";
    }
    QDir customNodesDir(sdir + "cnode");
    if (!customNodesDir.exists()) {
        if (customNodesDir.mkpath("."))
            LOG(INFO) << "Prepare phase: Create [~/.mina/cnode]";
    } else {
        LOG(INFO) << "Prepare phase: Found custom nodes directory";
    }
    // The node registry is the most relevant part of the application. This is indeed
    // a double check because NodeRegistry's constructor also checks if the database is already
    // created and creates one if it doesn't exist.
    QFileInfo dbInf(sdir + "n.db");
    if (!dbInf.exists()) {
        LOG(DEBUG) << "Initialize nodes db";
        if (m_globalRegistry->initializeLocalDb()) {
            LOG(INFO) << "Prepare phase: Initialized new node registry";
            emit preparationDone();
        }
    } else {
        LOG(INFO) << "Prepare phase: Found node registry in [~/.mina/n.db]";
        emit preparationDone();
    }
}

QStringList MinaApp::nodeEntriesForCategory(const QString &_category) {
    if (m_globalRegistry)
        return m_globalRegistry->nodesFromCategory(_category);
}

QFont MinaApp::platformFont(int _pxSz) {
    QFont font;
    if (m_fontInstalled) {
        font.setFamily("Rubik");
    } else {
#if defined(Q_OS_WIN)
    font.setFamily("Tahoma");
#endif // todo
    }
    font.setPixelSize(_pxSz);
    return font;
}

QString MinaApp::INIvalueFromKey(const QString &_part, const QString &_key) {
    QString ini;
    QString qrc = ":/resources/texts/" + _part + ".ini";
    QFileInfo check(qrc);
    if (!check.exists())
        LOG(ERROR) << "Trying to load value from a file that does not exist in resources.";
    else
        ini = qrc;
    
    QFile fIni(ini);
    if (fIni.open( QIODevice::ReadOnly )) {
        QTextStream in(&fIni);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString k(_key + "=");
            int pos = line.indexOf(k);
            if (pos >= 0)
                return line.mid(pos + k.length());
        }
    }
    return ini;
}

SysGpuInfo MinaApp::currentGpuInfo() {
    return m_gpuInfo;
}

void MinaApp::ngConfigureAA(bool c) {
    m_ngAA = c;
}

bool MinaApp::ngConfiguredAA() {
    return m_ngAA;
}

void MinaApp::ngConfigureGLAcceleration(bool c) {
    m_ngGLAcceleration = c;
}

bool MinaApp::ngConfiguredGLAcceleration() {
    return m_ngGLAcceleration;
}

bool MinaApp::installApplicationFont() {
    int c;
    c = QFontDatabase::addApplicationFont(":/resources/font/Rubik-Regular.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/Rubik-Medium.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/Rubik-Bold.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/Rubik-SemiBold.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/Rubik-Light.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/Rubik-Italic.ttf");

    if (c == -1) {
        LOG(WARNING) << "Rubik was not added to the font database. Using fallback.";
        return false;
    }
    else {
        LOG(INFO) << "Rubik successfully added to font database.";
        return true;
    }
    return false;
}

void MinaApp::indexNodes() {
    // TODO: load search path from preferences
    if (m_globalRegistry) {
        m_globalRegistry->indexResourcePath();
        m_globalRegistry->indexSearchPath(m_globalRegistry->nodeSearchPath());
    }
}
