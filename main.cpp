#include "custom.h"

#include <QApplication>
#include <QObject>
#include <QSysInfo>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    customMsg w;

    QString text(QString::number(QSysInfo::windowsVersion(),16));

    qDebug() << text;

    w.setContentText("这是一条消息");
    w.setmsgType(INFO);
    w.setBackgroundColor("#FFFFFF");
    w.show();

    return a.exec();
}
