#include "definedfilter.h"
#include "ui_definedfilter.h"

definedFilter::definedFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::definedFilter)
{
    ui->setupUi(this);
    x1=0;
    x2=0;
    x3=0;
    x4=0;
    x5=0;
    x6=0;
    x7=0;
    x8=0;
    x9=0;

}

definedFilter::~definedFilter()
{
    delete ui;
}

void definedFilter::on_buttonBox_accepted()
{
    QString s1=ui->lineEdit1->text();
    QString s2=ui->lineEdit2->text();
    QString s3=ui->lineEdit3->text();
    QString s4=ui->lineEdit4->text();
    QString s5=ui->lineEdit5->text();
    QString s6=ui->lineEdit6->text();
    QString s7=ui->lineEdit7->text();
    QString s8=ui->lineEdit8->text();
    QString s9=ui->lineEdit9->text();

    x1 = s1.toDouble();
    x2 = s2.toDouble();
    x3 = s3.toDouble();
    x4 = s4.toDouble();
    x5 = s5.toDouble();
    x6 = s6.toDouble();
    x7 = s7.toDouble();
    x8 = s8.toDouble();
    x9 = s9.toDouble();
}
double definedFilter:: getInput1()
{
    return x1;
}
double definedFilter:: getInput2()
{
    return x2;
}

double definedFilter:: getInput3()
{
    return x3;
}

double definedFilter:: getInput4()
{
    return x4;
}

double definedFilter:: getInput5()
{
    return x5;
}

double definedFilter:: getInput6()
{
    return x6;
}

double definedFilter:: getInput7()
{
    return x7;
}

double definedFilter:: getInput8()
{
    return x8;
}

double definedFilter:: getInput9()
{
    return x9;
}

