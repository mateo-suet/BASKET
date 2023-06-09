#ifndef PUISSANCE4_H
#define PUISSANCE4_H

#include <QSpinBox>
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
#include <QGridLayout>
#include <QLCDNumber>
#include <QTimer>
#include "BDD.h"
#include "new_mdp.h"
#include "equipe.h"
#include "parametre.h"
#include "mdp.h"
#include "resultat.h"

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

    void quitter();

    void quitter_1();

    void quitter_2();

    void ouverture_historique();

    void quitter_tout();

    void createLayout();
    void afficherJeton();
    void createPlateau();
    void verification();
    void clearList();
    void keyPressEvent(QKeyEvent *event);
    void setBoutonLayout(QLayout *newBoutonLayout);

public slots:
    void le_bouton_ok();

    bool verifMDP();

    bool nouveau_mdp();

    void fin_de_ligne();

    void les_joueurs();

    void les_new_joueur();

    void suppresion();

    void ajout_j();



    void changementJoueur();
    void menupause();
    void resumeGame();
    void quitGame();
    void restartGame();
    void timerSlot();

private:
    Ui::puissance4 *ui;



    QButtonGroup *Groupe;

    int position_combo;


    QLineEdit *ligne_new_player;
    QLineEdit *Nom_Equipe_1;
    QLineEdit *Nom_Equipe_2;

    QList<QString> LesNoms_combobox;
    QList<QString> les_noms_historique_bdd;
    QList<QString> les_noms_historique_bdd2;

    QString un_nom;
    QString un_nom2;

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

    Resultat Historique;



    QLabel  *label_img ;
    QPixmap *pixmap_img;
    QGridLayout *winningGL;
    QGridLayout *timerjoueurLayout;
    QGridLayout *mainLayout;            //creation d'un layout
    QGridLayout *tableauLayout;
    QGridLayout *equipeLayout;
    QGridLayout *boutonLayout;
    QGridLayout *menuPauseGL;
    QLabel *equipeRouge;
    QLabel *equipeJaune;
    QPushButton *quit;
    QPushButton *resume;
    QPushButton *restart;
    QPushButton *restartWin;
    QDialog *pause;
    QDialog *winningDL;
    QGridLayout *pauseButton;
    QTimer *timer;
    QLCDNumber *numberTimer;
    QLabel *player;
    int tmps;
    int i;
    int k;
    int jeton_col1=6;
    int jeton_col2=6;
    int jeton_col3=6;
    int jeton_col4=6;
    int jeton_col5=6;
    int jeton_col6=6;
    int jeton_col7=6;
    int j;
    int color=0;
    int nbPanier;
    int playerlist;

    QList<QString> col1_vrif ;
    QList<QString> col2_vrif;
    QList<QString> col3_vrif;
    QList<QString> col4_vrif;
    QList<QString> col5_vrif;
    QList<QString> col6_vrif;
    QList<QString> col7_vrif;
    QList<QString> ligne1_vrif = {"","","","","","",""};
    QList<QString> ligne2_vrif = {"","","","","","",""};
    QList<QString> ligne3_vrif = {"","","","","","",""};
    QList<QString> ligne4_vrif = {"","","","","","",""};
    QList<QString> ligne5_vrif = {"","","","","","",""};
    QList<QString> ligne6_vrif = {"","","","","","",""};
    QList<QString> ligne7_vrif = {"","","","","","",""};
    QList<QString> diag1D_vrif = {"","","",""};
    QList<QString> diag2D_vrif = {"","","","",""};
    QList<QString> diag3D_vrif = {"","","","","",""};
    QList<QString> diag4D_vrif = {"","","","","","",""};
    QList<QString> diag5D_vrif = {"","","","","",""};
    QList<QString> diag6D_vrif = {"","","","",""};
    QList<QString> diag7D_vrif = {"","","",""};
    QList<QString> diag1G_vrif = {"","","",""};
    QList<QString> diag2G_vrif = {"","","","",""};
    QList<QString> diag3G_vrif = {"","","","","",""};
    QList<QString> diag4G_vrif = {"","","","","","",""};
    QList<QString> diag5G_vrif = {"","","","","",""};
    QList<QString> diag6G_vrif = {"","","","",""};
    QList<QString> diag7G_vrif = {"","","",""};
    QList<QString> players;
    int testest = 0;

};

#endif // PUISSANCE4_H
