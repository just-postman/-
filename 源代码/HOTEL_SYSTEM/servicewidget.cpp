#include "servicewidget.h"
#include "ui_servicewidget.h"

servicewidget::servicewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::servicewidget)
{
    ui->setupUi(this);
    setCurrentTime();//线程执行，设置当前时间
    showtable("select * from room");
    showclient("select * from client");
    setComboboxItem();//设置下拉列表子项
    setCancelComboboxaItem();
    control_textEdit();//控制文本框输入格式
    showReserve();//listview显示
    exitRoomRecord("select * from exitrecord");
    ui->dateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setMinimumDateTime(QDateTime::currentDateTime());
    //为选项卡添加图标
    ui->tabWidget->setTabIcon(0,QIcon(":/icon/tab01.png"));
    ui->tabWidget->setTabIcon(1,QIcon(":/icon/tab02.png"));
    ui->tabWidget->setTabIcon(2,QIcon(":/icon/tab03.png"));
    ui->tabWidget->setTabIcon(3,QIcon(":/icon/tab04.png"));
    ui->tabWidget->setTabIcon(4,QIcon(":/icon/tab05.png"));
    ui->tabWidget->setTabIcon(5,QIcon(":/icon/tab06.png"));
}

servicewidget::~servicewidget()
{
    delete ui;
}

void servicewidget::setCurrentTime()
{
    mythread=new  myThread;
    thread=new QThread(this);
    mythread->moveToThread(thread);
    thread->start();
    connect(this,&servicewidget::startTimer,mythread,&myThread::myTimer);
    connect(thread,&QThread::finished,mythread,&QObject::deleteLater);
    emit startTimer(ui->label_7);
}

//房间查询模块
void servicewidget::showtable(QString tabquery)
{
    model=new mysqlQueryModel;
    model->setQuery(tabquery);
    //删除有image路径的一列
    model->removeColumn(1,QModelIndex());
    //插入自定义的实现的按钮列
    model->insertColumn(4,QModelIndex());
    model->insertColumn(5,QModelIndex());
    //设置table表的头部数据字段
    model->setHeaderData(0,Qt::Horizontal,QString("房间编号"));    
    model->setHeaderData(1,Qt::Horizontal,QString("房间价格"));
    model->setHeaderData(2,Qt::Horizontal,QString("房间状态"));
    model->setHeaderData(3,Qt::Horizontal,QString("房间类型"));
    model->setHeaderData(4,Qt::Horizontal,QString("房间照片"));
    model->setHeaderData(5,Qt::Horizontal,QString("客房入住"));
    //将设置好的model添加如tableview控件
    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);//设置隔行变色
   //row_count用于记录model的行数
    int row_count=model->rowCount();
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    //设置高度
    for (int i=0;i<row_count;i++) {
        ui->tableView->setRowHeight(i,20);
    }
    //为每一行添加查看按钮
     for(int i=0;i<model->rowCount();i++)
    {
        btn1=new QPushButton(QString("查看照片"));
        btn2=new QPushButton(QString("入住"));
        QString roomid=model->record(i).value(0).toString();
        btn1->setProperty("roomIndex",roomid);//设置属性值
        btn2->setProperty("roomIndex",roomid);
        ui->tableView->setIndexWidget(model->index(i,4),btn1);
        ui->tableView->setIndexWidget(model->index(i,5),btn2);
        connect(btn1,&QPushButton::clicked,this,&servicewidget::BtnClicked);
        connect(btn2,&QPushButton::clicked,this,&servicewidget::Btn2Clicked);
     }
     ui->tableView->setColumnWidth(4,80);
     ui->tableView->setColumnWidth(5,60);
}

//客户信息模块
void servicewidget::showclient(QString tabquery)
{
    clientmodel=new mysqlQueryModel;
    clientmodel->setQuery(tabquery);
    clientmodel->removeColumn(5,QModelIndex());
    clientmodel->setHeaderData(0,Qt::Horizontal,"房间号");
    clientmodel->setHeaderData(1,Qt::Horizontal,"姓名");
    clientmodel->setHeaderData(2,Qt::Horizontal,"身份证号");
    clientmodel->setHeaderData(3,Qt::Horizontal,"联系方式");
    clientmodel->setHeaderData(4,Qt::Horizontal,"入住时间");
    clientmodel->setHeaderData(5,Qt::Horizontal,"入住天数");
    //设置表格的model
    ui->tableView_2->setModel(clientmodel);

    //设置列宽
    ui->tableView_2->setColumnWidth(0,60);
    ui->tableView_2->setColumnWidth(1,60);
    ui->tableView_2->setColumnWidth(2,160);
    ui->tableView_2->setColumnWidth(3,120);
    ui->tableView_2->setColumnWidth(4,150);
    ui->tableView_2->setColumnWidth(5,60);
}

//客房预订模块
void servicewidget::showReserve()
{
        itemModel=new QStandardItemModel(this);
        QStringList treelist;
        treelist.append("单人间");
        treelist.append("双人房");
        treelist.append("家庭房");
        treelist.append("总统套间");

        //设置每个树叶下的查询语句
        QSqlQueryModel *treemodel_single=new QSqlQueryModel;
        treemodel_single->setQuery(QString("select * from room where roomtype='单人间'"));
        int model_single_count=treemodel_single->rowCount();

        QSqlQueryModel *treemodel_double=new QSqlQueryModel;
        treemodel_double->setQuery(QString("select * from room where roomtype='双人房'"));
        int model_double_count=treemodel_double->rowCount();

        QSqlQueryModel *treemodel_family=new QSqlQueryModel;
        treemodel_family->setQuery(QString("select * from room where roomtype='家庭房'"));
        int model_family_count=treemodel_family->rowCount();

        QSqlQueryModel *treemodel_president=new QSqlQueryModel;
        treemodel_president->setQuery(QString("select * from room where roomtype='总统套房'"));
        int model_president_count=treemodel_president->rowCount();

        itemModel->setColumnCount(3);
        itemModel->setHeaderData(0,Qt::Horizontal,"        房间号");
        itemModel->setHeaderData(1,Qt::Horizontal,"房间价格/晚");
        itemModel->setHeaderData(2,Qt::Horizontal,"房间状态");

        //为单人间listview下添加子项
        QStandardItem *item1=new QStandardItem(treelist.at(0));
        for(int j=0;j<model_single_count;j++)
        {
            QStandardItem *item_roomid=new QStandardItem(treemodel_single->record(j).value(0).toString());
            QStandardItem *item_roomprice=new QStandardItem(treemodel_single->record(j).value(2).toString());
            QStandardItem *item_roomstatus=new QStandardItem(treemodel_single->record(j).value(3).toString());
            QList<QStandardItem *>item_room;
            item_room<<item_roomid<<item_roomprice<<item_roomstatus;
             item1->appendRow(item_room);
        }
        itemModel->appendRow(item1);
        //为双人房listview下添加子项
        QStandardItem *item2=new QStandardItem(treelist.at(1));
        for(int j=0;j<model_double_count;j++)
        {
            QStandardItem *item_roomid=new QStandardItem(treemodel_double->record(j).value(0).toString());
            QStandardItem *item_roomprice=new QStandardItem(treemodel_double->record(j).value(2).toString());
            QStandardItem *item_roomstatus=new QStandardItem(treemodel_double->record(j).value(3).toString());
            QList<QStandardItem *>item_room;
            item_room<<item_roomid<<item_roomprice<<item_roomstatus;
             item2->appendRow(item_room);
        }
        itemModel->appendRow(item2);

         //为家庭房listview下添加子项
        QStandardItem *item3=new QStandardItem(treelist.at(2));
        for(int j=0;j<model_family_count;j++)
        {
            QStandardItem *item_roomid=new QStandardItem(treemodel_family->record(j).value(0).toString());
            QStandardItem *item_roomprice=new QStandardItem(treemodel_family->record(j).value(2).toString());
            QStandardItem *item_roomstatus=new QStandardItem(treemodel_family->record(j).value(3).toString());
            QList<QStandardItem *>item_room;
            item_room<<item_roomid<<item_roomprice<<item_roomstatus;
            item3->appendRow(item_room);
        }
        itemModel->appendRow(item3);

        //为总统套间listview下添加子项
         QStandardItem *item4=new QStandardItem(treelist.at(3));
         for(int j=0;j<model_president_count;j++)
        {
            QStandardItem *item_roomid=new QStandardItem(treemodel_president->record(j).value(0).toString());
            QStandardItem *item_roomprice=new QStandardItem(treemodel_president->record(j).value(2).toString());
            QStandardItem *item_roomstatus=new QStandardItem(treemodel_president->record(j).value(3).toString());
            QList<QStandardItem *>item_room;
            item_room<<item_roomid<<item_roomprice<<item_roomstatus;
            item4->appendRow(item_room);
        }
        itemModel->appendRow(item4);

        //添加设置好的itemmodel模型
        ui->treeView->setModel(itemModel);
        ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
}

//退房记录模块
void servicewidget::exitRoomRecord(QString tabquery)
{
    exitRoomModel=new mysqlQueryModel;
    exitRoomModel->setQuery(tabquery);
    exitRoomModel->removeColumn(2,QModelIndex());
    exitRoomModel->removeColumn(3,QModelIndex());

    exitRoomModel->setHeaderData(0,Qt::Horizontal,"房间号");
    exitRoomModel->setHeaderData(1,Qt::Horizontal,"姓名");
    exitRoomModel->setHeaderData(2,Qt::Horizontal,"入住时间");
    exitRoomModel->setHeaderData(3,Qt::Horizontal,"退房时间");
    exitRoomModel->setHeaderData(4,Qt::Horizontal,"入住天数");
    exitRoomModel->setHeaderData(5,Qt::Horizontal,"支付金额");

    ui->tableView_3->setModel(exitRoomModel);
    //设置列宽
    ui->tableView_3->setColumnWidth(0,60);
    ui->tableView_3->setColumnWidth(1,100);
    ui->tableView_3->setColumnWidth(2,132);
    ui->tableView_3->setColumnWidth(3,132);
    ui->tableView_3->setColumnWidth(4,100);
    ui->tableView_3->setColumnWidth(5,100);
}

//设置退房续房下拉列表选项
void servicewidget::setComboboxItem()
{
    ui->exitroom_comboBox->clear();
    ui->continueroom_comboBox->clear();
    QString findroomsql=QString("select roomid from room where roomstatus='租用中'");
    QSqlQuery roomidQuery;
    roomidQuery.exec(findroomsql);
    while(roomidQuery.next())
    {
        ui->exitroom_comboBox->addItem(roomidQuery.value(0).toString());
        ui->continueroom_comboBox->addItem(roomidQuery.value(0).toString());
    }
}

//设置取消预订下拉列表选项
void servicewidget::setCancelComboboxaItem()
{
    ui->canceledReserve_comboBox->clear();
    QString findReserve=QString("select roomid from room where roomstatus='已预订'");
    QSqlQuery cancelQuery;
    cancelQuery.exec(findReserve);
    while(cancelQuery.next())
    {
        ui->canceledReserve_comboBox->addItem(cancelQuery.value(0).toString());
    }
}

//控制文本框输入格式函数
void servicewidget::control_textEdit()
{
     //正则表达式,控制输入有效的身份证号
     QRegExp id_rx("^[0-9x]{18}$");
     ui->clientid_lineEdit->setValidator(new QRegExpValidator(id_rx,this));
     //正则表达式输入有效的手机号
     QRegExp phone_rx("^[0-9]{11}$");
     ui->clientphone_lineEdit->setValidator(new QRegExpValidator(phone_rx,this));
     ui->clientphone_lineEdit_2->setValidator(new QRegExpValidator(phone_rx,this));
}

//******************************按钮点击事件***************************
//**********************************************************************
//查看照片槽函数的实现
void servicewidget::BtnClicked(bool checked)
{
     Q_UNUSED(checked)
    //强制类型转换
    QPushButton *btn = dynamic_cast<QPushButton*> (sender());
    //Q_NULLPTR是一个宏，如果编译器支持c++11，则替换为NULLPTR；如果不支持，则替换为NULL
    if(btn != Q_NULLPTR)
    {
            QString index = btn->property("roomIndex").toString();
            QSqlQuery query;
            query.exec(QString("select * from room where roomid=%1").arg(index));
            //如果query查询index的按钮是设置的index为真，显示图片
            if(query.next())
            {
                QPixmap poto;
                QLabel *lable=new QLabel;
                poto.loadFromData(query.value(1).toByteArray(),"jpg");
                //设置pixmap自动填充lable大小S
                lable->setGeometry(400,200,500,400);
                poto.scaled(lable->size(),Qt::KeepAspectRatio);
                lable->setScaledContents(true);
                lable->setPixmap(poto);
                lable->show();
        }
    }
}

//按钮入住功能实现
void servicewidget::Btn2Clicked(bool checked)
{
    Q_UNUSED(checked)
    //强制类型转换
    QPushButton *btn = dynamic_cast<QPushButton*> (sender());
     if(btn != Q_NULLPTR)
    {
        QString index = btn->property("roomIndex").toString();
        QSqlQuery sqlquery;
        QString sql=QString("select roomstatus from room where roomid =%1").arg(index);
        sqlquery.exec(sql);
        sqlquery.next();
        if(sqlquery.value(0).toString()!="空闲中")
        {
            QMessageBox::critical(nullptr,"提示信息","房间已被占用");
            return ;
        }
        page1 = new ServicePage1(nullptr,index);
        page1->show();
        connect(page1,&ServicePage1::pageclosed,this,[=](){
                on_findroom_button_clicked();
                setComboboxItem();
        });  
    }
}

//查询房间信息按钮的点击事件
void servicewidget::on_findroom_button_clicked()
{
    QString tablesql="";
    int type_index=ui->roomtype_combobox->currentIndex();
    int stat_index=ui->roomstatus_combobox->currentIndex();
    switch (type_index) {
        //******************************当选择的房间是不限************************
        case nolimit_type:
            tablesql=QString("select * from room");
               switch (stat_index)
                {
                    case nolimit_stat:
                        ;
                        break;
                    case free_stat:
                        tablesql=QString("select * from room where roomstatus='空闲中'");
                        break;
                    case using_stat:
                        tablesql=QString("select * from room where roomstatus='租用中'");
                        break;
                    case reserve_stat:
                        tablesql=QString("select * from room where roomstatus='已预订'");
                        break;
                 }
            break;
        //**************************当选择的房间类型是单人间***********************
        case sigleroom:
            tablesql=QString("select * from room where roomtype='单人间'");
            switch (stat_index)
                {
                    case nolimit_stat:
                        ;
                        break;
                    case free_stat:
                        tablesql=QString("select * from room where roomtype='单人间' and roomstatus='空闲中'");
                        break;
                    case using_stat:
                       tablesql=QString("select * from room where roomtype='单人间' and roomstatus='租用中'");
                        break;
                    case reserve_stat:
                       tablesql=QString("select * from room where roomtype='单人间'and roomstatus='已预订'");
                        break;
                 }
            break;
        //**************当下拉列表的选择是双人间*****************************************
        case doubleroom:
            tablesql=QString("select * from room where roomtype='双人房'");
             switch (stat_index)
                {
                    case nolimit_stat:
                        ;
                        break;
                    case free_stat:
                       tablesql=QString("select * from room where roomtype='双人房' and roomstatus='空闲中'");
                        break;
                    case using_stat:
                        tablesql=QString("select * from room where roomtype='双人房' and roomstatus='租用中'");
                        break;
                    case reserve_stat:
                        tablesql=QString("select * from room where roomtype='双人房' and roomstatus='已预订'");
                        break;
                 }
            break;
        //**************当下拉列表的选择是家庭房*****************************************
        case familyroom:
            tablesql=QString("select * from room where roomtype='家庭房'");
             switch (stat_index)
                {
                    case nolimit_stat:
                        ;
                        break;
                    case free_stat:
                      tablesql=QString("select * from room where roomtype='家庭房' and roomstatus='空闲中'");
                        break;
                    case using_stat:
                      tablesql=QString("select * from room where roomtype='家庭房' and roomstatus='租用中'");
                        break;
                    case reserve_stat:
                      tablesql=QString("select * from room where roomtype='家庭房' and roomstatus='已预订'");
                        break;
                 }
            break;
        //**************当下拉列表的选择是总统套房*****************************************
        case presidentroom:
            tablesql=QString("select * from room where roomtype='总统套房'");
             switch (stat_index)
                {
                    case nolimit_stat:
                        ;
                        break;
                    case free_stat:
                        tablesql=QString("select * from room where roomtype='总统套房' and roomstatus='空闲中'");
                        break;
                    case using_stat:
                        tablesql=QString("select * from room where roomtype='总统套房' and roomstatus='租用中'");
                        break;
                    case reserve_stat:
                        tablesql=QString("select * from room where roomtype='总统套房' and roomstatus='已预订'");
                        break;
                 }
            break;
    }
    qDebug()<<tablesql;
    showtable(tablesql);
}

//清空按钮事件
void servicewidget::on_clear_button_clicked()
{
    ui->roomid_lineEdit->clear();
    ui->clientid_lineEdit->clear();
    ui->clientname_lineEdit->clear();
    ui->clientphone_lineEdit->clear();
}

//显示当前时间按钮事件
void servicewidget::on_showdate_button_clicked()
{
    QDateTime datetime=ui->dateTimeEdit->dateTime();
    // 设置当前时间在datetimeeidt控件上
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

//登记入住按钮事件
void servicewidget::on_signin_button_clicked()
{
    QString room_id=ui->roomid_lineEdit->text();
    QString client_name=ui->clientname_lineEdit->text();
    QString client_id=ui->clientid_lineEdit->text();
    QString client_phone=ui->clientphone_lineEdit->text();
    //将获取的时间转化成自己定义的格式
    QDateTime datetime=ui->dateTimeEdit->dateTime();
    QString date_time=datetime.toString("yyyy-MM-dd hh:mm:ss");
    //拼接ql语句
    QString client_sql=QString("insert into client values('%1','%2','%3','%4','%5','0000-00-00 00:00:00',1)")
    .arg(room_id).arg(client_name).arg(client_id).arg(client_phone).arg(date_time);
    QSqlQuery client_query;
    qDebug()<<"sql:"<<client_sql;

    //输入框不为空
    if(room_id==QString("")||client_id==QString("")||client_name==QString("")||client_phone==QString(""))
    {
        QMessageBox::warning(nullptr,"错误提示","所填写内容不能为空");
        return ;
    }

    //房间号不存在
    QSqlQuery find_room;
    find_room.exec(QString("select roomid from room"));
    bool isfind=false;
    while(find_room.next())
    {
        if(find_room.value(0).toString()==room_id)
        {
            isfind=true;
            break;
        }
    }
    if(isfind==false)
    {
        QMessageBox::critical(nullptr,"错误提示","没有找到该房间");
        return;
    }

    //身份证只能是18位
    if(ui->clientid_lineEdit->text().length()!=18)
    {
        QMessageBox::critical(nullptr,"错误提示","请输入有效的身份证号码");
        return;
    }

    //手机号只能为11位数字
    if(ui->clientphone_lineEdit->text().length()!=11)
    {
        QMessageBox::critical(nullptr,"错误提示","请输入有效的手机号码");
        return;
    }

    //房间处于租用或者预订状态
    QSqlQuery find_roomstatus;
    find_roomstatus.exec(QString("select roomstatus from room where roomid=%1").arg(room_id));
    while(find_roomstatus.next())
    {
        if(find_roomstatus.value(0).toString()=="租用中"||find_roomstatus.value(0).toString()=="已预订")
        {
            QMessageBox::critical(nullptr,"错误提示","房间已被占用");
            return;
        }
    }

    //执行sql语句
    if(client_query.exec(client_sql)==false)
    {
         QMessageBox::critical(nullptr,"错误提示","数据登记失败");
         return ;
    }

    //修改房间状态为租用中，并显示登记成功
    QSqlQuery update_roomstatus;
    update_roomstatus.exec(QString("update room set roomstatus='租用中' where roomid=%2").arg(room_id));
    QMessageBox::information(nullptr,"登记提示","登记成功");
    on_clear_button_clicked();
    setComboboxItem();
}

//房间预订事件
void servicewidget::on_reserveButton_clicked()
{
    QString roomid=ui->roomid_lineEdit_2->text();
    QString username=ui->clientname_lineEdit_2->text();
    QString userphone=ui->clientphone_lineEdit_2->text();
    QDateTime datetime=ui->dateTimeEdit_2->dateTime();
    QString date_time=datetime.toString("yyyy-MM-dd hh:mm:ss");
    QString reserveSql=QString("insert into reserve values('%1','%2','%3','%4')")
    .arg(roomid).arg(username).arg(userphone).arg(date_time);
    //输入框不为空
    if(username==QString("")||userphone==QString("")||roomid==QString(""))
    {
        QMessageBox::warning(nullptr,"错误提示","所填写内容不能为空");
        return ;
    }
    //手机号只能为11位数字
    if(ui->clientphone_lineEdit_2->text().length()!=11)
    {
        QMessageBox::critical(nullptr,"错误提示","请输入有效的手机号码");
        return;
    }
    QSqlQuery reserveQuery;
    QSqlQuery updateQuery;
    reserveQuery.exec(reserveSql);
    updateQuery.exec(QString("update room set roomstatus ='已预订' where roomid =%1").arg(roomid));
    QMessageBox::information(nullptr,"预订成功",QString("客户：%1").arg(username).append("预订成功"));
    ui->roomid_lineEdit_2->clear();
    showReserve();
    setComboboxItem();
    setCancelComboboxaItem();
}

//treeview双击点击事件
void servicewidget::on_treeView_doubleClicked(const QModelIndex &index)
{
//    QStandardItemModel *   standardModel = static_cast < QStandardItemModel*>(itemModel);
//    QAbstractItemModel *abmodel=(QAbstractItemModel *)index.model();
    QString indexValue=ui->treeView->model()->itemData(index).value(0).toString();
    QSqlQuery treequery;
    treequery.exec(QString("select * from room where roomid=%1").arg(indexValue.toInt()));
    QSqlRecord treeRecord;
    QString str="房间号:";
    QString roomtype="房间类型:";
    QString roomprice="房间价格:";
    QString hh="\n";
   if(treequery.next())
    {
//        int col=treequery.record().count();//获取记录中每一个查询结果的列
        if(treequery.value(3).toString()=="已预订"||treequery.value(3).toString()=="租用中")
        {
            QMessageBox::critical(nullptr,"错误提示","该房间已租用或已预订");
            ui->textBrowser->clear();
            ui->roomid_lineEdit_2->clear();
            return;
        }
        str.append(treequery.value(0).toString()).append(hh).append(roomtype);
        str.append(treequery.value(2).toString()).append(hh).append(roomprice);
        str.append(treequery.value(4).toString());
        ui->textBrowser->setText(str.replace("\\n","\n"));//添加换行
        ui->roomid_lineEdit_2->setText(treequery.value(0).toString());
    }
}

//实现模糊查询客户按钮事件
void servicewidget::on_findAllButton_clicked()
{
    QString textstr,findSql;
    textstr=ui->username_Edit->text();
    if(ui->reserve_radioButton->isChecked())
    {
        findSql=QString("select * from reserve where reservename like '%%1%'").arg(textstr);
        reserveClientModel=new mysqlQueryModel;
        ui->tableView_2->setModel(nullptr);//清除原有结果集
        reserveClientModel->setQuery(findSql);
        reserveClientModel->setHeaderData(0,Qt::Horizontal,"房间号");
        reserveClientModel->setHeaderData(1,Qt::Horizontal,"姓名");
        reserveClientModel->setHeaderData(2,Qt::Horizontal,"联系方式");
        reserveClientModel->setHeaderData(3,Qt::Horizontal,"预订时间");
        ui->tableView_2->setModel(reserveClientModel);
        ui->tableView_2->setColumnWidth(0,60);
        ui->tableView_2->setColumnWidth(1,60);
        ui->tableView_2->setColumnWidth(2,150);
        ui->tableView_2->setColumnWidth(3,150);
    }
    if(ui->lived_radioButton->isChecked())
    {
        findSql=QString("select * from client where clientname like '%%1%'").arg(textstr);
        showclient(findSql);
    }
}

//退房按钮点击事件
void servicewidget::on_exit_pushButton_clicked()
{
    QString currentText=ui->continueroom_comboBox->currentText();
//    QMessageBox::StandardButton resultbotton;
//    resultbotton=QMessageBox::information(this,"确认窗口",QString("确定（房间号：%1）退房？").arg(ui->exitroom_comboBox->currentText()),
//                                                        QMessageBox::Ok,QMessageBox::Cancel);
    QMessageBox msgbox(QMessageBox::Information,"确认窗口",QString("确定（房间号：%1）退房？").arg(ui->exitroom_comboBox->currentText()));
    msgbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgbox.button(QMessageBox::Yes)->setText("确定");
    msgbox.button(QMessageBox::No)->setText("取消");
    int res=msgbox.exec();
    if(res==QMessageBox::Yes)
    {
        QSqlQuery sql;
        QString str=QString("insert into exitrecord values('%1','%2','%3','%4','%5','%6','%7','%8')")
        .arg(exitRecordList[0]).arg(exitRecordList[1]).arg(exitRecordList[2]).arg(exitRecordList[3])
        .arg(exitRecordList[4]).arg(exitRecordList[5]).arg(exitRecordList[6]).arg(exitRecordList[7].toFloat());
        if(sql.exec(str))
        {
            //将房间状态设置为空闲中
           QSqlQuery setsql;
           setsql.exec(QString("update room set roomstatus='空闲中' where roomid=%1").arg(currentText));
            QMessageBox::information(nullptr,"提示信息",QString("房间号：%1\n客户：%2\n退房成功").arg(exitRecordList[0]).arg(exitRecordList[1]));
            //删除client表信息
            QSqlQuery deletesql;
            sql.exec(QString("delete from client where roomid=%1").arg(currentText));
            //重新显示退房记录sad
            exitRoomRecord("select * from exitrecord");
        }
        else
        {
            QMessageBox::information(nullptr,"提示信息",QString("退房失败"));
        }
    }
        setComboboxItem();
}

//续房按钮点击事件
void servicewidget::on_continue_pushButton_2_clicked()
{
    QString currentText=ui->continueroom_comboBox->currentText();
    QSqlQuery sql;
    QMessageBox::StandardButton result;
    result=QMessageBox::information(nullptr,"确认窗口",QString("确定（房间号：%1）续房？").arg(currentText),
                                                        QMessageBox::Ok,QMessageBox::Cancel);
    if(result==QMessageBox::Ok)
    {
        QSqlQuery sql;
        sql.exec(QString("select days from client where roomid=%1").arg(currentText));
        if(sql.next())
        {
            int currentDays=sql.value(0).toInt();
            currentDays+=1;
            QSqlQuery adddays;
            adddays.exec(QString("UPDATE client SET days=%1 WHERE roomid=%2").arg(currentDays).arg(currentText));
            QMessageBox::information(nullptr,"提示窗口","续房成功");
        }
    }
    setComboboxItem();
}

//取消预订按钮事件
void servicewidget::on_cancelReserve_pushButton_clicked()
{
    QString currentText=ui->canceledReserve_comboBox->currentText();
    QSqlQuery sql;
    QMessageBox::StandardButton result;
    result=QMessageBox::information(nullptr,"确认窗口",QString("确定（房间号：%1）取消预订？").arg(currentText),
                                                        QMessageBox::Ok,QMessageBox::Cancel);
    if(result==QMessageBox::Ok)
    {
        //删除预订信息
        QSqlQuery sql;
        sql.exec(QString("delete from reserve where roomid=%1").arg(currentText));
        //修改房间状态为空闲
        QSqlQuery changesql;
        bool ischanged=changesql.exec(QString("update room set roomstatus='空闲中' where roomid=%1").arg(currentText));
        if(sql.next()&&ischanged)
        {
            QMessageBox::information(nullptr,"提示窗口","取消成功");
        }
    }
    setCancelComboboxaItem();
}

//续房combobox控件值改变事件
void servicewidget::on_continueroom_comboBox_currentIndexChanged(const QString &arg1)
{
     QString clientsql=QString("SELECT roomid,clientname,clientdate,days FROM client where roomid=%1").arg(arg1);
    QString temp="";
    QString temp1="房间号：";
    QString temp2="客户姓名：";
    QString temp3="入住时间：";
    QString temp4="入住天数：";
    QStringList templist;
    templist<<temp1<<temp2<<temp3<<temp4;
    QSqlQuery sqlquery;
    sqlquery.exec(clientsql);
    while(sqlquery.next())
    {
        temp.append(templist[0]).append(sqlquery.value(0).toString()).append("\n");
        temp.append(templist[1]).append(sqlquery.value(1).toString()).append("\n");
        temp.append(templist[2]).append(sqlquery.value(2).toDateTime().toString("yyyy-MM-dd hh:mm:ss")).append("\n");
        temp.append(templist[3]).append(sqlquery.value(3).toString()).append("\n");
    }
    ui->textBrowser_3->setText(temp.replace("\\n","\n"));
}

//退房combobox控件值改变事件
void servicewidget::on_exitroom_comboBox_currentIndexChanged(const QString &arg1)
{
     exitRecordList.clear();
     //将client表和room表做个连接查询，保存结果集
     QString clientsql=QString("select room.roomid,client.clientname,client.clientid,client.clientphone,client.clientdate,client.exitdate,client.days "
                                                     "from room left join client on room.roomid=client.roomid "
                                                     "where room.roomid=%1").arg(arg1);
    QString temp="";
    QString temp1="房间号：";
    QString temp2="客户姓名：";
    QString temp3="入住时间：";
    QString temp4="入住天数：";
    QString temp5="应付款：";
    QStringList templist;
    templist<<temp1<<temp2<<temp3<<temp4<<temp5;
    QSqlQuery sqlquery;
    sqlquery.exec(clientsql);
    if(sqlquery.next())
    {
        for (int i=0;i<sqlquery.record().count();i++)
        {
            if(i==4)
            {
                exitRecordList<<sqlquery.value(i).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            }
            else if(i==5)
            {
                 exitRecordList<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            }
            else
            {
                exitRecordList<<sqlquery.value(i).toString();
            }
        }
        temp.append(templist[0]).append(sqlquery.value(0).toString()).append("\n");
        temp.append(templist[1]).append(sqlquery.value(1).toString()).append("\n");
        temp.append(templist[2]).append(sqlquery.value(4).toDateTime().toString("yyyy-MM-dd hh:mm:ss")).append("\n");
        temp.append(templist[3]).append(sqlquery.value(6).toString()).append("\n");
        QSqlQuery moneysql;
        moneysql.exec(QString("select roomprice from room where roomid =%1").arg(arg1));
        float money;
        if(moneysql.next())
        {
          money=moneysql.value(0).toFloat();
        }
        float days=sqlquery.value(6).toFloat();
        float count=days*money;
        temp.append(templist[4]).append(QString("%1").arg(count));
                qDebug()<<"money:"<<money;
        exitRecordList<<QString("%1").arg(count);
    }
    qDebug()<<exitRecordList;
    ui->textBrowser_2->setText(temp.replace("\\n","\n"));
}

//取消预订combobox控件值改变事件
void servicewidget::on_canceledReserve_comboBox_currentIndexChanged(const QString &arg1)
{
    QString reservesql=QString("select * from reserve where roomid=%1").arg(arg1);
    QString temp="";
    QString temp1="房间号：";
    QString temp2="客户姓名：";
    QString temp3="联系电话：";
    QString temp4="预订时间：";
    QStringList templist;
    templist<<temp1<<temp2<<temp3<<temp4;
    QSqlQuery sqlquery;
    sqlquery.exec(reservesql);
    while(sqlquery.next())
    {
        temp.append(templist[0]).append(sqlquery.value(0).toString()).append("\n");
        temp.append(templist[1]).append(sqlquery.value(1).toString()).append("\n");
        temp.append(templist[2]).append(sqlquery.value(2).toString()).append("\n");
        temp.append(templist[3]).append(sqlquery.value(3).toDateTime().toString("yyyy-MM-dd hh:mm:ss")).append("\n");
    }
    ui->textBrowser_4->setText(temp.replace("\\n","\n"));
}

//导入excel表格按钮事件
void servicewidget::on_commandLinkButton_clicked()
{
    //获取保存excel文件的路径；
   QString filepath=QFileDialog::getSaveFileName(this,tr("Save as..."),QString(""),tr("EXCEL files (*.xls);;HTML-Files (*.txt);;"));

    QSqlQuery SaveSql;
    SaveSql.exec("select * from exitrecord");
    //列表数据
    QString header="";
    QList<QString> list;
    QSqlRecord sqlRecord=SaveSql.record();
    //添加表头数据
    header.append("房间号").append("\t");
    header.append("客户姓名").append("\t");
    header.append("身份证号").append("\t");
    header.append("联系电话").append("\t");
    header.append("入住时间").append("\t");
    header.append("退房时间").append("\t");
    header.append("入住天数").append("\t");
    header.append("支付金额").append("\t");
    list.push_back(header);

    while(SaveSql.next())//添加列表项数据
    {
        QString str="";
        for (int j=0;j<sqlRecord.count();j++)
        {
            str.append(SaveSql.value(j).toString().append("\t"));
        }
        qDebug()<<str;
        list.push_back(str);
    }
    //设置成文本类，是用于文件的文本输入流
    QTextEdit textedit;
    for (int i=0;i<list.size();i++)
    {
        textedit.append(list.at(i));
    }
    //操作文件
    QFile file(filepath);
    if(file.open(QFile::WriteOnly|QIODevice::Text))
    {
        //一种是data数据流，一种是text文本流
        QTextStream ts(&file);
        ts.setCodec("GB2312");//windows基本GBK，其他平台utf-8
        ts<<textedit.document()->toPlainText();
        file.close();
        QMessageBox::information(nullptr,"信息提示","数据导入文件成功！！");
    }
    else
    {
        QMessageBox::information(nullptr,"信息提示","数据导入文件失败！！");
    }
}
