#include "puissance4.h"
#include "./ui_puissance4.h"
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QRect>
#include <QComboBox>
#include <QFontComboBox>

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
    ui->PlayPB->hide();                          // supprime le bouton
    ui->QuitPB->hide();                          // supprime le bouton
    ui->SettingsPB->hide();                      // supprime le bouton
    ui->ResultPB->hide();                        // supprime le bouton

    createLayout();

    connect(confirmPlayPB, SIGNAL(clicked()), this, SLOT(play_button()));
    connect(quitConfirmPB, SIGNAL(clicked()), this, SLOT(quit_button()));

}

void Puissance4::createCombox()
{
    QComboBox *combo = new QComboBox();
    combo->addItem("/");
    combo->addItem("matéo");
    combo->addItem("Anthony");
    combo->addItem("Le pompier");
    combo->addItem("thibault");
    combo->setMaximumWidth(100);

    layout->addWidget(combo,i,j);

}

void Puissance4::createLayout()
{
    teamLB = new QLabel();
    team2LB = new QLabel();
    layout = new QGridLayout();
    confirmPlayPB = new QPushButton(ui->centralwidget);
    quitConfirmPB = new QPushButton(ui->centralwidget);


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
    layout->setContentsMargins(0,0,0,300);            //change le layout de position

    for(j=1;j<3;j++)
    {
        for(i=1; i<5; i++)
        {
            createCombox();
        }
    }
    confirmPlayPB->setText("Jouer");
    confirmPlayPB->setGeometry(500,520,100,55);
    confirmPlayPB->show();
    quitConfirmPB->setText("Quitter");
    quitConfirmPB->setGeometry(20,520,100,55);
    quitConfirmPB->show();
    ui->centralwidget->setLayout(layout);               // met le layout dans l'ui

}


void clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

void Puissance4::play_button()
{
    qDebug() << "e";
    quitConfirmPB->hide();
    confirmPlayPB->hide();
    clearLayout(layout);
    layout->deleteLater();


}

void Puissance4::quit_button()
{
    qDebug() << "e";
    quitConfirmPB->deleteLater();
    confirmPlayPB->deleteLater();
    clearLayout(layout);
    layout->deleteLater();
    ui->PlayPB->show();
    ui->SettingsPB->show();
    ui->ResultPB->show();
    ui->QuitPB->show();
}



