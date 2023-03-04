#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectOdbc();//连接数据库
    startMyThread();//启动线程,用于设置
    ui->register_2->installEventFilter(this);//安装事件过滤器
}
MainWindow::~MainWindow()
{
    delete ui;
//    thread->wait();
    thread->quit();
    delete mythread;
    delete thread;
}

//输入列表，查看账号密码是否正确
bool MainWindow::checkUserId(QStringList strlist)
{
    QString id=ui->idlineEdit->text();
    QString pwd=ui->pwdlineEdit->text();
    for(int i=0;i<strlist.length();i+=2)
    {
        if(strlist.at(i)==id&&strlist.at(i+1)==pwd)
        {
            return true;
        }
    }
    return false;
}

//检查连接数据库是否成功
bool MainWindow::connectOdbc()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    qDebug()<<"odbc  driver?"<<db.isValid();
    db.setHostName("127.0.0.1");//配置本地ip即localhost
    db.setDatabaseName("hotel_system");//这里就是你配置的odbc数据源名称
    db.setUserName("root");//这里是你登录数据库的用户名
    db.setPassword("123456");//密码
    qDebug()<<"available drivers";
    //查看是否打开了数据库
    if (!db.open())
    {
        qDebug()<<db.lastError().text();
        QMessageBox::critical(this,QObject::tr("connect error"),db.lastError().text());
        return false;
    }
    return true;
}

//查看是哪张表格
void MainWindow::whichTable(QString table)
{
    QSqlQuery query;//数据库查询,经验表明该语句不能放在头函数中
    bool querysuccess=query.exec(QString("select * from %1").arg(table));//查询table
    if(!querysuccess)
    {
        qDebug()<<"查询失败";
    }
    //向list列表末尾中插入数据
    while(query.next())
    {
        QSqlRecord rec =query.record();
//        for(int i=0;i<rec.count();i++)
//        {
            QString username=query.value(0).toString();
            QString password=query.value(1).toString();
            strlist.append(username);//向末尾添加元素
            strlist.append(password);
//        }
    }
}

//添加按钮点击事件
void MainWindow::on_pushButton_clicked()
{

    if(ui->idlineEdit->text()==""||ui->pwdlineEdit->text()=="")
    {
        QMessageBox::warning(nullptr,"错误提示","账号密码不能为空","Ok","Cancel");
        return;
    }
//******************************验证radiobutton组************************************
  if(ui->client_button->isChecked())
    {
        //查询客户表，并将数据存放在list中
        strlist.clear();
        whichTable("clienttable");
        //--------------------------------------验证账号密码--------------------------------------
        //**************************************当选中客户button**********************************
         if(checkUserId(strlist))
        {
            valid=new mySliderValid(nullptr,0);
            valid->show();
            connect(valid,SIGNAL(hasclose(int)),this,SLOT(on_closed(int)));
        }
         else
        {
            QMessageBox::critical(nullptr,"信息提示","登录失败\n请检查账号密码是否输入正确");
        }
    }
    else if(ui->service_Button->isChecked())
    {
        strlist.clear();
        whichTable("userTable");//查询前台表，并将数据存放在list中
        //--------------------------------------验证账号密码--------------------------------------
        //**************************************当选中前台button********************************
         if(checkUserId(strlist))
        {
            valid=new mySliderValid(nullptr,1);
            valid->show();
            connect(valid,SIGNAL(hasclose(int)),this,SLOT(on_closed(int)));
        }
         else
        {
            QMessageBox::critical(nullptr,"信息提示","登录失败\n请检查账号密码是否输入正确");
        }
    }
    else if(ui->shopkeeper_button->isChecked())
    {
        strlist.clear();
        whichTable("ShopKeeper");//查询店长表，并将数据存放在list中
        //--------------------------------------验证账号密码--------------------------------------
        //*************************************当选中店长buttton*********************************
         if(checkUserId(strlist))
        {
            valid=new mySliderValid(nullptr,2);
            valid->show();
            connect(valid,SIGNAL(hasclose(int)),this,SLOT(on_closed(int)));
        }
         else
        {
            QMessageBox::critical(nullptr,"信息提示","登录失败\n请检查账号密码是否输入正确");
        }
  }
}

//验证窗口关闭槽函数
void MainWindow::on_closed(int index)
{
    this->close();
    //接收客户的信号
    if(index==0)
    {
        //通过滑动验证
        if(valid->state)
        {
            QMessageBox::information(nullptr,"信息提示","登录成功");
            this->window()->hide();
            cliwidget=new clientWidget;
            cliwidget->setWindowTitle("新华智慧科技酒店");
            cliwidget->show();
        }
    }
    //接前台的信号
    if(index==1)
    {
        //通过滑动验证
        if(valid->state)
        {
            QMessageBox::information(nullptr,"信息提示","登录成功");
            this->window()->hide();//隐藏当前窗口
            Serwidget=new servicewidget;
            Serwidget->setWindowTitle("新华智慧科技酒店");
            Serwidget->show();//显示前台界面
        }
    }
    //接收店长的信号
    if(index==2)
    {
        QMessageBox::information(nullptr,"信息提示","登录成功");
        this->window()->hide();//隐藏当前窗口
        supwidget=new SuperAdmin;
        supwidget->setWindowTitle("新华智慧科技酒店");
        supwidget->show();
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    //实现点击标签所进行的操作
    if(qobject_cast<QLabel *>(obj)==ui->register_2&&event->type()==QEvent::MouseButtonRelease)
    {
        if(ui->client_button->isChecked())
        {
            registerpage=new registerPage;
            registerpage->show();
            return true;
        }
        if(ui->service_Button->isChecked())
        {
            registeruserpage=new registeruser;
            registeruserpage->show();
            return true;
        }
    }
    return false;
}

void MainWindow::onSendThread(QString css)
{
    QAction *action_login=new QAction(this);
    action_login->setIcon(QIcon(":/icon/username.png"));
    QAction *action_pwd=new QAction(this);
    action_pwd->setIcon(QIcon(":/icon/password.png"));
    ui->idlineEdit->addAction(action_login,QLineEdit::LeadingPosition);
    ui->pwdlineEdit->addAction(action_pwd,QLineEdit::LeadingPosition);
    ui->centralwidget->setStyleSheet(css);
}

void MainWindow::startMyThread()
{
    mythread=new  myThread;
    thread=new QThread(this);
    mythread->moveToThread(thread);
    thread->start();
    connect(this,&MainWindow::sendByMainwindow,mythread,&myThread::setMainwindowStyle);
    connect(mythread,&myThread::sendMainwindowstyle,this,&MainWindow::onSendThread);
    connect(thread,&QThread::finished,mythread,&QObject::deleteLater);
    connect(thread,&QThread::destroyed,mythread,&QObject::deleteLater);
    emit sendByMainwindow();
}
