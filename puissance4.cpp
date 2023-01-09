#include "puissance4.h"
#include "ui_puissance4.h"


puissance4::puissance4(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::puissance4)
{
    ui->setupUi(this);

    connect(ui->SettingsPB, &QPushButton::clicked, this, &puissance4::on_sett_clicked);    
}

puissance4::~puissance4()
{
    delete ui;
}


void puissance4::on_sett_clicked()
{
    ui->PlayPB->hide();  //supprime tout les premier bouton
    ui->QuitPB->hide();
    ui->SettingsPB->hide();
    ui->ResultPB->hide();

    creation_des_widget();

    connect(Bouton_ok, SIGNAL(clicked()), this, SLOT(le_bouton_ok()));
    connect(Bouton_quitter, SIGNAL(clicked()), this, SLOT(le_bouton_quitter()));
    connect(Bouton_default, SIGNAL(clicked()), this, SLOT(le_bouton_default()));
}

void clearLayout(QLayout *layout){
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while ((item = layout->takeAt(0))) {
        if (  (item->layout())){
              clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void puissance4::le_bouton_ok()
{

}

void puissance4::le_bouton_quitter()
{
    clearLayout(lay);
    lay->deleteLater();
    ui->PlayPB->show();  //supprime tout les premier bouton
    ui->QuitPB->show();
    ui->SettingsPB->show();
    ui->ResultPB->show();
}

void puissance4::le_bouton_default()
{
    nb5->setChecked(true);
    LeTemps->setTime(QTime(0,5,0,0));
}

void puissance4::creation_des_widget()
{
    nb5 = new QRadioButton("5",this);  // Créer les boutons de 5 et 7
    nb7 = new QRadioButton("7",this);
    Bouton_ok = new QPushButton("OK"); //Créer les bouton ok quitter et default
    Bouton_quitter = new QPushButton("Quitter");
    Bouton_default = new QPushButton("Default");
    titre = new QLabel(); //Créer les titres
    titre1 = new QLabel();
    LeTemps = new QTimeEdit(); //Créer la zone de temps

    titre->setText("Nombre de Panier");
    titre->setStyleSheet("font-size: 20px");

    titre1->setText("Le Temps");
    titre1->setStyleSheet("font-size: 20px");

    lay = new QGridLayout();
    ui->LeTout->setLayout(lay);


    lay->addWidget(titre);  //Place tout les widget dans le Layout
    lay->addWidget(nb5,1,0);
    lay->addWidget(nb7,1,1);
    lay->addWidget(titre1,2,0);
    lay->addWidget(LeTemps,3,0);
    lay->addWidget(Bouton_ok,4,0);
    lay->addWidget(Bouton_quitter,4,1);
    lay->addWidget(Bouton_default,4,2);

    lay->setSizeConstraint(QLayout::SetFixedSize);
    lay->setContentsMargins(10,10,0,0);
}
