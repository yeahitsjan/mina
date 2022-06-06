// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "application.h"

#include <QtGlobal>

#include <QFontDatabase>

#include <QFileInfo>
#include <QFile>
#include <QTextStream>

MinaApp::MinaApp(int &argc, char **argv) : QApplication(argc, argv) {
    MApp = this;
    LOG(INFO) << "Mina version " << MINA_VERSION << " - build date: " << MINA_BDATE;
    LOG(INFO) << "Copyright (c) 2022 Jan Kowalewicz -  Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.";
    m_gpuInfo = gpuInfo();

    m_fontInstalled = this->installApplicationFont();    
}

MinaApp::~MinaApp() {
}

QFont MinaApp::platformFont(int _pxSz) {
    QFont font;
    if (m_fontInstalled) {
        font.setFamily("Open Sans");
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
    c = QFontDatabase::addApplicationFont(":/resources/font/OpenSans-Regular.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/OpenSans-Medium.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/OpenSans-Bold.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/OpenSans-SemiBold.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/OpenSans-Light.ttf");
    c = QFontDatabase::addApplicationFont(":/resources/font/OpenSans-Italic.ttf");

    if (c == -1) {
        LOG(WARNING) << "OpenSans was not added to the font database. Using fallback.";
        return false;
    }
    else {
        LOG(INFO) << "OpenSans successfully added to font database.";
        return true;
    }
    return false;
}