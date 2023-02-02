#ifndef NEW_MDP_H
#define NEW_MDP_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include "BDD.h"
namespace Ui {
class new_mdp;
}

class new_mdp : public QDialog
{
    Q_OBJECT

public:
    explicit new_mdp(QWidget *parent = nullptr);
    ~new_mdp();

    void appuie_touche(QKeyEvent * event);

    void ecrire();

public slots :
    bool le_bouton_new_mdp();

private:
    Ui::new_mdp *ui;
};

#endif // NEW_MDP_H
