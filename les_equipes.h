#ifndef LES_EQUIPES_H
#define LES_EQUIPES_H

#include <QMainWindow>
#include <QPushButton>
namespace Ui {
class Les_Equipes;
}
class Les_Equipes : public QMainWindow
{
    Q_OBJECT
public:
    explicit Les_Equipes(QWidget *parent = nullptr);

    void creation_Widget();


private:
    QPushButton *Bouton_ajouter;
    QPushButton *Bouton_ajouter2;

    QPushButton *Bouton_supprimer1;
    QPushButton *Bouton_supprimer2;

private:
    Ui::Les_Equipes *ui;

signals:

};

#endif // LES_EQUIPES_H
