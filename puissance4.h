#ifndef PUISSANCE4_H
#define PUISSANCE4_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Puissance4; }
QT_END_NAMESPACE

class Puissance4 : public QMainWindow
{
    Q_OBJECT

public:
    Puissance4(QWidget *parent = nullptr);
    ~Puissance4();
    void on_playButton_clicked();

private:
    Ui::Puissance4 *ui;
};
#endif // PUISSANCE4_H
