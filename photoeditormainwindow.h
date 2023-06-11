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

private:
    Ui::PhotoEditorMainWindow *ui;
};
#endif // PHOTOEDITORMAINWINDOW_H
