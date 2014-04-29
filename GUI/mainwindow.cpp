#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloader.h"

#include <QProcess>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect (process, SIGNAL(readyReadStandardOutput()),this, SLOT(printOutput()));

    //Already implemented by Form creator

    //test connect
   // connect(ui->radioButton_4, SIGNAL(toggled(bool)), this, SLOT(do_something(bool)));

    //connect(ui->radioButton_3, SIGNAL(toggled(bool)), this, SLOT(do_something(bool)));
    //connect(ui->radioButton_3, false, this, SLOT(on_radioButton_4_clicked(bool)));


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

    if(wget == true){
        result = "wget ";
    url += result + ui->lineEdit->text().toStdString();
    }
    else if(debug == false)
        url = "";
    else
        url = ui->lineEdit->text().toStdString();

    ui->lineEdit->clear();
    cShell();
    /*
    ui->label->setText("Fetching...");
    QString lawl = QString::fromStdString(url);

    options.clear();
#if defined(Q_OS_LINUX)
    options << "-c" << lawl;
    process->start("/bin/sh", options);
#elif defined(Q_OS_WIN)
   // process->start(ui->lineEdit->text(), options);
#endif
    process->waitForFinished();
            //clear result buffer
    */
    url.clear();

    }

void MainWindow::on_radioButton_3_clicked(bool checked)
{


    if(checked == false)
    {
        debug = false;
        //result = "wget ";
    }
    else
    {
        result = "";
        debug = true;
        wget = false;
        url = ui->lineEdit->text().toStdString();
        ui->radioButton_4->setChecked(false);                       //if debug is checked, uncheck wget.
    }



}

void MainWindow::on_pushButton_2_clicked()
{


    ui->label_5->setText("Authentication Accepted!");
    Downloader * lol = new Downloader();
    lol->doDownload();

}

void MainWindow::on_radioButton_4_clicked(bool checked)
{
   if(checked)
   {
       ui->radioButton_3->setChecked(false);         //if wget button is checked, uncheck debug
       on_radioButton_3_clicked(false);

       wget = true;

   }
   else
       wget = false;
}

//create new header file

void MainWindow::cShell()
{
    ui->label->setText("Fetching...");
    QString lawl = QString::fromStdString(url);

    options.clear();
#if defined(Q_OS_LINUX)
    options << "-c" << lawl;
    process->start("/bin/sh", options);
#elif defined(Q_OS_WIN)
   // process->start(ui->lineEdit->text(), options);
#endif
    process->waitForFinished();
            //clear result buffer
}



void MainWindow::on_actionPhrack_triggered()
{
    QMessageBox::information(this,"PhrackR v1.0", "Phrack Reader Not Installed!");
}
