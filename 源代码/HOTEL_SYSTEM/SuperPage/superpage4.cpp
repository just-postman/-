#include "superpage4.h"
#include "ui_superpage4.h"

superPage4::superPage4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::superPage4)
{
    ui->setupUi(this);
    showinfo("select * from exitrecord");

}

superPage4::~superPage4()
{
    delete ui;
}

void superPage4::showinfo(QString sql)
{
    QSqlQuery sqlquery;
    model=new mysqlQueryModel;
    model->setQuery(sql);
    model->setHeaderData(0,Qt::Horizontal,"房间号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"身份证号");
    model->setHeaderData(3,Qt::Horizontal,"联系电话");
    model->setHeaderData(4,Qt::Horizontal,"入住时间");
    model->setHeaderData(5,Qt::Horizontal,"退房时间");
    model->setHeaderData(6,Qt::Horizontal,"入住天数");
    model->setHeaderData(7,Qt::Horizontal,"付款金额");
    model->insertColumns(8,1,QModelIndex());
    model->setHeaderData(8,Qt::Horizontal,"删除");
     ui->tableView->setModel(model);
    for(int i=0;i<model->rowCount();i++)
    {
        delete_button=new QPushButton("删除");
        QString name=model->record(i).value(1).toString();
        delete_button->setProperty("name",name);
        ui->tableView->setIndexWidget(model->index(i,8),delete_button);
        connect(delete_button,&QPushButton::clicked,this,&superPage4::deleteButtonClicked);
    }
     ui->tableView->setColumnWidth(0,50);
     ui->tableView->setColumnWidth(1,50);
     ui->tableView->setColumnWidth(2,90);
     ui->tableView->setColumnWidth(3,90);
     ui->tableView->setColumnWidth(4,90);
     ui->tableView->setColumnWidth(5,80);
     ui->tableView->setColumnWidth(6,60);
     ui->tableView->setColumnWidth(7,60);
     ui->tableView->setColumnWidth(8,50);
}

void superPage4::deleteButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString name=btn->property("name").toString();
        QString sql=QString("delete from exitrecord where clientname='%1'").arg(name);
        QSqlQuery sqlquery;
        QMessageBox::StandardButton button= QMessageBox::information(nullptr,"删除提示",QString("确定要删除(%1)的记录吗").arg(name),QMessageBox::Ok,QMessageBox::Cancel);
        if(button==QMessageBox::Ok)
        {
            if(sqlquery.exec(sql))
            {
                QMessageBox::information(nullptr,"删除提示","删除成功");
                showinfo("select * from exitrecord");
            }
            else
            {
                QMessageBox::critical(nullptr,"删除提示","删除失败");
            }
        }
    }
}

void superPage4::on_pushButton_clicked()
{
    QString text=ui->lineEdit->text();
    if(text!="")
    {
        showinfo(QString("select * from exitrecord where clientname='%1'").arg(text));
    }
    else
    {
        showinfo("select * from exitrecord");
    }
}
