#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "areapreview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initModelName();
    connect(ui->setButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    setWindowTitle(tr("Wacom settings"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked()
{
    QList<QLineEdit *> lines = { ui->line1_3, ui->line2_3, ui->line3, ui->line4 };
    QList<int> values = takeTextsFromWidgets(lines);
    setArea(values);
}

int MainWindow::extractInteger(QLineEdit *line)
{
    return line->text().toInt();
}

void MainWindow::setArea(QList<int> values)
{
    const QString &modelName = this->modelName;
    QString command = "xsetwacom --set \"" + modelName + " Pen stylus\" Area ";
    for (int item : values) {
        command += QString::number(item) + " ";
    }
    const char *exCommand = command.toLocal8Bit().data();
    qDebug() << command;
    system(exCommand);
}

QList<int> MainWindow::takeTextsFromWidgets(QList<QLineEdit *> lines)
{
    QList<int> values;
    for (auto line : lines) {
        values.append(extractInteger(line));
    }
    return values;
}

QStringList MainWindow::findDevices()
{
    QString programm = "xsetwacom";
    QStringList args = QStringList() << "--list" << "devices";
    QIODevice::OpenMode mode = QIODevice::ReadOnly;
    QProcess process;
    process.start(programm,args,mode);
    process.waitForFinished();
    QString out = process.readAllStandardOutput();
    QStringList result = out.split("\n");
    process.terminate();
    return result;
}

void MainWindow::initModelName()
{
    QStringList devices = findDevices();
    QString modelName;
    for (const QString &device : devices) {
        if (device.contains("type: STYLUS")) {
            this->modelName = parseModelName(device);
            ui->modelName->setText(this->modelName);
            break;
        }
    }
}

QString MainWindow::parseModelName(QString device)
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

