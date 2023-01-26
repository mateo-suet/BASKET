#include "puissance4.h"
#include "BDD.h"

BDD::BDD()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("Basket.db");
    m_db.open();
    if (!m_db.open())
       {
          qDebug() << "Erreur de connection a la BDD";
       }
       else
       {
          qDebug() << "BDD OK";
    }
}

bool BDD::verifMotDePasse(QString mdp)
{
    bool success=false;
    QSqlQuery requete("SELECT MDP FROM Entraineur");
    requete.value(mdp);
    qDebug() << mdp;

    //Faire requete aupres de la BDD pour savoir si mdp est correct
    //


    return success;
}


bool success;
