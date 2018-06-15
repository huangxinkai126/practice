#include "thresholdinput.h"
#include "ui_thresholdinput.h"

thresholdInput::thresholdInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thresholdInput)
{
    ui->setupUi(this);
    xxx=0;
}

thresholdInput::~thresholdInput()
{
    delete ui;
}

void thresholdInput::on_buttonBox_accepted()
{
    QString x1=ui->lineEdit->text();
    xxx = x1.toDouble();
}
int thresholdInput::getInputx()
{
    return xxx;
}
