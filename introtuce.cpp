#include "introtuce.h"
#include "ui_introtuce.h"

introtuce::introtuce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::introtuce)
{
    ui->setupUi(this);
}

introtuce::~introtuce()
{
    delete ui;
}
