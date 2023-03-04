#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include<QFile>
#include<QTimer>
#include<QLabel>
#include<QDateTime>
class myThread : public QObject
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = nullptr);
    void setMainwindowStyle();
    void setServiceStyle();
    void myTimer(QObject *widget);
    QLabel *lable;
signals:
    void sendMainwindowstyle(QString css);
    void sendServiceStyle(QString css);
public slots:
    void myTimeUpdate(void);
};

#endif // MYTHREAD_H
