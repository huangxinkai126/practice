#include "movexy.h"
#include "ui_movexy.h"

movexy::movexy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::movexy)
{
    ui->setupUi(this);
    xxx=0;
    yyy=0;
}

movexy::~movexy()
{
    delete ui;
}

void movexy::on_buttonBox_accepted()
{
    QString x1=ui->lineEdit1->text();
    QString x2=ui->lineEdit2->text();
    xxx=x1.toDouble();
    yyy=x2.toDouble();
}
double movexy::getInputx()
{
    return xxx;
}
double movexy::getInputy()
{
    return yyy;
}
