// Mina - Copyright (c) 2022 Jan Kowalewicz 
// Contact: <jan(dot)kowalewicz(at)web(dot)de>
// Licensed under GNU GPLv3. See LICENSE or visit <https://www.gnu.org/licenses/>.

#include "project.h"
#include "application.h"
#include "easylogging++.h"

#include <QThread>
#include <QDate>
#include <QTime>

#include <QCryptographicHash>

namespace mina {

Project::Project(QObject *parent) : QObject(parent) {
    // create a new project
    QThread::msleep(6); // more randomness; makes it theoretically impossible to be a duplicate?
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString combination = cd.toString() + "**" + ct.toString("hh:mm:ss.zzz");
    this->setProjectUniqueId( this->textToMd5(combination) );

    if (!m_projectNodeGraph)
        m_projectNodeGraph = new NodeGraphView;
    m_projectNodeGraph->setGlAcceleration(MApp->ngConfiguredGLAcceleration());
    m_projectNodeGraph->setAA(MApp->ngConfiguredAA());
}

Project::Project(const QString &_fromPath, QObject *parent) : m_mprFilePath(_fromPath), QObject(parent) {
    QFileInfo fi(m_mprFilePath);
    if (!fi.exists())
        LOG(ERROR) << "Could not check MPR from path " + m_mprFilePath;
    // TODO
    //read
    //initialize projectNodeGraph
}

Project::~Project() {
}

void Project::setProjectName(const QString &_projectName) {
    if (m_projectName.isEmpty())
        m_projectName = _projectName;
}

QString Project::projectName() {
    return m_projectName;
}

QString Project::projectUniqueId() {
    return m_projectUniqueId;
}

NodeGraphView* Project::nodeGraph() {
    return m_projectNodeGraph;
}

void Project::setProjectUniqueId(const QString &_id) {
    if (m_projectUniqueId.isEmpty())
        m_projectUniqueId = _id;
}

QString Project::textToMd5(const QString &_t) {
    QString hash = QString("%1").arg(QString(QCryptographicHash::hash(_t.toUtf8(), QCryptographicHash::Md5).toHex()));
    return hash;
}

} // namespace