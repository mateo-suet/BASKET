#ifndef PUISSANCE4_H
#define PUISSANCE4_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QHBoxLayout>
#include <QRect>
#include <QComboBox>
#include <QFontComboBox>
#include <QPushButton>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Puissance4; }
QT_END_NAMESPACE

class Puissance4 : public QMainWindow
{
    Q_OBJECT

public:
    Puissance4(QWidget *parent = nullptr);
    ~Puissance4();
    void on_playButton_clicked();
    void createCombox();
    void createLayout();
    void createPlateau();
    void change_color();
    void keyPressEvent(QKeyEvent *event);

public slots:
    void play_button();
    void quit_button();


private:
    Ui::Puissance4 *ui;
    QLabel *teamLB;                     //creation d'un label
    QLabel *team2LB;
    QLabel  *label_img ;
    QLabel *label_equipe1_play;
    QPixmap *pixmap_img;
    QGridLayout *layout;            //creation d'un layout
    QPushButton *confirmPlayPB;
    QPushButton *quitConfirmPB;
    int i;
    int jeton_col1=6;
    int jeton_col2=6;
    int jeton_col3=6;
    int jeton_col4=6;
    int jeton_col5=6;
    int jeton_col6=6;
    int j;
    int color=0;


};
#endif // PUISSANCE4_H
