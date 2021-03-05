#include "custom.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    customMsg w;
    w.setContentText("你好");
    w.setButtonType(ONLY_CLOSE_BUTTON);
    w.show();
    return a.exec();
}
