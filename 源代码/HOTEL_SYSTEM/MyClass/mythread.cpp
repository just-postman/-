#include "mythread.h"
#include <QDebug>
myThread::myThread(QObject *parent) : QObject(parent)
{

}


void myThread::setMainwindowStyle()
{
    QFile file(":/qss/mainwindowstyle.qss");
    file.open(QFile::ReadOnly);
    QString css =QLatin1String(file.readAll());
    emit sendMainwindowstyle(css);
}

void myThread::setServiceStyle()
{
    QFile file(":/qss/gray.css");
    file.open(QFile::ReadOnly);
    QString css =QLatin1String(file.readAll());
    emit sendServiceStyle(css);
}

void myThread::myTimer(QObject *widget)
{
    lable=qobject_cast<QLabel *>(widget);
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&myThread::myTimeUpdate);
    timer->start(1000);
}

void myThread::myTimeUpdate()
{
    QDateTime time=QDateTime::currentDateTime();
    QString str=time.toString("yyyy-MM-dd hh:mm:ss dddd");
    lable->setText(str+"    ");
}

