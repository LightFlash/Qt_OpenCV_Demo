#include <QCoreApplication>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mat img = imread("D:/OpenCVImg/0001-1.jpg");
    imshow("Picture", img);
    return a.exec();
}
