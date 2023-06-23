#ifndef PHOTOEDITORMAINWINDOW_H
#define PHOTOEDITORMAINWINDOW_H

#include <QMainWindow>
#include<qpixmap.h>
#include<qlabel.h>
#include"WorkSpace/workspace.h"
#include<qevent.h>


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

    public:// 初始化函数
        // 主工作区（中间
        void initWorkSpace();
        // 初始化工作模式切换组件
        void initWorkModeTranslation();
        // 初始化笔刷工具栏（左侧
        void initWorkBrushBar();
        // 初始化笔刷详情设置（右侧
        void initWorkBrushDatils();
        // 初始化整体图片修改按键（右侧

    public:// 事件
        void resizeEvent(QResizeEvent* resizeEvent);

    public:
        // 测试功能
        QPixmap initQPixmap(QImage& image);
        void setPixmap(QImage& image);
    private:
        Ui::PhotoEditorMainWindow* ui;
        QLabel* imagelable;
        QWidget* centerwindows;
        WorkSpace* m_workspace;
    };
}
#endif // PHOTOEDITORMAINWINDOW_H
