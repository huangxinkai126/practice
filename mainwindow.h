#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QTextCodec>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<QLineEdit>
#include<Windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static cv::Mat copysrc;


private slots:
    void on_actionNew_file_triggered();

    void DisplayMat(cv::Mat image);

    void DisplayMat2(cv::Mat image);

    void DisplayMat3(cv::Mat image);


    void on_actionTranslation_triggered();

    void on_actionZoom_triggered();

    void on_actionRotate_triggered();

    void on_actionGrayChange_triggered();

    void on_actionGrayLevelav_triggered();

    void on_actionGrayLevelrule_triggered();

    void on_actionGrayLevelRe_triggered();

    void on_actionGrayBinaryzation_triggered();

    void on_actionFourAveFl_triggered();

    void on_actionEightAveFl_triggered();

    void on_actionTemplateFl_triggered();

    void on_actionGaussianFl_triggered();

    void on_actionMidFl_triggered();

    void on_actionBilateralFl_triggered();

    void on_actionUserDefined_triggered();

    void on_actionSharpen_triggered();

    void on_actionConstIncrease_triggered();

    void on_actionColorReverse_triggered();



    void on_actionQgradient_triggered();

    void on_actionRoberts_triggered();

    void on_actionPrewitt_triggered();

    void on_actionSobel_triggered();

    void on_actionFourLaplacian_triggered();

    void on_actionEightLaplacian_triggered();

    void on_actionLogWay_triggered();

    void on_actionCropImage_triggered();

    void on_actionPlateRecognition_triggered();

    void on_actionSavePicture_triggered();

    void on_actionIntrotuce_triggered();

private:
    Ui::MainWindow *ui;
     cv::Mat image;
     cv::Mat saveImage;
};

#endif // MAINWINDOW_H
