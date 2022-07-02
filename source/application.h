// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#pragma once

#include "easylogging++.h"
#include <QOpenGLContext>
#include <QOffscreenSurface>
#include <QOpenGLFunctions>

#include <QPointer>

#include <QStringList>

#include <QApplication>
#include <QObject>

#include <QFont>

#include "node_registry.h"

#define MINA_VERSION "0.0v0"
#define MINA_BDATE "01 June 2022"

struct SysGpuInfo {
    QString vendor;
    QString devName;
    QString openGlVer;
};

inline SysGpuInfo gpuInfo() {
    SysGpuInfo inf;

    QOpenGLContext ctx;
    ctx.create();
    QOffscreenSurface surf;
    surf.create();
    QOpenGLFunctions funcs;
    ctx.makeCurrent(&surf);
    funcs.initializeOpenGLFunctions();

    inf.vendor = QString::fromLatin1((const char*)funcs.glGetString(GL_VENDOR));
    inf.devName = QString::fromLatin1((const char*)funcs.glGetString(GL_RENDERER));
    inf.openGlVer = QString::fromLatin1((const char*)funcs.glGetString(GL_VERSION));
    LOG(INFO) << "GPU vendor: " << inf.vendor;
    LOG(INFO) << "GPU renderer: " << inf.devName;
    LOG(INFO) << "OpenGL version: " << inf.openGlVer;

    return inf;
}

class MinaApp : public QApplication {
    Q_OBJECT
public:
    MinaApp(int &argc, char **argv);
    ~MinaApp();

    // Run some checks over mina's home dir (~/.mina)
    void prepareHomeDirectory();

    // Forward call of NodeRegistry::nodesFromCategory.
    QStringList nodeEntriesForCategory(const QString &_category);

    QFont platformFont(int _pxSz);
    QString INIvalueFromKey(const QString &_part, const QString &_key);

    // Returns informations about the graphics device in the current session.
    SysGpuInfo currentGpuInfo();

    void ngConfigureAA(bool c);
    bool ngConfiguredAA();

    void ngConfigureGLAcceleration(bool c);
    bool ngConfiguredGLAcceleration();

protected:
    QPointer<mina::NodeRegistry> m_globalRegistry;
    SysGpuInfo m_gpuInfo;
    
    bool installApplicationFont();

private:
    bool m_fontInstalled = false;

    bool m_ngAA;
    bool m_ngGLAcceleration;

public slots:
    void indexNodes();

signals:
    void preparationDone();
};

extern MinaApp *MApp;
