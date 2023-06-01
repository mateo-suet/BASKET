#include "equipe.h"
#include "ui_equipe.h"

Equipe::Equipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Equipe)
{
    ui->setupUi(this);
    connect(ui->Valider, &QPushButton::clicked, this, &Equipe::les_nouveau_j);
    connect(ui->Supprimer, &QPushButton::clicked, this, &Equipe::sup_joueur);
    connect(ui->PLUS_1, &QPushButton::clicked, this, &Equipe::lancement_joueur);
    connect(ui->PLUS_2, &QPushButton::clicked, this, &Equipe::lancement_joueur_2);
    connect(ui->MOINS_1, &QPushButton::clicked, this, &Equipe::supprimer_combobox_equipe1);
    connect(ui->MOINS_2, &QPushButton::clicked, this, &Equipe::supprimer_combobox_equipe2);
    connect(ui->Bouton_Valider, &QPushButton::clicked, this, &Equipe::ajout_joueur_bdd);
    //this->lancement();

    //connect(this, &Equipe::nouveau_combo_1, this, &Equipe::plus_joueur_1);
}

Equipe::~Equipe()
{
    delete ui;
}

QString Equipe::ajouter_joueur()
{
    le_nouveau = ui->ligne_nouveau_joueur->text();
    return le_nouveau;
}

QString Equipe::supprimer_joueur()
{
    le_sortant = ui->combo_sup->currentText();
    return le_sortant;
}

int Equipe::compter_combobox_1p()
{
    position = ui->lay_equipe1->count();
    return position;
}

int Equipe::compter_combobox_2p()
{
    position_2 = ui->lay_equipe2->count();
    return position_2;
}


bool Equipe::recup_les_noms(QList<QString>& noms)
{

    noms_des_joueurs = noms;
    if(i == 0)
    {
    ++i;
    ui->combo_sup->addItems(noms);
    }
    combo_1->addItems(noms);
    combo_2->addItems(noms);

}


void Equipe::les_nouveau_j()
{
    emit new_player();

}

void Equipe::sup_joueur()
{
    emit out_player();
}

void Equipe::lancement()
{    
    //qDebug() << "lala";
    emit recup_noms();
}

void Equipe::lancement_joueur()
{
    if(compter_combobox_1p() < 11)
    {
        combo_1 = new QComboBox();
        position_j1 = compter_combobox_1p()+1;
        recup_les_noms(noms_des_joueurs);
        ui->lay_equipe1->addWidget(combo_1,position_j1,0);
    }
    else
    {
        --position_j1;
    }
}

void Equipe::lancement_joueur_2()
{
    if(compter_combobox_2p() < 11)
    {
        combo_2 = new QComboBox();
        position_j2 = compter_combobox_2p()+1;
        recup_les_noms(noms_des_joueurs);
        ui->lay_equipe2->addWidget(combo_2, position_j2, 0);
    }
    else
    {
        --position_j2;
    }
}

void Equipe::supprimer_combobox_equipe1()
{
    //position = compter_combobox_1p();
    qDebug() << "position" << position;
    qDebug() << "1";
    if(position > 1)
    {
        QLayoutItem* item = ui->lay_equipe1->itemAt(position);
        qDebug() << "2";
        ui->lay_equipe1->removeItem(item);
        qDebug() << "3";
        qDebug() << position_j1;
        QWidget* widget = item->widget();
        qDebug() << "4";

        if(widget)
        {
            qDebug() << "6";
            delete widget;
            --position;
        }
    }
}

void Equipe::supprimer_combobox_equipe2()
{
    //position_2 = compter_combobox_2p();
    if(position_2 > 1)
    {
        QLayoutItem* item = ui->lay_equipe2->itemAt(position_2);
        ui->lay_equipe2->removeItem(item);
        QWidget* widget = item->widget();
        qDebug() <<"position" << position_2 ;
        if(widget)
        {
            delete widget;
            --position_2;
        }
    }
}

void Equipe::message()
{
    QMessageBox::information(this,"ajout","Ajout du joueur valider");
    ui->ligne_nouveau_joueur->clear();
}

void Equipe::ajout_joueur_bdd()
{
    emit ajout_bdd();
}

void Equipe::nom_historique(QList<QString>& noms_historique)
{
    noms_historique << combo_1->currentText();
    qDebug() << "les" << noms_historique;
    //noms_historique << combo_2->currentText();
    //qDebug() << "ici" << noms_historique;
}
