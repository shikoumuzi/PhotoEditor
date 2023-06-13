#include "photoeditormainwindow.h"

#include <QApplication>
#include"Image/Image.h"
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>   
#include <opencv2/imgproc/imgproc.hpp>

#include<qdebug.h>
using namespace cv;
using namespace PhotoEdit;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //PhotoEdit::PhotoEditorMainWindow w;
    //w.show();
    std::locale::global(std::locale(""));
    setlocale(LC_ALL, "Chinese-simplified");
    Image image;
    image.imread(Image::Path("F:\\University\\作业与报告\\医学影像处理\\实验5\\noise.png"));

    Mat* src = image.toMat();
    image.imshow(String("nana"));
    int error_no = 0;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

    Image::CMatrix* d = image.dilate(error_no, element, 1, Image::IMAGE_FLAG::NEWOBJECT);
    Image::imshow(*d, String("nana1"));
    image.imshow("nana1_src");


    image.dilate(error_no, element, 1);
    image.imshow("nana2");



    image.finalize(d);
    image.finalize(src);
    
    return a.exec();
}
