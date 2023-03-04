#include "myitemdelegate.h"
#include<QtWidgets>
myItemDelegate::myItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    isSigned=false;
    connect(this,SIGNAL(signal_signedRoom(QString)),this,SLOT(buttonClicked(QString)));

}

void myItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //decorationrole支持图标icon、image等显示
    QByteArray arr=index.data(Qt::DecorationRole).toByteArray();
    QString pic=index.data(Qt::DecorationRole).toString();
//    QString roomid=index.data(Qt::DecorationRole).toString();
    QPixmap pixmap;
    pixmap.loadFromData(arr,"jpg");
    //等比例缩放
    pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    QString text="";
    //设置当前文本option的xy坐标
    int x=option.rect.x();
    int y=option.rect.y()+170;
    //设置照片的option的xy坐标
    int pix_x=option.rect.x();
    int pix_y=option.rect.y();
    //设置按钮位置
    QStyleOptionButton button;
    button.text="客房入住";
    button.rect=QRect(option.rect.x(),option.rect.y()+220,80,20);
    button.state=option.state;
    if(option.state &QStyle::State_Selected)
        painter->fillRect(option.rect,option.palette.highlight());//高亮绘制
    QStyleOptionViewItem p;
    text=index.data(Qt::DisplayRole).toString();
//    button.text=index.data(Qt::ToolTipRole).toString();
    qApp->style()->drawItemPixmap(painter,QRect(pix_x,pix_y,200,180),Qt::AlignCenter,pixmap);
    qApp->style()->drawItemText(painter,QRect(x,y,180,40),option.displayAlignment,QApplication::palette(),true,text);
    if(pic!="")
    {
        qApp->style()->drawControl(QStyle::CE_PushButton,&button,painter);
    }
//    painter->save();

}

bool myItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect rect=option.rect;
    //鼠标响应区域
    QRect replyRect=QRect(rect);
    //按钮响应区域
    QStyleOptionButton button;
    QRect buttonRect=QRect(option.rect.x(),option.rect.y()+220,80,20);
    button.rect=buttonRect;
    QMouseEvent *mouseevent=static_cast<QMouseEvent *>(event);
    if(!mouseevent) return false;
    //鼠标释放时间
    if(mouseevent->type()==QEvent::MouseButtonRelease&&replyRect.contains(mouseevent->pos()))
    {
        qDebug()<<"鼠标点击了:index:"<<index.row();
    }
    if(buttonRect.contains(mouseevent->pos()))
    {
        switch (event->type()) {
            case QEvent::MouseButtonPress:
            {
                QString roomid=index.data(Qt::ToolTipRole).toString();
                emit signal_signedRoom(roomid);
                break;
            }
            default:
            break;
        }
    }

    //否则返回父类函数
    return QStyledItemDelegate::editorEvent(event,model,option,index);
}

void myItemDelegate::buttonClicked(QString roomid)
{
    qDebug()<<roomid;
    QSqlQuery sqlquery;
    QString sql=QString("select roomstatus from room where roomid =%1").arg(roomid);
    sqlquery.exec(sql);
    sqlquery.next();
    if(sqlquery.value(0).toString()!="空闲中")
    {
        QMessageBox::critical(nullptr,"提示信息","房间已被占用");
        return ;
    }
    page1 = new ServicePage1(nullptr,roomid);
    page1->show();
    //更新视图
    connect(page1,&ServicePage1::pageclosed,this,[=](){
         emit send_update();
    });
}



