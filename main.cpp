#include "photoeditormainwindow.h"

#include <QApplication>
#include"Image/Image.h"
#include<opencv2/core.hpp>
#include<opencv2/highgui/highgui.hpp>   
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
    image.imread(Image::Path("C:/Users/й╦©зд╬вс/Desktop/photo/7c151372-420b-46e1-abdd-eb33a0e777e1.jpg"));

    Mat* src = image.toMat();
    image.imshow(String("nana"));
    QImage* qsrc = image.toQImage();
    image.synchronization();


    Mat qmat = cv::Mat(qsrc->height(), qsrc->width(), CV_8UC3, (void*)qsrc->constBits(), qsrc->bytesPerLine());
    if(!qmat.empty())
        imshow("qsrc", qmat);
    else
    {
        qDebug("error");
    }


    waitKey(0);
    image.finalize(src);
    return a.exec();
}
