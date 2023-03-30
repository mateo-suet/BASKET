#ifndef EQUIPE_H
#define EQUIPE_H

#include <QDialog>

namespace Ui {
class Equipe;
}

class Equipe : public QDialog
{
    Q_OBJECT

public:
    explicit Equipe(QWidget *parent = nullptr);
    ~Equipe();

private:
    Ui::Equipe *ui;
};

#endif // EQUIPE_H
