#ifndef SSRESULTMODEL_H
#define SSRESULTMODEL_H

#include <QStandardItemModel>

class ssResultModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum SS_CONNECTION_TYPE {SS_CONNECTION_ALL, SS_CONNECTION_TCP, SS_CONNECTION_UDP};
    enum SS_IP_VERSION {SS_IP_ALL, SS_IPV4, SS_IPV6};

    explicit ssResultModel(QObject *parent = 0);
    
    void update(SS_CONNECTION_TYPE socketType, SS_IP_VERSION ipVersion, const QStringList& ssStdOutResult);

private:
    short int getIpVersion(const QString& ipStr);
    void splitIpPort(const QString& ipPort, QString& ip, QString& port);
    void getProcessInfo(const QString& processStr, QString& process, int &pid);
signals:
    
public slots:
    
};

#endif // SSRESULTMODEL_H
