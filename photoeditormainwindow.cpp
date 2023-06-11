#include "photoeditormainwindow.h"
#include "./ui_photoeditormainwindow.h"
#include<qwidget.h>
#include<qlabel.h>
#include<qlayout.h>
#include<atlalloc.h>

PhotoEditorMainWindow::PhotoEditorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhotoEditorMainWindow)
{
    ui->setupUi(this);
    
    
}

PhotoEditorMainWindow::~PhotoEditorMainWindow()
{
    delete ui;
}

