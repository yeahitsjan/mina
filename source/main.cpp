// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "application.h"
#include "easylogging++.h"

#include <QStyleFactory>
#include <QPalette>
#include <QColor>

#include <QFile>
#include <QTextStream>

#include "main_window.h"

MinaApp *MApp { nullptr };

using namespace mina;
INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    MinaApp mApp(argc, argv);
    mApp.setStyle(QStyleFactory::create("fusion"));

    QPalette p;
    // widgets
    p.setColor(QPalette::Window, QColor(41, 41, 41));
    p.setColor(QPalette::Base, QColor(41, 41, 41));
    p.setColor(QPalette::AlternateBase, QColor(41, 41, 41));
    p.setColor(QPalette::Button, QColor(41, 41, 41));
    // text
    p.setColor(QPalette::WindowText, QColor(198, 198, 198));
    p.setColor(QPalette::Text, QColor(198, 198, 198));
    p.setColor(QPalette::ButtonText, QColor(198, 198, 198));
    p.setColor(QPalette::Link, QColor(235, 135, 0));
    // ---
    p.setColor(QPalette::Highlight, QColor(230, 8, 70));
    mApp.setPalette(p);

    QString _stylesheet;
    QFile _stylesheetFile(":/resources/style/app.qss");
    if (_stylesheetFile.open( QIODevice::ReadOnly )) {
        QTextStream rd(&_stylesheetFile);
        _stylesheet = rd.readAll();
        _stylesheetFile.close();
    }
    mApp.setStyleSheet(_stylesheet);

    mApp.setFont(mApp.platformFont(12));

    //todo: splashscreen
    mApp.prepareHomeDirectory();

    MainWindow win;
    win.show();

    return mApp.exec();
}