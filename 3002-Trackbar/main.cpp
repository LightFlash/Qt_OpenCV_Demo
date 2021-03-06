#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

# define WINDOW_NAME "【线性混合示例】"
/*--------------【全局变量声明部分】-------------
// 描述： 全局变量声明
//--------------------------------------------*/
const int g_nMaxAlphaValue = 100;  //Alpha值的最大值
int g_nAlphaValueSlider;  //滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明图像变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

/*--------------【on_Trackbar()函数】-------------
// 描述： 相应滑动条的回调函数
//--------------------------------------------*/
void on_Trackbat(int, void*)
{
    //求出当前alpha值相对于最大值的比例
    g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue;
    //beta值为 1-alpha
    g_dBetaValue = 1-g_dAlphaValue;

    //线性混合图像
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

    //图像结果显示
    imshow(WINDOW_NAME, g_dstImage);
}

/*--------------【main()函数】-------------
// 描述： 控制台入口函数
//--------------------------------------------*/
int main()
{
    //加载图像
    g_srcImage1 = imread("D:/OpenCVImg/3002-1.jpg");
    g_srcImage2 = imread("D:/OpenCVImg/3002-2.jpg");
    if (!g_srcImage1.data)
        printf("读取第一张图片错误，请确定目录下是否有图片！");
    if (!g_srcImage2.data)
        printf("读取第二张图片错误，请确定目录下是否有图片！");

    g_nAlphaValueSlider = 70; //设置滑动条初始值
    namedWindow(WINDOW_NAME, CV_LOAD_IMAGE_COLOR); //创建窗体

    //在窗体中创建滑动条，命名为“透明值：xx”
    char trackbarName[50];
    sprintf(trackbarName, "透明值 %d", g_nMaxAlphaValue);
    createTrackbar(trackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbat);

    on_Trackbat(g_nAlphaValueSlider, 0); //加上这句主要是用于程序第一次运行时显示结果。没有这一句，拉动滑动条时也会调用on_Trackbar();
    printf("滑动条位置: %d", getTrackbarPos(trackbarName, WINDOW_NAME)); //获取滑动条位置，但是似乎不会实时更新

    waitKey(0);

    return 0;
}
