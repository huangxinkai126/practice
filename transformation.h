#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QTextCodec>
#include <QMessageBox>
#include <opencv2/opencv.hpp>

class transformation
{

public:
     transformation();
     static void imageRotate1(cv::Mat src, cv::Mat &dst, double angle);
     static void imageCrop(cv::Mat src,cv::Mat &dst,cv::Rect rect);


signals:

public slots:

public:
    static void translateTransformSize(cv::Mat &src,cv::Mat &dst,int dx,int dy);
};


#endif // TRANSFORMATION_H
