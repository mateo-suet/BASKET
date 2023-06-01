#include "new_mdp.h"
#include "ui_new_mdp.h"
//#include "BDD.h"
new_mdp::new_mdp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_mdp)
{
    ui->setupUi(this);
    connect(ui->bouton_new_mdp, &QPushButton::clicked, this, &new_mdp::le_bouton_new_mdp);
    connect(ui->ligne_new_mdp, &QLineEdit::textChanged, this, &new_mdp::ecrire);
}
bool success;
new_mdp::~new_mdp()
{
    delete ui;
}


void new_mdp::appuie_touche(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        ui->bouton_new_mdp->click();
    }
}

void new_mdp::ecrire()
{
    if((ui->ligne_new_mdp->text().length() !=0))
    {
        ui->bouton_new_mdp->setEnabled(true);
    }
    else
    {
        ui->bouton_new_mdp->setEnabled(false);
    }
}

QString new_mdp::get_new_MDP()
{
   le_nouveau_mdp = ui->ligne_new_mdp->text();
   return le_nouveau_mdp;
}


bool new_mdp::le_bouton_new_mdp()
{
    emit Sig_new_mdp();
}

void new_mdp::ligne_zero()
{
    ui->ligne_new_mdp->clear();
}
