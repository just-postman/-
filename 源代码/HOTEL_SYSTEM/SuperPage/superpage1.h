#ifndef SUPERPAGE1_H
#define SUPERPAGE1_H

#include<QWidget>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QSqlRecord>
#include<QPushButton>
#include"MyClass/mysqlquerymodel.h"
#include"superpage1edit.h"
namespace Ui {
class superPage1;
}

class superPage1 : public QWidget
{
    Q_OBJECT

public:
    explicit superPage1(QWidget *parent = nullptr);
    ~superPage1();
    //获取总共数据个数
    int sqlCount();
    //初始化
    void initTableView();
    //查询表格显示范围
    void findPageRange(int first,int last,QString roomid);

//    void setroomtype(QString roomtype){this->roomtype=roomtype;}
//    void setroomstatus(QString roomstatus){this->roomstatus=roomstatus;}
//    QString getroomtype(){ return roomtype;}
//    QString getroomstatus(){return roomstatus;}

private:

    //model
    mysqlQueryModel *mymodel;
   //当前页码数
    int currentpage;
    //每页显示的数据行数
    int showcount;
    //总共页数
    int countpage;

    QPushButton *edit_bn;
    QPushButton *delete_bn;
    superPage1Edit *editpage;
    QString roomtype;
    QString roomstatus;
    QString filepath;
private slots:
    void on_last_button_clicked();

    void on_next_button_clicked();

    void editbutton_clicked();

    void deletebutton_clicked();

    void on_findroom_Button_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_add_pushButton_clicked();

    void on_pic_pushButton_clicked();

    void editpageClosed();

private:
    Ui::superPage1 *ui;
};

#endif // SUPERPAGE1_H
