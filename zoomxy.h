#ifndef ZOOMXY_H
#define ZOOMXY_H

#include <QDialog>

namespace Ui {
class zoomxy;
}

class zoomxy : public QDialog
{
    Q_OBJECT

public:
    explicit zoomxy(QWidget *parent = 0);
    ~zoomxy();
    double getInputx();
    double getInputy();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::zoomxy *ui;
    double xxx;
    double yyy;
};

#endif // ZOOMXY_H
