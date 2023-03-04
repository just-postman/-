#include "superpage1edit.h"
#include "ui_superpage1edit.h"

superPage1Edit::superPage1Edit(QWidget *parent,QString roomid) :
    QWidget(parent),
    ui(new Ui::superPage1Edit),roomid(roomid)
{
    ui->setupUi(this);
    this->setWindowTitle("房间编辑");
    ui->roomidLine->setText(roomid);
    roomtype=ui->comboBox->currentText();
    roomstatus=ui->comboBox_2->currentText();
}

superPage1Edit::~superPage1Edit()
{
    delete ui;
}

void superPage1Edit::closeEvent(QCloseEvent *event)
{
    emit pageclosed();
}

void superPage1Edit::on_submit_pushButton_clicked()
{
    if(ui->roomidLine->text()==""||ui->roomPriceline->text()=="")
    {
        QMessageBox::critical(this,"提示","所填写内容不能为空");
        return ;
    }
    QString roomprice=ui->roomPriceline->text();
    QSqlQuery query;
    QString execstring=QString("update room set roomprice='%1',roomstatus='%2',roomtype='%3',roompicture=load_file('%4') where roomid='%5'")
    .arg(roomprice).arg(roomstatus).arg(roomtype).arg(filepath).arg(roomid);
    if(filepath=="")
    {
        execstring=QString("update room set roomprice='%1',roomstatus='%2',roomtype='%3' where roomid='%4'")
        .arg(roomprice).arg(roomstatus).arg(roomtype).arg(roomid);
    }
    qDebug()<<execstring;
    if(!query.exec(execstring))
    {
        QMessageBox::critical(this,"提示","数据更新失败/n该房间号已存在(请选择小于1MB的图片上传!)");
    }
    else {
        QMessageBox::information(this,"提示","数据更新成功");
        this->close();
    }
}

void superPage1Edit::on_file_pushButton_clicked()
{
    filepath=QFileDialog::getOpenFileName(this,"选择照片位置","/","照片(*.png *.jpg)");
    ui->textBrowser->setText(filepath);
    filepath.replace("/","//");
}

void superPage1Edit::on_comboBox_currentIndexChanged(const QString &arg1)
{
    roomtype=arg1;
}

void superPage1Edit::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    roomstatus=arg1;
}
