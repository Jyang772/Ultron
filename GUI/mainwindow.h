#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QProcess>
#include <string>

#include "steamlog.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();



    void printOutput();



    void on_radioButton_3_clicked(bool checked);

    //void on_pushButton_2_clicked();

    void on_radioButton_4_clicked(bool checked);

   // void do_something(bool checked);



    void on_actionPhrack_triggered();

    void on_login_clicked();


    void on_lineEdit_3_returnPressed();

    void on_actionSteamLogger_triggered();

private:
    Ui::MainWindow *ui;

        QProcess *process;
        QStringList options;


        //DEBUG RADIO BUTTON TRACKING//
        string result;// = "wget ";
        string url;

        bool wget;// = false;
        bool debug;// = false;


       //QProcess create
        void cShell();

        SteamLog *test;



};

#endif // MAINWINDOW_H
