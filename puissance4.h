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


public slots:
    void play_button();
    void quit_button();


private:
    Ui::Puissance4 *ui;
    QLabel *teamLB;                     //creation d'un label
    QLabel *team2LB;
    QGridLayout *layout;            //creation d'un layout
    QPushButton *confirmPlayPB;
    QPushButton *quitConfirmPB;
    int i;
    int j;
};
#endif // PUISSANCE4_H
