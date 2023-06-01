#include "puissance4.h"
#include "ui_puissance4.h"
#include <QMessageBox>
#include <QFontComboBox>
#include <QFont>
#include "BDD.h"
#include "equipe.h"
#include "new_mdp.h"
#include "parametre.h"
#include "mdp.h"

puissance4::puissance4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::puissance4),le_new(new new_mdp), les_equipes(new Equipe), settings(new Parametre), pages(new MDP)
{
    ui->setupUi(this);

    connect(ui->SettingsPB, &QPushButton::clicked, this, &puissance4::on_sett_clicked);

    connect(&pages, &MDP::SigMDP, this, &puissance4::verifMDP);

    connect(&ma_bdd,&BDD::la_BDD, this, &puissance4::verifMDP);

    connect(&settings, &Parametre::s_changement_mdp, this, &puissance4::nouveau_mdp);

    connect(&le_new, &new_mdp::Sig_new_mdp, this, &puissance4::nouveau_mdp);

    connect(&ma_bdd, &BDD::New_MDP_OK, this, &puissance4::fin_de_ligne);

    connect(&settings, &Parametre::s_valider, this, &puissance4::les_joueurs);

    connect(&les_equipes, &Equipe::new_player, this, &puissance4::les_new_joueur);
    connect(&les_equipes, &Equipe::out_player, this, &puissance4::suppresion);

    connect(&les_equipes, &Equipe::ajout_bdd, this, &puissance4::ajout_bdd_historique);
    //connect(&les_equipes, &Equipe::recup_noms, this, &puissance4::ajout_j);
    //connect(&les_equipes, &Equipe::nouveau_combo_1, this, &puissance4::ajout_combobox_1);

}

puissance4::~puissance4()
{
    delete ui;
}


void puissance4::on_sett_clicked()
{ 
    pages.open();
}

void puissance4::ajout_bdd_historique()
{
    les_equipes.nom_historique(les_noms_historique_bdd);
    qDebug() << les_noms_historique_bdd;
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
    les_equipes.open();
    qDebug() << "Affiche Equipe";
    ajout_j();
}


//void puissance4::keyPressEvent(QKeyEvent *event)
//{

//    if( event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
//    {

//    }
//}

//void puissance4::le_bouton_ajouter() //ajoute un joueur dans l'equipe 1
//{
//
//}

//void puissance4::le_bouton_ajouter2() //ajoute un+ joueur dans l'equipe 2
//{
//    j=1;
//    i=b_equipe_2;
//    createCombox();
//    lay->addWidget(Bouton_ajouter2,++b_equipe_2,j);
//    lay->addWidget(Bouton_supprimer2,++b_sup_equipe_2,j);

//}

//void puissance4::le_bouton_supprimer1()
//{
//     j=0;
//    if(b_equipe_1 == 10)
//    {
//        createCombox();
//        ++b_equipe_1;
//        ++b_sup_equipe_1;
//    }
//    --i=b_equipe_1;
//    lay->addWidget(Bouton_ajouter,--b_equipe_1,j);
//    lay->addWidget(Bouton_supprimer1,--b_sup_equipe_1,j);

//    destroyCombox();
//}

//void puissance4::le_bouton_supprimer2()
//{
//     j=1;
//    if(b_equipe_2 == 10)
//    {
//        createCombox();
//        ++b_equipe_2;
//        ++b_sup_equipe_2;
//    }
//    --i=b_equipe_2;
//    lay->addWidget(Bouton_ajouter2,--b_equipe_2,j);
//    lay->addWidget(Bouton_supprimer2,--b_sup_equipe_2,j);

//    destroyCombox();


//}


bool puissance4::verifMDP()
{
    QString mot = pages.getMDP();


    if(ma_bdd.le_mdp(mot))
    {

        settings.open();
        pages.hide();
        pages.ligne_a_zero();

    }
    else
    {       
        pages.ligne_a_zero();
        pages.message();
    }

    return true;
}

bool puissance4::nouveau_mdp()
{
   le_new.open();

   QString mdp_new = le_new.get_new_MDP();

   ma_bdd.ajouter_mdp(mdp_new);

}

void puissance4::fin_de_ligne()
{
    le_new.ligne_zero();
}

void puissance4::les_joueurs()
{
    les_equipes.open();
    qDebug() << "Affiche Equipe";
    ajout_j();

    this->hide();
    settings.hide();
}

void puissance4::les_new_joueur()
{
    QString les_joueurs = les_equipes.ajouter_joueur();

    if(ma_bdd.ajouter_Joueur(les_joueurs))
    {
        les_equipes.message();
    }


}

void puissance4::suppresion()
{
    QString Joueur_a_sup = les_equipes.supprimer_joueur();

    if(ma_bdd.La_suppresion(Joueur_a_sup))
    {
        QMessageBox::information(this,"supprimer","Joueur bien supprimer");
    }
}

void puissance4::ajout_j()
{
    QList<QString> les_noms;

    qDebug() << "coucou";

    if(ma_bdd.verifNomJoueur(les_noms))
    {
        qDebug() << les_noms;
    }


    les_equipes.recup_les_noms(les_noms);

}

//void puissance4::lesnoms_bdd()
//{
//    LesNoms_combobox.clear();
//    QSqlQuery requette; QString lesNoms;
//        requette.prepare("SELECT DISTINCT Joeur FROM Historique");
//        requette.exec();

//        while(requette.next()){

//        lesNoms = requette.value(0).toString();

//        LesNoms_combobox << lesNoms;


//        }
//}

//void puissance4::ajout_combobox_1()
//{
//     int position_combo = les_equipes.ajout_combobox_1p();

//     position_combo++;

     /*combo = new QComboBox();
     combo_sup = new QComboBox;*/

//     lesnoms_bdd();

//     combo->addItems(LesNoms_combobox);
//     combo_sup->addItems(LesNoms_combobox);

    //les_equipes.plus_joueur_1(position_combo,combo);



//    createCombox();
//    lay->addWidget(Bouton_ajouter,++b_equipe_1,j);
//    lay->addWidget(Bouton_supprimer1,++b_sup_equipe_1,j);
//}

