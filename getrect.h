#ifndef GETRECT_H
#define GETRECT_H

#include <QDialog>

namespace Ui {
class getRect;
}

class getRect : public QDialog
{
    Q_OBJECT

public:
    explicit getRect(QWidget *parent = 0);
    ~getRect();
    double getDoublex();
    double getDoubley();
    double getDoubleh();
    double getDoublev();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::getRect *ui;
    double x;
    double y;
    double h;
    double v;
};

#endif // GETRECT_H
