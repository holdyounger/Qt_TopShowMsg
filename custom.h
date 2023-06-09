#ifndef WIDGET_H
#define WIDGET_H

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QDialog>
#include <QScreen>
#include <QString>
#include <QFile>
#include <QRect>
#include <QTimer>
#include <QTime>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QStyle>
#include <QPixmap>
#include <QPainter>
#define BUTTON_HEIGHT 60        // 按钮高度;
#define BUTTON_WIDTH 60         // 按钮宽度;
#define TITLE_HEIGHT 30         // 标题栏高度;

enum messageType
{
    INFO = 0,
    CRITICAL,
    WARNING,
    ABOUT,
    SUCCESS,
};


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class customMsg : public QWidget
{
    Q_OBJECT

public:
    customMsg(QWidget *parent = nullptr);
    customMsg(QString &contentStr,const messageType &msgType,QWidget *parent = nullptr);

    ~customMsg();


    void setContentText(const QString &content);        //设置提示框内容
    void setmsgType(messageType msgtypr);               // 设置消息内容
    void setBackgroundColor(QString color);             //设置背景色 注：文本颜色需要到Qss文件中修改

private:
    void initcontrol();                 // 初始化控件
    void initConnections();             // 信号槽的绑定
    void loadStyleSheet(const QString &styleFileName); // 加载样式文件
private:
    Ui::Widget *ui;

    QHBoxLayout *m_HBoxLaytitle;

    QLabel* m_pIcon;                    // 提示信息图标;
    QLabel* m_pcontent;                 // 内容信息

    QPixmap *pixmap;                    // 图表信息
    QString m_content;

    messageType m_msgtype;              // 消息类型：info、about、warning、critical

    int m_height;                       // 信息窗口高度
    int m_width;                        // 窗口高度
    QString m_bgColor;

    void pushWindow();

protected:
    void showEvent(QShowEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};
#endif // WIDGET_H
