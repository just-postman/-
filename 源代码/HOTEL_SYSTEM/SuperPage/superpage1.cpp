#include "superpage1.h"
#include "ui_superpage1.h"

superPage1::superPage1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::superPage1)
{
    ui->setupUi(this);
    //界面初始化
    initTableView();
}

superPage1::~superPage1()
{
    delete ui;
}

int superPage1::sqlCount()
{
    QSqlQuery countquery;
    countquery.exec("select count(*) from room");
    countquery.next();
    int count=countquery.value(0).toInt();
    return count;
}

void superPage1::initTableView()
{
   currentpage=1;//当前页为1
   showcount=10;//每页显示数据
   findPageRange(0,showcount,"");
   countpage=sqlCount()/showcount+1;//总页数
   ui->label->setText(QString("当前页数：%1/%2").arg(currentpage).arg(countpage));
   ui->last_button->setEnabled(false);
}

void superPage1::findPageRange(int first, int last,QString roomid)
{
    mymodel=new mysqlQueryModel;
    QString findroom=QString("select * from room limit %1,%2").arg(first).arg(last);
    if(roomid!="")
    {
        findroom=QString("select * from room  where roomid like '%%1%' limit %2,%3").arg(roomid).arg(first).arg(last);
    }
    qDebug()<<findroom;
    mymodel->setQuery(findroom);
    mymodel->removeColumn(1,QModelIndex());
    mymodel->insertColumns(4,2,QModelIndex());
    mymodel->setHeaderData(0,Qt::Horizontal,QString("房间号"));
    mymodel->setHeaderData(1,Qt::Horizontal,QString("房间价格"));
    mymodel->setHeaderData(2,Qt::Horizontal,QString("房间状态"));
    mymodel->setHeaderData(3,Qt::Horizontal,QString("房间类型"));
    mymodel->setHeaderData(4,Qt::Horizontal,QString("编辑"));
    mymodel->setHeaderData(5,Qt::Horizontal,QString("删除"));
    ui->tableView->setModel(mymodel);
    for(int i=0;i<mymodel->rowCount();i++)
    {
        edit_bn=new QPushButton("编辑");
        delete_bn=new QPushButton("删除");
        QString roomid=mymodel->record(i).value(0).toString();
        edit_bn->setProperty("rowIndex",roomid);
        delete_bn->setProperty("rowIndex",roomid);
        ui->tableView->setIndexWidget(mymodel->index(i,4),edit_bn);
        ui->tableView->setIndexWidget(mymodel->index(i,5),delete_bn);
        connect(edit_bn,&QPushButton::clicked,this,&superPage1::editbutton_clicked);
        connect(delete_bn,&QPushButton::clicked,this,&superPage1::deletebutton_clicked);
    }
}

void superPage1::on_last_button_clicked()
{
    currentpage--;
    ui->next_button->setEnabled(true);
    if(currentpage<=1)
    {
        qDebug()<<"==current:"<<currentpage;
        ui->last_button->setEnabled(false);
        int first=(currentpage-1)*showcount;
        findPageRange(first,showcount,"");
        ui->label->setText(QString("当前页数：%1/%2").arg(currentpage).arg(countpage));
        return;
    }
    ui->label->setText(QString("当前页数：%1/%2").arg(currentpage).arg(countpage));
    int first=(currentpage-1)*showcount;
    findPageRange(first,showcount,"");
}

void superPage1::on_next_button_clicked()
{
    currentpage++;
    ui->last_button->setEnabled(true);
    if(currentpage>=countpage)
    {
        qDebug()<<"==current:"<<currentpage;
        ui->next_button->setEnabled(false);
        int first=(currentpage-1)*showcount;
        findPageRange(first,showcount,"");
        ui->label->setText(QString("当前页数：%1/%2").arg(currentpage).arg(countpage));
        return;
    }
    ui->label->setText(QString("当前页数：%1/%2").arg(currentpage).arg(countpage));
    int first=(currentpage-1)*showcount;
    findPageRange(first,showcount,"");
}

void superPage1::editbutton_clicked()
{
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("rowIndex").toString();
        editpage=new superPage1Edit(nullptr,index);
        editpage->show();
        connect(editpage,SIGNAL(pageclosed()),this,SLOT(editpageClosed()));
    }
}

void superPage1::deletebutton_clicked()
{
    qDebug()<<"delete clicked";
    QPushButton *btn=dynamic_cast<QPushButton *>(sender());
    if(btn!=Q_NULLPTR)
    {
        QString index=btn->property("rowIndex").toString();
        QSqlQuery query;
        QString deletestring=QString("delete from room where roomid=%1").arg(index);
        QString infostring=QString("确定删除房间:%1?").arg(index);
        QMessageBox::StandardButton mybutton;
        mybutton=QMessageBox::information(nullptr,"提示信息",infostring,QMessageBox::Ok,QMessageBox::Cancel);
        if(mybutton==QMessageBox::Ok)
        {
            query.exec(deletestring);
            int x=(currentpage-1)*showcount;
            int y=x+showcount;
            findPageRange(x,y,"");
        }
    }
}

void superPage1::on_findroom_Button_clicked()
{
    int x=(currentpage-1)*showcount;
    int y=x+showcount;
    if(ui->lineEdit->text()!="")
        findPageRange(0,sqlCount(),ui->lineEdit->text());
    else
        findPageRange(x,y,ui->lineEdit->text());
}

void superPage1::on_lineEdit_textEdited(const QString &arg1)
{
    if(arg1=="")
    {
        ui->widget_2->setEnabled(true);
    }
    else
    {
        ui->widget_2->setEnabled(false);
    }
}

void superPage1::on_add_pushButton_clicked()
{
    if(ui->roomid_lineEdit->text()==""||ui->roomprice_lineEdit->text()=="")
    {
        QMessageBox::critical(nullptr,"警告","所输入内容不能为空");
        return;
    }
    if(ui->textBrowser->toPlainText()=="")
    {
        QMessageBox::critical(nullptr,"警告","您还未选择图片路径");
        return;
    }
    QSqlQuery insertquery;
    QString roomtype=ui->roomtype_comboBox->currentText();
    QString roomstatus=ui->roomstat_comboBox->currentText();
    QString sql=QString("insert into room values('%1',load_file('%2'),'%3','%4','%5')")
    .arg(ui->roomid_lineEdit->text()).arg(filepath).arg(ui->roomprice_lineEdit->text().toFloat())
    .arg(roomstatus).arg(roomtype);
    if(insertquery.exec(sql))
    {
        QMessageBox::information(nullptr,"提示",QString("您已成功添加房间：%1").arg(ui->roomid_lineEdit->text()));
        ui->roomid_lineEdit->clear();
        ui->roomprice_lineEdit->clear();
        ui->textBrowser->clear();
        return;
    }
    else
    {
        QMessageBox::critical(nullptr,"警告",QString("添加失败，该房间号已存在（请选择小于1M的图片！！）"));
    }

}

void superPage1::on_pic_pushButton_clicked()
{
    filepath=QFileDialog::getOpenFileName(this,"选择照片位置","/","照片(*.png *.jpg)");
    ui->textBrowser->setText(filepath);
    filepath.replace("/","//");
}

void superPage1::editpageClosed()
{
    int x=(currentpage-1)*showcount;
    int y=x+showcount;
    findPageRange(x,y,"");
}
