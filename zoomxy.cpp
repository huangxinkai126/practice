#include "zoomxy.h"
#include "ui_zoomxy.h"

zoomxy::zoomxy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zoomxy)
{
    ui->setupUi(this);
}

zoomxy::~zoomxy()
{
    delete ui;
}


void zoomxy::on_buttonBox_accepted()
{
    QString x1=ui->lineEdit1->text();
    QString x2=ui->lineEdit2->text();
    xxx = x1.toDouble();
    yyy = x2.toDouble();
}
double zoomxy::getInputx()
{
    return xxx;
}
double zoomxy::getInputy()
{
    return yyy;
}
