#ifndef WIDGET_H
#define WIDGET_H

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

#define BUTTON_HEIGHT 30        // 按钮高度;
#define BUTTON_WIDTH 30         // 按钮宽度;
#define TITLE_HEIGHT 30         // 标题栏高度;


enum ButtonType
{
    MIN_BUTTON = 0,         // 最小化和关闭按钮;
    MIN_MAX_BUTTON ,        // 最小化、最大化和关闭按钮;
    ONLY_CLOSE_BUTTON,      // 只有关闭按钮;
    NOT_ALL                 // 一个按钮都没有
};
enum messageType
{
    INFO = 0,
    CRITICAL,
    WARNING,
    ABOUT,
};


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class customMsg : public QDialog
{
    Q_OBJECT

public:
    customMsg(QWidget *parent = nullptr);
    customMsg(QString &contentStr,QWidget *parent = nullptr);

    ~customMsg();


    void setButtonType(ButtonType buttontype);
    void setContentText(const QString &content);
    void setmsgType(messageType msgtypr);
private:
    void initcontrol();      // 初始化控件
    void initConnections(); // 信号槽的绑定
    void loadStyleSheet(const QString &styleFileName); // 加载样式文件

private:
    Ui::Widget *ui;
    QVBoxLayout *m_VBoxLaymain;         // 主体布局
    QHBoxLayout *m_HBoxLaybuttonTop;    // 顶部按钮布局
    QHBoxLayout *m_HBoxLaybuttonBottom; // 底部按钮布局
    QHBoxLayout *m_HBoxLaytitle;

    QLabel* m_pIcon;                    // 标题栏图标;
    QLabel* m_pTitleContent;            // 标题栏内容;
    QLabel* m_pcontent;                  // 内容信息

    QPushButton* m_pButtonMin;          // 最小化按钮;
    QPushButton* m_pButtonRestore;      // 最大化还原按钮;
    QPushButton* m_pButtonMax;          // 最大化按钮;
    QPushButton* m_pButtonClose;        // 关闭按钮;


    QString m_content;

    ButtonType m_buttonType;

protected:
    void showEvent(QShowEvent *event) override;

};
#endif // WIDGET_H
