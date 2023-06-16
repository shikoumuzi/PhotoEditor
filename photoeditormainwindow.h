#ifndef PHOTOEDITORMAINWINDOW_H
#define PHOTOEDITORMAINWINDOW_H

#include <QMainWindow>
#include<qpixmap.h>
#include<qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class PhotoEditorMainWindow; }
QT_END_NAMESPACE

namespace PhotoEdit {
    class PhotoEditorMainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        PhotoEditorMainWindow(QWidget* parent = nullptr);
        ~PhotoEditorMainWindow();

    public:// ��ʼ������
        // �����������м�
        void initWorkSpace();
        // ��ʼ������ģʽ�л����
        void initWorkModeTranslation();
        // ��ʼ����ˢ�����������
        void initWorkBrushBar();
        // ��ʼ����ˢ�������ã��Ҳ�
        void initWorkBrushDatils();
        // ��ʼ������ͼƬ�޸İ������Ҳ�

    public:
        // ���Թ���
        QPixmap initQPixmap(QImage& image);
        void setPixmap(QImage& image);
    private:
        Ui::PhotoEditorMainWindow* ui;
        QLabel* imagelable;
        QWidget* centerwindows;
    };
}
#endif // PHOTOEDITORMAINWINDOW_H
