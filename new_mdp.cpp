#include "new_mdp.h"
#include "ui_new_mdp.h"
//#include "BDD.h"
new_mdp::new_mdp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_mdp)
{
    ui->setupUi(this);
    connect(ui->bouton_new_mdp, SIGNAL(clicked()), this, SLOT(le_bouton_new_mdp()));
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

bool new_mdp::le_bouton_new_mdp()
{
    success = false;
    QSqlQuery query;


    query.prepare("UPDATE Entraineur set MDP = (:MDP)");
    query.bindValue(":MDP",ui->ligne_new_mdp->text());

     if(query.exec())
     {
         success = true;
         ui->ligne_new_mdp->setText("");
         QMessageBox::information(this,"nouveau mdp", "votre nouveau mdp a était valider");

         new_mdp::setVisible(false);

     }
     else
     {
         ui->ligne_new_mdp->setText("");
         QMessageBox::information(this,"nouveau mdp", "nouveau mot de passe erreur");
     }
     return success;
}
