#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <QDialog>

namespace Ui {
class Parametre;
}

class Parametre : public QDialog
{
    Q_OBJECT

public:
    explicit Parametre(QWidget *parent = nullptr);
    ~Parametre();

    void changer_le_mdp();

    void valider();

    void quitter();
    int envoieTemps();
    int nombrePanier();
    int nbPaniers;
    //int envoiePanier();

private:
    Ui::Parametre *ui;
    int tempsTir;


signals:
    void s_changement_mdp();

    void s_valider();

    void s_quitter();
};

#endif // PARAMETRE_H
