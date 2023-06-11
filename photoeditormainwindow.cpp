#include "photoeditormainwindow.h"
#include "./ui_photoeditormainwindow.h"

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

