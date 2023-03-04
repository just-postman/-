#ifndef MYPROPERTYANIMATION_H
#define MYPROPERTYANIMATION_H

#include <QWidget>
#include<QHBoxLayout>
#include<QPropertyAnimation>
#include<QPainter>
namespace Ui {
class myPropertyAnimation;
}

class myPropertyAnimation : public QWidget
{
    Q_OBJECT
    //qt特有的属性系统，这里表示 float（QVariant类）类型 读m_alpha的方法是getAlpha函数，写m_alpha的方法是setAlpha
    //如果在后面加入 USER ture则表示是用户自定义的类型
    Q_PROPERTY(float m_alpha READ getAlpha WRITE setAlpha)
public:
    explicit myPropertyAnimation(QWidget *parent = nullptr ,QRect rect=QRect());
    ~myPropertyAnimation();

private:
    Ui::myPropertyAnimation *ui;
public:
    //设置特效的窗体
    void setWidget(QWidget *widget);
    //设置边距（边距=线条宽度）
    void setMarginis(int margins);
    //设置边框颜色
    void setBorderColor(QColor color);
    //获取边距
    int getMargins();
    //获取边框颜色
    QColor getBorderColor();

protected:
    void paintEvent(QPaintEvent *);
    void drawBorder(QPainter *painter);

private:
    void setAlpha(float alpha);
    float getAlpha()    const;

private:
    int m_contentMargin;                      //保存控件边距
    QColor m_borderColor;                  //边框颜色
    float m_alpha;                                    //α通道值
    QWidget *m_widget;                       //特效窗体
    QHBoxLayout *m_hLayout;             //水平布局
    QPropertyAnimation *m_animation;    //动画
    QRect m_rect;                   //设置绘制边框大小
};

#endif // MYPROPERTYANIMATION_H
