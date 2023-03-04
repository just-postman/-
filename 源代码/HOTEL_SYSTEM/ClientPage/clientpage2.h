#ifndef CLIENTPAGE2_H
#define CLIENTPAGE2_H

#include <QWidget>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QStandardItemModel>
#include<QDebug>
#include"MyClass/myitemdelegate.h"
namespace Ui {
class clientPage2;
}

class clientPage2 : public QWidget
{
    Q_OBJECT

public:
    explicit clientPage2(QWidget *parent = nullptr);
    ~clientPage2();
    myItemDelegate *itemdelegate;
    void showRoomInfo(QString text);
private slots:
    void on_pushButton_clicked();
private:
    Ui::clientPage2 *ui;
};

#endif // CLIENTPAGE2_H
