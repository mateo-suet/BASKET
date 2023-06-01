#include "mdp.h"
#include "ui_mdp.h"

MDP::MDP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MDP)
{
    ui->setupUi(this);

    connect(ui->Valider, &QPushButton::clicked, this, &MDP::valider);
}

MDP::~MDP()
{
    delete ui;
}

void MDP::valider()
{

    emit SigMDP();
}

QString MDP::getMDP()
{
    val_mdp = ui->ligne_mdp->text();
    return val_mdp;

}

void MDP::ligne_a_zero()
{
    ui->ligne_mdp->clear();
}

void MDP::message()
{
    QMessageBox::warning(this,"ERREUR","Mauvais MOT DE PASSE");
}
