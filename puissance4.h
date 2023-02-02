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
#include "BDD.h"
#include "new_mdp.h"

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

    QLabel *titre;
    QLabel *titre1;
    QLabel *titreBS;
    QLabel *titre_mdp;
    QLabel *teamLB;
    QLabel *team2LB;
    QLabel *titre_new_player;

    QGridLayout *lay;

    QButtonGroup *Groupe;

    QWidget *fenetre_mdp;

    QLineEdit *ligne_mdp;
    QLineEdit *ligne_new_player;

    QComboBox *combo;

    int i; // chiffre combobox
    int j;

    int b_equipe_1=15;
    int b_equipe_2=15;

    int b_sup_equipe_1=16;
    int b_sup_equipe_2=16;

    BDD ma_bdd;
    BDD new_player_bdd;

    new_mdp le_new;
};

#endif // PUISSANCE4_H
