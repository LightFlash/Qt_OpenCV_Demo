#include <QCoreApplication>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mat srcImg = imread("D:/OpenCVImg/0002-1.jpg");
    imshow("srcImg", srcImg);

    //矩形腐蚀
    Mat element = getStructuringElement(MORPH_RECT, Size(20, 20));
    Mat dstImg;
    erode(srcImg, dstImg, element);
    imshow("dstImg", dstImg);
    return a.exec();
}
