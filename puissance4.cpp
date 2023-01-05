#include "puissance4.h"
#include "./ui_puissance4.h"

Puissance4::Puissance4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Puissance4)
{
    ui->setupUi(this);
    connect(ui->PlayPB, &QPushButton::clicked, this, &Puissance4::on_playButton_clicked);
}

Puissance4::~Puissance4()
{
    delete ui;
}

void Puissance4::on_playButton_clicked()
{
    ui->PlayPB->deleteLater();
    ui->QuitPB->deleteLater();
    ui->SettingsPB->deleteLater();
    ui->ResultPB->deleteLater();
}

