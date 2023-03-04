#include "clientpage4.h"
#include "ui_clientpage4.h"
bool clientPage4::is_submit=false;
clientPage4::clientPage4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientPage4)
{
    ui->setupUi(this);
    investigate();
    setCombobox();
}

clientPage4::~clientPage4()
{
    delete ui;
}

void clientPage4::investigate()
{

    b1=new QButtonGroup();
    b2=new QButtonGroup();
    b3=new QButtonGroup();
    b4=new QButtonGroup();
    b5=new QButtonGroup();

    b1->addButton(ui->service_radioButton_1,0);
    b1->addButton(ui->service_radioButton_2,1);
    b1->addButton(ui->service_radioButton_3,2);
    b2->addButton(ui->clean_radioButton_1,0);
    b2->addButton(ui->clean_radioButton_2,1);
    b2->addButton(ui->clean_radioButton_3,2);
    b3->addButton(ui->around_radioButton_1,0);
    b3->addButton(ui->around_radioButton_2,1);
    b3->addButton(ui->around_radioButton_3,2);
    b4->addButton(ui->secret_radioButton_1,0);
    b4->addButton(ui->secret_radioButton_2,1);
    b4->addButton(ui->secret_radioButton_3,2);
    b5->addButton(ui->price_radioButton_1,0);
    b5->addButton(ui->price_radioButton_2,1);
    b5->addButton(ui->price_radioButton_3,2);

}

void clientPage4::setCombobox()
{
    ui->comboBox->clear();
    QString findroomsql=QString("select roomid from room");
    QSqlQuery roomidQuery;
    roomidQuery.exec(findroomsql);
    while(roomidQuery.next())
    {
        ui->comboBox->addItem(roomidQuery.value(0).toString());
    }
}

void clientPage4::on_pushButton_clicked()
{
    if(b1->checkedId()==-1||b2->checkedId()==-1||b3->checkedId()==-1||b4->checkedId()==-1||b5->checkedId()==-1)
    {
        QMessageBox::critical(nullptr,"错误提示","不能为空") ;
        return;
    }
    if(clientPage4::is_submit)
    {
        QMessageBox::critical(nullptr,"错误提示","您已经提交过留言了\n请勿重复提交");
        return;
    }
    QString b1_button=b1->checkedButton()->text();
    QString b2_button=b2->checkedButton()->text();
    QString b3_button=b3->checkedButton()->text();
    QString b4_button=b4->checkedButton()->text();
    QString b5_button=b5->checkedButton()->text();
    my_message.clear();
    my_message=QString("服务:")+b1_button+QString(",卫生:")+b2_button+QString(",环境:")+b3_button+QString(",保密：")+b4_button+QString(",消费:")+b5_button+QString(",客户想说:")+ui->textEdit->toPlainText();
    QSqlQuery setquery;
    QString roomid=ui->comboBox->currentText();
    QString info=QString("insert into research values(null,'%1','%2','%3')").arg(roomid).arg(my_message).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    bool isok=setquery.exec(info);
    if(isok)
    {
        QMessageBox::information(nullptr,"新华酒店","感谢您的反馈\n您可以到前台领取一份小礼品",QMessageBox::Ok,QMessageBox::Cancel);
        clientPage4::is_submit=true;
    }
    else
    {
        qDebug()<<info;
        QMessageBox::information(nullptr,"新华大酒店","您的输入有误",QMessageBox::Ok,QMessageBox::Cancel);
    }
}

