#ifndef BDD_H
#define BDD_H

#include <QMainWindow>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlQuery>

class BDD : public QObject
{
    Q_OBJECT

 public:
    BDD();
    //~BDD();

    bool verifMotDePasse(QString mdp);

  private:
    QSqlDatabase m_db;

};

#endif // BDD_H
