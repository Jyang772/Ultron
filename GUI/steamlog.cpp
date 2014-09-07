#include "steamlog.h"
#include "ui_steamlog.h"

SteamLog::SteamLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SteamLog)
{
    ui->setupUi(this);
}

SteamLog::~SteamLog()
{
    delete ui;
}
