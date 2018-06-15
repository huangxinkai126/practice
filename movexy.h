#ifndef MOVEXY_H
#define MOVEXY_H

#include <QDialog>


namespace Ui {
class movexy;
}

class movexy : public QDialog
{
    Q_OBJECT

public:
    explicit movexy(QWidget *parent = 0);
    ~movexy();
    double getInputx();
    double getInputy();
private slots:
    void on_buttonBox_accepted();


private:
    Ui::movexy *ui;
    double xxx;
    double yyy;
};

#endif // MOVEXY_H
