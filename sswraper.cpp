#include "sswraper.h"
#include <QProcess>

#include <QDebug>

ssWraper::ssWraper()
{
}

QStringList ssWraper::execute(QStringList options)
{
    QProcess ss;
    ss.start("ss", options);
    if (!ss.waitForStarted()) {
        return QStringList();
    }

    if (!ss.waitForFinished()) {
        return QStringList();
    }

    QByteArray result = ss.readAllStandardOutput();
    return QString(result).split("\n");
}

QStringList ssWraper::execute()
{
    QString options = "-apnut";
    return execute(QStringList() << options);
}
