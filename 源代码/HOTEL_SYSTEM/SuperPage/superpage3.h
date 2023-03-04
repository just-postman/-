#ifndef SUPERPAGE3_H
#define SUPERPAGE3_H

#include <QWidget>
#include<QSqlQuery>
#include<QDebug>
#include<QPushButton>
#include<QMessageBox>
#include<QSqlRecord>
#include<QLabel>
#include"MyClass/mysqlquerymodel.h"
#include"superpage5detail.h"
#include"superpage3edit.h"
namespace Ui {
class superPage3;
}

class superPage3 : public QWidget
{
    Q_OBJECT

public:
    explicit superPage3(QWidget *parent = nullptr);
    ~superPage3();
    void showinfo(QString sql);
    void showpwd(QString sql);
public slots:
void deleteButtonClicked();
void editButtonClicked();
private slots:
void on_pushButton_clicked();
void editpwdButtonClicked();
void deletepwdButtonClicked();
private:
    Ui::superPage3 *ui;
    superPage3Edit *page;
    mysqlQueryModel *model;
    mysqlQueryModel *psdmodel;
    QPushButton *delete_button;
    QPushButton *edit_button;
    QPushButton *edit_pwd_button;
    QPushButton *delete_pwd_button;
};

#endif // SUPERPAGE3_H
