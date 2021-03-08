#include "custom.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    customMsg w;
    w.setContentText("需要一些准备才可以~");
    w.setmsgType(ABOUT);
    w.setBackgroundColor("#FFFFFF");
    w.show();
    return a.exec();
}
