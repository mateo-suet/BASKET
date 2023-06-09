#include "puissance4.h"
#include "ui_puissance4.h"
#include <QMessageBox>
#include <QFontComboBox>
#include <QFont>
#include <QGridLayout>
#include "BDD.h"
#include "equipe.h"
#include "new_mdp.h"
#include "parametre.h"
#include "mdp.h"

puissance4::puissance4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::puissance4),le_new(new new_mdp), les_equipes(new Equipe), settings(new Parametre), pages(new MDP), Historique(new Resultat)
{
    ui->setupUi(this);

    connect(ui->PlayPB, &QPushButton::clicked, this, &puissance4::on_playButton_clicked);

    connect(ui->SettingsPB, &QPushButton::clicked, this, &puissance4::on_sett_clicked);

    connect(ui->QuitPB, &QPushButton::clicked, this, &puissance4::quitter_tout);

    connect(&pages, &MDP::SigMDP, this, &puissance4::verifMDP);

    connect(&ma_bdd,&BDD::la_BDD, this, &puissance4::verifMDP);

    connect(&settings, &Parametre::s_changement_mdp, this, &puissance4::nouveau_mdp);

    connect(&le_new, &new_mdp::Sig_new_mdp, this, &puissance4::nouveau_mdp);

    connect(&ma_bdd, &BDD::New_MDP_OK, this, &puissance4::fin_de_ligne);

    connect(&settings, &Parametre::s_valider, this, &puissance4::les_joueurs);

    connect(&les_equipes, &Equipe::new_player, this, &puissance4::les_new_joueur);
    connect(&les_equipes, &Equipe::out_player, this, &puissance4::suppresion);

    connect(&les_equipes, &Equipe::ajout_bdd, this, &puissance4::ajout_bdd_historique);

    connect(&les_equipes, &Equipe::quitter_sign, this, &puissance4::quitter);
    connect(&settings, &Parametre::s_quitter, this, &puissance4::quitter_1);

    connect(ui->ResultPB, &QPushButton::clicked, this, &puissance4::ouverture_historique);

    connect(&Historique, &Resultat::sign_quitter, this, &puissance4::quitter_2);

    ui->PlayPB->setEnabled(false);
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
    les_equipes.nom_equipe1(les_noms_historique_bdd);
    les_equipes.nom_equipe2(les_noms_historique_bdd2);
    QList<QString> nom_1;
    QList<QString> nom_2;
    nom_1 << les_noms_historique_bdd;
    nom_2 << les_noms_historique_bdd2;

   for (int o = 0; o < nom_1.size(); ++o)
   {

       if(!nom_1.isEmpty())
       {
         un_nom=nom_1.at(o);
         qDebug() <<"la"<< un_nom;
         ma_bdd.ajout_joueur_party(un_nom);
       }
   }

   for (int o = 0; o < nom_2.size(); ++o)
   {
       if(!nom_2.isEmpty())
       {
         un_nom2 = nom_2.at(o);
          ma_bdd.ajout_joueur_party2(un_nom2);
       }
   }
   les_equipes.close();
    this->show();
   ui->PlayPB->setEnabled(true);
    qDebug() << les_noms_historique_bdd;
}

void puissance4::quitter()
{
    les_equipes.close();
    settings.open();
}

void puissance4::quitter_1()
{
    settings.close();
    this->show();
}

void puissance4::quitter_2()
{
    Historique.close();
    this->show();
}

void puissance4::ouverture_historique()
{
    Historique.open();
    this->hide();
}

void puissance4::quitter_tout()
{
    this->close();
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
    les_equipes.lancement_joueur();
    les_equipes.lancement_joueur_2();

    this->hide();
    settings.hide();
}

void puissance4::les_new_joueur()
{
    QString les_joueurs = les_equipes.ajouter_joueur();

    ui->PlayPB->setCheckable(true);
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


    les_equipes.recup_les_noms1(les_noms);
    les_equipes.recup_les_noms2(les_noms);

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

void puissance4::on_playButton_clicked()
{
    ui->PlayPB->hide();                          // supprime le bouton
    ui->QuitPB->hide();                          // supprime le bouton
    ui->SettingsPB->hide();                      // supprime le bouton
    ui->ResultPB->hide();
    ui->LeTout->setStyleSheet("background-color: #99CBFF");
    mainLayout = new QGridLayout(this);
    k=9;

    createPlateau();
}



void puissance4::createPlateau()
{
    nbPanier = settings.nombrePanier();
    pixmap_img = new QPixmap("U:\\Documents\\rond_vide.png");
    tableauLayout = new QGridLayout(this);
    for( j=0; j <=6;j++)
    {


        for ( i = 1; i<=nbPanier;i++)
        {
            label_img= new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,j,i);
        }

        tableauLayout->setColumnStretch(i,1);
    }
    equipeLayout = new QGridLayout (this);

    equipeRouge = new QLabel ("Equipe Rouge");
    equipeRouge->setStyleSheet("QLabel {font: 40px;"
                                    "color:#FF0000 ; background-color : #99CBFF;}");
    equipeLayout->addWidget(equipeRouge,0,0);


    equipeJaune = new QLabel ("Equipe Jaune");
    equipeJaune->setStyleSheet("QLabel {font : 20px;"
                                        "color:#8F8D0F; background-color : #99CBFF;}");
    equipeLayout->addWidget(equipeJaune,0,1);
    equipeLayout->setColumnStretch(0,5);
    equipeLayout->setColumnStretch(1,5);

    boutonLayout = new QGridLayout(this);
    QPushButton *jSuivant = new QPushButton ("Joueur Suivant");
    QPushButton *pausePB = new QPushButton ("Pause");
    jSuivant->setStyleSheet("background-color: #CCE5FF");
    pausePB->setStyleSheet("background-color: #CCE5FF");
    jSuivant->setMinimumSize(100,100);
    pausePB->setMinimumSize(100,100);
    boutonLayout->addWidget(jSuivant,0,0);
    boutonLayout->addWidget(pausePB,0,1);

    timerjoueurLayout = new QGridLayout(this);
    numberTimer = new QLCDNumber(this);
    numberTimer->setDigitCount(QString("%1").arg(10).length());
    numberTimer->setStyleSheet("background-color: #99CBFF; color: green;");
    tmps = settings.envoieTemps();
    numberTimer->display(tmps);

    timerjoueurLayout->addWidget(numberTimer,0,0);

    color=0;

    QList<QString> liste_compte;
    QList<QString> liste_compte2;

    les_equipes.nom_equipe1(liste_compte);
    les_equipes.nom_equipe2(liste_compte2);
    qDebug()<< liste_compte;
    for(i=0; i<liste_compte.size();i++)
    {
        players.append(liste_compte[i]);
        for(j=i ; j<i+1;j++)
        {
            players.append(liste_compte2[j]);
        }
    }

    qDebug() << players;
    playerlist=0;
    player = new QLabel(players[0]);
    qDebug() << player;
    player->setAlignment(Qt::AlignCenter);
    player->setStyleSheet("QLabel {font : 45px;"
                          "background-color : #99CBFF; color : #FF0000;}");


    timerjoueurLayout->addWidget(player,1,0);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout ()), this, SLOT(timerSlot()));
    timer->start(1000);


    mainLayout->addLayout(tableauLayout,0,0);
    mainLayout->addLayout(timerjoueurLayout,0,1);
    mainLayout->addLayout(equipeLayout,1,0);
    mainLayout->addLayout(boutonLayout,1,1);
    ui->LeTout->setLayout(mainLayout);

    connect(jSuivant, SIGNAL(clicked()),this,SLOT(changementJoueur()));
    connect(pausePB, SIGNAL(clicked()),this,SLOT(menupause()));

}

void puissance4::verification()
{
        QList<QList<QString>> verif_listes;
        verif_listes.append(col1_vrif);
        verif_listes.append(col2_vrif);
        verif_listes.append(col3_vrif);
        verif_listes.append(col4_vrif);
        verif_listes.append(col5_vrif);
        verif_listes.append(col6_vrif);
        verif_listes.append(col7_vrif);
        verif_listes.append(ligne1_vrif);
        verif_listes.append(ligne2_vrif);
        verif_listes.append(ligne3_vrif);
        verif_listes.append(ligne4_vrif);
        verif_listes.append(ligne5_vrif);
        verif_listes.append(ligne6_vrif);
        verif_listes.append(ligne7_vrif);
        verif_listes.append(diag1D_vrif);
        verif_listes.append(diag2D_vrif);
        verif_listes.append(diag3D_vrif);
        verif_listes.append(diag4D_vrif);
        verif_listes.append(diag5D_vrif);
        verif_listes.append(diag6D_vrif);
        verif_listes.append(diag7D_vrif);
        verif_listes.append(diag1G_vrif);
        verif_listes.append(diag2G_vrif);
        verif_listes.append(diag3G_vrif);
        verif_listes.append(diag4G_vrif);
        verif_listes.append(diag5G_vrif);
        verif_listes.append(diag6G_vrif);
        verif_listes.append(diag7G_vrif);
        if(color == 1)
        {
            for(int i = 0; i<verif_listes.size();i++)
            {
                QList<QString> verif_liste = verif_listes.at(i);
                if(verif_liste.size()>3)
                {
                    for(int j=0; j<verif_liste.size()-3; j++)
                    {
                        if(verif_liste.at(j)=="red" && verif_liste.at(j+1)=="red" && verif_liste.at(j+2)=="red" && verif_liste.at(j+3)=="red")
                        {
                            k=10;
                            timer->stop();
                            winningGL = new QGridLayout();
                            winningDL = new QDialog();
                            QLabel *winRed = new QLabel("Les Rouges ont gagnés");

                            restartWin = new QPushButton("Recommencer");
                            restartWin->setMinimumSize(200,100);
                            connect(restartWin, SIGNAL(clicked()),this,SLOT(restartGame()));

                            quit = new QPushButton("quitter");
                            quit->setMinimumSize(200,100);
                            connect(quit, SIGNAL(clicked()),this,SLOT(quitGame()));

                            winningGL->addWidget(winRed,0,0);
                            winningGL->addWidget(restartWin,1,0);
                            winningGL->addWidget(quit,1,1);
                            winningDL->setLayout(winningGL);
                            winningDL->exec();
                        }
                    }
                }
            }

        }
        else{
            for(int i = 0; i<verif_listes.size();i++)
            {
                QList<QString> verif_liste = verif_listes.at(i);
                if(verif_liste.size()>3)
                {
                    for(int j=0; j<verif_liste.size()-3; j++)
                    {
                        if(verif_liste.at(j)=="yellow" && verif_liste.at(j+1)=="yellow" && verif_liste.at(j+2)=="yellow" && verif_liste.at(j+3)=="yellow")
                        {
                            k=10;
                            timer->stop();
                            winningGL = new QGridLayout();
                            winningDL = new QDialog();
                            QLabel *winRed = new QLabel("Les Jaunes ont gagnés");

                            restartWin = new QPushButton("Recommencer");
                            restartWin->setMinimumSize(200,100);
                            connect(restartWin, SIGNAL(clicked()),this,SLOT(restartGame()));

                            quit = new QPushButton("quitter");
                            quit->setMinimumSize(200,100);
                            connect(quit, SIGNAL(clicked()),this,SLOT(quitGame()));

                            winningGL->addWidget(winRed,0,0);
                            winningGL->addWidget(restartWin,1,0);
                            winningGL->addWidget(quit,1,1);
                            winningDL->setLayout(winningGL);
                            winningDL->exec();
                        }
                    }
                }
            }
            equipeJaune->setStyleSheet("QLabel {font : 20px;"
                                                "color:#8F8D0F;}");
            equipeRouge->setStyleSheet("QLabel {font: 40px;"
                                            "color:#FF0000 }");
        }


    }


void puissance4::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_A)
    {
        if (color==0)
        {
                pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
                label_img=new QLabel(this);
                label_img->setMaximumHeight(120);
                label_img->setMaximumWidth(120);
                pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                label_img->setPixmap(*pixmap_img);
                tableauLayout->addWidget(label_img,jeton_col1,1);
                if(jeton_col1==6)
                {
                    col1_vrif.append("red");
                    ligne1_vrif.replace(0,"red");
                    diag4D_vrif.replace(0,"red");
                }
                if(jeton_col1==5)
                {
                    col1_vrif.append("red");
                    ligne2_vrif.replace(0,"red");
                    diag3D_vrif.replace(0,"red");
                }
                if(jeton_col1==4)
                {
                    col1_vrif.append("red");
                    ligne3_vrif.replace(0,"red");
                    diag2D_vrif.replace(0,"red");
                }
                if(jeton_col1==3)
                {
                    col1_vrif.append("red");
                    ligne4_vrif.replace(0,"red");
                    diag1G_vrif.replace(3,"red");
                    diag1D_vrif.replace(0,"red");
                }
                if(jeton_col1==2)
                {
                    col1_vrif.append("red");
                    ligne5_vrif.replace(0,"red");
                    diag2G_vrif.replace(4,"red");
                }
                if(jeton_col1==1)
                {
                    col1_vrif.append("red");
                    ligne6_vrif.replace(0,"red");
                    diag3G_vrif.replace(5,"red");
                }
                if(jeton_col1==0)
                {
                    col1_vrif.append("red");
                    ligne7_vrif.replace(0,"red");
                    diag4G_vrif.replace(6,"red");
                }
                jeton_col1--;
                changementJoueur();
                verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col1,1);
            if(jeton_col1==6)
            {
                col1_vrif.append("yellow");
                ligne1_vrif.replace(0,"yellow");
                diag4D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==5)
            {
                col1_vrif.append("yellow");
                ligne2_vrif.replace(0,"yellow");
                diag3D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==4)
            {
                col1_vrif.append("yellow");
                ligne3_vrif.replace(0,"yellow");
                diag2D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==3)
            {
                col1_vrif.append("yellow");
                ligne4_vrif.replace(0,"yellow");
                diag1G_vrif.replace(3,"yellow");
                diag1D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==2)
            {
                col1_vrif.append("yellow");
                ligne5_vrif.replace(0,"yellow");
                diag2G_vrif.replace(4,"yellow");
            }
            if(jeton_col1==1)
            {
                col1_vrif.append("yellow");
                ligne6_vrif.replace(0,"yellow");
                diag3G_vrif.replace(5,"yellow");
            }
            if(jeton_col1==0)
            {
                col1_vrif.append("yellow");
                ligne7_vrif.replace(0,"yellow");
                diag4G_vrif.replace(6,"yellow");
            }
            jeton_col1--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_Z)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col2,2);
            if(jeton_col2==6)
            {
                col2_vrif.append("red");
                ligne1_vrif.replace(1,"red");
                diag5D_vrif.replace(0,"red");
            }
            if(jeton_col2==5)
            {
                col2_vrif.append("red");
                ligne2_vrif.replace(1,"red");
                diag4D_vrif.replace(1,"red");
            }
            if(jeton_col2==4)
            {
                col2_vrif.append("red");
                ligne3_vrif.replace(1,"red");
                diag3D_vrif.replace(1,"red");
                diag1G_vrif.replace(2,"red");
            }
            if(jeton_col2==3)
            {
                col2_vrif.append("red");
                ligne4_vrif.replace(1,"red");
                diag2D_vrif.replace(1,"red");
                diag2G_vrif.replace(3,"red");
            }
            if(jeton_col2==2)
            {
                col2_vrif.append("red");
                ligne5_vrif.replace(1,"red");
                diag1D_vrif.replace(1,"red");
                diag3G_vrif.replace(4,"red");
            }
            if(jeton_col2==1)
            {
                col2_vrif.append("red");
                ligne6_vrif.replace(1,"red");
                diag4G_vrif.replace(5,"red");
            }
            if(jeton_col2==0)
            {
                col2_vrif.append("red");
                ligne7_vrif.replace(1,"red");
                diag5G_vrif.replace(5,"red");
            }
            jeton_col2--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col2,2);
            if(jeton_col2==6)
            {
                col2_vrif.append("yellow");
                ligne1_vrif.replace(1,"yellow");
                diag5D_vrif.replace(0,"yellow");
            }
            if(jeton_col2==5)
            {
                col2_vrif.append("yellow");
                ligne2_vrif.replace(1,"yellow");
                diag4D_vrif.replace(1,"yellow");
            }
            if(jeton_col2==4)
            {
                col2_vrif.append("yellow");
                ligne3_vrif.replace(1,"yellow");
                diag3D_vrif.replace(1,"yellow");
                diag1G_vrif.replace(2,"yellow");
            }
            if(jeton_col2==3)
            {
                col2_vrif.append("yellow");
                ligne4_vrif.replace(1,"yellow");
                diag2D_vrif.replace(1,"yellow");
                diag2G_vrif.replace(3,"yellow");
            }
            if(jeton_col2==2)
            {
                col2_vrif.append("yellow");
                ligne5_vrif.replace(1,"yellow");
                diag1D_vrif.replace(1,"yellow");
                diag3G_vrif.replace(4,"yellow");
            }
            if(jeton_col2==1)
            {
                col2_vrif.append("yellow");
                ligne6_vrif.replace(1,"yellow");
                diag4G_vrif.replace(5,"yellow");
            }
            if(jeton_col2==0)
            {
                col2_vrif.append("yellow");
                ligne7_vrif.replace(1,"yellow");
                diag5G_vrif.replace(5,"yellow");
            }
            jeton_col2--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_E)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col3,3);
            if(jeton_col3==6)
            {
                col3_vrif.append("red");
                ligne1_vrif.replace(2,"red");
                diag6D_vrif.replace(0,"red");
            }
            if(jeton_col3==5)
            {
                col3_vrif.append("red");
                ligne2_vrif.replace(2,"red");
                diag5D_vrif.replace(1,"red");
                diag1G_vrif.replace(1,"red");
            }
            if(jeton_col3==4)
            {
                col3_vrif.append("red");
                ligne3_vrif.replace(2,"red");
                diag4D_vrif.replace(2,"red");
                diag2G_vrif.replace(2,"red");
            }
            if(jeton_col3==3)
            {
                col3_vrif.append("red");
                ligne4_vrif.replace(2,"red");
                diag3D_vrif.replace(2,"red");
                diag3G_vrif.replace(3,"red");
            }
            if(jeton_col3==2)
            {
                col3_vrif.append("red");
                ligne5_vrif.replace(2,"red");
                diag2D_vrif.replace(2,"red");
                diag4G_vrif.replace(4,"red");
            }
            if(jeton_col3==1)
            {
                col3_vrif.append("red");
                ligne6_vrif.replace(2,"red");
                diag1D_vrif.replace(2,"red");
                diag5G_vrif.replace(4,"red");
            }
            if(jeton_col3==0)
            {
                col3_vrif.append("red");
                ligne7_vrif.replace(2,"red");
                diag5G_vrif.replace(4,"red");
            }
            jeton_col3--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col3,3);
            if(jeton_col3==6)
            {
                col3_vrif.append("yellow");
                ligne1_vrif.replace(2,"yellow");
                diag6D_vrif.replace(0,"yellow");
            }
            if(jeton_col3==5)
            {
                col3_vrif.append("yellow");
                ligne2_vrif.replace(2,"yellow");
                diag5D_vrif.replace(1,"yellow");
                diag1G_vrif.replace(1,"yellow");
            }
            if(jeton_col3==4)
            {
                col3_vrif.append("yellow");
                ligne3_vrif.replace(2,"yellow");
                diag4D_vrif.replace(2,"yellow");
                diag2G_vrif.replace(2,"yellow");
            }
            if(jeton_col3==3)
            {
                col3_vrif.append("yellow");
                ligne4_vrif.replace(2,"yellow");
                diag3D_vrif.replace(2,"yellow");
                diag3G_vrif.replace(3,"yellow");
            }
            if(jeton_col3==2)
            {
                col3_vrif.append("yellow");
                ligne5_vrif.replace(2,"yellow");
                diag2D_vrif.replace(2,"yellow");
                diag4G_vrif.replace(4,"yellow");
            }
            if(jeton_col3==1)
            {
                col3_vrif.append("yellow");
                ligne6_vrif.replace(2,"yellow");
                diag1D_vrif.replace(2,"yellow");
                diag5G_vrif.replace(4,"yellow");
            }
            if(jeton_col3==0)
            {
                col3_vrif.append("yellow");
                ligne7_vrif.replace(2,"yellow");
                diag5G_vrif.replace(4,"yellow");
            }
            jeton_col3--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_R)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col4,4);
            if(jeton_col4==6)
            {
                col4_vrif.append("red");
                ligne1_vrif.replace(3,"red");
                diag1G_vrif.replace(0,"red");
                diag7D_vrif.replace(0,"red");
            }
            if(jeton_col4==5)
            {
                col4_vrif.append("red");
                ligne2_vrif.replace(3,"red");
                diag2G_vrif.replace(1,"red");
                diag6D_vrif.replace(1,"red");
            }
            if(jeton_col4==4)
            {
                col4_vrif.append("red");
                ligne3_vrif.replace(3,"red");
                diag3G_vrif.replace(2,"red");
                diag5D_vrif.replace(2,"red");
            }
            if(jeton_col4==3)
            {
                col4_vrif.append("red");
                ligne4_vrif.replace(3,"red");
                diag4G_vrif.replace(3,"red");
                diag4D_vrif.replace(3,"red");
            }
            if(jeton_col4==2)
            {
                col4_vrif.append("red");
                ligne5_vrif.replace(3,"red");
                diag5G_vrif.replace(3,"red");
                diag3D_vrif.replace(3,"red");
            }
            if(jeton_col4==1)
            {
                col4_vrif.append("red");
                ligne6_vrif.replace(3,"red");
                diag6G_vrif.replace(3,"red");
                diag2D_vrif.replace(3,"red");
            }
            if(jeton_col4==0)
            {
                col4_vrif.append("red");
                ligne4_vrif.replace(3,"red");
                diag7G_vrif.replace(3,"red");
                diag1D_vrif.replace(3,"red");
            }
            jeton_col4--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col4,4);
            if(jeton_col4==6)
            {
                col4_vrif.append("yellow");
                ligne1_vrif.replace(3,"yellow");
                diag1G_vrif.replace(0,"yellow");
                diag7D_vrif.replace(0,"yellow");
            }
            if(jeton_col4==5)
            {
                col4_vrif.append("yellow");
                ligne2_vrif.replace(3,"yellow");
                diag2G_vrif.replace(1,"yellow");
                diag6D_vrif.replace(1,"yellow");
            }
            if(jeton_col4==4)
            {
                col4_vrif.append("yellow");
                ligne3_vrif.replace(3,"yellow");
                diag3G_vrif.replace(2,"yellow");
                diag5D_vrif.replace(2,"yellow");
            }
            if(jeton_col4==3)
            {
                col4_vrif.append("yellow");
                ligne4_vrif.replace(3,"yellow");
                diag4G_vrif.replace(3,"yellow");
                diag4D_vrif.replace(3,"yellow");
            }
            if(jeton_col4==2)
            {
                col4_vrif.append("yellow");
                ligne5_vrif.replace(3,"yellow");
                diag5G_vrif.replace(3,"yellow");
                diag3D_vrif.replace(3,"yellow");
            }
            if(jeton_col4==1)
            {
                col4_vrif.append("yellow");
                ligne6_vrif.replace(3,"yellow");
                diag6G_vrif.replace(3,"yellow");
                diag2D_vrif.replace(3,"yellow");
            }
            if(jeton_col4==0)
            {
                col4_vrif.append("yellow");
                ligne4_vrif.replace(3,"yellow");
                diag7G_vrif.replace(3,"yellow");
                diag1D_vrif.replace(3,"yellow");
            }
            jeton_col4--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_T)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col5,5);
            if(jeton_col5==6)
            {
                col5_vrif.append("red");
                ligne1_vrif.replace(4,"red");
                diag2G_vrif.replace(0,"red");
            }
            if(jeton_col5==5)
            {
                col5_vrif.append("red");
                ligne2_vrif.replace(4,"red");
                diag3G_vrif.replace(1,"red");
                diag7D_vrif.replace(1,"red");
            }
            if(jeton_col5==4)
            {
                col5_vrif.append("red");
                ligne3_vrif.replace(4,"red");
                diag4G_vrif.replace(2,"red");
                diag6D_vrif.replace(2,"red");
            }
            if(jeton_col5==3)
            {
                col5_vrif.append("red");
                ligne4_vrif.replace(4,"red");
                diag5G_vrif.replace(2,"red");
                diag5D_vrif.replace(3,"red");
            }
            if(jeton_col5==2)
            {
                col5_vrif.append("red");
                ligne5_vrif.replace(4,"red");
                diag6G_vrif.replace(2,"red");
                diag4D_vrif.replace(4,"red");
            }
            if(jeton_col5==1)
            {
                col5_vrif.append("red");
                ligne6_vrif.replace(4,"red");
                diag7G_vrif.replace(2,"red");
                diag3D_vrif.replace(4,"red");
            }
            if(jeton_col5==0)
            {
                col5_vrif.append("red");
                ligne7_vrif.replace(4,"red");
                diag2D_vrif.replace(4,"red");
            }
            jeton_col5--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col5,5);
            if(jeton_col5==6)
            {
                col5_vrif.append("yellow");
                ligne1_vrif.replace(4,"yellow");
                diag2G_vrif.replace(0,"yellow");
            }
            if(jeton_col5==5)
            {
                col5_vrif.append("yellow");
                ligne2_vrif.replace(4,"yellow");
                diag3G_vrif.replace(1,"yellow");
                diag7D_vrif.replace(1,"yellow");
            }
            if(jeton_col5==4)
            {
                col5_vrif.append("yellow");
                ligne3_vrif.replace(4,"yellow");
                diag4G_vrif.replace(2,"yellow");
                diag6D_vrif.replace(2,"yellow");
            }
            if(jeton_col5==3)
            {
                col5_vrif.append("yellow");
                ligne4_vrif.replace(4,"yellow");
                diag5G_vrif.replace(2,"yellow");
                diag5D_vrif.replace(3,"yellow");
            }
            if(jeton_col5==2)
            {
                col5_vrif.append("yellow");
                ligne5_vrif.replace(4,"yellow");
                diag6G_vrif.replace(2,"yellow");
                diag4D_vrif.replace(4,"yellow");
            }
            if(jeton_col5==1)
            {
                col5_vrif.append("yellow");
                ligne6_vrif.replace(4,"yellow");
                diag7G_vrif.replace(2,"yellow");
                diag3D_vrif.replace(4,"yellow");
            }
            if(jeton_col5==0)
            {
                col5_vrif.append("yellow");
                ligne7_vrif.replace(4,"yellow");
                diag2D_vrif.replace(4,"yellow");
            }
            jeton_col5--;
            changementJoueur();
            verification();

        }
    }
    if (nbPanier ==7)
    {
        if (event->key() == Qt::Key_Y)
        {
            if (color==0)
            {
                pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
                label_img=new QLabel(this);
                label_img->setMaximumHeight(120);
                label_img->setMaximumWidth(120);
                pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                label_img->setPixmap(*pixmap_img);
                tableauLayout->addWidget(label_img,jeton_col6,6);
                if(jeton_col6==6)
                {
                    col6_vrif.append("red");
                    ligne1_vrif.replace(5,"red");
                    diag3G_vrif.replace(0,"red");
                }
                if(jeton_col6==5)
                {
                    col6_vrif.append("red");
                    ligne2_vrif.replace(5,"red");
                    diag4G_vrif.replace(1,"red");
                }
                if(jeton_col6==4)
                {
                    col6_vrif.append("red");
                    ligne3_vrif.replace(5,"red");
                    diag7D_vrif.replace(2,"red");
                    diag5G_vrif.replace(1,"red");
                }
                if(jeton_col6==3)
                {
                    col6_vrif.append("red");
                    ligne4_vrif.replace(5,"red");
                    diag6D_vrif.replace(3,"red");
                    diag5G_vrif.replace(1,"red");
                }
                if(jeton_col6==2)
                {
                    col6_vrif.append("red");
                    ligne5_vrif.replace(5,"red");
                    diag5D_vrif.replace(4,"red");
                    diag7G_vrif.replace(1,"red");
                }
                if(jeton_col6==1)
                {
                    col6_vrif.append("red");
                    ligne6_vrif.replace(5,"red");
                    diag4D_vrif.replace(5,"red");
                }
                if(jeton_col6==0)
                {
                    col6_vrif.append("red");
                    ligne7_vrif.replace(5,"red");
                    diag3D_vrif.replace(5,"red");
                }
                jeton_col6--;
                changementJoueur();
                verification();

            }
            else
            {
                pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
                label_img=new QLabel(this);
                label_img->setMaximumHeight(120);
                label_img->setMaximumWidth(120);
                pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                label_img->setPixmap(*pixmap_img);
                tableauLayout->addWidget(label_img,jeton_col6,6);

                if(jeton_col6==6)
                {
                    col6_vrif.append("yellow");
                    ligne1_vrif.replace(5,"yellow");
                    diag3G_vrif.replace(0,"yellow");
                }
                if(jeton_col6==5)
                {
                    col6_vrif.append("yellow");
                    ligne2_vrif.replace(5,"yellow");
                    diag4G_vrif.replace(1,"yellow");
                }
                if(jeton_col6==4)
                {
                    col6_vrif.append("yellow");
                    ligne3_vrif.replace(5,"yellow");
                    diag7D_vrif.replace(2,"yellow");
                    diag5G_vrif.replace(1,"yellow");
                }
                if(jeton_col6==3)
                {
                    col6_vrif.append("yellow");
                    ligne4_vrif.replace(5,"yellow");
                    diag6D_vrif.replace(3,"yellow");
                    diag5G_vrif.replace(1,"yellow");
                }
                if(jeton_col6==2)
                {
                    col6_vrif.append("yellow");
                    ligne5_vrif.replace(5,"yellow");
                    diag5D_vrif.replace(4,"yellow");
                    diag7G_vrif.replace(1,"yellow");
                }
                if(jeton_col6==1)
                {
                    col6_vrif.append("yellow");
                    ligne6_vrif.replace(5,"yellow");
                    diag4D_vrif.replace(5,"yellow");
                }
                if(jeton_col6==0)
                {
                    col6_vrif.append("yellow");
                    ligne7_vrif.replace(5,"yellow");
                    diag3D_vrif.replace(5,"yellow");
                }
                jeton_col6--;
                changementJoueur();
                verification();
            }
        }
        if (event->key() == Qt::Key_U)
            {
                if (color==0)
                {
                    pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
                    label_img=new QLabel(this);
                    label_img->setMaximumHeight(120);
                    label_img->setMaximumWidth(120);
                    pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                    label_img->setPixmap(*pixmap_img);
                    tableauLayout->addWidget(label_img,jeton_col7,7);
                    if(jeton_col7==6)
                    {
                        col7_vrif.append("red");
                        ligne1_vrif.replace(6,"red");
                        diag4G_vrif.replace(0,"red");
                    }
                    if(jeton_col7==5)
                    {
                        col7_vrif.append("red");
                        ligne2_vrif.replace(6,"red");
                        diag5G_vrif.replace(0,"red");
                    }
                    if(jeton_col7==4)
                    {
                        col7_vrif.append("red");
                        ligne3_vrif.replace(6,"red");
                        diag6G_vrif.replace(0,"red");
                    }
                    if(jeton_col7==3)
                    {
                        col7_vrif.append("red");
                        ligne4_vrif.replace(6,"red");
                        diag6G_vrif.replace(0,"red");
                        diag7D_vrif.replace(3,"red");
                    }
                    if(jeton_col7==2)
                    {
                        col7_vrif.append("red");
                        ligne5_vrif.replace(6,"red");
                        diag6D_vrif.replace(4,"red");
                    }
                    if(jeton_col7==1)
                    {
                        col7_vrif.append("red");
                        ligne6_vrif.replace(6,"red");
                        diag5D_vrif.replace(5,"red");
                    }
                    if(jeton_col7==0)
                    {
                        col7_vrif.append("red");
                        ligne7_vrif.replace(6,"red");
                        diag4G_vrif.replace(6,"red");
                    }
                    jeton_col7--;
                    changementJoueur();
                    verification();

                }
                else
                {
                    pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
                    label_img=new QLabel(this);
                    label_img->setMaximumHeight(120);
                    label_img->setMaximumWidth(120);
                    pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                    label_img->setPixmap(*pixmap_img);
                    tableauLayout->addWidget(label_img,jeton_col7,7);
                    if(jeton_col7==6)
                    {
                        col7_vrif.append("yellow");
                        ligne1_vrif.replace(6,"yellow");
                        diag4G_vrif.replace(0,"yellow");
                    }
                    if(jeton_col7==5)
                    {
                        col7_vrif.append("yellow");
                        ligne2_vrif.replace(6,"yellow");
                        diag5G_vrif.replace(0,"yellow");
                    }
                    if(jeton_col7==4)
                    {
                        col7_vrif.append("yellow");
                        ligne3_vrif.replace(6,"yellow");
                        diag6G_vrif.replace(0,"yellow");
                    }
                    if(jeton_col7==3)
                    {
                        col7_vrif.append("yellow");
                        ligne4_vrif.replace(6,"yellow");
                        diag6G_vrif.replace(0,"yellow");
                        diag7D_vrif.replace(3,"yellow");
                    }
                    if(jeton_col7==2)
                    {
                        col7_vrif.append("yellow");
                        ligne5_vrif.replace(6,"yellow");
                        diag6D_vrif.replace(4,"yellow");
                    }
                    if(jeton_col7==1)
                    {
                        col7_vrif.append("yellow");
                        ligne6_vrif.replace(6,"yellow");
                        diag5D_vrif.replace(5,"yellow");
                    }
                    if(jeton_col7==0)
                    {
                        col7_vrif.append("yellow");
                        ligne7_vrif.replace(6,"yellow");
                        diag4G_vrif.replace(6,"yellow");
                    }
                    jeton_col7--;
                    changementJoueur();
                    verification();
                }
            }
    }
}
void puissance4::changementJoueur()
{
    if(color==0)
    {
        equipeJaune->setStyleSheet("QLabel {font : 40px;"
                                            "color:#F5F207; background-color : #99CBFF;}");
        equipeRouge->setStyleSheet("QLabel {font: 20px;"
                                        "color:#A40B0B ; background-color : #99CBFF;}");
        player->setStyleSheet("QLabel {font : 45px;"
                              "background-color : #99CBFF; color : #F5F207;}");
        color=1;
    }
    else
    {
        equipeJaune->setStyleSheet("QLabel {font : 20px;"
                                            "color:#8F8D0F; background-color : #99CBFF;}");
        equipeRouge->setStyleSheet("QLabel {font: 40px;"
                                        "color:#FF0000; background-color : #99CBFF; }");
        player->setStyleSheet("QLabel {font : 45px;"
                              "background-color : #99CBFF; color : #FF0000;}");

        color=0;
    }
    if(numberTimer!=0)
    {
        tmps = settings.envoieTemps();
        numberTimer->setStyleSheet("background-color: #99CBFF; color: green;");
        numberTimer->display(tmps);
        if (playerlist == players.length()-1)
        {
            playerlist=0;
            player->setText(players[playerlist]);
        }
        else
        {
            ++playerlist;
            player->setText(players[playerlist]);
        }

    }

}
void puissance4::menupause()
{
    k=9;
    timer->stop();
    pauseButton = new QGridLayout();
    pause = new QDialog();

    quit = new QPushButton("Quitter");
    quit->setMinimumSize(200,100);
    connect(quit, SIGNAL(clicked()),this,SLOT(quitGame()));

    resume = new QPushButton("Reprendre");
    resume->setMinimumSize(200,100);
    connect(resume, SIGNAL(clicked()),this,SLOT(resumeGame()));

    restart = new QPushButton("Recommencer");
    restart->setMinimumSize(200,100);
    connect(restart, SIGNAL(clicked()),this,SLOT(restartGame()));

    pauseButton->addWidget(quit,2,0);
    pauseButton->addWidget(resume,0,0);
    pauseButton->addWidget(restart,1,0);
    pause->setLayout(pauseButton);
    pause->exec();


}
void puissance4::resumeGame()
{
    pause->hide();
    timer->start();
}
void puissance4::quitGame()
{
    clearList();
    for (int i = 0; i < tableauLayout->count(); i++)
    {
       tableauLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < equipeLayout->count(); i++)
    {
       equipeLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < boutonLayout->count(); i++)
    {
       boutonLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < timerjoueurLayout->count(); i++)
    {
       timerjoueurLayout->itemAt(i)->widget()->deleteLater();
    }
    if(k==10)
    {
        winningDL->hide();
    }
    else
    {
        pause->hide();
    }
    mainLayout->deleteLater();
    tmps=settings.envoieTemps();
    ui->LeTout->setStyleSheet("background-color:rgb(255,255,255)");

    ui->PlayPB->show();
    ui->QuitPB->show();
    ui->ResultPB->show();
    ui->SettingsPB->show();

}
void puissance4::restartGame()
{


    for (int i = 0; i < tableauLayout->count(); i++)
    {
       tableauLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < equipeLayout->count(); i++)
    {
       equipeLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < boutonLayout->count(); i++)
    {
       boutonLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < timerjoueurLayout->count(); i++)
    {
       timerjoueurLayout->itemAt(i)->widget()->deleteLater();
    }
    if(k==10)
    {
        winningDL->hide();
    }
    else
    {
        pause->hide();
    }
    clearList();
    createPlateau();

    timer->start();
    numberTimer->display(tmps);
    qDebug() << playerlist;
}


void puissance4::timerSlot()
{
    --tmps;
    if(tmps==0)
    {
        numberTimer->setStyleSheet("background-color: #ED0000; color: #6D071A;");
    }
    if (tmps == -1)
    {
        changementJoueur();
    }
    numberTimer->display(tmps);
}
void puissance4::clearList()
{
    col1_vrif.clear();
    col2_vrif.clear();
    col3_vrif.clear();
    col4_vrif.clear();
    col5_vrif.clear();
    col6_vrif.clear();
    col7_vrif.clear();
    ligne1_vrif = {"","","","","","",""};
    ligne2_vrif = {"","","","","","",""};
    ligne3_vrif = {"","","","","","",""};
    ligne4_vrif = {"","","","","","",""};
    ligne5_vrif = {"","","","","","",""};
    ligne6_vrif = {"","","","","","",""};
    ligne7_vrif = {"","","","","","",""};
    diag1D_vrif = {"","","",""};
    diag2D_vrif = {"","","","",""};
    diag3D_vrif = {"","","","","",""};
    diag4D_vrif = {"","","","","","",""};
    diag5D_vrif = {"","","","","",""};
    diag6D_vrif = {"","","","",""};
    diag7D_vrif = {"","","",""};
    diag1G_vrif = {"","","",""};
    diag2G_vrif = {"","","","",""};
    diag3G_vrif = {"","","","","",""};
    diag4G_vrif = {"","","","","","",""};
    diag5G_vrif = {"","","","","",""};
    diag6G_vrif = {"","","","",""};
    diag7G_vrif = {"","","",""};
    players.clear();
    jeton_col1 = 6;
    jeton_col2 = 6;
    jeton_col3 = 6;
    jeton_col4 = 6;
    jeton_col5 = 6;
    jeton_col6 = 6;
    jeton_col7 = 6;

}

