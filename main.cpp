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
    image.imread(Image::Path("C:\\Users\\й╦©зд╬вс\\Desktop\\photo\\3E103F23326933BA9227FAFE1BEE0DB7.jpg"));

    int error_no = 0;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));


    //image.Rgb2Gray(error_no);
    //image.imshow("Rgb2Gray");

    image.Rgb2Gray(error_no, Image::Coordinates(image, image.rows() / 2, 0), Image::Coordinates(image, image.rows(), image.cols()));
    image.imshow("PartRgb2Gray");

    
    return a.exec();
}
