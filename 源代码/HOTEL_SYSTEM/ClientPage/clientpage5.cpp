#include "clientpage5.h"
#include "ui_clientpage5.h"

clientPage5::clientPage5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientPage5)
{
    ui->setupUi(this);
    setCombobox();//设置下拉列表选项
     //正则表达式,控制输入有效的身份证号
     QRegExp id_rx("^[0-9x]{18}$");
     ui->id_lineEdit->setValidator(new QRegExpValidator(id_rx,this));
     //正则表达式输入有效的手机号
     QRegExp phone_rx("^[0-9]{11}$");
     ui->phone_lineEdit->setValidator(new QRegExpValidator(phone_rx,this));
     ui->phone_lineEdit->setValidator(new QRegExpValidator(phone_rx,this));
}

clientPage5::~clientPage5()
{
    delete ui;
}

void clientPage5::setCombobox()
{
    ui->comboBox->clear();
    QSqlQuery sqlquery;
    QString sql=QString("select roomid from reserve");
    sqlquery.exec(sql);
    while(sqlquery.next())
    {
        ui->comboBox->addItem(sqlquery.value(0).toString());
    }
}

void clientPage5::on_pushButton_clicked()
{
    QDateTime datetime=QDateTime::currentDateTime();
    QString date_time=datetime.toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery sqlselect,sqlinsert,sqldelete;
    QString sql=QString("select * from reserve");
    QString insertstr=QString("insert into client values('%1','%2','%3','%4','%5',NULL,1)")
    .arg(ui->comboBox->currentText()).arg(ui->name_lineEdit->text()).arg(ui->id_lineEdit->text())
    .arg(ui->phone_lineEdit->text()).arg(date_time);
    QString deletestr=QString("delete from reserve where roomid='%1'").arg(ui->comboBox->currentText());
    sqlselect.exec(sql);

    bool isfind=false;
    if(ui->id_lineEdit->text().length()!=18)
    {
        QMessageBox::critical(nullptr,"警告","请输入有效的身份证号");
        return;
    }
    while(sqlselect.next())
    {
        if(sqlselect.value(0).toString()==ui->comboBox->currentText()&&
           sqlselect.value(1).toString()==ui->name_lineEdit->text()&&
           sqlselect.value(2).toString()==ui->phone_lineEdit->text())
        {
            isfind=true;
        }
    }

    if(!isfind)
    {
        QMessageBox::critical(nullptr,"提示","没有找到符合预订信息的客户");
        return;
    }
    qDebug()<<insertstr;
    qDebug()<<deletestr;
    if(sqldelete.exec(deletestr)&&sqlinsert.exec(insertstr))
    {
        QMessageBox::information(nullptr,"提示",QString("入住成功\n您的房间号为：%1,请到前台领取房卡").arg(ui->comboBox->currentText()));
    }
    else
    {
        QMessageBox::critical(nullptr,"提示","入住失败");
    }
    setCombobox();
}

void clientPage5::on_pushButton_2_clicked()
{
    ui->id_lineEdit->clear();
    ui->phone_lineEdit->clear();
    ui->name_lineEdit->clear();
}
