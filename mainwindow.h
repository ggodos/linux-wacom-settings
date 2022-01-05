#include <QProcess>
#include <QLineEdit>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "areapreview.h"
#include "cliinteractor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onButtonClicked();
private:
    Ui::MainWindow *ui;
    AreaPreview *areaPreview;
    QList<int> takeTextsFromWidgets(QList<QLineEdit *> lines);
    CLIInteractor *cli = new CLIInteractor();
    void setArea(QList<int> values);
    int extractInteger(QLineEdit *line);
    void initModelName();
};
#endif // MAINWINDOW_H
