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
    PhotoEdit::PhotoEditorMainWindow w;
    std::locale::global(std::locale(""));
    setlocale(LC_ALL, "Chinese-simplified");
    Image image;
    image.imRead(Image::Path("C:\\Users\\й╦©зд╬вс\\Desktop\\photo\\3E103F23326933BA9227FAFE1BEE0DB7.jpg"));

    int error_no = 0;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));


    //image.Rgb2Gray(error_no);
    //image.imshow("Rgb2Gray");

    //image.Rgb2Gray(error_no, Image::Coordinates(image, image.rows() / 2, 0), Image::Coordinates(image, image.rows(), image.cols()));
    //image.imshow("PartRgb2Gray");
    QImage* d = image.toQImage();
    if (d == nullptr)
    {
        qDebug("nullptr");
    }

    image.Rgb2Gray(error_no);
    image.thresold(error_no, 125, Image::Coordinates(image, image.rows() / 3, image.cols()/3), Image::Coordinates(image, image.rows()/2, image.cols()/2));
    //image.thresold(error_no, 125);
    image.imShow("thresold");

    image.dilate(error_no, element);
    image.imShow("erode");

    image.erode(error_no, element);
    image.imShow("erode");

    image.distanceTransform(error_no, 5);
    image.imShow("distanceTransform");


    Image::imShowNoWait(*d, "qimage");

    Image:waitKey();

    //w.setPixmap(*d);

    //w.show();



    return a.exec();
}
