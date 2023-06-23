#include "photoeditormainwindow.h"
#include "./ui_photoeditormainwindow.h"
#include<qwidget.h>
#include<qlabel.h>
#include<qlayout.h>
#include<atlalloc.h>
#include<qdesktopwidget.h>

namespace PhotoEdit {

    PhotoEditorMainWindow::PhotoEditorMainWindow(QWidget* parent)
        : QMainWindow(parent),
        m_workspace(new WorkSpace)
        , ui(new Ui::PhotoEditorMainWindow)
    {
        ui->setupUi(this);

        // ÉèÖÃ´°¿ÚÎ»ÖÃ
        auto qr = this->frameGeometry();
        auto desktop = QDesktopWidget();
        auto cp = desktop.availableGeometry().center();
        qr.moveCenter(cp);



        this->setCentralWidget(m_workspace);
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

    void PhotoEditorMainWindow::resizeEvent(QResizeEvent* event)
    {
        qDebug("old = %d, %d; new = %d, %d", event->oldSize().height(), event->oldSize().width(), event->size().height(), event->size().width());
        this->m_workspace->resizeEvent(event);
        this->repaint();

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

