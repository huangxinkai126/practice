#include "transformation.h"

using namespace std;
using namespace cv;

transformation::transformation()
{

}
void transformation::translateTransformSize(cv::Mat &src,cv::Mat &dst,int dx,int dy)
{
    CV_Assert(src.depth() == CV_8U);
    const int rows = src.rows + abs(dy); //输出图像的大小
    const int cols = src.cols + abs(dx);
    dst.create(rows, cols, src.type());
    Vec3b *p;
    for (int i = 0; i < rows; i++)
    {
        p = dst.ptr<Vec3b>(i);
        for (int j = 0; j < cols; j++)
        {
            int x = j - dx;
            int y = i - dy;
            if (x >= 0 && y >= 0 && x < src.cols && y < src.rows)
                p[j] = src.ptr<Vec3b>(y)[x];
        }
    }
}


void transformation::imageRotate1(cv::Mat src, cv::Mat &dst, double angle)//图像旋转
{
        Mat input = src;

        //得到图像大小
        int width = input.cols;
        int height = input.rows;

        //计算图像中心点
        Point2f center;
        center.x = width / 2.0;
        center.y = height / 2.0;

        //获得旋转变换矩阵
        double scale = 1.0;
        Mat trans_mat = getRotationMatrix2D( center, -angle, scale );

        //仿射变换
        warpAffine( input, dst, trans_mat, Size(width, height));

}

void transformation::imageCrop(Mat src,Mat &dst,Rect rect)//给定矩阵的图像切割
{
    Mat input = src;

                  //计算剪切区域：  剪切Rect与源图像所在Rect的交集
    Rect srcRect(0, 0, input.cols, input.rows);
    rect = rect & srcRect;


                           //创建结果图像
    dst.create(Size(rect.width, rect.height), src.type());
    Mat output = dst;

    input(rect).copyTo( output );
    return ;

}
