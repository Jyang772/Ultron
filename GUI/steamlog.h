#ifndef STEAMLOG_H
#define STEAMLOG_H

#include <QDialog>

namespace Ui {
class SteamLog;
}

class SteamLog : public QDialog
{
    Q_OBJECT

public:
    explicit SteamLog(QWidget *parent = 0);
    ~SteamLog();

private:
    Ui::SteamLog *ui;
};

#endif // STEAMLOG_H
