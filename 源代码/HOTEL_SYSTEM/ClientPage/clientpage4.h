#ifndef CLIENTPAGE4_H
#define CLIENTPAGE4_H

#include <QWidget>
#include<QDebug>
#include<QButtonGroup>
#include<QMessageBox>

#include<QSqlQuery>
#include<QDateTime>
namespace Ui {
class clientPage4;
}

class clientPage4 : public QWidget
{
    Q_OBJECT

public:
    explicit clientPage4(QWidget *parent = nullptr);
    ~clientPage4();
    static bool is_submit;
QString my_message;
QButtonGroup *b1;
QButtonGroup *b2;
QButtonGroup *b3;
QButtonGroup *b4;
QButtonGroup *b5;
void investigate();//调查报告
void setCombobox();//设置下拉列表
private slots:
void on_pushButton_clicked();

private:
    Ui::clientPage4 *ui;
};

#endif // CLIENTPAGE4_H
