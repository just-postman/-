#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QWidget>
#include<QSql>
#include<QDialog>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QFile>
#include<QSqlRecord>
#include<QList>
#include<QStringList>
#include<QThread>
#include<QAction>
#include"MyClass/mythread.h"
#include"servicewidget.h"
#include"SuperPage/superadmin.h"
#include"MyClass/mypropertyanimation.h"
#include"ClientPage/clientwidget.h"
#include"MyClass/myslidervalid.h"
#include"registerwidget.h"
#include"registerpage.h"
#include"registeruser.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool checkUserId(QStringList strlist);//检查账号匹配，搜索整个列表
    bool connectOdbc();//连接数据库是否成功
    void whichTable(QString table);
    //标签事件过滤
    bool eventFilter(QObject *obj,QEvent *event);
    void startMyThread();//启动自己的线程，用于设置样式表
    QStringList strlist;//存放数据库查询结果

    servicewidget *Serwidget;   //前台界面
    clientWidget *cliwidget;      //客户界面
    SuperAdmin *supwidget;    //店长界面
    registerPage *registerpage;//客户注册界面
    registeruser *registeruserpage;//员工注册界面
    mySliderValid *valid;           //滑动验证类

    myThread *mythread;         //自实现线程类
    QThread *thread;                //线程
public: signals:
    void sendByMainwindow();//主线程发送信号
private slots:
    void on_pushButton_clicked();
    void on_closed(int index);
    void onSendThread(QString css);//响应线程槽函数
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
