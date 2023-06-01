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


bool BDD::verifNomJoueur(QList<QString>& joueur)
{
    bool success=false;

    QSqlQuery query;
    query.prepare("SELECT Joeur FROM Historique");
    query.exec();
    while(query.next())
    {
        if(query.isValid())
        {
            joueur<<query.value(0).toString();

            qDebug() << joueur ;
            success = true;

        }
    }
    //Faire requete aupres de la BDD pour savoir si mdp est correct


    return success;
}

bool BDD::le_mdp(QString mdp)
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

bool BDD::ajouter_mdp(QString ajout)
{
    bool success=false;

    QSqlQuery query;
    query.prepare("UPDATE Entraineur set MDP = (:MDP)");
    query.bindValue(":MDP",ajout);
    if(query.exec())
    {
        success = true;

        emit New_MDP_OK();
         qDebug() << "marche";

    }
    else
    {
        qDebug() << "pas marche";
    }
    return success;

}

bool BDD::ajouter_Joueur(QString joueurs)
{
    bool success;
    success = false;
    QSqlQuery query;
    QSqlQuery query_2;

    query_2.prepare("DELETE FROM Historique WHERE Joeur = '"+joueurs+"'");
    query.prepare("INSERT INTO Historique (Joeur) VALUES (:nom)");
    query.bindValue(":nom",joueurs);

    if(query_2.exec())
    {
        qDebug() << "c'est bon";
    }
    else
    {
        qDebug() << "c'est pas bon";
    }

    if(query.exec())
    {
        success = true;

    }
    else
    {
        qDebug() << "ça marche pas";
    }
    return success;
}

bool BDD::La_suppresion(QString player)
{
    QSqlQuery requette;
    requette.prepare("DELETE FROM Historique WHERE Joeur = '"+ player +"'");
    bool success;
    success=false;
    if(requette.exec())
    {
       success = true;
    }
    else
    {


    }
    return success;
}
