#include "opencv2/opencv.hpp"
#include <time.h>
using namespace cv;

int main()
{
/*
    system("color 9F");  //改变背景颜色
    FileStorage fs("test.yaml", FileStorage::WRITE);
    fs << "strings" << "[" ;
    fs << "image1.jpg" << "Awesomeness" << "baboon.jpg";
    fs << "]";

    fs << "Mapping"<< "{" ;
    fs << "one" << 1;
    fs << "two" << 2 << "}";

    FileNode n = fs["Mapping"];
    cout << n.type();
    if (n.type() != FileNode::SEQ){
        cerr << "发生错误！字符串不是一个序列！" << endl;
        fs.release();
        return 1;
    }
    FileNodeIterator it = n.begin(), itend = n.end();
    for (; it != itend; ++it)
        cout << (string)*it << endl ;

    fs.release();
    return 0;
*/
    FileStorage fs("test.yaml", FileStorage::WRITE);
    //开始写入
    fs << "frameCount" << 5;
    time_t rawtime; time(&rawtime);
    fs <<"calibrationDate" << asctime(localtime(&rawtime));
    Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    Mat disCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);
    fs << "cameraMatrix" << cameraMatrix << "disCoeffs" << disCoeffs;
    fs << "features" << "[";
    for (int i=0; i<3; i++)
    {
        int x = rand() % 640;
        int y = rand() % 480;
        uchar lbp = rand() % 256;
        fs << "{:" << "x" << x << "y" << y << "lbp" << "[:"; // ":"的作用是将数据排成一行
        for (int j=0; j<8; j++)
            fs << ((lbp >> j) &1);
        fs << "]" << "}";
    }
    fs << "]";
    fs.release();
    std::cout << "文件写入完毕" << std::endl;
    //getchar();
    waitKey(30);

    FileStorage fr("test.yaml", FileStorage::READ);
    //开始读取
    int frameCount = (int)fr["frameCount"];

    std::string date;
    fr["calibrationDate"] >> date;

    Mat cameraMatrix2, disCoeffs2;
    fr["cameraMatrix"] >> cameraMatrix2;
    fr["disCoeffs"]    >> disCoeffs2;

    std::cout << "frameCount:" << frameCount << std::endl;
    std::cout << "date:" << date << std::endl;
    std::cout << "cameraMatrix2:" << cameraMatrix2 << std::endl;
    std::cout << "disCoeffs2:" << disCoeffs2 << std::endl;


    FileNode features = fr["features"];
    FileNodeIterator it = features.begin(), it_end = features.end();
    int idx = 0;
    std::vector<uchar> lbpval;
    for(; it!=it_end; ++it, ++idx)
    {
        std::cout << "features #" << idx << ": ";
        std::cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp:(";
        (*it)["lbp"] >> lbpval;
        for (int i=0; i<(int)lbpval.size(); i++)
            std::cout << " " << (int)lbpval[i];
        std::cout << ")" << std::endl;
    }
    fr.release();
    printf("文件读取完毕");
    getchar();

    return 0;
}
