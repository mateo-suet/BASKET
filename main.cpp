#include "puissance4.h"
#include "BDD.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    puissance4 w;
    w.show();
    return a.exec();
}
