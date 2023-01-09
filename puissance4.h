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

public slots:
    void le_bouton_ok();

    void le_bouton_quitter();

    void le_bouton_default();

private:
    Ui::puissance4 *ui;

    QRadioButton *nb5;
    QRadioButton *nb7;

    QTimeEdit *LeTemps;
    QPushButton *Bouton_ok;
    QPushButton *Bouton_quitter;
    QPushButton *Bouton_default;
    QLabel *titre;
    QLabel *titre1;
    QGridLayout *lay;

};
#endif // PUISSANCE4_H
