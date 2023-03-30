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
          qDebug() << "BDD OPEN";
    }
}

bool BDD::verifMotDePasse(QString mdp)
{
    bool success=false;

    QSqlQuery query;
    query.prepare("SELECT MDP FROM Entraineur");
    query.exec();
    while(query.next()){
        if(mdp ==query.value(0)){
            success = true;

        }
    }
    //Faire requete aupres de la BDD pour savoir si mdp est correct


    return success;
}

bool BDD::verifNomJoueur(QString joueur)
{
    bool success=false;

    QSqlQuery query;
    query.prepare("SELECT Joeur FROM Historique");
    query.exec();
    while(query.next()){
        if(joueur ==query.value(0)){
            success = true;

        }
    }
    //Faire requete aupres de la BDD pour savoir si mdp est correct


    return success;
}

