#ifndef THRESHOLDINPUT_H
#define THRESHOLDINPUT_H

#include <QDialog>

namespace Ui {
class thresholdInput;
}

class thresholdInput : public QDialog
{
    Q_OBJECT

public:
    explicit thresholdInput(QWidget *parent = 0);
    ~thresholdInput();
    int getInputx();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::thresholdInput *ui;
    int xxx;
};

#endif // THRESHOLDINPUT_H
