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

private:
    Ui::Parametre *ui;

signals:
    void s_changement_mdp();

    void s_valider();
};

#endif // PARAMETRE_H
