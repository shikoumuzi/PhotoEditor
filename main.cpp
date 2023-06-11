#include "photoeditormainwindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhotoEdit::PhotoEditorMainWindow w;
    w.show();
    return a.exec();
}
