#include "superpage3.h"
#include "ui_superpage3.h"

superPage3::superPage3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::superPage3)
{
    ui->setupUi(this);
    showinfo("select * from client");
    showpwd("select * from clienttable");
}

superPage3::~superPage3()
{
    delete ui;
}

void superPage3::showinfo(QString sql)
{
    QSqlQuery sqlquery;
    model=new mysqlQueryModel;
    model->setQuery(sql);
    model->removeColumn(5,QModelIndex());
    model->insertColumns(6,2,QModelIndex());
    model->setHeaderData(0,Qt::Horizontal,"房间号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"身份证号");
    model->setHeaderData(3,Qt::Horizontal,"联系电话");
    model->setHeaderData(4,Qt::Horizontal,"入住时间");
    model->setHeaderData(5,Qt::Horizontal,"入住天数");
    model->setHeaderData(6,Qt::Horizontal,"删除");
    model->setHeaderData(7,Qt::Horizontal,"修改");

     ui->tableView->setModel(model);
    for(int i=0;i<model->rowCount();i++)
    {
        delete_button=new QPushButton("删除");
        edit_button=new QPushButton("修改");
        QString name=model->record(i).value(1).toString();
        delete_button->setProperty("name",name);
        edit_button->setProperty("name",name);
        ui->tableView->setIndexWidget(model->index(i,6),delete_button);
        ui->tableView->setIndexWidget(model->index(i,7),edit_button);
        connect(delete_button,&QPushButton::clicked,this,&superPage3::deleteButtonClicked);
        connect(edit_button,&QPushButton::clicked,this,&superPage3::editButtonClicked);
    }
     ui->tableView->setColumnWidth(0,50);
     ui->tableView->setColumnWidth(1,80);
     ui->tableView->setColumnWidth(2,100);
     ui->tableView->setColumnWidth(3,100);
     ui->tableView->setColumnWidth(4,100);
     ui->tableView->setColumnWidth(5,60);
     ui->tableView->setColumnWidth(6,50);
     ui->tableView->setColumnWidth(7,50);
}

void superPage3::showpwd(QString sql)
{
    psdmodel=new mysqlQueryModel;
    psdmodel->setQuery(sql);
    psdmodel->insertColumn(3,QModelIndex());
//    psdmodel->insertColumn(4,QModelIndex());
    psdmodel->setHeaderData(0,Qt::Horizontal,QString("账号"));
    psdmodel->setHeaderData(1,Qt::Horizontal,QString("密码"));
    psdmodel->setHeaderData(2,Qt::Horizontal,QString("姓名"));
    psdmodel->setHeaderData(3,Qt::Horizontal,QString("删除"));

    ui->tableView_2->setModel(psdmodel);
    for(int i=0;i<psdmodel->rowCount();i++)
    {
//        edit_pwd_button=new QPushButton("重置");
        delete_pwd_button=new QPushButton("删除");
        QString workid=psdmodel->record(i).value(2).toString();
//        edit_pwd_button->setProperty("name",workid);
        delete_pwd_button->setProperty("name",workid);
        QLabel *lable=new QLabel("******");
        lable->setAlignment(Qt::AlignCenter);
        ui->tableView_2->setIndexWidget(psdmodel->index(i,1),lable);
//        ui->tableView_2->setIndexWidget(psdmodel->index(i,3),edit_pwd_button);
        ui->tableView_2->setIndexWidget(psdmodel->index(i,3),delete_pwd_button);
//        connect(edit_pwd_button,&QPushButton::clicked,this,&superPage3::editpwdButtonClicked);
        connect(delete_pwd_button,&QPushButton::clicked,this,&superPage3::deletepwdButtonClicked);
    }
}

void superPage3::deleteButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString name=btn->property("name").toString();
        QString sql=QString("delete from client where clientname='%1'").arg(name);
        QSqlQuery sqlquery;
        QMessageBox::StandardButton button= QMessageBox::information(nullptr,"删除提示",QString("确定要删除客户(%1)的记录吗").arg(name),QMessageBox::Ok,QMessageBox::Cancel);
        if(button==QMessageBox::Ok)
        {
            if(sqlquery.exec(sql))
            {
                QMessageBox::information(nullptr,"删除提示","删除成功");
                showinfo("select * from client");
            }
            else
            {
                QMessageBox::critical(nullptr,"删除提示","删除失败");
            }
        }
    }
}

void superPage3::editButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString name=btn->property("name").toString();
        page=new superPage3Edit(nullptr,name);
        page->show();
    }
}

void superPage3::on_pushButton_clicked()
{
    QString text=ui->lineEdit->text();
    if(text=="")
    {
        showinfo("select * from client");
    }
    else
    {
        showinfo(QString("select * from client where clientname='%1'").arg(text));
    }
}

void superPage3::editpwdButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString name=btn->property("idIndex").toString();
    }
}

void superPage3::deletepwdButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString name=btn->property("name").toString();
        QSqlQuery query;
        QString deletestring=QString("delete from clienttable where clientname='%1'").arg(name);
        QString infostring=QString("确定删除租客(%1)密码:?").arg(name);
        QMessageBox::StandardButton mybutton;
        mybutton=QMessageBox::information(nullptr,"提示信息",infostring,QMessageBox::Ok,QMessageBox::Cancel);
        if(mybutton==QMessageBox::Ok)
        {
            query.exec(deletestring);
            QMessageBox::information(nullptr,"提示","删除成功");
            showpwd("select * from clienttable");
        }
    }
}
