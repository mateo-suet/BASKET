#include "parametre.h"
#include "ui_parametre.h"

Parametre::Parametre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametre)
{
    ui->setupUi(this);

    connect(ui->bouton_changez_mdp, &QPushButton::clicked, this, &Parametre::changer_le_mdp);
    connect(ui->Valider, &QPushButton::clicked, this, &Parametre::valider);
    connect(ui->Quitter_1, &QPushButton::clicked, this, &Parametre::quitter);
}

Parametre::~Parametre()
{
    delete ui;
}

void Parametre::changer_le_mdp()
{
    emit s_changement_mdp();
}

void Parametre::valider()
{
    emit s_valider();
}

void Parametre::quitter()
{
    emit s_quitter();
}

int Parametre::envoieTemps()
{
    tempsTir = ui->temps->value();
    return tempsTir;
}

int Parametre::nombrePanier()
{
    if(ui->panier_5->isChecked())
    {
        nbPaniers = 5;
        return nbPaniers;
    }
    else
    {
        nbPaniers = 7;
        return nbPaniers;

    }
}

