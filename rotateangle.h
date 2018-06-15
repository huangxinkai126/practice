#ifndef ROTATEANGLE_H
#define ROTATEANGLE_H

#include <QDialog>

namespace Ui {
class rotateAngle;
}

class rotateAngle : public QDialog
{
    Q_OBJECT

public:
    explicit rotateAngle(QWidget *parent = 0);
    ~rotateAngle();
    double getDoublex();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::rotateAngle *ui;
    double xxx;
};

#endif // ROTATEANGLE_H
