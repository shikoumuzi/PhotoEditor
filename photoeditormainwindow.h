#ifndef PHOTOEDITORMAINWINDOW_H
#define PHOTOEDITORMAINWINDOW_H

#include <QMainWindow>
#include<qpixmap.h>
#include<qlabel.h>
#include"WorkSpace/workspace.h"
#include<qevent.h>
#include"ToolBar/ToolBar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PhotoEditorMainWindow; }
QT_END_NAMESPACE

namespace PhotoEdit {
    class PhotoEditorMainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        friend class ToolBar;
    public:
        PhotoEditorMainWindow(QWidget* parent = nullptr);
        ~PhotoEditorMainWindow();

    public:// ��ʼ������
        // �����������м�
        void initWorkSpace();
        // ��ʼ������ģʽ�л����
        void initToolBar();

    public:// �¼�
        void resizeEvent(QResizeEvent* resizeEvent);

    public:
        // ���Թ���
        QPixmap initQPixmap(QImage& image);
        void setPixmap(QImage& image);

    public slots:
        void readImage();

    private:
        Ui::PhotoEditorMainWindow* ui;
        QLabel* imagelable;
        QWidget* centerwindows;
        WorkSpace* m_workspace;
        ToolBar* m_toolbar;
    };
}
#endif // PHOTOEDITORMAINWINDOW_H
