#include "resetpassword.h"
#include "ui_resetpassword.h"

resetPassword::resetPassword(QWidget *parent, QString workid) :
    QWidget(parent),workid(workid),
    ui(new Ui::resetPassword)
{
    ui->setupUi(this);
    ui->clientid_lineEdit->setText(workid);
}

resetPassword::~resetPassword()
{
    delete ui;
}

void resetPassword::on_pushButton_clicked()
{
    if(ui->before_lineEdit->text()==""||ui->after_lineEdit->text()==""||ui->sure_lineEdit->text()=="")
    {
        QMessageBox::critical(nullptr,"提示信息","输入内容不能为空");
        return ;
    }
    QSqlQuery sqlquery;
    sqlquery.exec(QString("select password from usertable where workid ='%1'").arg(workid));
    sqlquery.next();
    if(sqlquery.value(0).toString()!=ui->before_lineEdit->text())
    {
        QMessageBox::critical(nullptr,"提示信息","原密码错误\n请重新输入");
        return ;
    }
    if(ui->sure_lineEdit->text()!=ui->after_lineEdit->text())
    {
        QMessageBox::critical(nullptr,"提示信息","两次密码输入不一致");
        return ;
    }
   QSqlQuery resetsql;
   bool isreset=resetsql.exec(QString("UPDATE usertable SET PASSWORD='%1' WHERE workid='%2' ").arg(ui->sure_lineEdit->text()).arg(workid));
   if(isreset)
   {
     QMessageBox::information(nullptr,"提示信息","密码修改成功");
     this->close();
   }
}
