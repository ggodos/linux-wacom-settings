#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    areaPreview = new AreaPreview;
    ui->drawingArea->addWidget(areaPreview);

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
    areaPreview->changeArea(values[0], values[1], values[2], values[3]);
}

void MainWindow::showEvent(QShowEvent *event)
{
    loadCurrentArea();
}

void MainWindow::setArea(QList<int> values)
{
    QString newArea = "";
    for (int i = 0; i < values.length() - 1; i++) {
        newArea += QString::number(values[i]) + " ";
    }
    newArea += QString::number(values.last());

    cli->setField("Area", newArea);
}

QList<int> MainWindow::takeTextsFromWidgets(QList<QLineEdit *> lines)
{
    QList<int> values;
    for (auto line : lines) {
        values.append(extractInteger(line));
    }
    return values;
}

int MainWindow::extractInteger(QLineEdit *line)
{
    return line->text().toInt();
}

void MainWindow::initModelName()
{
    ui->modelName->setText(cli->modelName);
}

void MainWindow::loadCurrentArea()
{
    QStringList currentArea = cli->getField("Area").split(" ");
    QList<int> areaValues(4);
    for (int i = 0; i < currentArea.length(); i++) {
        areaValues[i] = currentArea[i].toInt();
    }
    setWidgets(areaValues);
    areaPreview->changeArea(areaValues[0], areaValues[1], areaValues[2], areaValues[3]);
}

void MainWindow::setWidgets(QList<int> values)
{
    ui->line1_3->setText(QString::number(values[0]));
    ui->line2_3->setText(QString::number(values[1]));
    ui->line3->setText(QString::number(values[2]));
    ui->line4->setText(QString::number(values[3]));
}
