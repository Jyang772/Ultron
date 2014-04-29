#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloader.h"

#include <QProcess>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;


string result = "wget ";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect (process, SIGNAL(readyReadStandardOutput()),this, SLOT(printOutput()));


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Pressed!");
    on_lineEdit_returnPressed();


}
void MainWindow::printOutput()
{
    ui->display->setPlainText(process->readAll());
}


void MainWindow::on_lineEdit_returnPressed()
{

    result += ui->lineEdit->text().toStdString();

    ui->lineEdit->clear();

    ui->label->setText("Fetching...");
    QString lawl = QString::fromStdString(result);

    options.clear();
#if defined(Q_OS_LINUX)
    options << "-c" << lawl;
    process->start("/bin/sh", options);
#elif defined(Q_OS_WIN)
   // process->start(ui->lineEdit->text(), options);
#endif
    process->waitForFinished();
    result.clear();        //clear result buffer
    }

void MainWindow::on_radioButton_3_clicked(bool checked)
{
    result = "";
    if(checked == false)
        result = "wget ";
}

void MainWindow::on_pushButton_2_clicked()
{


    ui->label_5->setText("Authentication Accepted!");

    Downloader * lol = new Downloader();

    lol->doDownload();


}







void MainWindow::on_radioButton_4_clicked(bool checked)
{

}
