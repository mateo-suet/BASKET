#include "parametre.h"
#include "ui_parametre.h"

Parametre::Parametre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametre)
{
    ui->setupUi(this);

    connect(ui->bouton_changez_mdp, &QPushButton::clicked, this, &Parametre::changer_le_mdp);
    connect(ui->Valider, &QPushButton::clicked, this, &Parametre::valider);
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
