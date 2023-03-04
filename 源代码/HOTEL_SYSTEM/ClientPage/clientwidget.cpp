#include "clientwidget.h"
#include "ui_clientwidget.h"


clientWidget::clientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientWidget)
{
    ui->setupUi(this);
    this->setFixedSize(1050,700);
    //设置当前时间
     setTimer();
    //添加呼吸框,渲染界面
    animation=new myPropertyAnimation(ui->topwidget,QRect(2,2,799,90));
    //为toolbutton添加按钮组
    addButtonGroup();
}

void clientWidget::addButtonGroup()
{

   toolgroup=new QButtonGroup;
   toolgroup->addButton(ui->hotel_toolButton,0);
   toolgroup->addButton(ui->findroom_toolButton,1);
   toolgroup->addButton(ui->Aboutus_toolButton,2);
   toolgroup->addButton(ui->message_toolButton,3);
    toolgroup->addButton(ui->food_toolButton,4);
    toolgroup->setExclusive(true);
   ui->hotel_toolButton->setChecked(true);

    //添加界面
    page1=new clientPage1(nullptr);
    page2=new clientPage2(nullptr);
    page3=new clientPage3(nullptr);
    page4=new clientPage4(nullptr);
    page5=new clientPage5(nullptr);

    ui->stackedWidget->addWidget(page1);
    ui->stackedWidget->addWidget(page2);
    ui->stackedWidget->addWidget(page3);
    ui->stackedWidget->addWidget(page4);
    ui->stackedWidget->addWidget(page5);
   //按钮点击响应事件
   connect(toolgroup,SIGNAL(buttonClicked(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

clientWidget::~clientWidget()
{
    delete ui;
}

void clientWidget::closeEvent(QCloseEvent *event)
{
    if(!(clientPage4::is_submit))
    {
        QMessageBox msgbox(QMessageBox::Information,"温馨提示","您还没提交留言，确定退出吗？");
        msgbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        msgbox.button(QMessageBox::Yes)->setText("确定");
        msgbox.button(QMessageBox::No)->setText("取消");
        int res=msgbox.exec();
        if(res==QMessageBox::No)
        {
            event->ignore();
        }
    }
}

void clientWidget::setTimer()
{
    mythread=new  myThread;
    thread=new QThread(this);
    mythread->moveToThread(thread);
    thread->start();
    connect(this,&clientWidget::startTimer,mythread,&myThread::myTimer);
    connect(thread,&QThread::finished,mythread,&QObject::deleteLater);
    connect(thread,&QThread::destroyed,mythread,&QObject::deleteLater);
    emit startTimer(ui->time_lable);
}
