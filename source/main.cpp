// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "application.h"
#include "easylogging++.h"

#include "phantomstyle.h"
#include <QStyle>
#include <QPalette>
#include <QColor>

#include "main_window.h"

MinaApp *MApp { nullptr };

using namespace mina;
INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    MinaApp mApp(argc, argv);
    mApp.setStyle(new PhantomStyle);

    QPalette p;
    // widgets
    p.setColor(QPalette::Window, QColor(50, 50, 50));
    p.setColor(QPalette::Base, QColor(50, 50, 50));
    p.setColor(QPalette::AlternateBase, QColor(50, 50, 50));
    p.setColor(QPalette::Button, QColor(50, 50, 50));
    // text
    p.setColor(QPalette::WindowText, QColor(198, 198, 198));
    p.setColor(QPalette::Text, QColor(198, 198, 198));
    p.setColor(QPalette::ButtonText, QColor(198, 198, 198));
    p.setColor(QPalette::Link, QColor(235, 135, 0));
    // ---
    p.setColor(QPalette::Highlight, QColor(20, 135, 0));
    mApp.setPalette(p);

    mApp.setFont(mApp.platformFont(11));

    MainWindow win;
    win.show();

    return mApp.exec();
}