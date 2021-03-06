#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
enum sobelType{ X, Y, ALL };

Mat CannyImage(const Mat& srcImg)
{
    Mat dstImg, grayImg, edges;
    dstImg.create(srcImg.size(), srcImg.type());
    cvtColor(srcImg, grayImg, CV_BGR2GRAY);
    blur(grayImg, edges, Size(3, 3));
    int lowThresh = 1;
    Canny(edges, edges, lowThresh, lowThresh*3);
    srcImg.copyTo(dstImg, edges);
    return dstImg;
}

Mat SobelImage(const Mat& srcImg, int type)
{
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat dstImg;
    if (type == X)
    {
        Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
        convertScaleAbs(grad_x, abs_grad_x);
        return abs_grad_x;
    }
    else if (type == Y)
    {
        Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
        convertScaleAbs(grad_y, abs_grad_y);
        return abs_grad_y;
    }
    else
    {
        Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_x, abs_grad_x);

        Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_y, abs_grad_y);

        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstImg);
        return dstImg;
    }
}

Mat ScharrImage(const Mat& srcImg, int type)
{
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat dstImg;
    if (type == X)
    {
        Scharr(srcImg, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_x, abs_grad_x);
        return abs_grad_x;
    }
    else if (type == Y)
    {
        Scharr(srcImg, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_y, abs_grad_y);
        return abs_grad_y;
    }
    else
    {
        Scharr(srcImg, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_x, abs_grad_x);

        Scharr(srcImg, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(grad_y, abs_grad_y);

        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstImg);
        return dstImg;
    }
}

int main()
{
    //Mat srcImg = imread("D:/OpenCVImg/7001-1.jpg");
    Mat srcImg = imread("D:/OpenCVImg/7001-2.jpg");
    Mat dstImg;
    imshow("Sourse Image", srcImg);
    //**************************************  Sobel函数测试  **************************************//
    double start = static_cast<double>(cvGetTickCount()); //计时 us级
    //dstImg = CannyImage(srcImg);
    dstImg = SobelImage(srcImg, X);
    double time =  ((double)cvGetTickCount()-start)/cvGetTickFrequency(); //计时结束
    imshow("Sobel X Image", dstImg);
    cout << "Process Time is " << time/1000.0 << "ms" << endl;

    start = static_cast<double>(cvGetTickCount()); //计时 us级
    //Mat dstImg = CannyImage(srcImg);
    dstImg = SobelImage(srcImg, Y);
    time =  ((double)cvGetTickCount()-start)/cvGetTickFrequency(); //计时结束
    imshow("Sobel Y Image", dstImg);
    cout << "Process Time is " << time/1000.0 << "ms" << endl;

    start = static_cast<double>(cvGetTickCount()); //计时 us级
    //Mat dstImg = CannyImage(srcImg);
    dstImg = SobelImage(srcImg, ALL);
    time =  ((double)cvGetTickCount()-start)/cvGetTickFrequency(); //计时结束
    imshow("Sobel Image", dstImg);
    cout << "Process Time is " << time/1000.0 << "ms" << endl;

    //**************************************  Scharr函数测试  **************************************//
    start = static_cast<double>(cvGetTickCount()); //计时 us级
    //Mat dstImg = CannyImage(srcImg);
    dstImg = ScharrImage(srcImg, X);
    time =  ((double)cvGetTickCount()-start)/cvGetTickFrequency(); //计时结束
    imshow("Scharr X Image", dstImg);
    cout << "Process Time is " << time/1000.0 << "ms" << endl;

    start = static_cast<double>(cvGetTickCount()); //计时 us级
    //Mat dstImg = CannyImage(srcImg);
    dstImg = ScharrImage(srcImg, Y);
    time =  ((double)cvGetTickCount()-start)/cvGetTickFrequency(); //计时结束
    imshow("Scharr Y Image", dstImg);
    cout << "Process Time is " << time/1000.0 << "ms" << endl;

    start = static_cast<double>(cvGetTickCount()); //计时 us级
    //Mat dstImg = CannyImage(srcImg);
    dstImg = ScharrImage(srcImg, ALL);
    time =  ((double)cvGetTickCount()-start)/cvGetTickFrequency(); //计时结束
    imshow("Scharr Image", dstImg);
    cout << "Process Time is " << time/1000.0 << "ms" << endl;
    waitKey(0);
   return 0;
}
