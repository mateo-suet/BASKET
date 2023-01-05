#include "puissance4.h"
#include "ui_puissance4.h"
#include <QRadioButton>
#include <QHBoxLayout>
#include <QGridLayout>

puissance4::puissance4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::puissance4)
{
    ui->setupUi(this);

    connect(ui->SettingsPB, &QPushButton::clicked, this, &puissance4::on_sett_clicked);
}

puissance4::~puissance4()
{
    delete ui;
}


void puissance4::on_sett_clicked()
{
    ui->PlayPB->deleteLater();
    ui->QuitPB->deleteLater();
    ui->SettingsPB->deleteLater();
    ui->ResultPB->deleteLater();

    QRadioButton *nb4 = new QRadioButton("5",this);  // Affiche les boutons de 5 a 7
    QRadioButton *nb6 = new QRadioButton("7",this);

    QGridLayout *lay = new QGridLayout();
    ui->LeTout->setLayout(lay);

    lay->addWidget(nb4);
    lay->addWidget(nb6,0,1);

    lay->setSizeConstraint(QLayout::SetFixedSize);
    lay->setContentsMargins(350,100,0,0);



}
