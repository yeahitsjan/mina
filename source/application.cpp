// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "application.h"

#include <QtGlobal>

#include <QFontDatabase>

MinaApp::MinaApp(int &argc, char **argv) : QApplication(argc, argv) {
    MApp = this;
    LOG(INFO) << "Mina version " << MINA_VERSION << " - build date: " << MINA_BDATE;
    LOG(INFO) << "Copyright (c) 2022 Jan Kowalewicz -  Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.";
    m_gpuInfo = gpuInfo();

    fontInstalled = this->installApplicationFont();    
}

MinaApp::~MinaApp() {
}

QFont MinaApp::platformFont(int pxSz) {
    QFont font;
    if (fontInstalled) {
        font.setFamily("Open Sans");
    } else {
#if defined(Q_OS_WIN)
    font.setFamily("Tahoma");
#endif // todo
    }
    font.setPixelSize(pxSz);
    return font;
}

SysGpuInfo MinaApp::currentGpuInfo() {
    return m_gpuInfo;
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