#ifndef RESULTAT_H
#define RESULTAT_H

#include <QDialog>

namespace Ui {
class Resultat;
}

class Resultat : public QDialog
{
    Q_OBJECT

public:
    explicit Resultat(QWidget *parent = nullptr);
    ~Resultat();

    void quitter();



private:
    Ui::Resultat *ui;

signals :

    void sign_quitter();
};

#endif // RESULTAT_H
