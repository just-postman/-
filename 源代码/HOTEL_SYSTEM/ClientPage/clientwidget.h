#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include<QDebug>
#include<QButtonGroup>
#include<QHBoxLayout>
#include<QCloseEvent>
#include<QTimer>
#include<QThread>
#include"MyClass/mythread.h"
#include"MyClass/myrotatepictures.h"
#include"MyClass/mypropertyanimation.h"
#include"ClientPage/clientpage1.h"
#include"clientpage2.h"
#include"clientpage3.h"
#include"clientpage4.h"
#include"clientpage5.h"
namespace Ui {
class clientWidget;
}

class clientWidget : public QWidget
{
    Q_OBJECT
public:
    void addButtonGroup();

public:
    explicit clientWidget(QWidget *parent = nullptr);
    ~clientWidget();
private:

 myRotatePictures *rotato;//轮播图
 myPropertyAnimation *animation;//呼吸框
QButtonGroup *toolgroup;//toolbutton按钮组

//界面
clientPage1 *page1;
clientPage2 *page2;
clientPage3 *page3;
clientPage4 *page4;
clientPage5 *page5;
void closeEvent(QCloseEvent *event);
void setTimer(void);
    QThread *thread;
    myThread *mythread;
public:signals:
    void startTimer(QObject *widget);

private slots:

private:
    Ui::clientWidget *ui;
};

#endif // CLIENTWIDGET_H
