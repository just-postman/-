#include "superpage5detail.h"
#include "ui_superpage5detail.h"
#include<QDebug>
superPage5Detail::superPage5Detail(QWidget *parent,QString id) :
    QWidget(parent),id(id),
    ui(new Ui::superPage5Detail)
{
    ui->setupUi(this);
    showinfo();
}

superPage5Detail::~superPage5Detail()
{
    delete ui;
}

void superPage5Detail::showinfo()
{
    QSqlQuery sqlquery;
    QString sql=QString("select * from research where messageid='%1'").arg(id);
    sqlquery.exec(sql);
    if(sqlquery.next())
    {
        ui->roomid_lineEdit->setText(sqlquery.value(1).toString());
        QString  messageinfo=sqlquery.value(2).toString();
        messageinfo.replace(",","\n");
        ui->textBrowser->setText(messageinfo);
        ui->date_lineEdit->setText(sqlquery.value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
}
