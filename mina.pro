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
            source/abstract_material.cpp \
            source/material/metalrough_material.cpp \
            source/abstract_node.cpp \
            source/node_registry.cpp \
            source/bnode/material_bnode.cpp \
            source/bnode/bitmap_bnode.cpp \
            source/inode/read_inode.cpp \
            source/inode/solidcolor_inode.cpp \
            source/inode/normal_inode.cpp \
            source/inode/ao_inode.cpp \
            source/inode/metalness_inode.cpp \
            source/inode/roughness_inode.cpp \
            source/inode/basecolor_inode.cpp \
            source/project.cpp \
            source/project_manager.cpp \
            source/view/3d_view.cpp \
            source/view/2d_view.cpp \
            source/view/explorer_view.cpp \
            source/view/library_view.cpp

HEADERS += source/application.h \
            source/custom_tab_widget.h \
            source/main_window.h \
            source/preferences_dialog.h \
            source/node_graph.h \
            source/abstract_material.h \
            source/material/metalrough_material.h \
            source/abstract_node.h \
            source/node_registry.h \
            source/bnode/material_bnode.h \
            source/bnode/bitmap_bnode.h \
            source/inode/read_inode.h \
            source/inode/solidcolor_inode.h \
            source/inode/normal_inode.h \
            source/inode/ao_inode.h \
            source/inode/metalness_inode.h \
            source/inode/roughness_inode.h \
            source/inode/basecolor_inode.h \
            source/project.h \
            source/project_manager.h \
            source/view/3d_view.h \
            source/view/2d_view.h \
            source/view/explorer_view.h \
            source/view/library_view.h

## Submodules
include(modules/easyloggingpp/easyloggingpp.pri)
include(modules/QSimpleUpdater/QSimpleUpdater.pri)

RESOURCES += \
    resources.qrc