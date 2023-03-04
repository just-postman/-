#include "myslidervalid.h"
#include"QFile"
bool mySliderValid:: state=false;

mySliderValid::mySliderValid(QWidget *parent,int index) : QWidget(parent)
{
        this->index=index;
        this->setWindowTitle("安全验证");
        this->setWindowIcon(QIcon(":/image/main_main.png"));
        this->setFixedSize(490,400);
        this->setWindowModality(Qt::ApplicationModal);//阻塞除当前窗体外的其他所有窗体
        //滑动条
        varificationSlider=new QSlider(this);
        //设置样式表
        QFile file(QString(":/qss/myslider.css"));
        file.open(QFile::ReadOnly);
        QString css =QLatin1String(file.readAll());
        varificationSlider->setStyleSheet(css);
        //设置定位
        varificationSlider->setOrientation(Qt::Horizontal);
        varificationSlider->setRange(0,360);//设置滑动条value的范围
        varificationSlider->setGeometry(20,360,450,40);
        //信号与槽
        connect(varificationSlider,SIGNAL(sliderMoved(int)),this,SLOT(imageMove()));//滑块移动触发信号
        connect(varificationSlider,SIGNAL(valueChanged(int)),this,SLOT(imageMove()));//滑动条的值发生改变触发信号
        connect(varificationSlider,SIGNAL(sliderReleased()),this,SLOT(imageStop()));//鼠标释放触发信号

        //背景图片lable
        varificationLab1=new QLabel(this);
        varificationLab1->setPixmap(QPixmap(":/image/city1.jpg").scaled(447,350));//最大的图片
        varificationLab1->setGeometry(20,50,447,300);

        //缺口图片lable
        varificationLab2=new QLabel(this);
        varificationLab2->setPixmap(QPixmap(":/image/blank1.jpg").scaled(100,75));//缺口图片
        varificationLab2->setStyleSheet("border: 5px solid gray; border-style: solid;");
        varificationLab2->setGeometry(20,150,82,75);

        //提升在别的窗口之上、在别的窗口之下可以为lower()函数
        varificationLab2->raise();

         //验证提示
        QLabel *tipLab=new QLabel("拖动下方滑块完成拼图",this);
        tipLab->setGeometry(20,0,350,50);
        tipLab->setStyleSheet("font:14pt; font-family:'微软雅黑'");
}

void mySliderValid::imageMove()
{
    //控制缺块图片水平移动
        this->varificationLab2->move(25+this->varificationSlider->value(),this->varificationLab2->y());
//        qDebug()<<this->varificationSlider->value();//测试滑块的位置
}


void mySliderValid::imageStop()
{
    int ret=this->varificationSlider->value();
        //滑动条的值在某个范围内（可自行设定）  对应缺块图片正好拼接上原图
        if(ret>=276 && ret<=283)
        {
            mySliderValid::state = true;
            QMessageBox msgBox;
            msgBox.setFixedWidth(200);
            msgBox.setText("验证成功！");
            msgBox.setWindowTitle("安全验证");
            msgBox.setWindowIcon(QIcon(":/image/main_main.png"));
            msgBox.exec();
            this->varificationSlider->setValue(0);
            this->close();
            emit hasclose(index);
        }
        else  //不在这个范围内  则滑块和缺块图片回归原位
        {
            this->varificationSlider->setValue(0);
            this->varificationLab2->move(25+this->varificationSlider->value(),this->varificationLab2->y());
        }
}
