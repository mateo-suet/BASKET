#include "puissance4.h"
#include "ui_puissance4.h"
#include <QMessageBox>
#include <QFontComboBox>
#include <QFont>

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
    ui->PlayPB->hide();  //cache tout les premier boutons
    ui->QuitPB->hide();
    ui->SettingsPB->hide();
    ui->ResultPB->hide();

    la_page_mdp();

}

void clearLayout(QLayout *layout){
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while ((item = layout->takeAt(0))) {
        if (  (item->layout())){
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void puissance4::le_bouton_ok()
{

}

void puissance4::le_bouton_quitter()
{
    clearLayout(lay);
    lay->deleteLater();
    ui->PlayPB->show();  //re affiche tout les premier boutons
    ui->QuitPB->show();
    ui->SettingsPB->show();
    ui->ResultPB->show();
}

void puissance4::le_bouton_default()
{

    nb5->setChecked(true);
    bson->setChecked(true);
    LeTemps->setTime(QTime(0,5,0,0));

}

void puissance4::creation_des_widget()
{

    nb5 = new QRadioButton("5",this);  // Créer les boutons de 5 et 7
    nb7 = new QRadioButton("7",this);

    bson = new QRadioButton("ON", this);
    bsoff = new QRadioButton("OFF", this);

    Bouton_ok = new QPushButton("OK"); //Créer les bouton ok quitter et default
    Bouton_quitter = new QPushButton("Quitter");
    Bouton_default = new QPushButton("Default");
    Bouton_ajouter = new QPushButton("+");
    Bouton_ajouter2 = new QPushButton("+");

    titre = new QLabel(); //Créer les titres
    titre1 = new QLabel();
    titreBS = new QLabel();
    teamLB = new QLabel();
    team2LB = new QLabel();

    LeTemps = new QTimeEdit(); //Créer la zone de temps

    Groupe = new QButtonGroup(this);

    teamLB->setText("Equipe 1");
    teamLB->setStyleSheet("color:red");
    QFont newfont ( "Equipe 1", 18, QFont::Bold,false);
    team2LB->setText("Equipe 2");
    team2LB->setStyleSheet("color:Blue");
    QFont newfont2 ( "Equipe 2", 18, QFont::Bold,false);

    teamLB->setFont(newfont);
    team2LB->setFont(newfont2);

    titre->setText("Nombre de Panier");
    titre->setStyleSheet("font-size: 20px");

    titre1->setText("Le Temps");
    titre1->setStyleSheet("font-size: 20px");

    titreBS->setText("Son");
    titreBS->setStyleSheet("font-size: 20px");

    ui->LeTout->setLayout(lay);

    Bouton_ajouter->setMaximumWidth(100);
    Bouton_ajouter2->setMaximumWidth(100);

    Bouton_ok->setMaximumWidth(100);

    LeTemps->setMaximumWidth(100);

    lay->addWidget(titre,1,0);  //Place tout les widget dans le Layout
    lay->addWidget(nb5,2,0);
    lay->addWidget(nb7,2,1);

    lay->addWidget(titre1,3,0);
    lay->addWidget(LeTemps,4,0);

    lay->addWidget(titreBS,5,0);
    lay->addWidget(bson,6,0);
    lay->addWidget(bsoff,6,1);

    lay->addWidget(Bouton_ok,8,0);
    lay->addWidget(Bouton_quitter,8,1);
    lay->addWidget(Bouton_default,8,2);

    lay->addWidget(teamLB,9,0);
    lay->addWidget(team2LB,9,1);



    Groupe->addButton(nb5);
    Groupe->addButton(nb7);

    for(j=0;j<2;j++)
       {
           for(i=10; i<15; i++)
           {
               createCombox();
           }
       }

    lay->addWidget(Bouton_ajouter,i,0);
    lay->addWidget(Bouton_ajouter2,i,1);

    lay->setContentsMargins(250,10,250,250);

    connect(Bouton_ok, SIGNAL(clicked()), this, SLOT(le_bouton_ok()));
    connect(Bouton_quitter, SIGNAL(clicked()), this, SLOT(le_bouton_quitter()));
    connect(Bouton_default, SIGNAL(clicked()), this, SLOT(le_bouton_default()));
    connect(Bouton_ajouter, SIGNAL(clicked()), this, SLOT(le_bouton_ajouter()));
    connect(Bouton_ajouter2, SIGNAL(clicked()), this, SLOT(le_bouton_ajouter2()));
}

void puissance4::la_page_mdp()
{
    lay = new QGridLayout();

    ligne_mdp = new QLineEdit();

    titre_mdp = new QLabel();
    titre_mdp->setText("Mot de Passe");
    titre_mdp->setStyleSheet("font-size: 25px");

    ligne_mdp->setEchoMode(QLineEdit::Password);

    Bouton_valider_mdp = new QPushButton("Valider");

    ui->LeTout->setLayout(lay);

    lay->addWidget(titre_mdp,0,0);
    lay->addWidget(ligne_mdp,1,0);
    lay->addWidget(Bouton_valider_mdp,2,0);
    Bouton_valider_mdp->setMaximumWidth(100);
    lay->setContentsMargins(300,100,250,300);



    connect(Bouton_valider_mdp, SIGNAL(clicked()), this, SLOT(le_bouton_valider()));

}

void puissance4::le_bouton_valider()
{
    QString lemdp = "lui";
    QString c = ligne_mdp->text();

    if(c == lemdp)
    {
        clearLayout(lay);
        creation_des_widget();
    }
    else
    {
        QMessageBox::warning(this,"ERREUR","Mauvais MOT DE PASSE");
        ligne_mdp->clear();
    }
}

void puissance4::createCombox()
{
    combo = new QComboBox();
    combo->addItem("/");
    combo->addItem("matéo");
    combo->addItem("Anthony");
    combo->addItem("Le pompier");
    combo->addItem("thibault");
    combo->setMaximumWidth(100);

    lay->addWidget(combo,i,j);

}
void puissance4::le_bouton_ajouter()
{
    j=0;
    createCombox();
//    lay->addWidget(Bouton_ajouter,i,j);

}

void puissance4::le_bouton_ajouter2()
{
    j=1;
    createCombox();
//    lay->addWidget(Bouton_ajouter2,i,j);


}
