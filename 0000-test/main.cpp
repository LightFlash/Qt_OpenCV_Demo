#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    int a = 1;
    cout << "现在使用的OpenCV版本是 OpenCV"  << CV_VERSION << endl;

    Mat img = imread("D:\\OpenCVImg\\0001-1.jpg", -1);
    namedWindow("图片", WINDOW_NORMAL);
    imshow("图片", img);
    waitKey(1000);
    //destroyWindow("图片");
    return 0;
}
