#ifndef GRAYIMAGE_H
#define GRAYIMAGE_H
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QTextCodec>
#include <QMessageBox>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
class GrayImage
{
public:
    GrayImage();
    bool Cal_Hist(Mat Gray_img, MatND &hist);
    void DrawGrayHist(const char* pTitle, MatND& hist);
    void one_channel_hist_specify(Mat input_img, Mat dst_img, Mat &output_img);
    void three_channel_hist_specify(Mat input_img, Mat dst_img, Mat &output_img);
};

#endif // GRAYIMAGE_H
