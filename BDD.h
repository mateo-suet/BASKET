#ifndef BDD_H
#define BDD_H

#include <QMainWindow>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

class BDD : public QObject
{
    Q_OBJECT

 public:
     BDD();

    //~BDD();

    bool verifNomJoueur(QList<QString>& joueur);

    bool le_mdp(QString mdp);

    bool ajouter_mdp(QString ajout);

    bool ajouter_Joueur(QString joueurs);

    bool La_suppresion(QString player);

    bool ajout_joueur_party(QString joueur_equipe1);

    bool ajout_joueur_party2(QString joueur_equipe2);

  private:
    QSqlDatabase m_db;

  signals:

    void la_BDD();

    void New_MDP_OK();
};

#endif // BDD_H
