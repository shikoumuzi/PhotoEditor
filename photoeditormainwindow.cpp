#include "photoeditormainwindow.h"
#include "./ui_photoeditormainwindow.h"
#include<qwidget.h>
#include<qlabel.h>
#include<qlayout.h>
#include<atlalloc.h>
#include<qdesktopwidget.h>
#include"Thread/ReadRunable.h"
#include<qthreadpool.h>
namespace PhotoEdit {

    PhotoEditorMainWindow::PhotoEditorMainWindow(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::PhotoEditorMainWindow)
    {
        ui->setupUi(this);

        // ÉèÖÃ´°¿ÚÎ»ÖÃ
        auto qr = this->frameGeometry();
        auto desktop = QDesktopWidget();
        auto cp = desktop.availableGeometry().center();
        qr.moveCenter(cp);


        this->initToolBar();
        this->initWorkSpace();
    }


    PhotoEditorMainWindow::~PhotoEditorMainWindow()
    {
        delete ui;
    }

    void PhotoEditorMainWindow::initWorkSpace()
    {
        this->m_workspace = new WorkSpace();
        this->setCentralWidget(m_workspace);
    }

    void PhotoEditorMainWindow::initToolBar()
    {

        this->m_toolbar = new ToolBar(this);
        this->setMenuBar(this->m_toolbar);
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

    void PhotoEditorMainWindow::readImage()
    {
        qDebug("PhotoEditorMainWindow::readImage");
        this->m_workspace->readImage();

        auto pool = QThreadPool::globalInstance();
        ReadRunable* read_thread = new ReadRunable(this->m_workspace);
        read_thread->setAutoDelete(true);

        pool->start(read_thread);

        pool->waitForDone();
        this->m_workspace->paintImage();


        //auto read_thread = new ReadRunable(this->m_workspace->readImage, this->m_workspace)


    }

}

