#include "mainwindow.h"
#include"transformation.h"
#include "ui_mainwindow.h"
#include"movexy.h"
#include "zoomxy.h"
#include"rotateangle.h"
#include"grayimage.h"
#include"thresholdinput.h"
#include"definedfilter.h"
#include"getrect.h"
#include"introtuce.h"
using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_file_triggered()                                        //文件打开系统
{
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),".",tr("Image File (*.jpg *.png *.bmp)"));
    QTextCodec *code = QTextCodec::codecForName("gb18030");
    std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
    image = cv::imread(name);
  //  copysrc=image.clone();
    if(!image.data)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Image Data Is Null"));
        msgBox.exec();
    }
    else {
       DisplayMat(image);
    }
}

void MainWindow::DisplayMat(cv::Mat image)
{
    cv::Mat rgb;
    QImage img;
    if(image.channels() == 3)
    {
        cvtColor(image,rgb,CV_BGR2RGB);
        img = QImage((const unsigned char*)(rgb.data),
                     rgb.cols,rgb.rows,rgb.cols*rgb.channels(),
                     QImage::Format_RGB888);
    }
    else
    {
        img = QImage((const unsigned char*)(image.data),
                     image.cols,image.rows,rgb.cols*image.channels(),
                     QImage::Format_RGB888);
    }
    ui->labelimage1->setPixmap(QPixmap::fromImage(img).scaled(ui->labelimage1->size()));
    ui->labelimage1->resize(ui->labelimage1->pixmap()->size());
}

void MainWindow::DisplayMat2(cv::Mat image)                                            //显示的是彩色图像
{
    cv::Mat rgb;
    saveImage=image.clone();
    QImage img;
    if(image.channels() == 3)
    {
        cvtColor(image,rgb,CV_BGR2RGB);
        img = QImage((const unsigned char*)(rgb.data),
                     rgb.cols,rgb.rows,rgb.cols*rgb.channels(),
                     QImage::Format_RGB888);
    }
    else
    {
        img = QImage((const unsigned char*)(image.data),
                     image.cols,image.rows,rgb.cols*image.channels(),
                     QImage::Format_RGB888);
    }
    ui->labelimage2->setPixmap(QPixmap::fromImage(img).scaled(ui->labelimage1->size()));
    ui->labelimage2->resize(ui->labelimage1->pixmap()->size());

}

void MainWindow::DisplayMat3(cv::Mat image)                            //显示的是灰度图像
{
    QImage img;
    saveImage=image.clone();
    img = QImage((const unsigned char*)(image.data),
                     image.cols,image.rows,image.cols*image.channels(),
                     QImage::Format_Grayscale8);

    ui->labelimage2->setPixmap(QPixmap::fromImage(img).scaled(ui->labelimage1->size()));
    ui->labelimage2->resize(ui->labelimage1->pixmap()->size());

}

void MainWindow::on_actionTranslation_triggered()
{
    Mat src;
    int x=0;
    int y=0;
    movexy * c = new movexy(this);
    c->exec();

     x = c->getInputx();
     y = c->getInputy();


    transformation::translateTransformSize(image,src,x,y);
    DisplayMat2(src);
}

void MainWindow::on_actionZoom_triggered()
{
    Mat src;
    double x=1.0;
    double y=1.0;
    zoomxy * c = new zoomxy(this);
    c->exec();

     x = c->getInputx();
     y = c->getInputy();
     x=int(x*image.cols);
     y=int(y*image.rows);
     if(x<=0||y<=0)
     {
         x=1;
         y=1;
     }
    // imshow("formal", image);
     cv::resize(image,src,Size(x,y));
     //imshow("after",src);
     DisplayMat2(src);

}

void MainWindow::on_actionRotate_triggered()
{
    Mat src;
    double x=0;
    rotateAngle * c = new rotateAngle(this);
    c->exec();
    x=c->getDoublex();

    transformation::imageRotate1(image,src,x);
    DisplayMat2(src);


}

void MainWindow::on_actionGrayChange_triggered()
{
    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);
    DisplayMat3(src);
}


void MainWindow::on_actionGrayLevelav_triggered()
{
    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);
    equalizeHist(src,src);
    DisplayMat3(src);
}

void MainWindow::on_actionGrayLevelrule_triggered()
{
    Mat src;
    Mat src2;

    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    QString filename2 = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),".",tr("Image File (*.jpg *.png *.bmp)"));
    QTextCodec *code2 = QTextCodec::codecForName("gb18030");
    std::string ruleimage = code2->fromUnicode(filename2).data();//filename.toAscii().data()
    src2 = cv::imread(ruleimage);

    cvtColor(src2,src2,COLOR_BGR2GRAY);

    Mat output_img;
    GrayImage x;
    x.one_channel_hist_specify(src, src2, output_img);
    DisplayMat3(output_img);
}



void MainWindow::on_actionGrayLevelRe_triggered()
{
    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
    {for(j=0; j< width; j++){src.at<uchar>(i, j)= 255- src.at<uchar>(i, j);}}
    DisplayMat3(src);

}

void MainWindow::on_actionGrayBinaryzation_triggered()
{
    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);
    thresholdInput * c = new thresholdInput(this);
    c->exec();
    int x=0;
    x = c->getInputx();
    if(x<0||x>255)x=0;
    threshold(src,src,x,255,CV_THRESH_BINARY);
    DisplayMat3(src);

}

void MainWindow::on_actionFourAveFl_triggered()
{
    Mat src;
    src=image.clone();
    Mat array = (Mat_<float>(3, 3) <<0, 1/4.0, 0, 1/4.0, 0,1/4.0, 0, 1/4.0, 0);
    filter2D(src,src,-1,array,Point(-1,-1),0);
    DisplayMat2(src);
}

void MainWindow::on_actionEightAveFl_triggered()
{
    Mat src;
    src=image.clone();
    Mat array = (Mat_<float>(3, 3) <<1/8.0, 1/8.0,1/8.0, 1/8.0, 0,1/8.0, 1/8.0,1/8.0,1/8.0);
    filter2D(src,src,-1,array,Point(-1,-1),0);
    DisplayMat2(src);
}

void MainWindow::on_actionTemplateFl_triggered()
{
    Mat src;
    src=image.clone();
    blur(src,src,Size(10,10));
    DisplayMat2(src);
}

void MainWindow::on_actionGaussianFl_triggered()
{
    Mat src;
    src=image.clone();
    GaussianBlur(src,src,Size(5,5),5,5);
    DisplayMat2(src);
}

void MainWindow::on_actionMidFl_triggered()
{
    Mat src;
    src=image.clone();
    medianBlur(src,src,5);
    DisplayMat2(src);
}

void MainWindow::on_actionBilateralFl_triggered()
{
    Mat src;

    bilateralFilter(image,src,5,100,3);
    DisplayMat2(src);
}

void MainWindow::on_actionUserDefined_triggered()
{
    Mat src;
    src=image.clone();

    double x1=0;
    double x2=0;
    double x3=0;
    double x4=0;
    double x5=0;
    double x6=0;
    double x7=0;
    double x8=0;
    double x9=0;

    definedFilter * c = new definedFilter(this);
    c->exec();

    x1=c->getInput1();
    x2=c->getInput2();
    x3=c->getInput3();
    x4=c->getInput4();
    x5=c->getInput5();
    x6=c->getInput6();
    x7=c->getInput7();
    x8=c->getInput8();
    x9=c->getInput9();
    if(x1+x2+x3+x4+x5+x6+x7+x8+x9<0)
    {
        x1=0;
        x2=0;
        x3=0;
        x4=0;
        x5=1;
        x6=0;
        x7=0;
        x8=0;
        x9=0;
    }

    Mat array = (Mat_<double>(3, 3) <<x1,x2,x3,x4,x5,x6,x7,x8,x9);
    filter2D(src,src,-1,array,Point(-1,-1),0);
    DisplayMat2(src);
}

void MainWindow::on_actionSharpen_triggered()
{
    Mat src;
    src=image.clone();


    Mat array = (Mat_<double>(3, 3) <<-2,-2,-2,-2,17,-2,-2,-2,-2);
    filter2D(src,src,-1,array,Point(-1,-1),0);
    DisplayMat2(src);
}

void MainWindow::on_actionConstIncrease_triggered()
{
    Mat src1;
    src1=image.clone();
    IplImage *src= &IplImage(src1);

    IplImage *ycb = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3);


    cvCvtColor(src,ycb,CV_BGR2YCrCb);


    IplImage *y = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
    IplImage *cr = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
    IplImage *cb = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);



    cvSplit(ycb,y,cr,cb,0);
    Mat img;
    img=cvarrToMat(y);


    equalizeHist(img,img);
    y = &IplImage(img);

    IplImage *dst = cvCreateImage(cvGetSize(ycb),IPL_DEPTH_8U,3);

    cvMerge(y,cr,cb,0,dst);


    cvCvtColor(dst,dst,CV_YCrCb2BGR);
    Mat img1;
    img1=cvarrToMat(dst);
    DisplayMat2(img1);

}

void MainWindow::on_actionColorReverse_triggered()
{
    Mat src;
    src=image.clone();
    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   src.at<uchar>(i, j)= 255- src.at<uchar>(i, j);   // 每一个像素反转
               }
           }
     DisplayMat2(src);

}



void MainWindow::on_actionQgradient_triggered()
{
    int T=10;//阙值

    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    Mat Wh = (Mat_<double>(3, 3) <<0,0,0,-1,1,0,0,0,0);
    Mat Wv = (Mat_<double>(3, 3) <<0,-1,0,0,1,0,0,0,0);
    Mat Gh;
    Mat Gv;
    filter2D(src,Gh,-1,Wh,Point(-1,-1),0);
    filter2D(src,Gv,-1,Wv,Point(-1,-1),0);

    Mat G;
    G=src.clone();

    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   if(Gh.at<uchar>(i, j)<0)
                       Gh.at<uchar>(i, j)=-Gh.at<uchar>(i, j);
                   if(Gv.at<uchar>(i, j)<0)
                       Gv.at<uchar>(i, j)=-Gv.at<uchar>(i, j);

                   if( Gh.at<uchar>(i, j)+Gv.at<uchar>(i, j)>T)
                        G.at<uchar>(i, j)=0;
                   else
                        G.at<uchar>(i, j)=255;

               }
           }
     DisplayMat3(G);
}

void MainWindow::on_actionRoberts_triggered()
{
    int T=10;//阙值

    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    Mat Wh = (Mat_<double>(3, 3) <<-1,0,0,0,1,0,0,0,0);
    Mat Wv = (Mat_<double>(3, 3) <<0,-1,0,1,0,0,0,0,0);
    Mat Gh;
    Mat Gv;
    filter2D(src,Gh,-1,Wh,Point(-1,-1),0);
    filter2D(src,Gv,-1,Wv,Point(-1,-1),0);

    Mat G;
    G=src.clone();

    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   if(Gh.at<uchar>(i, j)<0)
                       Gh.at<uchar>(i, j)=-Gh.at<uchar>(i, j);
                   if(Gv.at<uchar>(i, j)<0)
                       Gv.at<uchar>(i, j)=-Gv.at<uchar>(i, j);

                   if( Gh.at<uchar>(i, j)+Gv.at<uchar>(i, j)>T)
                        G.at<uchar>(i, j)=0;
                   else
                        G.at<uchar>(i, j)=255;

               }
           }
     DisplayMat3(G);
}

void MainWindow::on_actionPrewitt_triggered()
{
    int T=10;//阙值

    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    Mat Wh = (Mat_<double>(3, 3) <<-1/3.0,0,1/3.0,-1/3.0,0,1/3.0,-1/3.0,0,1/3.0);
    Mat Wv = (Mat_<double>(3, 3) <<-1/3.0,-1/3.0,-1/3.0,0,0,0,1/3.0,1/3.0,1/3.0);
    Mat Gh;
    Mat Gv;
    filter2D(src,Gh,-1,Wh,Point(-1,-1),0);
    filter2D(src,Gv,-1,Wv,Point(-1,-1),0);

    Mat G;
    G=src.clone();

    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   if(Gh.at<uchar>(i, j)<0)
                       Gh.at<uchar>(i, j)=-Gh.at<uchar>(i, j);
                   if(Gv.at<uchar>(i, j)<0)
                       Gv.at<uchar>(i, j)=-Gv.at<uchar>(i, j);

                   if( Gh.at<uchar>(i, j)+Gv.at<uchar>(i, j)>T)
                        G.at<uchar>(i, j)=0;
                   else
                        G.at<uchar>(i, j)=255;

               }
           }
     DisplayMat3(G);
}

void MainWindow::on_actionSobel_triggered()
{
    int T=10;//阙值

    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    Mat Wh = (Mat_<double>(3, 3) <<-1/4.0,0,1/4.0,-1/2.0,0,1/2.0,-1/4.0,0,1/4.0);
    Mat Wv = (Mat_<double>(3, 3) <<-1/4.0,-1/2.0,-1/4.0,0,0,0,1/4.0,1/2.0,1/4.0);
    Mat Gh;
    Mat Gv;
    filter2D(src,Gh,-1,Wh,Point(-1,-1),0);
    filter2D(src,Gv,-1,Wv,Point(-1,-1),0);

    Mat G;
    G=src.clone();

    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   if(Gh.at<uchar>(i, j)<0)
                       Gh.at<uchar>(i, j)=-Gh.at<uchar>(i, j);
                   if(Gv.at<uchar>(i, j)<0)
                       Gv.at<uchar>(i, j)=-Gv.at<uchar>(i, j);

                   if( Gh.at<uchar>(i, j)+Gv.at<uchar>(i, j)>T)
                        G.at<uchar>(i, j)=0;
                   else
                        G.at<uchar>(i, j)=255;

               }
           }
     DisplayMat3(G);
}

void MainWindow::on_actionFourLaplacian_triggered()
{
    int T=10;//阙值

    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    Mat W = (Mat_<double>(3, 3) <<0,-1,0,-1,4,-1,0,-1,0);
    Mat G;
    filter2D(src,G,-1,W,Point(-1,-1),0);


    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   if(G.at<uchar>(i, j)<0)
                       G.at<uchar>(i, j)=-G.at<uchar>(i, j);


                   if( G.at<uchar>(i, j)>T)
                        G.at<uchar>(i, j)=0;
                   else
                        G.at<uchar>(i, j)=255;

               }
           }
     DisplayMat3(G);
}

void MainWindow::on_actionEightLaplacian_triggered()
{
    int T=10;//阙值

    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);

    Mat W = (Mat_<double>(3, 3) <<-1,-1,-1,-1,8,-1,-1,-1,-1);
    Mat G;
    filter2D(src,G,-1,W,Point(-1,-1),0);


    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   if(G.at<uchar>(i, j)<0)
                       G.at<uchar>(i, j)=-G.at<uchar>(i, j);


                   if( G.at<uchar>(i, j)>T)
                        G.at<uchar>(i, j)=0;
                   else
                        G.at<uchar>(i, j)=255;

               }
           }
     DisplayMat3(G);
}

void MainWindow::on_actionLogWay_triggered()
{
    int T=10;//阙值

    Mat src;
    src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);
    GaussianBlur(src,src,Size(5,5),5,5);

    Mat W = (Mat_<double>(3, 3) <<-1,-1,-1,-1,8,-1,-1,-1,-1);
    Mat G;
    filter2D(src,G,-1,W,Point(-1,-1),0);


    int height;  //定义变量
    int width;
    int i;
    int j;
    height= src.rows;
    width= src.cols* src.channels();
    for(i= 0; i< height; i++)
           {
               for(j=0; j< width; j++)
               {
                   if(G.at<uchar>(i, j)<0)
                       G.at<uchar>(i, j)=-G.at<uchar>(i, j);


                   if( G.at<uchar>(i, j)>T)
                        G.at<uchar>(i, j)=0;
                   else
                        G.at<uchar>(i, j)=255;

               }
           }
     DisplayMat3(G);
}

void MainWindow::on_actionCropImage_triggered()
{
    Mat src;
    src=image.clone();

    double x;
    double y;
    double h;
    double v;

    getRect * c = new getRect(this);
    c->exec();
    x=c->getDoublex();
    y=c->getDoubley();
    h=c->getDoubleh();
    v=c->getDoublev();



    if(x<0||y<0||x>src.cols||y>src.rows)
    {
        x=0,y=0;
    }
    if(h<0||h>src.cols+x||v<0||v>src.rows)
    {
        h=0,v=0;
    }
    Rect rect(x,y,h,v);
    transformation::imageCrop(src,src,rect);
    DisplayMat2(src);
}

void MainWindow::on_actionPlateRecognition_triggered()
{
    Mat src=image.clone();
    cvtColor(src,src,COLOR_BGR2GRAY);//转化为灰度图
    Canny(src, src, 500, 200, 3);
    threshold(src,src,100,255,CV_THRESH_BINARY);
    imshow("canny",src);

    Mat dilate_image, erode_image;                          //X方向膨胀腐蚀

    Mat elementX = getStructuringElement(MORPH_RECT, Size(25, 1));
    Mat elementY = getStructuringElement(MORPH_RECT, Size(1, 19));
    Point point(-1, -1);
    dilate(src, dilate_image, elementX, point, 2);
    erode(dilate_image, erode_image, elementX, point, 4);
    dilate(erode_image, dilate_image, elementX, point, 2);

    erode(dilate_image, erode_image, elementY, point,1 );   //Y方向膨胀腐蚀
    dilate(erode_image, dilate_image, elementY, point, 2);



    Mat blurr_image;                                        //平滑处理
    medianBlur(dilate_image, blurr_image, 15);
    medianBlur(blurr_image, blurr_image, 15);
                                                       imshow("meidablur", blurr_image);

    vector< vector< Point> > contours;                      //取轮廓
    findContours(blurr_image,contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


    vector<Rect> boundRect(contours.size());  //定义外接矩形集合
    vector<RotatedRect> box(contours.size()); //定义最小外接矩形集合
    Point2f rect[4];
    Mat dstImg =blurr_image.clone();
    for(int i=0;i<contours.size();i++)                                            //获得最小外界矩阵并存储在box数组中
   {
     box[i] = minAreaRect(Mat(contours[i]));  //计算每个轮廓最小外接矩形
                      boundRect[i] = boundingRect(Mat(contours[i]));


                     }
    for(int i=0;i<contours.size();i++)
   {

     box[i].points(rect);  //把最小外接矩形四个端点复制给rect数组
     double longs;
     double width;
     longs=rect[3].x-rect[1].x;
     width=rect[3].y-rect[1].y;
     double  bili;
     if(width==0)width=0.00001;
     bili=longs/width;
     if(bili<2.5||bili>4.2)
         continue;


     Rect rect1(rect[1],rect[3]);
     transformation::imageCrop(src,dstImg,rect1);
     break;
   }
     cout<<endl<<rect[0]<<endl;
     cout<<endl<<rect[1]<<endl;
     cout<<endl<<rect[2]<<endl;
     cout<<endl<<rect[3]<<endl;
     cv::resize(dstImg, dstImg, Size(136,36));
                                                     imshow("dst", dstImg);
     DisplayMat3(dstImg);
}

void MainWindow::on_actionSavePicture_triggered()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
        tr("Save Image"), "", tr("Image File (*.jpg *.png *.bmp)"));

    string fileAsSave = fileName.toStdString();
    imwrite(fileAsSave,saveImage);
}

void MainWindow::on_actionIntrotuce_triggered()
{
    introtuce *c=new introtuce;
    c->show();
}
