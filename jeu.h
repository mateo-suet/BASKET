#ifndef JEU_H
#define JEU_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QFont>
#include <QHBoxLayout>
#include <QRect>
#include <QComboBox>
#include <QFontComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QList>
#include <QGroupBox>
#include <QTimer>
#include <QLCDNumber>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class jeu; }
QT_END_NAMESPACE

class jeu : public QMainWindow
{
    Q_OBJECT

public:
    jeu(QWidget *parent = nullptr);
    ~jeu();
    void on_playButton_clicked();
    void createLayout();
    void afficherJeton();
    void createPlateau();
    void verification();
    void clearList();
    void keyPressEvent(QKeyEvent *event);



    void setBoutonLayout(QLayout *newBoutonLayout);


public slots:
    void changementJoueur();
    void menupause();
    void resumeGame();
    void quitGame();
    void restartGame();
    void timerSlot();



private:
//    QVector<bool> *coloneJeu;
//    QVector<QVector<bool>*>*tableauJeu;

    Ui::Puissance4 *ui;
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
    int tmps = 10;
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
    int nbPanier=7;
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
    int puissance4 = 0;


};
#endif // PUISSANCE4_H
