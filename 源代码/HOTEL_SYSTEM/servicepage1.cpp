#include "servicepage1.h"
#include "ui_servicepage1.h"

ServicePage1::ServicePage1(QWidget *parent,QString roomid) :
    QWidget(parent),roomid(roomid),
    ui(new Ui::ServicePage1)
{
    ui->setupUi(this);
    //正则表达式,控制输入有效的身份证号
     QRegExp id_rx("^[0-9x]{18}$");
     ui->id_lineEdit->setValidator(new QRegExpValidator(id_rx,this));
     //正则表达式输入有效的手机号
     QRegExp phone_rx("^[0-9]{11}$");
     ui->phone_lineEdit->setValidator(new QRegExpValidator(phone_rx,this));
     ui->phone_lineEdit->setValidator(new QRegExpValidator(phone_rx,this));
     FullInformation();
     this->setWindowTitle("房间入住");
}

ServicePage1::~ServicePage1()
{
    delete ui;
}

void ServicePage1::FullInformation()
{
    QSqlQuery sqlquery;
    QString sql=QString("select * from room where roomid=%1").arg(roomid);
    sqlquery.exec(sql);
    if(sqlquery.next())
    {
        ui->roomid_lineEdit->setText(sqlquery.value(0).toString());
        ui->roomtype_lineEdit->setText(sqlquery.value(4).toString());
        ui->roomprice_lineEdit->setText(sqlquery.value(2).toString());
        QPixmap poto;
        poto.loadFromData(sqlquery.value(1).toByteArray(),"jpg");
        poto=poto.scaled(150,150,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
        ui->piclable->setScaledContents(true);
        ui->piclable->setPixmap(poto);
    }
}

void ServicePage1::on_pushButton_clicked()
{
    QString clientname=ui->name_lineEdit->text();
    QString clientphone=ui->phone_lineEdit->text();
    QString clientid=ui->id_lineEdit->text();
    if(clientname==""||clientphone==""||clientid=="")
    {
        QMessageBox::critical(nullptr,"提示信息","所输入内容不能为空");
        return;
    }
    if(clientid.length()!=18)
    {
        QMessageBox::critical(nullptr,"提示信息","身份证号输入有误，请重新输入");
        return;
    }
    if(clientphone.length()!=11)
    {
        QMessageBox::critical(nullptr,"提示信息","手机号输入有误，请重新输入");
        return;
    }
    QSqlQuery sqlquery;
    QDateTime datetime=QDateTime::currentDateTime();
    QString date_time=datetime.toString("yyyy-MM-dd hh:mm:ss");
    QString client_sql=QString("insert into client values('%1','%2','%3','%4','%5','0000-00-00 00:00:00',1)")
    .arg(roomid).arg(clientname).arg(clientid).arg(clientphone).arg(date_time);
    if(sqlquery.exec(client_sql))
    {
        QString update_sql=QString("update room set roomstatus='租用中' where roomid =%1").arg(roomid);
        QSqlQuery updatequery;
        if(updatequery.exec(update_sql))
        {
            QMessageBox::information(nullptr,"提示信息","房间入住成功");
            this->close();
        }
        else
        {
            QMessageBox::critical(nullptr,"提示信息","房间入住失败");
        }
    }

}

void ServicePage1::on_pushButton_2_clicked()
{
    ui->name_lineEdit->clear();
    ui->id_lineEdit->clear();
    ui->phone_lineEdit->clear();
}

void ServicePage1::closeEvent(QCloseEvent *event)
{
    emit pageclosed();
}
