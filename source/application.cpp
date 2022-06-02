// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "application.h"

#include <QtGlobal>

MinaApp::MinaApp(int &argc, char **argv) : QApplication(argc, argv) {
    MApp = this;
    LOG(INFO) << "Mina version " << MINA_VERSION << " - build date: " << MINA_BDATE;
    LOG(INFO) << "Copyright (c) 2022 Jan Kowalewicz -  Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.";
    m_gpuInfo = gpuInfo();
}

MinaApp::~MinaApp() {
}

QFont MinaApp::platformFont(int pxSz) {
    QFont font;
#if defined(Q_OS_WIN)
    font.setFamily("Tahoma");
    font.setPixelSize(pxSz);
#endif // todo
    return font;
}

SysGpuInfo MinaApp::currentGpuInfo() {
    return m_gpuInfo;
}