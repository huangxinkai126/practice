#include "getrect.h"
#include "ui_getrect.h"

getRect::getRect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getRect)
{
    ui->setupUi(this);
    x=0;
    y=0;
    h=0;
    v=0;
}

getRect::~getRect()
{
    delete ui;
}

void getRect::on_buttonBox_accepted()
{
    QString s1=ui->lineEdit1->text();
    QString s2=ui->lineEdit2->text();
    QString s3=ui->lineEdit3->text();
    QString s4=ui->lineEdit4->text();

    x=s1.toDouble();
    y=s2.toDouble();
    h=s3.toDouble();
    v=s4.toDouble();
}
double getRect::getDoublex()
{
    return x;
}
double getRect::getDoubley()
{
    return y;
}
double getRect::getDoubleh()
{
    return h;
}
double getRect::getDoublev()
{
    return v;
}
