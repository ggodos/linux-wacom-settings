#include <QProcess>
#include <QLineEdit>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    int extractInteger(QLineEdit *line);
    void setArea(QList<int> values);
    QList<int> takeTextsFromWidgets(QList<QLineEdit *> lines);
    QStringList findDevices();
    void initModelName();
    QString parseModelName(QString device);
};
#endif // MAINWINDOW_H
