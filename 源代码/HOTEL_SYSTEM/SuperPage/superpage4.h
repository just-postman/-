#ifndef SUPERPAGE4_H
#define SUPERPAGE4_H

#include <QWidget>
#include<QSqlQuery>
#include<QDebug>
#include<QPushButton>
#include<QMessageBox>
#include<QSqlRecord>
#include"MyClass/mysqlquerymodel.h"
#include"SuperPage/superpage5detail.h"
namespace Ui {
class superPage4;
}

class superPage4 : public QWidget
{
    Q_OBJECT

public:
    explicit superPage4(QWidget *parent = nullptr);
    ~superPage4();
mysqlQueryModel *model;
QPushButton *detail_button;
QPushButton *delete_button;
    void showinfo(QString sql);
private slots:
    void deleteButtonClicked();
    void on_pushButton_clicked();

private:
    Ui::superPage4 *ui;
};

#endif // SUPERPAGE4_H
