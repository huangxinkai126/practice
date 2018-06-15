#ifndef INTROTUCE_H
#define INTROTUCE_H

#include <QDialog>

namespace Ui {
class introtuce;
}

class introtuce : public QDialog
{
    Q_OBJECT

public:
    explicit introtuce(QWidget *parent = 0);
    ~introtuce();

private:
    Ui::introtuce *ui;
};

#endif // INTROTUCE_H
