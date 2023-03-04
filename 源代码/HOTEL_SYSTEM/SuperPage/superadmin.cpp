#include "superadmin.h"
#include "ui_superadmin.h"

SuperAdmin::SuperAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperAdmin)
{
    ui->setupUi(this);
    startTimer();
    addToolButton();
}

SuperAdmin::~SuperAdmin()
{
    delete ui;
}

void SuperAdmin::addToolButton()
{

   toolgroup=new QButtonGroup;
   toolgroup->addButton(ui->room_toolButton,0);
   toolgroup->addButton(ui->employ_toolButton,1);
   toolgroup->addButton(ui->client_toolButton,2);
   toolgroup->addButton(ui->exitrecord_toolButton,3);
   toolgroup->addButton(ui->message_toolButton,4);
   toolgroup->addButton(ui->more_toolButton,5);
    toolgroup->setExclusive(true);
   ui->room_toolButton->setChecked(true);

    //添加界面
    page1=new superPage1(this);
    page2=new superPage2(this);
    page3=new superPage3(this);
    page4=new superPage4(this);
    page5=new superPage5(this);
    page6=new superPage6(this);
    ui->stackedWidget->addWidget(page1);
    ui->stackedWidget->addWidget(page2);
    ui->stackedWidget->addWidget(page3);
    ui->stackedWidget->addWidget(page4);
    ui->stackedWidget->addWidget(page5);
    ui->stackedWidget->addWidget(page6);
    //按钮点击响应事件
    connect(toolgroup,SIGNAL(buttonClicked(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

void SuperAdmin::startTimer()
{
    mythread=new  myThread;
    thread=new QThread(this);
    mythread->moveToThread(thread);
    thread->start();
    connect(this,&SuperAdmin::setTimer,mythread,&myThread::myTimer);
    connect(thread,&QThread::finished,mythread,&QObject::deleteLater);
    emit setTimer(ui->label_2);
}
