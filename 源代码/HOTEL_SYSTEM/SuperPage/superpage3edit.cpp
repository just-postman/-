#include "superpage3edit.h"
#include "ui_superpage3edit.h"

superPage3Edit::superPage3Edit(QWidget *parent,QString name) :
    QWidget(parent),name(name),
    ui(new Ui::superPage3Edit)
{
    ui->setupUi(this);
    fillinfo();
    this->setWindowTitle("客户编辑");
}

superPage3Edit::~superPage3Edit()
{
    delete ui;
}

void superPage3Edit::fillinfo()
{
    QSqlQuery query;
    query.exec("select roomid from room");
    while(query.next())
    {
          ui->comboBox->addItem(query.value(0).toString());
    }
    QSqlQuery sqlquery;
    QString sql=QString("select * from client where clientname='%1'").arg(name);
    sqlquery.exec(sql);
    if(sqlquery.next())
    {
        ui->comboBox->setCurrentText(sqlquery.value(0).toString());
        ui->name_lineEdit->setText(sqlquery.value(1).toString());
        ui->id_lineEdit->setText(sqlquery.value(2).toString());
        ui->phone_lineEdit->setText(sqlquery.value(3).toString());
        ui->datetime_lineEdit->setText(sqlquery.value(4).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        ui->days_lineEdit->setText(sqlquery.value(6).toString());
    }
}

void superPage3Edit::on_clear_pushButton_clicked()
{
    ui->name_lineEdit->clear();
    ui->phone_lineEdit->clear();
    ui->id_lineEdit->clear();
    ui->datetime_lineEdit->clear();
    ui->days_lineEdit->clear();
}

void superPage3Edit::on_update_pushButton_clicked()
{
    QSqlQuery sqlquery;
    QString sql=QString("update client set roomid=%1,clientname='%2',clientid='%3',clientphone='%4',clientdate='%5',days=%6 where clientname='%7'")
    .arg(ui->comboBox->currentText()).arg(ui->name_lineEdit->text()).arg(ui->id_lineEdit->text()).arg(ui->phone_lineEdit->text()).arg(ui->datetime_lineEdit->text()).arg(ui->days_lineEdit->text()).arg(name);
    qDebug()<<sql;
    if(sqlquery.exec(sql))
    {
        QMessageBox::information(nullptr,"提示","修改成功");
    }
    else
    {
        QMessageBox::information(nullptr,"提示","修改失败");
    }
}
