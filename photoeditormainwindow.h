#ifndef PHOTOEDITORMAINWINDOW_H
#define PHOTOEDITORMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PhotoEditorMainWindow; }
QT_END_NAMESPACE

class PhotoEditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PhotoEditorMainWindow(QWidget *parent = nullptr);
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

private:
    Ui::PhotoEditorMainWindow *ui;
};
#endif // PHOTOEDITORMAINWINDOW_H
