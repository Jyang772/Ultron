#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cookiesHandler.h"

#include <QProcess>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <QTimer>

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

void MainWindow::on_login_clicked()
{
    ui->label_5->setText("Authentication Accepted!");
   /* Downloader * lol = new Downloader();
    lol->url = ui->lineEdit->text();
    lol->username = ui->lineEdit_2->text();
    lol->password = ui->lineEdit_3->text();
    lol->doDownload();
*/

    QByteArray loginData;
    loginData.append("username="+(ui->lineEdit_2->text())+"&password="+(ui->lineEdit_3->text())+"&action=login");
   // loginData.append("username=justin@micropenguin.net&password=Password12&action=do_login");
    //loginData.append("username=justin_yang&password=bee1230");


    cookiesHandler* test = new cookiesHandler(this);
    QUrl url("https://moodle.redlands.edu/login/index.php");
    QUrl request("http://moodle.redlands.edu/mod/forum/view.php?id=114195");

    test->sendPostRequest(url, loginData);
    test->sendGetRequest(request);


    QEventLoop loop;
        QTimer::singleShot(8000, &loop, SLOT(quit()));
        loop.exec();

        QFile file("debug");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream outStream(&file);
        QString text = outStream.readAll();

        ui->display->setPlainText(text);

}



void MainWindow::on_lineEdit_3_returnPressed()
{
    on_login_clicked();
    ui->lineEdit_3->clear();
    ui->lineEdit_2->clear();
}
