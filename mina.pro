## Mina project file
QT += core gui 3dcore 3drender 3dinput 3dlogic 3dextras network multimedia opengl sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = mina
TEMPLATE = app

SOURCES += source/application.cpp \
            source/main.cpp \
            source/main_window.cpp \
            source/node_graph.cpp \
            source/abstract_node.cpp \
            source/bnode/bitmap_bnode.cpp \
            source/inode/read_inode.cpp

HEADERS += source/application.h \
            source/main_window.h \
            source/node_graph.h \
            source/abstract_node.h \
            source/bnode/bitmap_bnode.h \
            source/inode/read_inode.h

## Submodules
include(modules/phantomstyle/src/phantom/phantom.pri)
include(modules/easyloggingpp/easyloggingpp.pri)