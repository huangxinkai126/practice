#include "grayimage.h"

using namespace std;
using namespace cv;

GrayImage::GrayImage()
{

}
bool GrayImage::Cal_Hist(Mat Gray_img, MatND &hist){
    int bins = 256;
    int hist_size[] = { bins };
    float range[] = { 0, 256 };
    const float* ranges[] = { range };

    int channels[] = { 0 };
    //计算直方图
    calcHist(&Gray_img, 1, channels, Mat(), // do not use mask
        hist, 1, hist_size, ranges,
        true, // the histogram is uniform
        false);
    if (hist.data == 0) return false;
    return true;
}
void GrayImage::DrawGrayHist(const char* pTitle, MatND& hist)
{
    int hist_height = 256;
    int bins = 256;
    double max_val;  //直方图的最大值
    int scale = 2;   //直方图的宽度
    minMaxLoc(hist, 0, &max_val, 0, 0); //计算直方图最大值

    Mat hist_img = Mat::zeros(hist_height, bins*scale, CV_8UC3); //创建一个直方图图像并初始化为0
    for (int i = 0; i<bins; i++)
    {
        float bin_val = hist.at<float>(i); // 第i灰度级上的数
        int intensity = cvRound(bin_val*hist_height / max_val);  //要绘制的高度
        //填充第i灰度级的数据
        rectangle(hist_img, Point(i*scale, hist_height - 1),
            Point((i + 1)*scale - 1, hist_height - intensity),
            CV_RGB(255, 255, 255));
    }
    imshow(pTitle, hist_img);
}

void GrayImage::one_channel_hist_specify(Mat input_img, Mat dst_img, Mat &output_img)//单通道
{
    int i,j;

    //计算输入，规定图像的直方图
    MatND input_hist, dst_hist;
    Cal_Hist(input_img, input_hist);
    Cal_Hist(dst_img, dst_hist);

    //计算概率直方图
    MatND input_p_hist, dst_p_hist;
    input_p_hist = MatND::zeros(input_hist.size[0], input_hist.size[1], CV_32FC1);//原始概率直方图
    dst_p_hist = MatND::zeros(dst_hist.size[0], dst_hist.size[1], CV_32FC1);//规定概率直方图
    float input_totalnum = 0;
    float dst_totalnum = 0;
    for (i = 0; i < input_hist.rows; i++)
        input_totalnum += input_hist.at<float>(i);
    for (i = 0; i < dst_hist.rows; i++)
        dst_totalnum += dst_hist.at<float>(i);
    for (i = 0; i < input_hist.rows; i++)
        input_p_hist.at<float>(i) = input_hist.at<float>(i) / input_totalnum;
    for (i = 0; i < dst_hist.rows; i++)
        dst_p_hist.at<float>(i) = dst_hist.at<float>(i) / dst_totalnum;

    //计算累计直方图
    MatND input_c_hist, dst_c_hist;
    input_c_hist = MatND::zeros(input_hist.size[0], input_hist.size[1], CV_32FC1);//原始累计直方图
    dst_c_hist = MatND::zeros(dst_hist.size[0], dst_hist.size[1], CV_32FC1);//规定累计直方图
    float input_accum_p = 0;
    float dst_accum_p = 0;
    for (i = 0; i < input_hist.rows; i++)
    {
        input_accum_p += input_p_hist.at<float>(i);
        input_c_hist.at<float>(i) = input_accum_p;
    }
    for (i = 0; i < dst_hist.rows; i++)
    {
        dst_accum_p += dst_p_hist.at<float>(i);
        dst_c_hist.at<float>(i) = dst_accum_p;
    }

    //计算单映射规则
    MatND SML = MatND::zeros(input_hist.size[0], input_hist.size[1], CV_32FC1);//SML单映射规则
    for (i = 0; i < input_c_hist.rows; i++)
    {
        int minind = 0;
        float minval = 1;
        for (j = 0; j < dst_c_hist.rows; j++)
        {
            float abssub = abs(input_c_hist.at<float>(i)-dst_c_hist.at<float>(j));
            if (abssub < minval)
            {
                minval = abssub;
                minind = j;
            }
        }
        SML.at<float>(i) = minind;
    }

    //计算输出图像
    Mat outimg = Mat::zeros(input_img.size[0], input_img.size[1], CV_8U);
    for (i = 0; i < input_img.rows; i++)
    {
        for (j = 0; j < input_img.cols; j++)
        {
            outimg.at<uchar>(i, j) = SML.at<float>(input_img.at<uchar>(i, j));
        }
    }
    outimg.copyTo(output_img);

    //计算输出图像直方图
    //MatND output_hist;
    //Cal_Hist(output_img, output_hist);

    //DrawGrayHist("input_hist", input_hist);
    //DrawGrayHist("dst_hist", dst_hist);
    //DrawGrayHist("output_hist", output_hist);
}

void GrayImage::three_channel_hist_specify(Mat input_img, Mat dst_img, Mat &output_img)//三通道
{
    //Mat src = imread（"path", 1）;  //读入目标图像
    Mat out_img(input_img.rows, input_img.cols, CV_8UC3); //用来存储目的图片的矩阵
    //Mat数组来存车分离后的三个通道，每个通道都初始化为0;
    Mat input_planes[] = { Mat::zeros(input_img.size(), CV_8UC1), Mat::zeros(input_img.size(), CV_8UC1), Mat::zeros(input_img.size(), CV_8UC1) };
    Mat dst_planes[] = { Mat::zeros(dst_img.size(), CV_8UC1), Mat::zeros(dst_img.size(), CV_8UC1), Mat::zeros(dst_img.size(), CV_8UC1) };
    //多通道分成3个单通道,BGR
    split(input_img, input_planes);
    split(dst_img, dst_planes);
    Mat B_output_img, G_output_img, R_output_img;
    one_channel_hist_specify(input_planes[0], dst_planes[0], B_output_img);
    one_channel_hist_specify(input_planes[1], dst_planes[1], G_output_img);
    one_channel_hist_specify(input_planes[2], dst_planes[2], R_output_img);
    Mat output_planes[3];
    output_planes[0] = B_output_img;
    output_planes[1] = G_output_img;
    output_planes[2] = R_output_img;
    merge(output_planes,3, out_img);  //通道合并
    out_img.copyTo(output_img);
}
