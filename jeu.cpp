#include "jeu.h"
#include "ui_puissance4.h"

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QRect>
#include <QComboBox>
#include <QFontComboBox>
#include <QPainter>
#include <QPalette>
#include <QKeyEvent>
#include <QMessageBox>

jeu::jeu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::jeu)
{
    ui->setupUi(this);
    connect(ui->PlayPB, &QPushButton::clicked, this, &jeu::on_playButton_clicked);

}

jeu::~jeu(){delete ui;}

void jeu::on_playButton_clicked()
{
    ui->PlayPB->hide();                          // supprime le bouton
    ui->QuitPB->hide();                          // supprime le bouton
    ui->SettingsPB->hide();                      // supprime le bouton
    ui->ResultPB->hide();
    ui->centralwidget->setStyleSheet("background-color: #99CBFF");
    mainLayout = new QGridLayout(this);
    k=9;

    createPlateau();
}



void jeu::createPlateau()
{
    pixmap_img = new QPixmap("U:\\Documents\\rond_vide.png");
    tableauLayout = new QGridLayout(this);
    for( j=0; j <=6;j++)
    {


        for ( i = 1; i<=nbPanier;i++)
        {
            label_img= new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,j,i);
        }

        tableauLayout->setColumnStretch(i,1);
    }
    equipeLayout = new QGridLayout (this);

    equipeRouge = new QLabel ("Equipe Rouge");
    equipeRouge->setStyleSheet("QLabel {font: 40px;"
                                    "color:#FF0000 ; background-color : #99CBFF;}");
    equipeLayout->addWidget(equipeRouge,0,0);


    equipeJaune = new QLabel ("Equipe Jaune");
    equipeJaune->setStyleSheet("QLabel {font : 20px;"
                                        "color:#8F8D0F; background-color : #99CBFF;}");
    equipeLayout->addWidget(equipeJaune,0,1);
    equipeLayout->setColumnStretch(0,5);
    equipeLayout->setColumnStretch(1,5);

    boutonLayout = new QGridLayout(this);
    QPushButton *jSuivant = new QPushButton ("Joueur Suivant");
    QPushButton *pausePB = new QPushButton ("Pause");
    jSuivant->setStyleSheet("background-color: #CCE5FF");
    pausePB->setStyleSheet("background-color: #CCE5FF");
    jSuivant->setMinimumSize(100,100);
    pausePB->setMinimumSize(100,100);
    boutonLayout->addWidget(jSuivant,0,0);
    boutonLayout->addWidget(pausePB,0,1);

    timerjoueurLayout = new QGridLayout(this);
    numberTimer = new QLCDNumber(this);
    numberTimer->setDigitCount(QString("%1").arg(10).length());
    numberTimer->setStyleSheet("background-color: #99CBFF; color: green;");
    numberTimer->display(tmps);
    timerjoueurLayout->addWidget(numberTimer,0,0);

    color=0;
    players.append("Matéo");
    players.append("Anthony");
    players.append("Youyou");
    players.append("Thithi");
    qDebug() << players;
    playerlist=0;
    player = new QLabel(players[0]);
    qDebug() << player;
    player->setAlignment(Qt::AlignCenter);
    player->setStyleSheet("QLabel {font : 45px;"
                          "background-color : #99CBFF; color : #FF0000;}");


    timerjoueurLayout->addWidget(player,1,0);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout ()), this, SLOT(timerSlot()));
    timer->start(1000);


    mainLayout->addLayout(tableauLayout,0,0);
    mainLayout->addLayout(timerjoueurLayout,0,1);
    mainLayout->addLayout(equipeLayout,1,0);
    mainLayout->addLayout(boutonLayout,1,1);
    ui->centralwidget->setLayout(mainLayout);

    connect(jSuivant, SIGNAL(clicked()),this,SLOT(changementJoueur()));
    connect(pausePB, SIGNAL(clicked()),this,SLOT(menupause()));

}

void jeu::verification()
{
        QList<QList<QString>> verif_listes;
        verif_listes.append(col1_vrif);
        verif_listes.append(col2_vrif);
        verif_listes.append(col3_vrif);
        verif_listes.append(col4_vrif);
        verif_listes.append(col5_vrif);
        verif_listes.append(col6_vrif);
        verif_listes.append(col7_vrif);
        verif_listes.append(ligne1_vrif);
        verif_listes.append(ligne2_vrif);
        verif_listes.append(ligne3_vrif);
        verif_listes.append(ligne4_vrif);
        verif_listes.append(ligne5_vrif);
        verif_listes.append(ligne6_vrif);
        verif_listes.append(ligne7_vrif);
        verif_listes.append(diag1D_vrif);
        verif_listes.append(diag2D_vrif);
        verif_listes.append(diag3D_vrif);
        verif_listes.append(diag4D_vrif);
        verif_listes.append(diag5D_vrif);
        verif_listes.append(diag6D_vrif);
        verif_listes.append(diag7D_vrif);
        verif_listes.append(diag1G_vrif);
        verif_listes.append(diag2G_vrif);
        verif_listes.append(diag3G_vrif);
        verif_listes.append(diag4G_vrif);
        verif_listes.append(diag5G_vrif);
        verif_listes.append(diag6G_vrif);
        verif_listes.append(diag7G_vrif);
        if(color == 1)
        {
            for(int i = 0; i<verif_listes.size();i++)
            {
                QList<QString> verif_liste = verif_listes.at(i);
                if(verif_liste.size()>3)
                {
                    for(int j=0; j<verif_liste.size()-3; j++)
                    {
                        if(verif_liste.at(j)=="red" && verif_liste.at(j+1)=="red" && verif_liste.at(j+2)=="red" && verif_liste.at(j+3)=="red")
                        {
                            k=10;
                            timer->stop();
                            winningGL = new QGridLayout();
                            winningDL = new QDialog();
                            QLabel *winRed = new QLabel("Les Rouges ont gagnés");

                            restartWin = new QPushButton("Recommencer");
                            restartWin->setMinimumSize(200,100);
                            connect(restartWin, SIGNAL(clicked()),this,SLOT(restartGame()));

                            quit = new QPushButton("quitter");
                            quit->setMinimumSize(200,100);
                            connect(quit, SIGNAL(clicked()),this,SLOT(quitGame()));

                            winningGL->addWidget(winRed,0,0);
                            winningGL->addWidget(restartWin,1,0);
                            winningGL->addWidget(quit,1,1);
                            winningDL->setLayout(winningGL);
                            winningDL->exec();
                        }
                    }
                }
            }

        }
        else{
            for(int i = 0; i<verif_listes.size();i++)
            {
                QList<QString> verif_liste = verif_listes.at(i);
                if(verif_liste.size()>3)
                {
                    for(int j=0; j<verif_liste.size()-3; j++)
                    {
                        if(verif_liste.at(j)=="yellow" && verif_liste.at(j+1)=="yellow" && verif_liste.at(j+2)=="yellow" && verif_liste.at(j+3)=="yellow")
                        {
                            k=10;
                            timer->stop();
                            winningGL = new QGridLayout();
                            winningDL = new QDialog();
                            QLabel *winRed = new QLabel("Les Jaunes ont gagnés");

                            restartWin = new QPushButton("Recommencer");
                            restartWin->setMinimumSize(200,100);
                            connect(restartWin, SIGNAL(clicked()),this,SLOT(restartGame()));

                            quit = new QPushButton("quitter");
                            quit->setMinimumSize(200,100);
                            connect(quit, SIGNAL(clicked()),this,SLOT(quitGame()));

                            winningGL->addWidget(winRed,0,0);
                            winningGL->addWidget(restartWin,1,0);
                            winningGL->addWidget(quit,1,1);
                            winningDL->setLayout(winningGL);
                            winningDL->exec();
                        }
                    }
                }
            }
            equipeJaune->setStyleSheet("QLabel {font : 20px;"
                                                "color:#8F8D0F;}");
            equipeRouge->setStyleSheet("QLabel {font: 40px;"
                                            "color:#FF0000 }");
        }


    }


void jeu::keyPressEvent(QKeyEvent *event)
{
 qDebug() << diag7D_vrif;
    if (event->key() == Qt::Key_A)
    {
        if (color==0)
        {
                pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
                label_img=new QLabel(this);
                label_img->setMaximumHeight(120);
                label_img->setMaximumWidth(120);
                pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                label_img->setPixmap(*pixmap_img);
                tableauLayout->addWidget(label_img,jeton_col1,1);
                if(jeton_col1==6)
                {
                    col1_vrif.append("red");
                    ligne1_vrif.replace(0,"red");
                    diag4D_vrif.replace(0,"red");
                }
                if(jeton_col1==5)
                {
                    col1_vrif.append("red");
                    ligne2_vrif.replace(0,"red");
                    diag3D_vrif.replace(0,"red");
                }
                if(jeton_col1==4)
                {
                    col1_vrif.append("red");
                    ligne3_vrif.replace(0,"red");
                    diag2D_vrif.replace(0,"red");
                }
                if(jeton_col1==3)
                {
                    col1_vrif.append("red");
                    ligne4_vrif.replace(0,"red");
                    diag1G_vrif.replace(3,"red");
                    diag1D_vrif.replace(0,"red");
                }
                if(jeton_col1==2)
                {
                    col1_vrif.append("red");
                    ligne5_vrif.replace(0,"red");
                    diag2G_vrif.replace(4,"red");
                }
                if(jeton_col1==1)
                {
                    col1_vrif.append("red");
                    ligne6_vrif.replace(0,"red");
                    diag3G_vrif.replace(5,"red");
                }
                if(jeton_col1==0)
                {
                    col1_vrif.append("red");
                    ligne7_vrif.replace(0,"red");
                    diag4G_vrif.replace(6,"red");
                }
                jeton_col1--;
                changementJoueur();
                verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col1,1);
            if(jeton_col1==6)
            {
                col1_vrif.append("yellow");
                ligne1_vrif.replace(0,"yellow");
                diag4D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==5)
            {
                col1_vrif.append("yellow");
                ligne2_vrif.replace(0,"yellow");
                diag3D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==4)
            {
                col1_vrif.append("yellow");
                ligne3_vrif.replace(0,"yellow");
                diag2D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==3)
            {
                col1_vrif.append("yellow");
                ligne4_vrif.replace(0,"yellow");
                diag1G_vrif.replace(3,"yellow");
                diag1D_vrif.replace(0,"yellow");
            }
            if(jeton_col1==2)
            {
                col1_vrif.append("yellow");
                ligne5_vrif.replace(0,"yellow");
                diag2G_vrif.replace(4,"yellow");
            }
            if(jeton_col1==1)
            {
                col1_vrif.append("yellow");
                ligne6_vrif.replace(0,"yellow");
                diag3G_vrif.replace(5,"yellow");
            }
            if(jeton_col1==0)
            {
                col1_vrif.append("yellow");
                ligne7_vrif.replace(0,"yellow");
                diag4G_vrif.replace(6,"yellow");
            }
            jeton_col1--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_Z)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col2,2);
            if(jeton_col2==6)
            {
                col2_vrif.append("red");
                ligne1_vrif.replace(1,"red");
                diag5D_vrif.replace(0,"red");
            }
            if(jeton_col2==5)
            {
                col2_vrif.append("red");
                ligne2_vrif.replace(1,"red");
                diag4D_vrif.replace(1,"red");
            }
            if(jeton_col2==4)
            {
                col2_vrif.append("red");
                ligne3_vrif.replace(1,"red");
                diag3D_vrif.replace(1,"red");
                diag1G_vrif.replace(2,"red");
            }
            if(jeton_col2==3)
            {
                col2_vrif.append("red");
                ligne4_vrif.replace(1,"red");
                diag2D_vrif.replace(1,"red");
                diag2G_vrif.replace(3,"red");
            }
            if(jeton_col2==2)
            {
                col2_vrif.append("red");
                ligne5_vrif.replace(1,"red");
                diag1D_vrif.replace(1,"red");
                diag3G_vrif.replace(4,"red");
            }
            if(jeton_col2==1)
            {
                col2_vrif.append("red");
                ligne6_vrif.replace(1,"red");
                diag4G_vrif.replace(5,"red");
            }
            if(jeton_col2==0)
            {
                col2_vrif.append("red");
                ligne7_vrif.replace(1,"red");
                diag5G_vrif.replace(5,"red");
            }
            jeton_col2--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col2,2);
            if(jeton_col2==6)
            {
                col2_vrif.append("yellow");
                ligne1_vrif.replace(1,"yellow");
                diag5D_vrif.replace(0,"yellow");
            }
            if(jeton_col2==5)
            {
                col2_vrif.append("yellow");
                ligne2_vrif.replace(1,"yellow");
                diag4D_vrif.replace(1,"yellow");
            }
            if(jeton_col2==4)
            {
                col2_vrif.append("yellow");
                ligne3_vrif.replace(1,"yellow");
                diag3D_vrif.replace(1,"yellow");
                diag1G_vrif.replace(2,"yellow");
            }
            if(jeton_col2==3)
            {
                col2_vrif.append("yellow");
                ligne4_vrif.replace(1,"yellow");
                diag2D_vrif.replace(1,"yellow");
                diag2G_vrif.replace(3,"yellow");
            }
            if(jeton_col2==2)
            {
                col2_vrif.append("yellow");
                ligne5_vrif.replace(1,"yellow");
                diag1D_vrif.replace(1,"yellow");
                diag3G_vrif.replace(4,"yellow");
            }
            if(jeton_col2==1)
            {
                col2_vrif.append("yellow");
                ligne6_vrif.replace(1,"yellow");
                diag4G_vrif.replace(5,"yellow");
            }
            if(jeton_col2==0)
            {
                col2_vrif.append("yellow");
                ligne7_vrif.replace(1,"yellow");
                diag5G_vrif.replace(5,"yellow");
            }
            jeton_col2--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_E)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col3,3);
            if(jeton_col3==6)
            {
                col3_vrif.append("red");
                ligne1_vrif.replace(2,"red");
                diag6D_vrif.replace(0,"red");
            }
            if(jeton_col3==5)
            {
                col3_vrif.append("red");
                ligne2_vrif.replace(2,"red");
                diag5D_vrif.replace(1,"red");
                diag1G_vrif.replace(1,"red");
            }
            if(jeton_col3==4)
            {
                col3_vrif.append("red");
                ligne3_vrif.replace(2,"red");
                diag4D_vrif.replace(2,"red");
                diag2G_vrif.replace(2,"red");
            }
            if(jeton_col3==3)
            {
                col3_vrif.append("red");
                ligne4_vrif.replace(2,"red");
                diag3D_vrif.replace(2,"red");
                diag3G_vrif.replace(3,"red");
            }
            if(jeton_col3==2)
            {
                col3_vrif.append("red");
                ligne5_vrif.replace(2,"red");
                diag2D_vrif.replace(2,"red");
                diag4G_vrif.replace(4,"red");
            }
            if(jeton_col3==1)
            {
                col3_vrif.append("red");
                ligne6_vrif.replace(2,"red");
                diag1D_vrif.replace(2,"red");
                diag5G_vrif.replace(4,"red");
            }
            if(jeton_col3==0)
            {
                col3_vrif.append("red");
                ligne7_vrif.replace(2,"red");
                diag5G_vrif.replace(4,"red");
            }
            jeton_col3--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col3,3);
            if(jeton_col3==6)
            {
                col3_vrif.append("yellow");
                ligne1_vrif.replace(2,"yellow");
                diag6D_vrif.replace(0,"yellow");
            }
            if(jeton_col3==5)
            {
                col3_vrif.append("yellow");
                ligne2_vrif.replace(2,"yellow");
                diag5D_vrif.replace(1,"yellow");
                diag1G_vrif.replace(1,"yellow");
            }
            if(jeton_col3==4)
            {
                col3_vrif.append("yellow");
                ligne3_vrif.replace(2,"yellow");
                diag4D_vrif.replace(2,"yellow");
                diag2G_vrif.replace(2,"yellow");
            }
            if(jeton_col3==3)
            {
                col3_vrif.append("yellow");
                ligne4_vrif.replace(2,"yellow");
                diag3D_vrif.replace(2,"yellow");
                diag3G_vrif.replace(3,"yellow");
            }
            if(jeton_col3==2)
            {
                col3_vrif.append("yellow");
                ligne5_vrif.replace(2,"yellow");
                diag2D_vrif.replace(2,"yellow");
                diag4G_vrif.replace(4,"yellow");
            }
            if(jeton_col3==1)
            {
                col3_vrif.append("yellow");
                ligne6_vrif.replace(2,"yellow");
                diag1D_vrif.replace(2,"yellow");
                diag5G_vrif.replace(4,"yellow");
            }
            if(jeton_col3==0)
            {
                col3_vrif.append("yellow");
                ligne7_vrif.replace(2,"yellow");
                diag5G_vrif.replace(4,"yellow");
            }
            jeton_col3--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_R)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col4,4);
            if(jeton_col4==6)
            {
                col4_vrif.append("red");
                ligne1_vrif.replace(3,"red");
                diag1G_vrif.replace(0,"red");
                diag7D_vrif.replace(0,"red");
            }
            if(jeton_col4==5)
            {
                col4_vrif.append("red");
                ligne2_vrif.replace(3,"red");
                diag2G_vrif.replace(1,"red");
                diag6D_vrif.replace(1,"red");
            }
            if(jeton_col4==4)
            {
                col4_vrif.append("red");
                ligne3_vrif.replace(3,"red");
                diag3G_vrif.replace(2,"red");
                diag5D_vrif.replace(2,"red");
            }
            if(jeton_col4==3)
            {
                col4_vrif.append("red");
                ligne4_vrif.replace(3,"red");
                diag4G_vrif.replace(3,"red");
                diag4D_vrif.replace(3,"red");
            }
            if(jeton_col4==2)
            {
                col4_vrif.append("red");
                ligne5_vrif.replace(3,"red");
                diag5G_vrif.replace(3,"red");
                diag3D_vrif.replace(3,"red");
            }
            if(jeton_col4==1)
            {
                col4_vrif.append("red");
                ligne6_vrif.replace(3,"red");
                diag6G_vrif.replace(3,"red");
                diag2D_vrif.replace(3,"red");
            }
            if(jeton_col4==0)
            {
                col4_vrif.append("red");
                ligne4_vrif.replace(3,"red");
                diag7G_vrif.replace(3,"red");
                diag1D_vrif.replace(3,"red");
            }
            jeton_col4--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col4,4);
            if(jeton_col4==6)
            {
                col4_vrif.append("yellow");
                ligne1_vrif.replace(3,"yellow");
                diag1G_vrif.replace(0,"yellow");
                diag7D_vrif.replace(0,"yellow");
            }
            if(jeton_col4==5)
            {
                col4_vrif.append("yellow");
                ligne2_vrif.replace(3,"yellow");
                diag2G_vrif.replace(1,"yellow");
                diag6D_vrif.replace(1,"yellow");
            }
            if(jeton_col4==4)
            {
                col4_vrif.append("yellow");
                ligne3_vrif.replace(3,"yellow");
                diag3G_vrif.replace(2,"yellow");
                diag5D_vrif.replace(2,"yellow");
            }
            if(jeton_col4==3)
            {
                col4_vrif.append("yellow");
                ligne4_vrif.replace(3,"yellow");
                diag4G_vrif.replace(3,"yellow");
                diag4D_vrif.replace(3,"yellow");
            }
            if(jeton_col4==2)
            {
                col4_vrif.append("yellow");
                ligne5_vrif.replace(3,"yellow");
                diag5G_vrif.replace(3,"yellow");
                diag3D_vrif.replace(3,"yellow");
            }
            if(jeton_col4==1)
            {
                col4_vrif.append("yellow");
                ligne6_vrif.replace(3,"yellow");
                diag6G_vrif.replace(3,"yellow");
                diag2D_vrif.replace(3,"yellow");
            }
            if(jeton_col4==0)
            {
                col4_vrif.append("yellow");
                ligne4_vrif.replace(3,"yellow");
                diag7G_vrif.replace(3,"yellow");
                diag1D_vrif.replace(3,"yellow");
            }
            jeton_col4--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_T)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col5,5);
            if(jeton_col5==6)
            {
                col5_vrif.append("red");
                ligne1_vrif.replace(4,"red");
                diag2G_vrif.replace(0,"red");
            }
            if(jeton_col5==5)
            {
                col5_vrif.append("red");
                ligne2_vrif.replace(4,"red");
                diag3G_vrif.replace(1,"red");
                diag7D_vrif.replace(1,"red");
            }
            if(jeton_col5==4)
            {
                col5_vrif.append("red");
                ligne3_vrif.replace(4,"red");
                diag4G_vrif.replace(2,"red");
                diag6D_vrif.replace(2,"red");
            }
            if(jeton_col5==3)
            {
                col5_vrif.append("red");
                ligne4_vrif.replace(4,"red");
                diag5G_vrif.replace(2,"red");
                diag5D_vrif.replace(3,"red");
            }
            if(jeton_col5==2)
            {
                col5_vrif.append("red");
                ligne5_vrif.replace(4,"red");
                diag6G_vrif.replace(2,"red");
                diag4D_vrif.replace(4,"red");
            }
            if(jeton_col5==1)
            {
                col5_vrif.append("red");
                ligne6_vrif.replace(4,"red");
                diag7G_vrif.replace(2,"red");
                diag3D_vrif.replace(4,"red");
            }
            if(jeton_col5==0)
            {
                col5_vrif.append("red");
                ligne7_vrif.replace(4,"red");
                diag2D_vrif.replace(4,"red");
            }
            jeton_col5--;
            changementJoueur();
            verification();


        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col5,5);
            if(jeton_col5==6)
            {
                col5_vrif.append("yellow");
                ligne1_vrif.replace(4,"yellow");
                diag2G_vrif.replace(0,"yellow");
            }
            if(jeton_col5==5)
            {
                col5_vrif.append("yellow");
                ligne2_vrif.replace(4,"yellow");
                diag3G_vrif.replace(1,"yellow");
                diag7D_vrif.replace(1,"yellow");
            }
            if(jeton_col5==4)
            {
                col5_vrif.append("yellow");
                ligne3_vrif.replace(4,"yellow");
                diag4G_vrif.replace(2,"yellow");
                diag6D_vrif.replace(2,"yellow");
            }
            if(jeton_col5==3)
            {
                col5_vrif.append("yellow");
                ligne4_vrif.replace(4,"yellow");
                diag5G_vrif.replace(2,"yellow");
                diag5D_vrif.replace(3,"yellow");
            }
            if(jeton_col5==2)
            {
                col5_vrif.append("yellow");
                ligne5_vrif.replace(4,"yellow");
                diag6G_vrif.replace(2,"yellow");
                diag4D_vrif.replace(4,"yellow");
            }
            if(jeton_col5==1)
            {
                col5_vrif.append("yellow");
                ligne6_vrif.replace(4,"yellow");
                diag7G_vrif.replace(2,"yellow");
                diag3D_vrif.replace(4,"yellow");
            }
            if(jeton_col5==0)
            {
                col5_vrif.append("yellow");
                ligne7_vrif.replace(4,"yellow");
                diag2D_vrif.replace(4,"yellow");
            }
            jeton_col5--;
            changementJoueur();
            verification();

        }
    }
    if (event->key() == Qt::Key_Y)
    {
        if (color==0)
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col6,6);
            if(jeton_col6==6)
            {
                col6_vrif.append("red");
                ligne1_vrif.replace(5,"red");
                diag3G_vrif.replace(0,"red");
            }
            if(jeton_col6==5)
            {
                col6_vrif.append("red");
                ligne2_vrif.replace(5,"red");
                diag4G_vrif.replace(1,"red");
            }
            if(jeton_col6==4)
            {
                col6_vrif.append("red");
                ligne3_vrif.replace(5,"red");
                diag7D_vrif.replace(2,"red");
                diag5G_vrif.replace(1,"red");
            }
            if(jeton_col6==3)
            {
                col6_vrif.append("red");
                ligne4_vrif.replace(5,"red");
                diag6D_vrif.replace(3,"red");
                diag5G_vrif.replace(1,"red");
            }
            if(jeton_col6==2)
            {
                col6_vrif.append("red");
                ligne5_vrif.replace(5,"red");
                diag5D_vrif.replace(4,"red");
                diag7G_vrif.replace(1,"red");
            }
            if(jeton_col6==1)
            {
                col6_vrif.append("red");
                ligne6_vrif.replace(5,"red");
                diag4D_vrif.replace(5,"red");
            }
            if(jeton_col6==0)
            {
                col6_vrif.append("red");
                ligne7_vrif.replace(5,"red");
                diag3D_vrif.replace(5,"red");
            }
            jeton_col6--;
            changementJoueur();
            verification();

        }
        else
        {
            pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
            label_img=new QLabel(this);
            label_img->setMaximumHeight(120);
            label_img->setMaximumWidth(120);
            pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
            label_img->setPixmap(*pixmap_img);
            tableauLayout->addWidget(label_img,jeton_col6,6);

            if(jeton_col6==6)
            {
                col6_vrif.append("yellow");
                ligne1_vrif.replace(5,"yellow");
                diag3G_vrif.replace(0,"yellow");
            }
            if(jeton_col6==5)
            {
                col6_vrif.append("yellow");
                ligne2_vrif.replace(5,"yellow");
                diag4G_vrif.replace(1,"yellow");
            }
            if(jeton_col6==4)
            {
                col6_vrif.append("yellow");
                ligne3_vrif.replace(5,"yellow");
                diag7D_vrif.replace(2,"yellow");
                diag5G_vrif.replace(1,"yellow");
            }
            if(jeton_col6==3)
            {
                col6_vrif.append("yellow");
                ligne4_vrif.replace(5,"yellow");
                diag6D_vrif.replace(3,"yellow");
                diag5G_vrif.replace(1,"yellow");
            }
            if(jeton_col6==2)
            {
                col6_vrif.append("yellow");
                ligne5_vrif.replace(5,"yellow");
                diag5D_vrif.replace(4,"yellow");
                diag7G_vrif.replace(1,"yellow");
            }
            if(jeton_col6==1)
            {
                col6_vrif.append("yellow");
                ligne6_vrif.replace(5,"yellow");
                diag4D_vrif.replace(5,"yellow");
            }
            if(jeton_col6==0)
            {
                col6_vrif.append("yellow");
                ligne7_vrif.replace(5,"yellow");
                diag3D_vrif.replace(5,"yellow");
            }
            jeton_col6--;
            changementJoueur();
            verification();
        }
    }
    if (event->key() == Qt::Key_U)
        {
            if (color==0)
            {
                pixmap_img = new QPixmap("U:\\Documents\\rond_rouge.png");
                label_img=new QLabel(this);
                label_img->setMaximumHeight(120);
                label_img->setMaximumWidth(120);
                pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                label_img->setPixmap(*pixmap_img);
                tableauLayout->addWidget(label_img,jeton_col7,7);
                if(jeton_col7==6)
                {
                    col7_vrif.append("red");
                    ligne1_vrif.replace(6,"red");
                    diag4G_vrif.replace(0,"red");
                }
                if(jeton_col7==5)
                {
                    col7_vrif.append("red");
                    ligne2_vrif.replace(6,"red");
                    diag5G_vrif.replace(0,"red");
                }
                if(jeton_col7==4)
                {
                    col7_vrif.append("red");
                    ligne3_vrif.replace(6,"red");
                    diag6G_vrif.replace(0,"red");
                }
                if(jeton_col7==3)
                {
                    col7_vrif.append("red");
                    ligne4_vrif.replace(6,"red");
                    diag6G_vrif.replace(0,"red");
                    diag7D_vrif.replace(3,"red");
                }
                if(jeton_col7==2)
                {
                    col7_vrif.append("red");
                    ligne5_vrif.replace(6,"red");
                    diag6D_vrif.replace(4,"red");
                }
                if(jeton_col7==1)
                {
                    col7_vrif.append("red");
                    ligne6_vrif.replace(6,"red");
                    diag5D_vrif.replace(5,"red");
                }
                if(jeton_col7==0)
                {
                    col7_vrif.append("red");
                    ligne7_vrif.replace(6,"red");
                    diag4G_vrif.replace(6,"red");
                }
                jeton_col7--;
                changementJoueur();
                verification();

            }
            else
            {
                pixmap_img = new QPixmap("U:\\Documents\\rond_jaune.png");
                label_img=new QLabel(this);
                label_img->setMaximumHeight(120);
                label_img->setMaximumWidth(120);
                pixmap_img->scaled(label_img->maximumWidth(),label_img->maximumHeight(),Qt::IgnoreAspectRatio);
                label_img->setPixmap(*pixmap_img);
                tableauLayout->addWidget(label_img,jeton_col7,7);
                if(jeton_col7==6)
                {
                    col7_vrif.append("yellow");
                    ligne1_vrif.replace(6,"yellow");
                    diag4G_vrif.replace(0,"yellow");
                }
                if(jeton_col7==5)
                {
                    col7_vrif.append("yellow");
                    ligne2_vrif.replace(6,"yellow");
                    diag5G_vrif.replace(0,"yellow");
                }
                if(jeton_col7==4)
                {
                    col7_vrif.append("yellow");
                    ligne3_vrif.replace(6,"yellow");
                    diag6G_vrif.replace(0,"yellow");
                }
                if(jeton_col7==3)
                {
                    col7_vrif.append("yellow");
                    ligne4_vrif.replace(6,"yellow");
                    diag6G_vrif.replace(0,"yellow");
                    diag7D_vrif.replace(3,"yellow");
                }
                if(jeton_col7==2)
                {
                    col7_vrif.append("yellow");
                    ligne5_vrif.replace(6,"yellow");
                    diag6D_vrif.replace(4,"yellow");
                }
                if(jeton_col7==1)
                {
                    col7_vrif.append("yellow");
                    ligne6_vrif.replace(6,"yellow");
                    diag5D_vrif.replace(5,"yellow");
                }
                if(jeton_col7==0)
                {
                    col7_vrif.append("yellow");
                    ligne7_vrif.replace(6,"yellow");
                    diag4G_vrif.replace(6,"yellow");
                }
                jeton_col7--;
                changementJoueur();
                verification();
            }
        }
}
void jeu::changementJoueur()
{
    if(color==0)
    {
        equipeJaune->setStyleSheet("QLabel {font : 40px;"
                                            "color:#F5F207; background-color : #99CBFF;}");
        equipeRouge->setStyleSheet("QLabel {font: 20px;"
                                        "color:#A40B0B ; background-color : #99CBFF;}");
        player->setStyleSheet("QLabel {font : 45px;"
                              "background-color : #99CBFF; color : #F5F207;}");
        color=1;
    }
    else
    {
        equipeJaune->setStyleSheet("QLabel {font : 20px;"
                                            "color:#8F8D0F; background-color : #99CBFF;}");
        equipeRouge->setStyleSheet("QLabel {font: 40px;"
                                        "color:#FF0000; background-color : #99CBFF; }");
        player->setStyleSheet("QLabel {font : 45px;"
                              "background-color : #99CBFF; color : #FF0000;}");

        color=0;
    }
    if(numberTimer!=0)
    {
        tmps = 10;
        numberTimer->setStyleSheet("background-color: #99CBFF; color: green;");
        numberTimer->display(tmps);
        if (playerlist == players.length()-1)
        {
            playerlist=0;
            player->setText(players[playerlist]);
        }
        else
        {
            ++playerlist;
            player->setText(players[playerlist]);
        }

    }

}
void jeu::menupause()
{
    k=9;
    timer->stop();
    pauseButton = new QGridLayout();
    pause = new QDialog();

    quit = new QPushButton("Quitter");
    quit->setMinimumSize(200,100);
    connect(quit, SIGNAL(clicked()),this,SLOT(quitGame()));

    resume = new QPushButton("Reprendre");
    resume->setMinimumSize(200,100);
    connect(resume, SIGNAL(clicked()),this,SLOT(resumeGame()));

    restart = new QPushButton("Recommencer");
    restart->setMinimumSize(200,100);
    connect(restart, SIGNAL(clicked()),this,SLOT(restartGame()));

    pauseButton->addWidget(quit,2,0);
    pauseButton->addWidget(resume,0,0);
    pauseButton->addWidget(restart,1,0);
    pause->setLayout(pauseButton);
    pause->exec();


}
void jeu::resumeGame()
{
    pause->hide();
    timer->start();
}
void jeu::quitGame()
{
    clearList();
    for (int i = 0; i < tableauLayout->count(); i++)
    {
       tableauLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < equipeLayout->count(); i++)
    {
       equipeLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < boutonLayout->count(); i++)
    {
       boutonLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < timerjoueurLayout->count(); i++)
    {
       timerjoueurLayout->itemAt(i)->widget()->deleteLater();
    }
    if(k==10)
    {
        winningDL->hide();
    }
    else
    {
        pause->hide();
    }
    mainLayout->deleteLater();
    tmps=5;
    ui->PlayPB->show();
    ui->QuitPB->show();
    ui->ResultPB->show();
    ui->SettingsPB->show();

}
void jeu::restartGame()
{


    for (int i = 0; i < tableauLayout->count(); i++)
    {
       tableauLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < equipeLayout->count(); i++)
    {
       equipeLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < boutonLayout->count(); i++)
    {
       boutonLayout->itemAt(i)->widget()->deleteLater();
    }
    for (int i = 0; i < timerjoueurLayout->count(); i++)
    {
       timerjoueurLayout->itemAt(i)->widget()->deleteLater();
    }
    if(k==10)
    {
        winningDL->hide();
    }
    else
    {
        pause->hide();
    }
    clearList();
    createPlateau();

    timer->start();
    numberTimer->display(tmps);
    qDebug() << playerlist;
}


void jeu::timerSlot()
{
    --tmps;
    if(tmps==0)
    {
        numberTimer->setStyleSheet("background-color: #ED0000; color: #6D071A;");
    }
    if (tmps == -1)
    {
        changementJoueur();
    }
    numberTimer->display(tmps);
}
void jeu::clearList()
{
    col1_vrif.clear();
    col2_vrif.clear();
    col3_vrif.clear();
    col4_vrif.clear();
    col5_vrif.clear();
    col6_vrif.clear();
    col7_vrif.clear();
    ligne1_vrif = {"","","","","","",""};
    ligne2_vrif = {"","","","","","",""};
    ligne3_vrif = {"","","","","","",""};
    ligne4_vrif = {"","","","","","",""};
    ligne5_vrif = {"","","","","","",""};
    ligne6_vrif = {"","","","","","",""};
    ligne7_vrif = {"","","","","","",""};
    diag1D_vrif = {"","","",""};
    diag2D_vrif = {"","","","",""};
    diag3D_vrif = {"","","","","",""};
    diag4D_vrif = {"","","","","","",""};
    diag5D_vrif = {"","","","","",""};
    diag6D_vrif = {"","","","",""};
    diag7D_vrif = {"","","",""};
    diag1G_vrif = {"","","",""};
    diag2G_vrif = {"","","","",""};
    diag3G_vrif = {"","","","","",""};
    diag4G_vrif = {"","","","","","",""};
    diag5G_vrif = {"","","","","",""};
    diag6G_vrif = {"","","","",""};
    diag7G_vrif = {"","","",""};
    players.clear();
    jeton_col1 = 6;
    jeton_col2 = 6;
    jeton_col3 = 6;
    jeton_col4 = 6;
    jeton_col5 = 6;
    jeton_col6 = 6;
    jeton_col7 = 6;

}
