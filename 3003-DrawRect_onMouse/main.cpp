#include <opencv2/opencv.hpp>
using namespace cv;
#define WINDOW_NAME "【程序窗口】"

void onMouseHandle(int event, int x, int y, int flags, void* prama);
void DrawRectangle(Mat& img, Rect box);
void ShowHelpText();

Rect g_rectangle;
bool g_bDrawingBox = false; //是否进行绘制
RNG g_rng(12345);  //随机数生成器


int main()
{
    g_rectangle = Rect(-1,-1,0,0);
    Mat srcImage(600, 800, CV_8UC3), tempImage;
    srcImage.copyTo(tempImage);
    g_rectangle = Rect(-1,-1,0,0);
    srcImage = Scalar::all(0);

    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, onMouseHandle, (void*)&srcImage);

    while (1) {
        srcImage.copyTo(tempImage);
        if (g_bDrawingBox) DrawRectangle(tempImage, g_rectangle); //绘制矩形
        imshow(WINDOW_NAME, tempImage);
        if (waitKey(10) == 27) break;  // 按下"Esc"键退出程序
    }
    return 0;
}

//--------------------------------【onMouseHandle( )回调函数】------------------------------------
//		描述：鼠标操作回调， 根据不同的鼠标事件进行不同操作
//-------------------------------------------------------------------------------------------------
void onMouseHandle(int event, int x, int y, int flags, void* prama)
{
    Mat& image = *(Mat*) prama;
    switch (event) {
    case EVENT_MOUSEMOVE:  //鼠标移动
    {
        if (g_bDrawingBox) //如果进行绘制标识符为真，记录长宽到Rect型变量中
        {
            g_rectangle.width = x-g_rectangle.x;
            g_rectangle.height = y-g_rectangle.y;
        }
    }
        break;
    case EVENT_LBUTTONDBLCLK:  //鼠标左键按下
    {
        g_bDrawingBox = true;
        g_rectangle = Rect(x, y, 0, 0);
    }
        break;
    case EVENT_LBUTTONUP:  //鼠标左键松开
    {
        g_bDrawingBox = false;
        if (g_rectangle.width <0)   //对宽和高小于0的处理(例如鼠标从右下往左上)
        {
            g_rectangle.x += g_rectangle.width;
            g_rectangle.width *= -1;
        }
        if (g_rectangle.height <0)
        {
            g_rectangle.y += g_rectangle.height;
            g_rectangle.height *= -1;
        }
        DrawRectangle(image, g_rectangle);
    }
        break;
    }
}

//--------------------------------【DrawRectale()函数】------------------------------------
//		描述：自定义的矩形绘制函数
//-------------------------------------------------------------------------------------------------
void DrawRectangle(Mat& img, Rect box)
{
    rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}
