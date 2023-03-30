#include "equipe.h"
#include "ui_equipe.h"

Equipe::Equipe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Equipe)
{
    ui->setupUi(this);
}

Equipe::~Equipe()
{
    delete ui;
}
