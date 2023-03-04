#ifndef SUPERPAGE5_H
#define SUPERPAGE5_H

#include <QWidget>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QPushButton>
#include<QMessageBox>
#include<QSqlRecord>
#include"MyClass/mysqlquerymodel.h"
#include"superpage5detail.h"
namespace Ui {
class superPage5;
}

class superPage5 : public QWidget
{
    Q_OBJECT

public:
    explicit superPage5(QWidget *parent = nullptr);
    ~superPage5();
    void showMessage(QString sql);
    mysqlQueryModel *model;
    QPushButton *delete_button;
    QPushButton *detail_button;
    superPage5Detail *page;
private slots:
    void on_pushButton_clicked();

    void detailButtonClicked();

    void deleteButtonClicked();
    void on_pushButton_2_clicked();

private:
    Ui::superPage5 *ui;
};

#endif // SUPERPAGE5_H
