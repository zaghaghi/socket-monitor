#include "ssresultmodel.h"
#include <QVariant>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

ssResultModel::ssResultModel(QObject *parent) :
    QStandardItemModel(parent)
{
}

void ssResultModel::update(SS_CONNECTION_TYPE socketType, SS_IP_VERSION ipVersion, const QStringList& ssStdOutResult)
{
    QStringList result = ssStdOutResult;
    result.removeFirst();
    //clear();
    int index = 0;
    int rowCount = this->rowCount();
    foreach(QString line, result) {
        QStringList sections = line.split(" ", QString::SkipEmptyParts);
        if ((sections.length() < 6) ||
            (sections[0] == "udp" && socketType == SS_CONNECTION_TCP) ||
            (sections[0] == "tcp" && socketType == SS_CONNECTION_UDP)) {
            continue;
        }
        QString state = sections[1];
        QString srcIp, srcPort;
        splitIpPort(sections[4], srcIp, srcPort);
        QString dstIp, dstPort;
        splitIpPort(sections[5], dstIp, dstPort);
        if ((getIpVersion(srcIp) == 4 && ipVersion == SS_IPV6) ||
            (getIpVersion(srcIp) == 6 && ipVersion == SS_IPV4) ||
            (getIpVersion(dstIp) == 4 && ipVersion == SS_IPV6) ||
            (getIpVersion(dstIp) == 6 && ipVersion == SS_IPV4)) {
            continue;
        }
        QString process;
        int pid = 0;
        if (sections.length() > 6) {
            getProcessInfo(sections[6], process, pid);
        }
        QList<QStandardItem*> row;
        row << new QStandardItem(sections[0])
            << new QStandardItem(state)
            << new QStandardItem(srcIp)
            << new QStandardItem(srcPort)
            << new QStandardItem(dstIp)
            << new QStandardItem(dstPort)
            << new QStandardItem(process);
        row.last()->setData(QVariant((int)pid));
        if (index < rowCount) {
            int rowLen = row.length();
            for (int i = 0; i < rowLen; i++) {
                this->setItem(index, i, row[i]);
            }
        }
        else {
            appendRow(row);
        }

        index++;
    }
    setRowCount(index);
    QStringList labels;
    labels << "Type" << "State" << "Src IP" << "Src Port" << "Dst IP" << "Dst Port" << "Process";
    setHorizontalHeaderLabels(labels);
}

short int ssResultModel::getIpVersion(const QString& ipStr)
{
    if (ipStr.contains(':')) {
        return 6;
    }
    return 4;
}

void ssResultModel::splitIpPort(const QString& ipPort, QString& ip, QString& port)
{
    QStringList splits = ipPort.split(':');
    port = QString(splits.last());
    splits.removeLast();
    ip = splits.join(':');
}

void ssResultModel::getProcessInfo(const QString& processStr, QString& process, int & pid)
{
    QRegularExpression re("users\\:\\(\\(\"(\\w*?)\"\\,(\\d+)\\,\\d+\\)\\)", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = re.match(processStr);
    if (match.hasMatch()) {
        process = match.captured(1);
        pid = match.captured(2).toInt();
    }
}
