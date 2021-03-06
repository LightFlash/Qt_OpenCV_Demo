#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//-----------------【全局变量声明】-----------------
//  描述： 全局变量声明
//------------------------------------------------

//输入和输出图像
Mat srcImage, boxBlurImage, meanBlurImage, gaussBlurImage, medianBlurImage, bilateralImage;

//滤波系数
int boxBlurValue=3, meanBlurValue=3, gaussBlurValue=3, medianBlurValue=3, bilateralValue=3;

//轨迹条回调函数
static void on_boxBlur(int, void*);         //方框滤波
static void on_meanBlur(int, void*);        //均值滤波
static void on_gaussBlur(int, void*);       //高斯滤波
static void on_medianBlur(int, void*);      //中值滤波
static void on_bilateralBlur(int, void*);   //双边滤波


//-----------------【main()主函数】-----------------
//  描述： 控制台应用程序的入口函数
//------------------------------------------------
int main()
{
    system("color 5E");  //背景颜色
    srcImage = imread("D:/OpenCVImg/6001-1.jpg");
    if ( !srcImage.data)
    {
       printf("读取图片失败！");
       return false;
    }

    boxBlurImage    = srcImage.clone();
    meanBlurImage   = srcImage.clone();
    gaussBlurImage  = srcImage.clone();
    medianBlurImage = srcImage.clone();
    bilateralImage  = srcImage.clone();

    namedWindow("【原图】");
    imshow("【原图】", srcImage);

    //方框滤波控制条
    namedWindow("【方框滤波】");
    createTrackbar("内核值：", "【方框滤波】", &boxBlurValue, 50, on_boxBlur);
    on_boxBlur(boxBlurValue, 0);
    //imshow("【方框滤波】", boxBlurImage);

    //均值滤波控制条
    namedWindow("【均值滤波】");
    createTrackbar("内核值：", "【均值滤波】", &meanBlurValue, 50, on_meanBlur);
    on_meanBlur(meanBlurValue, 0);
    //imshow("【均值滤波】", meanBlurImage);

    //高斯滤波控制条
    namedWindow("【高斯滤波】");
    createTrackbar("内核值：", "【高斯滤波】", &gaussBlurValue, 50, on_gaussBlur);
    on_gaussBlur(gaussBlurValue, 0);
    //imshow("【高斯滤波】", gaussBlurImage);

    //中值滤波控制条
    namedWindow("【中值滤波】");
    createTrackbar("内核值：", "【中值滤波】", &medianBlurValue, 50, on_medianBlur);
    on_medianBlur(medianBlurValue, 0);
    //imshow("【中值滤波】", medianBlurImage);

    //双边滤波控制条
    namedWindow("【双边滤波】");
    createTrackbar("内核值：", "【双边滤波】", &bilateralValue, 50, on_bilateralBlur);
    on_bilateralBlur(bilateralValue, 0);
    //imshow("【双边滤波】", bilateralImage);

    while (char(waitKey(1)) != 'q') {};
    return 0;
}

static void on_boxBlur(int, void*)
{
    boxFilter(srcImage, boxBlurImage, -1, Size(boxBlurValue/2*2+1, boxBlurValue/2*2+1));
    imshow("【方框滤波】", boxBlurImage);
}

static void on_meanBlur(int, void*)
{
    blur(srcImage, meanBlurImage, Size(meanBlurValue/2*2+1, meanBlurValue/2*2+1));
    imshow("【均值滤波】", meanBlurImage);
}

static void on_gaussBlur(int, void*)
{
    GaussianBlur(srcImage, gaussBlurImage, Size(gaussBlurValue/2*2+1, gaussBlurValue/2*2+1), 0);
    imshow("【高斯滤波】", gaussBlurImage);
}

static void on_medianBlur(int, void*)
{
    medianBlur(srcImage, medianBlurImage, medianBlurValue/2*2+1);
    imshow("【中值滤波】", medianBlurImage);
}

static void on_bilateralBlur(int, void*)
{
    bilateralFilter(srcImage, bilateralImage, bilateralValue, bilateralValue*2, bilateralValue/2);
    imshow("【双边滤波】", bilateralImage);
}
