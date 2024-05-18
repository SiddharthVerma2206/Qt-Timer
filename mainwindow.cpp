#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      timer(new QTimer(this)),
      isRunning(false),
      totalRunTime(0),
      totalStopTime(0)
{
    QFile file("mydata.txt");
    ui->setupUi(this);
    startTime=QTime::currentTime();
    connect(timer , &QTimer::timeout ,this , &MainWindow::updateDisplay);
    connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(button2, &QPushButton::clicked, this, &MainWindow::handleButton2Click);
    QFont font("Bahnschrift Light" , 11);
    label->setFont(font);
    label->setGeometry(0, 0, 70, 22);
    button->setGeometry(70, 0, 30, 22);
    button2->setGeometry(100, 0, 30, 22);
    button2->setIcon(QIcon(":/icons/maximize.png"));
    window->move(1100, 0);
    window->resize(130, 22);
    window->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->btnclrhis->hide();
    QVBoxLayout *layout = new QVBoxLayout();
    filedisplay->setLayout(layout);
    dataopwindow->setCentralWidget(filedisplay);
}

MainWindow::~MainWindow()
{
    endtime=QTime::currentTime();
    if(totalRunTime!=0){
     writetofile();
    }
    delete label;
    delete button;
    delete button2;
    delete window;
    delete filedisplay;
    delete dataopwindow;
     delete ui;
}

void MainWindow :: writetofile(){
    QString startstring = startTime.toString("hh:mm:ss");
    QString endstring = endtime.toString("hh:mm:ss");
    QString dateString = QDate::currentDate().toString("dd MMM yy");
    QTime runTime(0, 0);
    runTime = runTime.addSecs(totalRunTime);
    QString runTimeString = runTime.toString("hh:mm:ss");
    QTime stopTime(0, 0);
    stopTime = stopTime.addSecs(totalStopTime);
    QString stopTimeString = stopTime.toString("hh:mm:ss");
    QString line , updatedContent;
    bool datefound=false;
    QFile file("mydata.txt");
    QTextStream reading(&file);
    if(!file.open(QIODevice::ReadWrite)){
        qCritical()<<file.errorString();
    }
    while (!reading.atEnd()) {
            line = reading.readLine();
            if (line.startsWith(dateString)) {
            updatedContent.append("----------------------------------\nLogin:-" + startstring+"\nTotal Time: " + runTimeString + "\nBreak Time: " + stopTimeString + "\nLogout:-" + endstring + "\n");
                datefound=true;
                break;
            }
    }
    if(!datefound){
        updatedContent.append("**********************\n" + dateString + ":-\n---------------------------------\nLogin:-"+startstring + "\nTotal Time: " + runTimeString + "\nBreak Time: " + stopTimeString +"\nLogout:-"+ endstring + "\n");
    }
    reading<<updatedContent;
    file.close();
}


void MainWindow :: updateDisplay(){
    currentTime=currentTime.addSecs(1);
    displayTime = currentTime.toString("hh:mm:ss");
    ui->labeltimer->setText(displayTime);
    label->setText(displayTime);
}


void MainWindow :: startnsavetimer(){
    startTime = QTime::currentTime();
           // if (!stopTime.isNull()) {
                int stopDuration = stopTime.secsTo(QTime::currentTime());
                totalStopTime += stopDuration;
            //}
    timer->start(1000);
    isRunning=true;
}

void MainWindow :: stopnsavetimer(){
    QTime now = QTime::currentTime();
    int runDuration = startTime.secsTo(now);
    totalRunTime += runDuration;
    stopTime = now;
    timer->stop();
    isRunning=false;

}


void MainWindow::on_btnstart_clicked()
{
    if(!isRunning){
        startnsavetimer();
        ui->btnstart->setIcon(QIcon(":/icons/pause.png"));
    }else{
        stopnsavetimer();
        ui->btnstart->setIcon(QIcon(":/icons/play.png"));
    }
}


void MainWindow::on_btnreset_clicked()
{
    timer->stop();
    isRunning=false;
    currentTime=QTime(0,0,0);
    ui->labeltimer->setText("00:00:00");
    label->setText("00:00:00");
    totalRunTime=0;
    totalStopTime=0;
    ui->btnstart->setIcon(QIcon(":/icons/play.png"));

}

void MainWindow::on_toggleFloatingButton_clicked() {
        setWindowState(Qt::WindowMinimized);
        if(isRunning){
            button->setIcon(QIcon(":/icons/pause.png"));
        }else{
            button->setIcon(QIcon(":/icons/play.png"));
        }
        window->show();
}

void MainWindow :: handleButtonClick(){
    if(!isRunning){
        startnsavetimer();
        button->setIcon(QIcon(":/icons/pause.png"));
        ui->btnstart->setIcon(QIcon(":/icons/pause.png"));

    }else{

        stopnsavetimer();
        button->setIcon(QIcon(":/icons/play.png"));
        ui->btnstart->setIcon(QIcon(":/icons/play.png"));
    }
}



void MainWindow::handleButton2Click() {
        window->close();
    setWindowState(Qt::WindowMaximized);
}

void MainWindow::on_btnstore_clicked(){
    dataopwindow->show();
    ui->btnclrhis->show();
    QFile file("mydata.txt");
    if(!file.open(QIODevice::ReadWrite)){
        qCritical()<<file.errorString();
    }
    QTextStream stream(&file);
    filedisplay->setText(stream.readAll());
}

void MainWindow::on_btnclrhis_clicked()
{
    filedisplay->setText(" ");
    QFile file("mydata.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    file.close();
}

