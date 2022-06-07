## Mina project file
QT += core gui 3dcore 3drender 3dinput 3dlogic 3dextras network multimedia opengl sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = mina
TEMPLATE = app

SOURCES += source/application.cpp \
            source/main.cpp \
            source/custom_tab_widget.cpp \
            source/main_window.cpp \
            source/preferences_dialog.cpp \
            source/node_graph.cpp \
            source/abstract_node.cpp \
            source/bnode/bitmap_bnode.cpp \
            source/inode/read_inode.cpp \
            source/project.cpp \
            source/project_manager.cpp

HEADERS += source/application.h \
            source/custom_tab_widget.h \
            source/main_window.h \
            source/preferences_dialog.h \
            source/node_graph.h \
            source/abstract_node.h \
            source/bnode/bitmap_bnode.h \
            source/inode/read_inode.h \
            source/project.h \
            source/project_manager.h

## Submodules
include(modules/phantomstyle/src/phantom/phantom.pri)
include(modules/easyloggingpp/easyloggingpp.pri)

RESOURCES += \
    resources.qrc