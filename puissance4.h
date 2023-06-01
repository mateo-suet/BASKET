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
#include <QKeyEvent>
#include <QList>
#include <QSpinBox>
#include <QDate>
#include "BDD.h"
#include "new_mdp.h"
#include "equipe.h"
#include "parametre.h"
#include "mdp.h"

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

//    void keyPressEvent(QKeyEvent * event);

    void lesnoms_bdd();

    void ajout_bdd_historique();

public slots:
    void le_bouton_ok();

    bool verifMDP();

    bool nouveau_mdp();

    void fin_de_ligne();

    void les_joueurs();

    void les_new_joueur();

    void suppresion();

    void ajout_j();

private:
    Ui::puissance4 *ui;



    QButtonGroup *Groupe;

    int position_combo;


    QLineEdit *ligne_new_player;
    QLineEdit *Nom_Equipe_1;
    QLineEdit *Nom_Equipe_2;

    QList<QString> LesNoms_combobox;
    QList<QString> les_noms_historique_bdd;

    QComboBox *combo_sup;
    QComboBox *combo;

    QDate *laDate;


    int b_equipe_1=15;
    int b_equipe_2=15;

    int b_sup_equipe_1=16;
    int b_sup_equipe_2=16;

    int x = 0;

    BDD ma_bdd;
    BDD ma_bdd_new;
    BDD sup_joueur;

    new_mdp le_new;

    Equipe les_equipes;

    Parametre settings;

    MDP pages;

};

#endif // PUISSANCE4_H
