#include "puissance4.h"
#include "ui_puissance4.h"


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


//    connect(Bouton_ok, SIGNAL(clicked()), this, SLOT(le_bouton_ok()));
//    connect(Bouton_quitter, SIGNAL(clicked()), this, SLOT(le_bouton_quitter()));
//    connect(Bouton_default, SIGNAL(clicked()), this, SLOT(le_bouton_default()));
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

    titre = new QLabel(); //Créer les titres
    titre1 = new QLabel();
    titreBS = new QLabel();

    LeTemps = new QTimeEdit(); //Créer la zone de temps

    Groupe = new QButtonGroup(this);

    titre->setText("Nombre de Panier");
    titre->setStyleSheet("font-size: 20px");

    titre1->setText("Le Temps");
    titre1->setStyleSheet("font-size: 20px");

    titreBS->setText("Son");
    titreBS->setStyleSheet("font-size: 20px");

    lay = new QGridLayout();
    ui->LeTout->setLayout(lay);


    lay->addWidget(titre);  //Place tout les widget dans le Layout
    lay->addWidget(nb5,1,0);
    lay->addWidget(nb7,1,1);

    lay->addWidget(titre1,2,0);
    lay->addWidget(LeTemps,3,0);
    lay->addWidget(titreBS,4,0);

    lay->addWidget(bson,5,0);
    lay->addWidget(bsoff,5,1);

    lay->addWidget(Bouton_ok,6,0);
    lay->addWidget(Bouton_quitter,6,1);
    lay->addWidget(Bouton_default,6,2);

    Groupe->addButton(nb5);
    Groupe->addButton(nb7);

    lay->setContentsMargins(250,10,250,250);
}

void puissance4::la_page_mdp()
{
    lay = new QGridLayout();

    ligne_mdp = new QLineEdit();

    lemdp = new QString("moi");

    titre_mdp = new QLabel();
    titre_mdp->setText("Mot de Passe");
    titre_mdp->setStyleSheet("font-size: 25px");

    ligne_mdp->setEchoMode(QLineEdit::Password);

    c = new QString(ligne_mdp->selectedText());

    Bouton_valider_mdp = new QPushButton("Valider");

    ui->LeTout->setLayout(lay);

    lay->addWidget(titre_mdp,0,0);
    lay->addWidget(ligne_mdp,1,0);
    lay->addWidget(Bouton_valider_mdp,2,0);
    lay->setContentsMargins(300,100,250,300);

    connect(Bouton_valider_mdp, SIGNAL(clicked()), this, SLOT(le_bouton_valider()));

}

void puissance4::le_bouton_valider()
{
    qDebug() << "on est dans le valider";
    if(c == lemdp)
    {
        qDebug() << "on est dans le test";
        creation_des_widget();
    }
}
