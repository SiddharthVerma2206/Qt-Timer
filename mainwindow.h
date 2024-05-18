#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include <QTextStream>
#include <QIcon>
#include <QFont>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QTextBrowser>
#include <QVBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QMainWindow *window = new QMainWindow(); 
    QMainWindow *dataopwindow = new QMainWindow();
    ~MainWindow();


private slots:
    void on_btnstart_clicked();

    void on_btnreset_clicked();

    void on_toggleFloatingButton_clicked();

    void on_btnstore_clicked();

    void on_btnclrhis_clicked();

private:
    Ui::MainWindow *ui;

public:
    QLabel *label = new QLabel("00:00:00", window);
    QPushButton *button = new QPushButton(window);
    QPushButton *button2 = new QPushButton(window);
    QTextBrowser *filedisplay = new QTextBrowser(dataopwindow);
    void writetofile();
    void updateDisplay();
    void handleButtonClick();
    void handleButton2Click();
    void startnsavetimer();
    void stopnsavetimer();
    QTime starttime;
    QTime endtime;
    QTimer *timer;
    bool isRunning;
    QTime currentTime=QTime(0,0,0);
    QString displayTime;
    QTime startTime;
    QTime stopTime;
    int totalRunTime;  // in milliseconds
    int totalStopTime;
};
#endif // MAINWINDOW_H
