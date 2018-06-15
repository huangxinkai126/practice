#ifndef DEFINEDFILTER_H
#define DEFINEDFILTER_H

#include <QDialog>

namespace Ui {
class definedFilter;
}

class definedFilter : public QDialog
{
    Q_OBJECT

public:
    explicit definedFilter(QWidget *parent = 0);
    ~definedFilter();
    double getInput1();
    double getInput2();
    double getInput3();
    double getInput4();
    double getInput5();
    double getInput6();
    double getInput7();
    double getInput8();
    double getInput9();


private slots:
    void on_buttonBox_accepted();

private:
    Ui::definedFilter *ui;
    double x1;
    double x2;
    double x3;
    double x4;
    double x5;
    double x6;
    double x7;
    double x8;
    double x9;
};

#endif // DEFINEDFILTER_H
