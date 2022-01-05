#include "cliinteractor.h"
#include <QProcess>

CLIInteractor::CLIInteractor()
{
    initModelName();
}

QString CLIInteractor::getField(QString field)
{
    QStringList args = QStringList() << "--get" << commandModelName << field;
    return executeCommand(args, QIODevice::ReadOnly);
}

void CLIInteractor::setField(QString field, QString newValue)
{
    QStringList args = QStringList() << "--set" << commandModelName << " " << field << " " << newValue;
    QString setCommand = command + " --set " + commandModelName + " " + field + " " + newValue;
    system((const char *)(setCommand.toUtf8()));
    //executeCommand(args, QIODevice::ReadOnly);
}

void CLIInteractor::makeCommandModelName()
{
    commandModelName = "\"" + modelName + " Pen stylus\"";
}

void CLIInteractor::initModelName()
{
    QStringList devices = findDevices();
    for (const QString &device : devices) {
        if (device.contains("type: STYLUS")) {
            modelName = parseModelName(device);
            makeCommandModelName();
            break;
        }
    }
}

QStringList CLIInteractor::findDevices()
{
    QStringList args = QStringList() << "--list" << "devices";
    QString out = executeCommand(args, QIODevice::ReadOnly);
    QStringList result = out.split("\n");
    return result;
}

QString CLIInteractor::parseModelName(QString device)
{
    QString result;
    QStringList words = device.split(' ');
    for (const QString &word : words) {
        if (word == "Pen") {
            result = result.left(result.length()-1);
            break;
        }
        result += word + " ";
    }
    return result;
}

QString CLIInteractor::executeCommand(QStringList args, QIODeviceBase::OpenMode mode)
{
    QProcess process;
    process.start(command,args,mode);
    process.waitForFinished();
    QString out = process.readAllStandardOutput();
    process.terminate();
    return out;
}
