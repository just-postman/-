#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <QWidget>
#include<QDebug>
#include<QButtonGroup>
#include<QHBoxLayout>
#include<QCloseEvent>
#include<QThread>
#include"MyClass/myrotatepictures.h"
#include"MyClass/mypropertyanimation.h"
#include"superpage1.h"
#include"superpage2.h"
#include"superpage3.h"
#include"superpage4.h"
#include"superpage5.h"
#include"superpage6.h"
#include"MyClass/mythread.h"

namespace Ui {
class SuperAdmin;
}

class SuperAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit SuperAdmin(QWidget *parent = nullptr);
    ~SuperAdmin();
private:

 myRotatePictures *rotato;//轮播图
 myPropertyAnimation *animation;//呼吸框
QButtonGroup *toolgroup;//toolbutton按钮组

void addToolButton(void);

void startTimer(void);
//界面
superPage1 *page1;
superPage2 *page2;
superPage3 *page3;
superPage4 *page4;
superPage5 *page5;
superPage6 *page6;

myThread *mythread;
QThread *thread;
public :signals:
    void setTimer(QObject *widget);
private:
    Ui::SuperAdmin *ui;
};

#endif // SUPERADMIN_H
