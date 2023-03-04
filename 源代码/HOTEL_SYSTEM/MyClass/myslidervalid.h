#ifndef MYSLIDERVALID_H
#define MYSLIDERVALID_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include<QMessageBox>
#include <QIcon>
#include <QDebug>

class mySliderValid : public QWidget
{
    Q_OBJECT
public:
    explicit mySliderValid(QWidget *parent = nullptr,int index=0);
static bool state;
    private:
        QSlider *varificationSlider;//滑动条
        QLabel *varificationLab1,*varificationLab2;//用于放置图片
        int index;//区别信号
    signals:
    void hasclose(int index);
public slots:
        void imageMove();
        void imageStop();
};

#endif // MYSLIDERVALID_H
