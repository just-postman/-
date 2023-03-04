#include "superpage5.h"
#include "ui_superpage5.h"

superPage5::superPage5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::superPage5)
{
    ui->setupUi(this);
    showMessage("select * from research");
}

superPage5::~superPage5()
{
    delete ui;
}

void superPage5::showMessage(QString sql)
{
    model=new mysqlQueryModel;
    model->setQuery(sql);
    model->setHeaderData(0,Qt::Horizontal,"序号");
    model->setHeaderData(1,Qt::Horizontal,"房间号");
    model->setHeaderData(2,Qt::Horizontal,"留言内容");
    model->setHeaderData(3,Qt::Horizontal,"留言日期");
    model->setHeaderData(4,Qt::Horizontal,"查看详情");
    model->setHeaderData(5,Qt::Horizontal,"删除");
    model->insertColumns(4,2,QModelIndex());
     ui->tableView->setModel(model);
    for(int i=0;i<model->rowCount();i++)
    {
        detail_button=new QPushButton("查看详情");
        delete_button=new QPushButton("删除");
        QString id=model->record(i).value(0).toString();
        detail_button->setProperty("idIndex",id);
        delete_button->setProperty("idIndex",id);
        ui->tableView->setIndexWidget(model->index(i,4),detail_button);
        ui->tableView->setIndexWidget(model->index(i,5),delete_button);
        connect(detail_button,&QPushButton::clicked,this,&superPage5::detailButtonClicked);
        connect(delete_button,&QPushButton::clicked,this,&superPage5::deleteButtonClicked);
    }
     ui->tableView->setColumnWidth(0,50);
     ui->tableView->setColumnWidth(1,50);
     ui->tableView->verticalHeader()->setVisible(false);
}

void superPage5::on_pushButton_clicked()
{
    QString text=ui->lineEdit->text();
    if(text=="")
    {
        showMessage("select * from research");
    }
    else
    {
        showMessage(QString("select * from research where roomid='%1'").arg(text));
    }
}

void superPage5::detailButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("idIndex").toString();
        page=new superPage5Detail(nullptr,index);
        page->show();
    }
}

void superPage5::deleteButtonClicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("idIndex").toString();
        QSqlQuery sqlquery;
        QString sql=QString("delete from research where messageid=%1").arg(index);
        if(sqlquery.exec(sql))
        {
            QMessageBox::information(nullptr,"删除提示","删除成功");
            showMessage("select * from research");
        }
        else
        {
            QMessageBox::critical(nullptr,"删除提示","删除失败");
        }
    }
}

void superPage5::on_pushButton_2_clicked()
{
    QSqlQuery sqlquery;
    QString sqldelete=QString("delete from research");
    QMessageBox::StandardButton button;
    button=QMessageBox::information(nullptr,"删除提示","您确定要删除所有吗？",QMessageBox::Ok,QMessageBox::Cancel);
    if(button==QMessageBox::Ok)
    {
        if(sqlquery.exec(sqldelete))
        {
            QMessageBox::information(nullptr,"提示","删除成功");
            showMessage("select * from research");
        }
        else
        {
            QMessageBox::critical(nullptr,"提示","删除失败");
        }
    }
}
