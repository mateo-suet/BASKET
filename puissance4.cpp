#include "puissance4.h"
#include "ui_puissance4.h"
#include <QMessageBox>
#include <QFontComboBox>
#include <QFont>
#include "BDD.h"
#include "equipe.h"
#include "new_mdp.h"

puissance4::puissance4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::puissance4),le_new(new new_mdp), les_equipes(new Equipe)
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
    qDebug() << "on est ici";
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

    les_equipes.open();

//    int emplacement = lay->indexOf(combo);

//    bool success;
//    success = false;
//    QSqlQuery query;

//    query.prepare("UPDATE Historique SET Date=:date");
//    query.bindValue(":date",laDate->currentDate());

//     if(query.exec())
//     {
//         success = true;
//         QMessageBox::information(this,"Parmétres OK", "Les paramétres sont OK");

//     }
//     else
//     {
//         QMessageBox::information(this,"Parmétres ERROR", "ERROR");
//     }
//     return success;
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
    Nom_Equipe_1->setText("Equipe 1");
    Nom_Equipe_2->setText("Equipe 2");
    tire->setValue(5);
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
    Bouton_default = new QPushButton("Par Défaut");

    Bouton_changer_mdp = new QPushButton("Changer Le Mot de Passe");

    Bouton_new_player = new QPushButton("Nouveau Joueur + ");
    Bouton_new_player->setEnabled(false);

    Bouton_sup_joueur = new QPushButton("Supprimer Joueur - ");

    ligne_new_player = new QLineEdit();

    titre = new QLabel(); //Créer les titres
    titre1 = new QLabel();
    titreBS = new QLabel();
    Nom_Equipe_1 = new QLineEdit("Equipe 1");
    Nom_Equipe_2 = new QLineEdit("Equipe 2");
    titre_new_player = new QLabel();
    titre_nb_tire = new QLabel();
    titre_sup_player = new QLabel();

    LeTemps = new QTimeEdit(); //Créer la zone de temps

    Groupe = new QButtonGroup(this);

    tire = new QSpinBox();
    tire->setValue(5);
    tire->setRange(1,30);

    titre->setText("Nombre de Panier");
    titre->setStyleSheet("font-size: 20px");

    titre1->setText("Délai De Tir");
    titre1->setStyleSheet("font-size: 20px");

    titreBS->setText("Son");
    titreBS->setStyleSheet("font-size: 20px");

    titre_nb_tire->setText("Nombre de tirs par joueur");
    titre_nb_tire->setStyleSheet("font-size: 20px");

    titre_sup_player->setText("Supprimer Joueur");
    titre_sup_player->setStyleSheet("font-size: 20px");

    ui->LeTout->setLayout(lay);

    //Bouton_ajouter->setMaximumWidth(100);
//    Bouton_ajouter2->setMaximumWidth(100);

//    Bouton_supprimer1->setMaximumWidth(100);
//    Bouton_supprimer2->setMaximumWidth(100);

//    Bouton_ok->setMaximumWidth(100);

//    LeTemps->setMaximumWidth(100);

//    tire->setMaximumWidth(100);

//    Bouton_default->setMaximumWidth(100);

//    Nom_Equipe_1->setMaximumWidth(100);
//    Nom_Equipe_1->setStyleSheet("color: red");

//    Nom_Equipe_2->setFixedWidth(100);
//    Nom_Equipe_2->setStyleSheet("color: #8B8000");

    lay->addWidget(titre,1,0);  //Place tout les widget dans le Layout
    lay->addWidget(nb5,2,0);
    lay->addWidget(nb7,2,1);

    lay->addWidget(titre1,3,0);
    lay->addWidget(LeTemps,4,0);
    LeTemps->setTime(QTime(0,5,0,0));

    lay->addWidget(titre_nb_tire,1,2);


    lay->addWidget(titreBS,5,0);
    lay->addWidget(bson,6,0);
    bson->setChecked(true);
    lay->addWidget(bsoff,6,1);

    lay->addWidget(Bouton_ok,8,0);
    lay->addWidget(Bouton_quitter,8,1);
    lay->addWidget(Bouton_default,8,2);
    lay->addWidget(Bouton_changer_mdp,8,3);

    lay->addWidget(Nom_Equipe_1,9,0);
    lay->addWidget(Nom_Equipe_2,9,1);

    lay->addWidget(tire,2,2);

    lay->addWidget(Bouton_sup_joueur,14,3);

    Groupe->addButton(nb5);
    Groupe->addButton(nb7);

    nb5->setChecked(true);

    for(j=0;j<2;j++)
    {
        for(i=10; i<15; i++)
        {
            createCombox();
        }
    }

    lay->addWidget(Bouton_ajouter,b_equipe_1,0);



    lay->addWidget(Bouton_ajouter2,b_equipe_2,1);

    lay->addWidget(Bouton_supprimer1,b_sup_equipe_1,0);
    lay->addWidget(Bouton_supprimer2,b_sup_equipe_2,1);

    titre_new_player->setText("Créer Joueur");
    titre_new_player->setStyleSheet("font-size: 20px");

    lay->addWidget(titre_new_player,9,3);
    lay->addWidget(ligne_new_player,10,3);
    lay->addWidget(Bouton_new_player,11,3);

    lay->addWidget(titre_sup_player,12,3);
/**/
    Bouton_ajouter->setMaximumWidth(100);
    Bouton_ajouter2->setMaximumWidth(100);

    Bouton_supprimer1->setMaximumWidth(100);
    Bouton_supprimer2->setMaximumWidth(100);

    Bouton_ok->setMaximumWidth(100);

    LeTemps->setMaximumWidth(100);

    tire->setMaximumWidth(100);

    Bouton_default->setMaximumWidth(100);

    Nom_Equipe_1->setMaximumWidth(100);
    Nom_Equipe_1->setStyleSheet("color: red");

    Nom_Equipe_2->setFixedWidth(100);
    Nom_Equipe_2->setStyleSheet("color: #8B8000");

/**/



    lay->setContentsMargins(50,10,100,25);

    connect(Bouton_ok, SIGNAL(clicked()), this, SLOT(le_bouton_ok()));
    connect(Bouton_quitter, SIGNAL(clicked()), this, SLOT(le_bouton_quitter()));
    connect(Bouton_default, SIGNAL(clicked()), this, SLOT(le_bouton_default()));
    connect(Bouton_ajouter, SIGNAL(clicked()), this, SLOT(le_bouton_ajouter()));
    connect(Bouton_ajouter2, SIGNAL(clicked()), this, SLOT(le_bouton_ajouter2()));
    connect(Bouton_supprimer1, SIGNAL(clicked()), this, SLOT(le_bouton_supprimer1()));
    connect(Bouton_supprimer2, SIGNAL(clicked()), this, SLOT(le_bouton_supprimer2()));
    connect(Bouton_changer_mdp, SIGNAL(clicked()), this, SLOT(le_bouton_changer_mdp()));
    connect(Bouton_new_player, SIGNAL(clicked()), this, SLOT(le_bouton_new_player()));
    connect(Bouton_sup_joueur, SIGNAL(clicked()), this, SLOT(le_bouton_supprimer_joueur()));
    connect(ligne_new_player, &QLineEdit::textChanged, this, &puissance4::Ecrire);

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
    Bouton_valider_mdp->setMaximumWidth(50);

    lay->setContentsMargins(50,10,50,250);

    connect(Bouton_valider_mdp, SIGNAL(clicked()), this, SLOT(le_bouton_valider()));


}

void puissance4::le_bouton_valider()
{

    QString c = ligne_mdp->text();

    if(ma_bdd.verifMotDePasse(c))
    {
        clearLayout(lay);
        b_equipe_1 = 15;
        b_equipe_2 = 15;

        b_sup_equipe_1 = 16;
        b_sup_equipe_2 = 16;

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
    combo_sup = new QComboBox;

    combo->setMaximumWidth(100);

    lesnoms_bdd();

    combo->addItems(LesNoms_combobox);
    combo_sup->addItems(LesNoms_combobox);

    lay->addWidget(combo,i,j);
    lay->addWidget(combo_sup,13,3);
}
void puissance4::destroyCombox()
{
    QLayoutItem* item = lay->itemAtPosition(--i,j);
    lay->removeItem(item);
    qDebug() << i;
    QWidget* widget = item->widget();

        if(widget)
        {
            delete widget;
        }

}

void puissance4::keyPressEvent(QKeyEvent *event)
{

    if( event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        Bouton_valider_mdp->click();
    }
}

void puissance4::le_bouton_ajouter() //ajoute un joueur dans l'equipe 1
{
    j=0;
    i=b_equipe_1;
    createCombox();
    lay->addWidget(Bouton_ajouter,++b_equipe_1,j);
    lay->addWidget(Bouton_supprimer1,++b_sup_equipe_1,j);
}

void puissance4::le_bouton_ajouter2() //ajoute un+ joueur dans l'equipe 2
{
    j=1;
    i=b_equipe_2;
    createCombox();
    lay->addWidget(Bouton_ajouter2,++b_equipe_2,j);
    lay->addWidget(Bouton_supprimer2,++b_sup_equipe_2,j);

}

void puissance4::le_bouton_supprimer1()
{
     j=0;
    if(b_equipe_1 == 10)
    {
        createCombox();
        ++b_equipe_1;
        ++b_sup_equipe_1;
    }
    --i=b_equipe_1;
    lay->addWidget(Bouton_ajouter,--b_equipe_1,j);
    lay->addWidget(Bouton_supprimer1,--b_sup_equipe_1,j);

    destroyCombox();
}

void puissance4::le_bouton_supprimer2()
{
     j=1;
    if(b_equipe_2 == 10)
    {
        createCombox();
        ++b_equipe_2;
        ++b_sup_equipe_2;
    }
    --i=b_equipe_2;
    lay->addWidget(Bouton_ajouter2,--b_equipe_2,j);
    lay->addWidget(Bouton_supprimer2,--b_sup_equipe_2,j);

    destroyCombox();


}
void puissance4::le_bouton_changer_mdp()
{
    le_new.open();
}

bool puissance4::le_bouton_new_player()
{
    bool success;
    success = false;
    QSqlQuery query;


    query.prepare("INSERT INTO Historique (Joeur) VALUES (:nom)");
    query.bindValue(":nom",ligne_new_player->text());

     if(query.exec())
     {
         success = true;
         ligne_new_player->setText("");
         QMessageBox::information(this,"nouveau joueur", "votre nouveau jouer a était valider");

     }
     else
     {
         ligne_new_player->setText("");
         QMessageBox::information(this,"nouveau joueur", "nouveau joueur erreur");
     }
     return success;
}

void puissance4::Ecrire()
{
    if((ligne_new_player->text().length() !=0))
    {
        Bouton_new_player->setEnabled(true);
    }
    else
    {
        Bouton_new_player->setEnabled(false);
    }
}

void puissance4::lesnoms_bdd()
{
    LesNoms_combobox.clear();
    QSqlQuery requette; QString lesNoms;
        requette.prepare("SELECT DISTINCT Joeur FROM Historique");
        requette.exec();

        while(requette.next()){

        lesNoms = requette.value(0).toString();

        LesNoms_combobox << lesNoms;




        }
}

void puissance4::compteur_de_widget()
{
    int y = lay->rowCount();

    int y_c = lay->columnCount();

    for (f=0; f < lay->count(); f++)
    {
        lay->itemAt(f);
    }
}

void puissance4::le_bouton_supprimer_joueur()
{

    QString l = combo_sup->currentText();
    QSqlQuery requette;
    requette.prepare("DELETE FROM Historique WHERE Joeur = '"+ l +"'");

    if(sup_joueur.verifNomJoueur(l))
    {
        if(requette.exec())
        {
           QMessageBox::warning(this,"SUPPRIMER","Suppresion Joueur Réussi");
        }
    }
    else
    {
        QMessageBox::warning(this,"ERREUR","Suppresion Joueur n'a pas marcher");
    }
}

