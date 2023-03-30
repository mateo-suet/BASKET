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

    void keyPressEvent(QKeyEvent * event);

    void destroyCombox();

    void Ecrire();

    void lesnoms_bdd();

    void compteur_de_widget();

public slots:
    void le_bouton_ok();

    void le_bouton_quitter();

    void le_bouton_default();

    void le_bouton_valider();

    void le_bouton_ajouter();

    void le_bouton_ajouter2();

    void le_bouton_supprimer1();

    void le_bouton_supprimer2();

    void le_bouton_changer_mdp();

    void le_bouton_supprimer_joueur();

    bool le_bouton_new_player();


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
    QPushButton *Bouton_supprimer1;
    QPushButton *Bouton_supprimer2;
    QPushButton *Bouton_changer_mdp;
    QPushButton *Bouton_new_player;
    QPushButton *Bouton_sup_joueur;
    QSpinBox *tire;

    QLabel *titre;
    QLabel *titre1;
    QLabel *titre_nb_tire;
    QLabel *titreBS;
    QLabel *titre_mdp;
    QLabel *titre_new_player;
    QLabel *titre_sup_player;

    QGridLayout *lay;

    QButtonGroup *Groupe;

    QWidget *fenetre_mdp;

    QLineEdit *ligne_mdp;
    QLineEdit *ligne_new_player;
    QLineEdit *Nom_Equipe_1;
    QLineEdit *Nom_Equipe_2;

    QList<QString> LesNoms_combobox;

    QComboBox *combo_sup;
    QComboBox *combo;

    QDate *laDate;

    int i; // chiffre combobox
    int j;
    int f;

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
};

#endif // PUISSANCE4_H
