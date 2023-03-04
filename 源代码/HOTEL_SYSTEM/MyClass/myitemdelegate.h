#ifndef MYITEMDELEGATE_H
#define MYITEMDELEGATE_H

#include <QObject>
#include<QStyledItemDelegate>
#include<QWidget>
#include<QSqlQuery>
#include"servicepage1.h"
class myItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit myItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
signals:
    void signal_deleteclick(QModelIndex index);
    void signal_signedRoom(QString roomid);
    void send_update(void);
public slots:
    void buttonClicked(QString roomid);
private:
    ServicePage1 *page1;
    bool isSigned;
};

#endif // MYITEMDELEGATE_H
