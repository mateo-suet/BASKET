#ifndef PUISSANCE4_H
#define PUISSANCE4_H

#include <QRadioButton>
#include <QMainWindow>
#include <QWidget>
#include <QTimeEdit>
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QButtonGroup>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
//#include <QSqlQuery>
//#include <QSqlDatabase>
//#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class puissance4; }
QT_END_NAMESPACE

class puissance4 : public QMainWindow
{
    Q_OBJECT

public:
    puissance4(QWidget *parent = nullptr);
    ~puissance4();

    void on_playButton_clicked();

    void on_sett_clicked();

    void creation_des_widget();

    void la_page_mdp();

    void createCombox();

public slots:
    void le_bouton_ok();

    void le_bouton_quitter();

    void le_bouton_default();

    void le_bouton_valider();

    void le_bouton_ajouter();

    void le_bouton_ajouter2();

private:
    Ui::puissance4 *ui;

    QRadioButton *nb5;
    QRadioButton *nb7;
    QRadioButton *bson;
    QRadioButton *bsoff;

    QTimeEdit *LeTemps;

    QPushButton *Bouton_ok;
    QPushButton *Bouton_quitter;
    QPushButton *Bouton_default;
    QPushButton *Bouton_valider_mdp;
    QPushButton *Bouton_ajouter;
     QPushButton *Bouton_ajouter2;

    QLabel *titre;
    QLabel *titre1;
    QLabel *titreBS;
    QLabel *titre_mdp;
    QLabel *teamLB;
    QLabel *team2LB;

    QGridLayout *lay;

    QButtonGroup *Groupe;

    QWidget *fenetre_mdp;

    QLineEdit *ligne_mdp;

    QComboBox *combo;

    int i; // chiffre combobox
    int j;
};
#endif // PUISSANCE4_H
