#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

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


    void on_radioButton_3_clicked();

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_pushButton_2_clicked();

//private:
    void on_radioButton_4_clicked(bool checked);

private:
    Ui::MainWindow *ui;

        QProcess *process;
        QStringList options;
};

#endif // MAINWINDOW_H
