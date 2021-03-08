#include "custom.h"
#include "ui_widget.h"

customMsg::customMsg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Widget)
    ,m_bgColor("white")
{

    //初始化
    initcontrol();
    initConnections();

    //加载本地样式文件"dialog.qss"
    loadStyleSheet("dialog");


}

customMsg::customMsg(QString &contentStr,const messageType &msgType,QWidget *parent)
    :m_content(contentStr)
    ,m_msgtype(msgType)
    ,m_bgColor("white")
{
    if(parent != nullptr)
        this->setParent(parent);

    //初始化
    initcontrol();
    initConnections();
    //加载本地样式文件"dialog.qss"
    loadStyleSheet(contentStr);

}

customMsg::~customMsg()
{
    delete ui;
}



void customMsg::initcontrol()
{
    setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    m_HBoxLaytitle = new QHBoxLayout;

    m_pIcon = new QLabel;
    m_pcontent = new QLabel;

    m_pIcon->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);

    m_pIcon->setObjectName("Icon");
    m_pcontent->setObjectName("contentInfo");

    m_pIcon->setAlignment(Qt::AlignCenter);
    m_pcontent->setAlignment(Qt::AlignCenter);
    m_pcontent->setWordWrap(1);


    pixmap = new QPixmap;
    pixmap->scaled(m_pIcon->size(), Qt::KeepAspectRatio);
    m_pIcon->setScaledContents(true);
    m_pIcon->setPixmap(*pixmap);




    m_HBoxLaytitle->addWidget(m_pIcon);
    m_HBoxLaytitle->addWidget(m_pcontent);

    m_HBoxLaytitle->setStretch(0,1);
    m_HBoxLaytitle->setStretch(1,4);
    m_HBoxLaytitle->setAlignment(Qt::AlignCenter);

    this->setLayout(m_HBoxLaytitle);

}

void customMsg::initConnections()
{
    //
    // 定时器设置 显示时长
    //
    QTimer::singleShot(5000,this,[=](){

        //获取屏幕尺寸
        QScreen *screen=QGuiApplication::primaryScreen();
        QRect mm=screen->availableGeometry() ;
        static double _gy = this->y();
        //qDebug() << "当前窗口的高度：" << mm.y()  << ":" << _gy << endl;


        QTimer *slideOutTimer = new QTimer(this);
        slideOutTimer->start(1);
        connect(slideOutTimer,&QTimer::timeout,[=](){
            double acceleSpeed = 0.0;
            if(_gy >= 40)
            {
                acceleSpeed += 0.05;
                _gy -= (0.05 + acceleSpeed);
            }
            else if(_gy >= 0){
                acceleSpeed += 0.01;
                _gy -= (0.1 + acceleSpeed);
            }
            if(_gy < 0){
                this->close();
            }
            setGeometry(mm.width() / 5 * 2,_gy,mm.width() / 4,mm.height() / 10);
        });
    });


}

void customMsg::loadStyleSheet(const QString &styleFileName)
{
    //读取qss文件
    QFile File(":/qss/" + styleFileName +".qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = (File.readAll());
    setStyleSheet(styleSheet);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setAttribute(Qt::WA_TranslucentBackground); //设置窗体透明
}


void customMsg::setContentText(const QString &content)
{
    m_content = content;
}
void customMsg::setmsgType(messageType msgtypr)
{
    m_msgtype = msgtypr;
}

void customMsg::setBackgroundColor(QString color)
{
    m_bgColor = color;
}

void customMsg::showEvent(QShowEvent *event)
{

    QDialog::showEvent(event);
    m_pcontent->setText(m_content);

    switch(m_msgtype){
    case INFO:
        // m_pcontent->setText("提示：" + m_pcontent->text());
        pixmap = new QPixmap(":/img/info.png");
        setWindowIcon(QIcon(":/img/info.png"));
        break;
    case CRITICAL:
        // m_pcontent->setText("警告：" + m_pcontent->text());
        pixmap = new QPixmap(":/img/critical.png");
        setWindowIcon(QIcon(":/img/critical.png"));
        break;
    case WARNING:
        // m_pcontent->setText("错误：" + m_pcontent->text());
        pixmap = new QPixmap(":/img/warning.png");
        setWindowIcon(QIcon(":/img/warning.png"));
        break;
    case ABOUT:
        // m_pcontent->setText("关于：" + m_pcontent->text());
        pixmap = new QPixmap(":/img/info.png");
        setWindowIcon(QIcon(":/img/info.png"));
        break;
    case SUCCESS:
        pixmap = new QPixmap(":/img/success.png");
        setWindowIcon(QIcon(":/img/success.png"));
        break;
    default:
        //  m_pcontent->setText("提示：" + m_pcontent->text());
        pixmap = new QPixmap(":/img/info.png");
        setWindowIcon(QIcon(":/img/info.png"));
        break;
    }
    m_pIcon->setPixmap(*pixmap);


    //获取屏幕尺寸
    QScreen *screen=QGuiApplication::primaryScreen();
    QRect mm=screen->availableGeometry() ;
    double screen_width = mm.width();
    double screen_height = mm.height();
    double posy = mm.y(); // 获取窗口显示y方向的起点
    if(posy == 0)
        posy = 40;

    QTimer *slideTimer = new QTimer(this);
    slideTimer->start(10);
    double gy = 0;
    connect(slideTimer,&QTimer::timeout,[=,&gy](){
        double acceleSpeed = 0.0;
        if(gy < posy / 3 * 2){
            acceleSpeed += 0.01;
            gy += (0.75 + acceleSpeed);
        }
        else if(gy < posy)
        {
            acceleSpeed += 0.65;
            gy += (0.55 + acceleSpeed);

        }
        if(gy >= posy)
            slideTimer->stop();
        setGeometry(screen_width / 5 * 2,gy,screen_width / 4,screen_height / 10);

    });

}

void customMsg::paintEvent(QPaintEvent *event)
{
    // 设置窗体为圆角
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //抗锯齿
    painter.setBrush(QBrush(QColor(m_bgColor))); // 背景颜色
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);

    // rect: 绘制区域  15：圆角弧度
    painter.drawRoundedRect(rect, 15, 15);

    QDialog::paintEvent(event);
}

