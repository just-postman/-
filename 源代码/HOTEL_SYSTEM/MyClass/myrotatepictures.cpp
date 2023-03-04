#include "myrotatepictures.h"
#include "ui_myrotatepictures.h"

myRotatePictures::myRotatePictures(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myRotatePictures)
{
    ui->setupUi(this);
    //添加照片
    addImage(":/room/singleroom02.jpg");
    addImage(":/room/doubleroom02.jpg");
    addImage(":/room/familyroom05.jpg");
    addImage(":/room/presidentroom01.jpg");
    m_currentDrawImageIndx=0;
    startPlay();
    // 添加ImageOpacity属性;
    this->setProperty("ImageOpacity", 1.0);
    // 动画切换类;
    m_opacityAnimation = new QPropertyAnimation(this, "ImageOpacity");
    // 这里要设置的动画时间小于图片切换时间;
    m_opacityAnimation->setDuration(1000);

    // 设置ImageOpacity属性值的变化范围;
    m_opacityAnimation->setStartValue(1.0);
    m_opacityAnimation->setEndValue(0.0);
    // 透明度变化及时更新绘图;
    connect(m_opacityAnimation, SIGNAL(valueChanged(const QVariant&)), this, SLOT(update()));
    // 设置图片切换时钟槽函数;
    connect(&m_imageChangeTimer, SIGNAL(timeout()), this, SLOT(onImageChangeTimeout()));
    //没有边框的窗口
    this->setWindowFlags(Qt::FramelessWindowHint);
}


// 初始化按钮组
void myRotatePictures::initChangeImageButton()
{
    // 注意图片过多按钮可能放置不下;
    QButtonGroup* changeButtonGroup = new QButtonGroup;
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();//用于按钮间添加伸缩量

    for (int i = 0; i < m_imageFileNameList.count(); i++)
    {
        QPushButton* pButton = new QPushButton;
        pButton->setFixedSize(QSize(16, 16));
        pButton->setCheckable(true);
        //在此处设置button设置样式
        pButton->setStyleSheet("QPushButton:checked {background-color:#c3e9e5; } QPushButton:!checked { background-color:#ff0000 }");
        changeButtonGroup->addButton(pButton, i);
        m_pButtonChangeImageList.append(pButton);
        hLayout->addWidget(pButton);
    }
    hLayout->addStretch();
    hLayout->setSpacing(10);
    hLayout->setMargin(0);

    connect(changeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onImageSwitchButtonClicked(int)));

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(hLayout);
    mainLayout->setContentsMargins(0, 0, 0, 20);
}

void myRotatePictures::setImageList(QStringList imageFileNameList)
{
    m_imageFileNameList = imageFileNameList;
}

void myRotatePictures::addImage(QString imageFileName)
{
    m_imageFileNameList.append(imageFileName);
}

void myRotatePictures::startPlay()
{
    // 添加完图片之后，根据图片多少设置图片切换按钮;
    initChangeImageButton();
    if (m_imageFileNameList.count() == 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
    }
    else if (m_imageFileNameList.count() > 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
        m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
        m_imageChangeTimer.start(2000);
        update();
    }
}

void myRotatePictures::onImageChangeTimeout()
{
    // 设置前后的图片;
    m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
    m_currentDrawImageIndx++;
    if (m_currentDrawImageIndx >= m_imageFileNameList.count())
    {
        m_currentDrawImageIndx = 0;
    }
    m_nextPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
    m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);

    // 动画类重新开始;
    m_opacityAnimation->start();
}

void myRotatePictures::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect imageRect = this->rect();

    // 如果图片列表为空，显示默认图片;
    if (m_imageFileNameList.isEmpty())
    {
        QPixmap backPixmap = QPixmap(":/Resources/CarouselImageBack.png");
        painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    // 如果只有一张图片;
    else if (m_imageFileNameList.count() == 1)
    {
        QPixmap backPixmap = QPixmap(m_imageFileNameList.first());
        painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    // 多张图片;
    else if (m_imageFileNameList.count() > 1)
    {
        float imageOpacity = this->property("ImageOpacity").toFloat();
        //根据尺寸缩小pixmap大小
        painter.drawPixmap(imageRect, m_nextPixmap.scaled(imageRect.size()));
        painter.setOpacity(imageOpacity);
        painter.drawPixmap(imageRect, m_currentPixmap.scaled(imageRect.size()));
    }
}

void myRotatePictures::onImageSwitchButtonClicked(int buttonId)
{
    m_currentDrawImageIndx = buttonId - 1;
    if (m_currentDrawImageIndx == -1)
    {
        m_currentDrawImageIndx = m_imageFileNameList.count() - 1;
    }
    onImageChangeTimeout();
    m_imageChangeTimer.start(2000);
    update();
}

void myRotatePictures::mousePressEvent(QMouseEvent* event)
{
    // 这里可以对当前图片进行点击然后触发每个图片对应的效果;
    // 比如web上好多类似的弹出对应的广告页面等功能;
    qDebug() << m_currentDrawImageIndx;
}

myRotatePictures::~myRotatePictures()
{
    delete ui;
}
