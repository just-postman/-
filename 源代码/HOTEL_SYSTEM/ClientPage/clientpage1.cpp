#include "clientpage1.h"
#include "ui_clientpage1.h"

clientPage1::clientPage1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientPage1)
{
    ui->setupUi(this);
    //添加轮播图
    m_rotate=new myRotatePictures(ui->widget_2);
    //添加表格数据
    showtable();
}

clientPage1::~clientPage1()
{
    delete ui;
}

void clientPage1::showtable()
{
    m_model=new QStandardItemModel(4,3,this);
    m_model->setHeaderData(0,Qt::Horizontal,"房间类型");
    m_model->setHeaderData(1,Qt::Horizontal,"最高价");
    m_model->setHeaderData(2,Qt::Horizontal,"最低价");

    QString max_single=QString("SELECT MAX(room.roomprice) FROM room WHERE roomtype='单人间'");
    QString min_single=QString("SELECT MIN(room.roomprice) FROM room WHERE roomtype='单人间'");
    QString max_double=QString("SELECT MAX(room.roomprice) FROM room WHERE roomtype='双人房'");
    QString min_double=QString("SELECT MIN(room.roomprice) FROM room WHERE roomtype='双人房'");

     QString max_family=QString("SELECT MAX(room.roomprice) FROM room WHERE roomtype='家庭房'");
     QString min_family=QString("SELECT MIN(room.roomprice) FROM room WHERE roomtype='家庭房'");
     QString max_president=QString("SELECT MAX(room.roomprice) FROM room WHERE roomtype='总统套房'");
     QString min_president=QString("SELECT MIN(room.roomprice) FROM room WHERE roomtype='总统套房'");
     //获取每个查询语句的值，即获取最大最小值
    QSqlQuery mysql;
    mysql.exec(max_single);
    mysql.next();
    float max_single_f=mysql.value(0).toFloat();

    mysql.exec(min_single);
    mysql.next();
    float min_single_f=mysql.value(0).toFloat();

    mysql.exec(max_double);
    mysql.next();
    float max_double_f=mysql.value(0).toFloat();

    mysql.exec(min_double);
    mysql.next();
    float min_double_f=mysql.value(0).toFloat();
    //--
    mysql.exec(max_family);
    mysql.next();
    float max_family_f=mysql.value(0).toFloat();

    mysql.exec(min_family);
    mysql.next();
    float min_family_f=mysql.value(0).toFloat();

    mysql.exec(max_president);
    mysql.next();
    float max_president_f=mysql.value(0).toFloat();

    mysql.exec(min_president);
    mysql.next();
    float min_president_f=mysql.value(0).toFloat();
    //model添加行列
    m_model->setData(m_model->index(0,0,QModelIndex()),"单人间");
    m_model->setData(m_model->index(0,1,QModelIndex()),max_single_f);
    m_model->setData(m_model->index(0,2,QModelIndex()),min_single_f);

    m_model->setData(m_model->index(1,0,QModelIndex()),"双人间");
    m_model->setData(m_model->index(1,1,QModelIndex()),max_double_f);
    m_model->setData(m_model->index(1,2,QModelIndex()),min_double_f);

    m_model->setData(m_model->index(2,0,QModelIndex()),"家庭套间");
    m_model->setData(m_model->index(2,1,QModelIndex()),max_family_f);
    m_model->setData(m_model->index(2,2,QModelIndex()),min_family_f);

    m_model->setData(m_model->index(3,0,QModelIndex()),"总统套房");
    m_model->setData(m_model->index(3,1,QModelIndex()),max_president_f);
    m_model->setData(m_model->index(3,2,QModelIndex()),min_president_f);

    //设置行列高度
    ui->tableView->setModel(m_model);
    ui->tableView->setColumnWidth(0,60);
    ui->tableView->setColumnWidth(1,60);
    ui->tableView->setColumnWidth(2,60);
    ui->tableView->setRowHeight(0,80);
    ui->tableView->setRowHeight(1,80);
    ui->tableView->setRowHeight(2,80);
    ui->tableView->setRowHeight(3,80);
    ui->tableView->verticalHeader()->setVisible(false);

}
