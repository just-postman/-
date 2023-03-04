#include "registerpage.h"
#include "ui_registerpage.h"
#include"QMessageBox"
#include"QSqlQuery"
registerPage::registerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerPage)
{
    ui->setupUi(this);
    this->setWindowTitle("客户注册界面");
}

registerPage::~registerPage()
{
    delete ui;
}

void registerPage::on_clear_pushButton_clicked()
{
    ui->name_lineEdit->clear();
    ui->id_lineEdit->clear();
    ui->sure_lineEdit->clear();
    ui->pwd_lineEdit->clear();
    ui->workid_lineEdit->clear();
}

void registerPage::on_register_pushButton_clicked()
{
    if(ui->name_lineEdit->text()==""||ui->id_lineEdit->text()==""||ui->sure_lineEdit->text()==""||ui->pwd_lineEdit->text()=="")
    {
        QMessageBox::critical(nullptr,"提示","不能为空");
        return;
    }
    QSqlQuery query;
    query.exec("select * from usertable");
    bool isfind=false;
    while(query.next())
    {
        if(query.value(2).toString()==ui->workid_lineEdit->text())
        {
            isfind=!isfind;
            break;
        }
    }
    if(!isfind)
    {
        QMessageBox::information(nullptr,"提示信息","协助员工号不存在/n请重新输入");
        return ;
    }
    if(ui->pwd_lineEdit->text()!=ui->sure_lineEdit->text())
    {
        QMessageBox::critical(nullptr,"提示","两次输入密码不一致");
        return;
    }
    QSqlQuery sqlquery;
    bool isinsert=sqlquery.exec(QString("insert into clienttable values('%1','%2','%3')").arg(ui->id_lineEdit->text()).arg(ui->pwd_lineEdit->text()).arg(ui->name_lineEdit->text()));
    if(isinsert)
    {
        QMessageBox::information(nullptr,"提示","注册成功");
        this->close();
    }
    else
    {
        QMessageBox::critical(nullptr,"提示","注册失败");
    }
}
