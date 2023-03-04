#include "superpage2.h"
#include "ui_superpage2.h"

superPage2::superPage2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::superPage2)
{
    ui->setupUi(this);

     //正则表达式,控制输入有效的身份证号
     QRegExp id_rx("^[0-9x]{18}$");
     ui->idcard_lineEdit->setValidator(new QRegExpValidator(id_rx,this));
     //正则表达式输入有效的手机号
     QRegExp phone_rx("^[0-9]{11}$");
     ui->phone_lineEdit->setValidator(new QRegExpValidator(phone_rx,this));
     findEmployee("select * from employee");
     findPassword("select * from usertable");
}

superPage2::~superPage2()
{
    delete ui;
}

void superPage2::findEmployee(QString sql)
{
    model=new mysqlQueryModel;
    model->setQuery(sql);
    model->insertColumn(7,QModelIndex());
    model->insertColumn(8,QModelIndex());
    model->setHeaderData(0,Qt::Horizontal,QString("姓名"));
    model->setHeaderData(1,Qt::Horizontal,QString("工号"));
    model->setHeaderData(2,Qt::Horizontal,QString("年龄"));
    model->setHeaderData(3,Qt::Horizontal,QString("身份证号"));
    model->setHeaderData(4,Qt::Horizontal,QString("联系电话"));
    model->setHeaderData(5,Qt::Horizontal,QString("住址"));
    model->setHeaderData(6,Qt::Horizontal,QString("入职时间"));
    model->setHeaderData(7,Qt::Horizontal,QString("编辑"));
    model->setHeaderData(8,Qt::Horizontal,QString("删除"));

    ui->tableView->setModel(model);
    for(int i=0;i<model->rowCount();i++)
    {
        edit_button=new QPushButton("编辑");
        delete_button=new QPushButton("删除");
        QString workid=model->record(i).value(1).toString();
        edit_button->setProperty("idIndex",workid);
        delete_button->setProperty("idIndex",workid);
        ui->tableView->setIndexWidget(model->index(i,7),edit_button);
        ui->tableView->setIndexWidget(model->index(i,8),delete_button);
        connect(edit_button,&QPushButton::clicked,this,&superPage2::editButtonClicked);
        connect(delete_button,&QPushButton::clicked,this,&superPage2::deleteButtonClicked);
    }
        ui->tableView->setColumnWidth(0,50);
        ui->tableView->setColumnWidth(1,60);
        ui->tableView->setColumnWidth(2,50);
        ui->tableView->setColumnWidth(3,80);
        ui->tableView->setColumnWidth(4,80);
        ui->tableView->setColumnWidth(5,80);
        ui->tableView->setColumnWidth(6,100);
        ui->tableView->setColumnWidth(7,50);
        ui->tableView->setColumnWidth(8,50);
}

void superPage2::findPassword(QString sql)
{
    psdmodel=new mysqlQueryModel;
    psdmodel->setQuery(sql);
    psdmodel->insertColumn(3,QModelIndex());
    psdmodel->insertColumn(4,QModelIndex());
//    psdmodel->removeColumn(1,QModelIndex());
    psdmodel->setHeaderData(0,Qt::Horizontal,QString("账号"));
    psdmodel->setHeaderData(1,Qt::Horizontal,QString("密码"));

    psdmodel->setHeaderData(2,Qt::Horizontal,QString("工号"));
    psdmodel->setHeaderData(3,Qt::Horizontal,QString("重置"));
    psdmodel->setHeaderData(4,Qt::Horizontal,QString("删除"));

    ui->tableView_2->setModel(psdmodel);
    for(int i=0;i<psdmodel->rowCount();i++)
    {

        edit_pwd_button=new QPushButton("重置");
        delete_pwd_button=new QPushButton("删除");
        QString workid=psdmodel->record(i).value(2).toString();
        edit_pwd_button->setProperty("idIndex",workid);
        delete_pwd_button->setProperty("idIndex",workid);
        QLabel *lable=new QLabel("******");
        lable->setAlignment(Qt::AlignCenter);
        ui->tableView_2->setIndexWidget(psdmodel->index(i,1),lable);
        ui->tableView_2->setIndexWidget(psdmodel->index(i,3),edit_pwd_button);
        ui->tableView_2->setIndexWidget(psdmodel->index(i,4),delete_pwd_button);
        connect(edit_pwd_button,&QPushButton::clicked,this,&superPage2::editpwdButtonClicked);
        connect(delete_pwd_button,&QPushButton::clicked,this,&superPage2::deletepwdButtonClicked);
    }

}


void superPage2::on_find_pushButton_clicked()
{
    QString id=ui->lineEdit->text();
    if(id=="")
    {
        findEmployee("select * from employee");
    }
    else
    {
        findEmployee(QString("select * from employee where workid='%1'").arg(id));
    }
}

void superPage2::on_add_pushButton_clicked()
{
    if(ui->name_lineEdit->text()=="" || ui->workid_lineEdit->text()==""||
       ui->phone_lineEdit->text()=="" || ui->address_lineEdit->text()==""||
       ui->age_lineEdit->text()==""||ui->idcard_lineEdit->text()=="")
    {
        QMessageBox::critical(nullptr,"错误提示","所填写内容不能为空");
        return ;
    }
    if(ui->phone_lineEdit->text().length()!=11 || ui->idcard_lineEdit->text().length()!=18)
    {
        QMessageBox::critical(nullptr,"错误提示","请按照提示输入正确的格式");
    }
    QSqlQuery sqlquery;
    QString sql=QString("insert into employee values('%1','%2','%3','%4','%5','%6','%7')")
    .arg(ui->name_lineEdit->text()).arg(ui->workid_lineEdit->text()).arg(ui->age_lineEdit->text())
    .arg(ui->idcard_lineEdit->text()).arg(ui->phone_lineEdit->text()).arg(ui->address_lineEdit->text())
    .arg(ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(sqlquery.exec(sql))
    {
        QMessageBox::information(nullptr,"提示",QString("添加员工成功\n员工号：%1").arg(ui->name_lineEdit->text()));
    }
    else
    {
        QMessageBox::critical(nullptr,"错误",QString("添加员工失败"));
    }
}

void superPage2::on_clear_pushButton_clicked()
{
    ui->name_lineEdit->clear();
    ui->workid_lineEdit->clear();
    ui->phone_lineEdit->clear();
    ui->address_lineEdit->clear();
    ui->age_lineEdit->clear();
    ui->idcard_lineEdit->clear();
}

void superPage2::editButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("idIndex").toString();
        editpage=new superPage2Edit(nullptr,index);
        editpage->show();
    }
}

void superPage2::deleteButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("idIndex").toString();
        QSqlQuery query;
        QString deletestring=QString("delete from employee where workid=%1").arg(index);
        QString infostring=QString("确定删除员工:%1?").arg(index);
        QMessageBox::StandardButton mybutton;
        mybutton=QMessageBox::information(nullptr,"提示信息",infostring,QMessageBox::Ok,QMessageBox::Cancel);
        if(mybutton==QMessageBox::Ok)
        {
            query.exec(deletestring);
            QMessageBox::information(nullptr,"提示","删除成功");
        }
    }
}

void superPage2::editpwdButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("idIndex").toString();
        resetpage=new resetPassword(nullptr,index);
        resetpage->show();
    }
}

void superPage2::deletepwdButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("idIndex").toString();
        QSqlQuery query;
        QString deletestring=QString("delete from usertable where workid=%1").arg(index);
        QString infostring=QString("确定删除员工(%1)密码:?").arg(index);
        QMessageBox::StandardButton mybutton;
        mybutton=QMessageBox::information(nullptr,"提示信息",infostring,QMessageBox::Ok,QMessageBox::Cancel);
        if(mybutton==QMessageBox::Ok)
        {
            query.exec(deletestring);
            QMessageBox::information(nullptr,"提示","删除成功");
            findPassword("select * from usertable");
        }
    }
}
