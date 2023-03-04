#include "registeruser.h"
#include "ui_registeruser.h"
#include"QMessageBox"
#include"QSqlQuery"
registeruser::registeruser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registeruser)
{
    ui->setupUi(this);
    this->setWindowTitle("员工注册界面");
}

registeruser::~registeruser()
{
    delete ui;
}

void registeruser::on_clear_pushButton_clicked()
{
    ui->id_lineEdit->clear();
    ui->sure_lineEdit->clear();
    ui->pwd_lineEdit->clear();
    ui->workid_lineEdit->clear();
}

void registeruser::on_register_pushButton_clicked()
{
    if(ui->id_lineEdit->text()==""||ui->sure_lineEdit->text()==""||ui->pwd_lineEdit->text()=="")
    {
        QMessageBox::critical(nullptr,"提示","不能为空");
        return;
    }
    if(ui->pwd_lineEdit->text()!=ui->sure_lineEdit->text())
    {
        QMessageBox::critical(nullptr,"提示","两次输入密码不一致");
        return;
    }
    QSqlQuery sqlquery;
    bool isinsert=sqlquery.exec(QString("insert into usertable values('%1','%2','%3')").arg(ui->id_lineEdit->text()).arg(ui->pwd_lineEdit->text()).arg(ui->workid_lineEdit->text()));
    if(isinsert)
    {
        QMessageBox::information(nullptr,"提示","注册成功");
        this->close();
    }
    else
    {
        QMessageBox::critical(nullptr,"提示","注册失败\n请检查员工id是否已存在");
    }
}
