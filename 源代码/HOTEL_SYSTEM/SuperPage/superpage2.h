#ifndef SUPERPAGE2_H
#define SUPERPAGE2_H

#include <QWidget>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QSqlRecord>
#include<QPushButton>
#include<QMessageBox>
#include<QRegExp>
#include<QRegExpValidator>
#include<QLabel>
#include"MyClass/mysqlquerymodel.h"
#include"superpage2edit.h"
#include"resetpassword.h"
namespace Ui {
class superPage2;
}

class superPage2 : public QWidget
{
    Q_OBJECT

public:
    explicit superPage2(QWidget *parent = nullptr);
    ~superPage2();

    mysqlQueryModel *model;
    mysqlQueryModel *psdmodel;
    QPushButton *delete_button;
    QPushButton *edit_button;

    QPushButton *delete_pwd_button;
    QPushButton *edit_pwd_button;
    superPage2Edit *editpage;
    resetPassword *resetpage;
    void findEmployee(QString sql);
    void findPassword(QString sql);
private slots:
    void on_find_pushButton_clicked();

    void on_add_pushButton_clicked();

    void on_clear_pushButton_clicked();

    void editButtonClicked();

    void deleteButtonClicked();

    void editpwdButtonClicked();

    void deletepwdButtonClicked();

private:
    Ui::superPage2 *ui;
};

#endif // SUPERPAGE2_H
