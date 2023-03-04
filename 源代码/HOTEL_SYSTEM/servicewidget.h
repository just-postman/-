#ifndef SERVICEWIDGET_H
#define SERVICEWIDGET_H

#include <QWidget>
#include <QWidget>
#include<QSqlQueryModel>
#include<QPixmap>
#include<QSqlQuery>
#include<QDebug>
#include<QList>
#include<QSqlRecord>
#include<QLabel>
#include<QPushButton>
#include<QDateTime>
#include<QMessageBox>
#include<qvalidator.h>
#include<QRegExp>
#include<QRegExpValidator>
#include<QStandardItemModel>
#include<QModelIndex>
#include<QTreeWidgetItem>
#include<QFileDialog>
#include<QThread>
#include"MyClass/mysqlquerymodel.h"
#include"MyClass/mythread.h"
#include"servicepage1.h"
namespace Ui {
class servicewidget;
}

class servicewidget : public QWidget
{
    Q_OBJECT

public:
    explicit servicewidget(QWidget *parent = nullptr);
    ~servicewidget();
    //枚举房间的类型
    enum type{nolimit_type,sigleroom,doubleroom,familyroom,presidentroom};
    //枚举房间状态
    enum status{nolimit_stat,free_stat,using_stat,reserve_stat};
    //数据库查询model
   mysqlQueryModel *model;//房间model
   mysqlQueryModel *clientmodel;//客户入住信息model
   mysqlQueryModel *reserveClientModel;//客户预订model
   mysqlQueryModel *exitRoomModel;//退房记录model

   QStandardItemModel *itemModel;//列表model
   QPushButton *btn1;//添加的查看图片按钮
   QPushButton *btn2;//入住按钮
   ServicePage1 *page1;
   QStringList exitRecordList;//记录退房所有信息
   myThread *mythread;
   QThread *thread;

    void setCurrentTime(void);
    void showtable(QString tabquery);//表格内容显示
    void showclient(QString tabquery);//显示入住客人信息
    void showReserve();//listview列表显示
    void exitRoomRecord(QString tabquery);//退房记录
    void setComboboxItem();//设置续房退房下拉列表
    void setCancelComboboxaItem();//设置取消预订下拉列表
    //控制输入格式函数
    void control_textEdit(void);

private:
    Ui::servicewidget *ui;
public: signals:
    void startTimer(QObject *widget);
public  slots:
    void BtnClicked(bool checked);//按钮点击实现lable显示房间照片
    void Btn2Clicked(bool checked);//按钮实现入住功能
private slots:

    void on_findroom_button_clicked();//查找房间信息
    void on_clear_button_clicked();//清除文本框按钮
    void on_showdate_button_clicked();//显示日期按钮
    void on_signin_button_clicked();//登记按钮实现
    void on_treeView_doubleClicked(const QModelIndex &index);//treeview双击选中项

    //ui界面跳转槽函数
    void on_reserveButton_clicked();
    void on_findAllButton_clicked();
    void on_exit_pushButton_clicked();
    void on_continue_pushButton_2_clicked();
    void on_continueroom_comboBox_currentIndexChanged(const QString &arg1);
    void on_exitroom_comboBox_currentIndexChanged(const QString &arg1);
    void on_canceledReserve_comboBox_currentIndexChanged(const QString &arg1);
    void on_cancelReserve_pushButton_clicked();
    void on_commandLinkButton_clicked();

};


#endif // SERVICEWIDGET_H
