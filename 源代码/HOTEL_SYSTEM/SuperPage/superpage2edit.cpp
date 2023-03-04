#include "superpage2edit.h"
#include "ui_superpage2edit.h"

superPage2Edit::superPage2Edit(QWidget *parent,QString workid) :
    QWidget(parent),workid(workid),
    ui(new Ui::superPage2Edit)
{
    ui->setupUi(this);
    this->setWindowTitle("员工编辑");
    fullinfo();
}

superPage2Edit::~superPage2Edit()
{
    delete ui;
}

void superPage2Edit::fullinfo()
{
    QSqlQuery sqlquery;
    QString sql=QString("select * from employee where workid='%1'").arg(workid);
    if(!sqlquery.exec(sql))
    {
        QMessageBox::information(this,"查询结果","查询不到该员工号！");
        return;
    }
    if(sqlquery.next())
    {
        ui->name_lineEdit->setText(sqlquery.value(0).toString());
        ui->workid_lineEdit->setText(sqlquery.value(1).toString());
        ui->agelineEdit->setText(sqlquery.value(2).toString());
        ui->idcard_lineEdit->setText(sqlquery.value(3).toString());
        ui->phone_lineEdit->setText(sqlquery.value(4).toString());
        ui->address_lineEdit->setText(sqlquery.value(5).toString());
        ui->datetime_lineEdit->setText(sqlquery.value(6).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
}

void superPage2Edit::on_update_pushButton_clicked()
{
    if(ui->name_lineEdit->text()==""||
        ui->phone_lineEdit->text()==""||
        ui->agelineEdit->text()==""||
        ui->idcard_lineEdit->text()==""||
        ui->address_lineEdit->text()=="")
    {
        QMessageBox::critical(this,"更新提示","所填写内容不能为空");
        return;
    }
    QSqlQuery sqlquery;
    QString sql=QString("update employee set name='%1',age='%2',idcard='%3',phone='%4',address='%5' where workid='%6'")
    .arg(ui->name_lineEdit->text()).arg(ui->agelineEdit->text()).arg(ui->idcard_lineEdit->text()).arg(ui->phone_lineEdit->text()).arg(ui->address_lineEdit->text()).arg(workid);
    qDebug()<<sql;
    if(!sqlquery.exec(sql))
    {
        QMessageBox::critical(this,"更新提示","修改员工失败");
        return;
    }
    else
    {
        QMessageBox::information(this,"更新提示","修改员工成功");
        this->close();
    }
}

void superPage2Edit::on_clear_pushButton_clicked()
{
    ui->name_lineEdit->clear();
    ui->phone_lineEdit->clear();
    ui->agelineEdit->clear();
    ui->idcard_lineEdit->clear();
    ui->address_lineEdit->clear();
}
