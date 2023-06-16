#include "photoeditormainwindow.h"
#include "./ui_photoeditormainwindow.h"
#include<qwidget.h>
#include<qlabel.h>
#include<qlayout.h>
#include<atlalloc.h>
namespace PhotoEdit {

    PhotoEditorMainWindow::PhotoEditorMainWindow(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::PhotoEditorMainWindow)
    {
        ui->setupUi(this);

        this->centerwindows = new QWidget();

        QHBoxLayout hlayout;
        this->imagelable = new QLabel();
        hlayout.addWidget(this->imagelable);
       


        this->centerwindows->setLayout(&hlayout);
        this->setCentralWidget(this->centerwindows);
    }


    PhotoEditorMainWindow::~PhotoEditorMainWindow()
    {
        delete ui;
    }

    void PhotoEditorMainWindow::initWorkSpace()
    {
    }

    void PhotoEditorMainWindow::initWorkModeTranslation()
    {
    }

    void PhotoEditorMainWindow::initWorkBrushBar()
    {
    }

    void PhotoEditorMainWindow::initWorkBrushDatils()
    {
    }

    QPixmap PhotoEditorMainWindow::initQPixmap(QImage& image)
    {
        return QPixmap::fromImage(image);
    }

    void PhotoEditorMainWindow::setPixmap(QImage& image)
    {
        this->imagelable->setPixmap(initQPixmap(image).scaled(600, 300));
    }

}

