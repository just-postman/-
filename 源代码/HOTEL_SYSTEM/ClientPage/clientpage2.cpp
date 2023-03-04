#include "clientpage2.h"
#include "ui_clientpage2.h"

clientPage2::clientPage2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientPage2)
{
    ui->setupUi(this);
    //table显示房间信息
    showRoomInfo("");


}

clientPage2::~clientPage2()
{
    delete ui;
}

void clientPage2::showRoomInfo(QString text)
{
    QString room;
    room=QString("select roompicture,roomid,roomtype,roomstatus from room where roomtype like'%%1%'").arg(text);
    QSqlQuery query;
    query.exec(room);

    int count=0;
    int cols=4;//列
    int rows=(query.size()/4)+1;//行

    QStandardItemModel *itemmodel=new QStandardItemModel(rows,cols,this);
    while(query.next())
    {
        //添加model数据
        QString mydata_1="房间号："+query.value(1).toString()+"\n房间类型："+query.value(2).toString()+"\n房间状态："+query.value(3).toString();
        itemmodel->setData(itemmodel->index(count,0,QModelIndex()),query.value(0),Qt::DecorationRole);
        itemmodel->setData(itemmodel->index(count,0,QModelIndex()),mydata_1,Qt::DisplayRole);
        itemmodel->setData(itemmodel->index(count,0,QModelIndex()),query.value(1).toString(),Qt::ToolTipRole);
        if(!query.next())
        break;
        //------------------
        QString mydata_2="房间号："+query.value(1).toString()+"\n房间类型："+query.value(2).toString()+"\n房间状态："+query.value(3).toString();
        itemmodel->setData(itemmodel->index(count,1,QModelIndex()),query.value(0),Qt::DecorationRole);
        itemmodel->setData(itemmodel->index(count,1,QModelIndex()),mydata_2,Qt::DisplayRole);
        itemmodel->setData(itemmodel->index(count,1,QModelIndex()),query.value(1).toString(),Qt::ToolTipRole);
        if(!query.next())
        break;
        //-------------------
        QString mydata_3="房间号："+query.value(1).toString()+"\n房间类型："+query.value(2).toString()+"\n房间状态："+query.value(3).toString();
        itemmodel->setData(itemmodel->index(count,2,QModelIndex()),query.value(0),Qt::DecorationRole);
        itemmodel->setData(itemmodel->index(count,2,QModelIndex()),mydata_3,Qt::DisplayRole);
        itemmodel->setData(itemmodel->index(count,2,QModelIndex()),query.value(1).toString(),Qt::ToolTipRole);
        if(!query.next())
        break;
        //-------------------
        QString mydata_4="房间号："+query.value(1).toString()+"\n房间类型："+query.value(2).toString()+"\n房间状态："+query.value(3).toString();
        itemmodel->setData(itemmodel->index(count,3,QModelIndex()),query.value(0),Qt::DecorationRole);
        itemmodel->setData(itemmodel->index(count,3,QModelIndex()),mydata_4,Qt::DisplayRole);
        itemmodel->setData(itemmodel->index(count,3,QModelIndex()),query.value(1).toString(),Qt::ToolTipRole);
        if(!query.next())
        break;
        count++;
    }
    itemdelegate=new myItemDelegate(this);

    ui->tableView->setItemDelegate(itemdelegate);
    ui->tableView->setModel(itemmodel);
    //隐藏列表列头和行首
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setVisible(false);
    //表格不可编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int i=0;i<itemmodel->rowCount();i++) {
        ui->tableView->setRowHeight(i,240);
        ui->tableView->setColumnWidth(i,200);
    }
    connect(itemdelegate,&myItemDelegate::send_update,this,&clientPage2::on_pushButton_clicked);
}

void clientPage2::on_pushButton_clicked()
{
//    QString text=ui->lineEdit->text();
    qDebug()<<"进来了";
    QString text=ui->comboBox->currentText();
    if(text=="不限")
    {
        text="";
    }
    showRoomInfo(text);
}

