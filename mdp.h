#ifndef MDP_H
#define MDP_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class MDP;
}

class MDP : public QDialog
{
    Q_OBJECT

public:
    explicit MDP(QWidget *parent = nullptr);
    ~MDP();

    void valider();

    QString getMDP();

    void ligne_a_zero();

    void message();

private:

    QString val_mdp;


    Ui::MDP *ui;
signals:
    void SigMDP();
};

#endif // MDP_H
