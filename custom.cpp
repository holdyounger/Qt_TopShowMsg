#include "custom.h"
#include "ui_widget.h"

customMsg::customMsg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Widget)
    ,m_buttonType(ONLY_CLOSE_BUTTON)
{


    //初始化
    initcontrol();
    initConnections();

    // 按钮类型
    setButtonType(m_buttonType);

    //加载本地样式文件"dialog.qss"
    loadStyleSheet("dialog");


    // 成员变量赋值
   // m_content = "contentStr";

    //定时器设置
//    QTimer::singleShot(5000,this,[=](){
//       this->close();
//    });




}

customMsg::customMsg(QString &contentStr, QWidget *parent)
    :m_buttonType(NOT_ALL)
{
    //初始化
    initcontrol();
    initConnections();

    // 成员变量赋值
    m_content = contentStr;

    // 按钮类型
    setButtonType(m_buttonType);

    //加载本地样式文件"dialog.qss"
    loadStyleSheet(contentStr);
    setButtonType(m_buttonType);

}

customMsg::~customMsg()
{
    delete ui;
}

void customMsg::setButtonType(ButtonType buttontype)
{
    switch (buttontype)
    {
    case MIN_BUTTON:
    {
        //m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
        break;
    case MIN_MAX_BUTTON:
    {
        //m_pButtonRestore->setVisible(false);
    }
        break;
    case ONLY_CLOSE_BUTTON:
    {
        m_pButtonMin->setVisible(false);
        //m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
    }
        break;
    case NOT_ALL:
    {
        m_pButtonMin->setVisible(false);
        //m_pButtonRestore->setVisible(false);
        m_pButtonMax->setVisible(false);
        m_pButtonClose->setVisible(false);
    }
    default:
        break;
    }

}

void customMsg::initcontrol()
{
    m_VBoxLaymain = new QVBoxLayout(this);
    m_HBoxLaytitle = new QHBoxLayout;
    m_HBoxLaybuttonTop = new QHBoxLayout;
    m_HBoxLaybuttonBottom = new QHBoxLayout;

    m_pIcon = new QLabel;
    m_pTitleContent = new QLabel;
    m_pcontent = new QLabel;

    m_pButtonMin = new QPushButton;
    m_pButtonMax = new QPushButton;
    m_pButtonClose = new QPushButton;


    m_pIcon->setObjectName("Icon");
    m_pcontent->setObjectName("contentInfo");
    m_pcontent->setAlignment(Qt::AlignCenter);


    m_pButtonMin->setObjectName("ButtonMin");
    m_pButtonMax->setObjectName("ButtonMax");
    m_pButtonClose->setObjectName("ButtonClose");



    m_pButtonMin->setToolTip("最小化");
    m_pButtonMax->setToolTip("最大化");
    m_pButtonClose->setToolTip("关闭");


    //获取最小化、关闭按钮图标
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);

    m_pIcon->setFixedSize(20,20);
    QPixmap *pixmap = new QPixmap(":/img/iconblue.png");
    pixmap->scaled(m_pIcon->size(), Qt::KeepAspectRatio);
    m_pIcon->setScaledContents(true);
    m_pIcon->setPixmap(*pixmap);
    m_pButtonMin->setIcon(minPix);
    m_pButtonMax->setIcon(maxPix);
    m_pButtonClose->setIcon(closePix);




    m_pIcon->setAttribute(Qt::WA_TranslucentBackground);
    m_pButtonMin->setGeometry(width()-45,5,20,20);
    m_pButtonMin->setAttribute(Qt::WA_TranslucentBackground);
    m_pButtonMax->setGeometry(width()-45,5,20,20);
    m_pButtonMax->setAttribute(Qt::WA_TranslucentBackground);
    m_pButtonClose->setGeometry(width()-45,5,20,20);
    m_pButtonClose->setAttribute(Qt::WA_TranslucentBackground);



    m_HBoxLaybuttonTop->addWidget(m_pIcon);
    m_HBoxLaybuttonTop->addSpacerItem(new QSpacerItem(width()-40,0));
    m_HBoxLaybuttonTop->addWidget(m_pButtonMin);
    m_HBoxLaybuttonTop->addWidget(m_pButtonMax);
    //m_HBoxLaybuttonTop->addWidget(m_pButtonRestore);
    m_HBoxLaybuttonTop->addWidget(m_pButtonClose);



    m_VBoxLaymain->addLayout(m_HBoxLaybuttonTop);
    m_VBoxLaymain->addWidget(m_pcontent);
    m_VBoxLaymain->addLayout(m_HBoxLaybuttonBottom);



}

void customMsg::initConnections()
{
    connect(m_pButtonClose,SIGNAL(clicked()),this,SLOT(close()));
}

void customMsg::loadStyleSheet(const QString &styleFileName)
{
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    setWindowFlag(Qt::FramelessWindowHint);
    //setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setWindowIcon(QIcon(":/img/iconblue.png"));
    setWindowTitle("消息提示框");
    setGeometry(this->width() / 4 * 3,0,this->width() / 4,this->height() / 6);

    //setAttribute(Qt::WA_TranslucentBackground); //设置窗体透明

    //读取qss文件
    QFile File(":/qss/" + styleFileName +".qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = (File.readAll());
    setStyleSheet(styleSheet);

}

void customMsg::setContentText(const QString &content)
{
    m_content = content;
}

void customMsg::setmsgType(messageType msgtypr)
{
    switch(msgtypr){
    case INFO:

        break;
    case CRITICAL:

        break;
    case WARNING:

        break;
    case ABOUT:

        break;
    default:
        break;
    }
}

void customMsg::showEvent(QShowEvent *event)
{

    //获取屏幕尺寸
    QScreen *screen=QGuiApplication::primaryScreen();
    QRect mm=screen->availableGeometry() ;
    double screen_width = mm.width();
    double screen_height = mm.height();
    setFixedSize(screen_width / 4 ,screen_height / 6);


    QTimer *slideTimer = new QTimer(this);
    slideTimer->start(1);
    int step = screen_height / 180;

    int gx=screen_width / 4;
    double gy = 1;
    qDebug() << "gy" << gx << ":" << gy << endl;
    connect(slideTimer,&QTimer::timeout,[=,&gx,&gy](){
        //qDebug() << "位置：" << gx <<":" << gy << ":" << step << endl;
        gy += 1;
        setGeometry(screen_width / 5 * 2,gy,screen_width / 4,screen_height / 6);
        if(gy >= 80)
            slideTimer->stop();
    });



    m_pcontent->setText(m_content);

}

