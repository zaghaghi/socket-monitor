#ifndef SSWRAPER_H
#define SSWRAPER_H
#include <QStringList>

class ssWraper
{
public:
    ssWraper();
    QStringList execute();

protected:
    QStringList execute(QStringList Options);
};

#endif // SSWRAPER_H
