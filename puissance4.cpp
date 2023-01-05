#include "puissance4.h"
#include "./ui_puissance4.h"
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QRect>

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
    ui->PlayPB->deleteLater();                          // supprime le bouton
    ui->QuitPB->deleteLater();                          // supprime le bouton
    ui->SettingsPB->deleteLater();                      // supprime le bouton
    ui->ResultPB->deleteLater();                        // supprime le bouton



    QLabel *teamLB = new QLabel();                      //creation d'un label
    QLabel *team2LB = new QLabel();
    QGridLayout *layout = new QGridLayout();            //creation d'un layout
    teamLB->setText("Equipe 1");                        //Ecrit "Equipe 1" dans le label
    teamLB->setStyleSheet("color:red");                 // Met en rouge le texte du label
    QFont newfont ( "Equipe 1", 18, QFont::Bold,false); // parametre la police ainsi que la taille du Label
    team2LB->setText("Equipe 2");                        //Ecrit "Equipe 1" dans le label
    team2LB->setStyleSheet("color:Blue");                 // Met en rouge le texte du label
    QFont newfont2 ( "Equipe 2", 18, QFont::Bold,false); // parametre la police ainsi que la taille du Label

    teamLB->setFont(newfont);                           //parametre la police ainsi que la taille du Label
    team2LB->setFont(newfont2);

    layout->addWidget(teamLB,0,1);                          // met le label dans un layout
    layout->addWidget(team2LB,0,2);
    layout->setContentsMargins(125,0,0,400);            //change le layout de position
    ui->centralwidget->setLayout(layout);               // met le layout dans l'ui




}

