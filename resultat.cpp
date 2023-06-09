#include "resultat.h"
#include "ui_resultat.h"

Resultat::Resultat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resultat)
{
    ui->setupUi(this);
    connect(ui->Quitter, &QPushButton::clicked, this, &Resultat::quitter);
}

Resultat::~Resultat()
{
    delete ui;
}

void Resultat::quitter()
{
    emit sign_quitter();
}
