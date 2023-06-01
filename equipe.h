#ifndef EQUIPE_H
#define EQUIPE_H

#include <QDialog>

#include <QDebug>
#include <QComboBox>
#include <QMessageBox>

namespace Ui {
class Equipe;
}

class Equipe : public QDialog
{
    Q_OBJECT

public:
    explicit Equipe(QWidget *parent = nullptr);
    ~Equipe();

    void les_nouveau_j();

    void sup_joueur();

    void plus_joueur_1(int position_j1, QComboBox *combo_1);

    bool recup_les_noms(QList<QString>& noms);

    void nom_historique(QList<QString>& noms_historique);

    QString ajouter_joueur();

    QString supprimer_joueur();

    int compter_combobox_1p();

    int compter_combobox_2p();

    void lancement_joueur();

    void lancement_joueur_2();

    void supprimer_combobox_equipe1();

    void supprimer_combobox_equipe2();

    void message();

    void ajout_joueur_bdd();

private:

    QString le_nouveau;

    QString le_sortant;

    int position;
    int position_2;
    int position_j1;
    int position_j2;

    int i = 0;

    Ui::Equipe *ui;

    QComboBox *combo_sup;
    QComboBox *combo_1 = new QComboBox;
    QComboBox *combo_2 = new QComboBox;

    QList<QString> noms_des_joueurs;

    QString combo_num1;
    QString combo_num2;
    QString combo_num3;
    QString combo_num4;
    QString combo_num5;
    QString combo_num6;
    QString combo_num7;
    QString combo_num8;
    QString combo_num9;
    QString combo_num10;

public slots :
    void lancement();

signals:

    void new_player();

    void out_player();

    void recup_noms();

    void nouveau_combo_1();

    void ajout_bdd();

};

#endif // EQUIPE_H
