#include "mypropertyanimation.h"
#include "ui_mypropertyanimation.h"
/*
        此类为呼吸边框类
*/
myPropertyAnimation::myPropertyAnimation(QWidget *parent,QRect rect) :
    QWidget(parent),
    ui(new Ui::myPropertyAnimation)
{
    ui->setupUi(this);
    this->m_rect=rect;
    m_contentMargin = 2;                    //保存控件边距
    m_borderColor = Qt::blue;            //边框颜色
    m_alpha = 255;                                //α通道值
//    m_widget = nullptr;                       //特效窗体
//    m_hLayout = new QHBoxLayout(this);  //水平布局
//    m_hLayout->setMargin(0);
//    m_hLayout->setContentsMargins(m_contentMargin, m_contentMargin, m_contentMargin, m_contentMargin);
//    this->setLayout(m_hLayout);

    //添加动画对象
    m_animation = new QPropertyAnimation(this, "m_alpha");
    m_animation->setStartValue(50);//设置属性起始值
    m_animation->setKeyValueAt(0.5, 255);//中间值
    m_animation->setEndValue(50);//结束值
    m_animation->setDuration(2000);//持续时间
    m_animation->setLoopCount(-1);//设置动画无限循环
    m_animation->start();//开始
    //添加动画信号，实现循环
//    connect(m_animation, SIGNAL(finished()), this, SLOT(onFinished()));
}

myPropertyAnimation::~myPropertyAnimation()
{
    delete ui;
}
/*
void myPropertyAnimation::setWidget(QWidget *widget)
{
    //清楚布局，但不包括布局内控件
    if (this->layout() != nullptr)
    {
        QLayoutItem *item;
        while ((item = this->layout()->takeAt(0)) != nullptr)
        {
            delete item;
            item = nullptr;
        }
    }
    //重新添加控件
    m_widget = widget;
    m_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_hLayout->addWidget(m_widget);
}*/

void myPropertyAnimation::setMarginis(int margins)
{
    m_contentMargin = margins;
}

void myPropertyAnimation::setBorderColor(QColor color)
{
    m_borderColor = color;
}

int myPropertyAnimation::getMargins()
{
    return m_contentMargin;
}

QColor myPropertyAnimation::getBorderColor()
{
    return m_borderColor;
}

void myPropertyAnimation::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    drawBorder(&painter);
}

void myPropertyAnimation::drawBorder(QPainter *painter)
{
    painter->save();
    //setAlpha设置透明度，参数是float
    m_borderColor.setAlpha(m_animation->currentValue().toInt());
    //添加画笔
    painter->setPen(QPen(m_borderColor, m_contentMargin * 2));
    //添加画刷
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(m_rect);
    painter->restore();
}

void myPropertyAnimation::setAlpha(float alpha)
{
    m_alpha = alpha;
    update();
}

float myPropertyAnimation::getAlpha() const
{
    return m_alpha;
}

