#include <QCoreApplication>
#include <Qdebug>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    VideoCapture capture("D:/OpenCVImg/0003-1.avi");
    while (1) {
        Mat frame;
        capture >> frame;
        if ( frame.empty() ) break;

        Mat grayImg, destImg;
        cvtColor(frame, grayImg, CV_BGR2GRAY);
        blur (grayImg, destImg, Size(3, 3));  //均值滤波
        Canny (destImg, destImg, 3, 9, 3);
        imshow("Video", destImg);
        waitKey(30);
    }
    return a.exec();
}
