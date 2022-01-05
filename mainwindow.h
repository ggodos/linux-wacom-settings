#include <QProcess>
#include <QLineEdit>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "areapreview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString modelName = "";

public slots:
    void onButtonClicked();
private:
    Ui::MainWindow *ui;
    AreaPreview *areaPreview;
    QList<int> takeTextsFromWidgets(QList<QLineEdit *> lines);
    QStringList findDevices();
    QString parseModelName(QString device);
    void initModelName();
    void setArea(QList<int> values);
    int extractInteger(QLineEdit *line);
};
#endif // MAINWINDOW_H
