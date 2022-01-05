#ifndef CLIINTERACTOR_H
#define CLIINTERACTOR_H

#include <qstring.h>
#include <qiodevice.h>
#include "qdebug.h"


class CLIInteractor
{
public:
    QString modelName = "";
    QString command = "xsetwacom";
    QString commandModelName = "";

    CLIInteractor();
    void initModelName();
    QString getField(QString field);
    void setField(QString field, QString newValue);
    void makeCommandModelName();
private:
    QString executeCommand(QStringList args, QIODevice::OpenMode mode);
    QStringList findDevices();
    QString parseModelName(QString device);
};

#endif // CLIINTERACTOR_H
