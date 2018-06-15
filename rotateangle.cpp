#include "rotateangle.h"
#include "ui_rotateangle.h"

rotateAngle::rotateAngle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rotateAngle)
{
    ui->setupUi(this);
    xxx=0;
}

rotateAngle::~rotateAngle()
{
    delete ui;

}

void rotateAngle::on_buttonBox_accepted()
{
    QString x1=ui->lineEdit->text();
    xxx = x1.toDouble();
}
double rotateAngle::getDoublex()
{
    return xxx;

}
