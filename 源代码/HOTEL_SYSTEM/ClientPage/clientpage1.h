#ifndef CLIENTPAGE1_H
#define CLIENTPAGE1_H

#include <QWidget>
#include<QSqlQueryModel>
#include<QAbstractTableModel>
#include<QStandardItemModel>
#include<QPixmap>
#include<QSqlQuery>
#include<QDebug>
#include"MyClass/myrotatepictures.h"
#include"MyClass/mysqlquerymodel.h"
namespace Ui {
class clientPage1;
}

class clientPage1 : public QWidget
{
    Q_OBJECT

public:
    explicit clientPage1(QWidget *parent = nullptr);
    ~clientPage1();
    myRotatePictures *m_rotate;
    QStandardItemModel *m_model;
    void showtable(void);
private:
    Ui::clientPage1 *ui;
};

#endif // CLIENTPAGE1_H
