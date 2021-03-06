#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void ColorReduce0(Mat& inputImage, Mat& outputImage, int div); //指针访问
void ColorReduce1(Mat& inputImage, Mat& outputImage, int div); //迭代器
void ColorReduce2(Mat& inputImage, Mat& outputImage, int div); //动态地址计算

int main()
{
    Mat srcImage = imread("D:/OpenCVImg/0001-1.jpg");
    imshow("原始图像", srcImage);

    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

    double time0 = static_cast<double>(getTickCount());
    ColorReduce0(srcImage, dstImage, 128);
    time0 = ((double)getTickCount()-time0)/getTickFrequency();
    cout << "方法0耗时： " << time0 << endl;

    time0 = static_cast<double>(getTickCount());
    ColorReduce1(srcImage, dstImage, 128);
    time0 = ((double)getTickCount()-time0)/getTickFrequency();
    cout << "方法1耗时： " << time0 << endl;

    time0 = static_cast<double>(getTickCount());
    ColorReduce2(srcImage, dstImage, 128);
    time0 = ((double)getTickCount()-time0)/getTickFrequency();
    cout << "方法2耗时： " << time0 << endl;

    imshow("效果图", dstImage);
    waitKey(0);
}


void ColorReduce0(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();
    int rowNum = outputImage.rows;
    int colNum = outputImage.cols*outputImage.channels();

    for (int i=0; i < rowNum; ++i)
    {
        uchar *data = outputImage.ptr<uchar>(i);
        for (int j=0; j < colNum; ++j)
        {
            data[j] = data[j]/div*div+div/2;
        }
    }
}

void ColorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();

    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();

    for (; it != itend; ++it)
    {
        (*it)[0] = (*it)[0]/div*div+div/2;
        (*it)[1] = (*it)[1]/div*div+div/2;
        (*it)[2] = (*it)[2]/div*div+div/2;
    }
}

void ColorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();
    int rowNum = outputImage.rows;
    int colNum = outputImage.cols;

    for (int i=0; i < rowNum; ++i)
    {
        for (int j=0; j < colNum; ++j)
        {
            outputImage.at<Vec3b>(i,j)[0] = outputImage.at<Vec3b>(i,j)[0]/div*div+div/2;
            outputImage.at<Vec3b>(i,j)[1] = outputImage.at<Vec3b>(i,j)[1]/div*div+div/2;
            outputImage.at<Vec3b>(i,j)[2] = outputImage.at<Vec3b>(i,j)[2]/div*div+div/2;
        }
    }
}
