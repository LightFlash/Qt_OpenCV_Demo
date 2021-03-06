#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
    Mat girl=imread("D:/OpenCVImg/3001-girl.jpg");
    namedWindow("【1】动漫图");
    imshow("【1】动漫图", girl);

    Mat image = imread("D:/OpenCVImg/3001-dota.jpg");
    Mat logo  = imread("D:/OpenCVImg/3001-dota_logo.jpg");
    namedWindow("【2】原画图");
    imshow("【2】原画图", image);
    namedWindow("【3】Logo");
    imshow("【3】Logo", logo);

    Mat imageROI;
    imageROI = image(Rect(800, 350, logo.cols, logo.rows));
    addWeighted(imageROI, 0.5, logo, 0.3, 0, imageROI);

    namedWindow("【4】原画图+Logo图");
    imshow("【4】原画图+Logo图", image);

    imwrite("由imwrite生成的图片.jpg", image);

    waitKey();
    return 0;
}
