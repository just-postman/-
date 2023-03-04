#ifndef SERVICEPAGE1_H
#define SERVICEPAGE1_H

#include <QWidget>
#include<QDebug>
#include<QSqlQuery>
#include<QFile>
#include<QDialog>
#include<QFileDialog>
#include<QMessageBox>
#include<QRegExp>
#include<QRegExpValidator>
#include<QDateTime>
namespace Ui {
class ServicePage1;
}

class ServicePage1 : public QWidget
{
    Q_OBJECT

public:
    explicit ServicePage1(QWidget *parent = nullptr,QString roomid="");
    ~ServicePage1();

void FullInformation(void);
void closeEvent(QCloseEvent *event) override;
public :signals:
    void pageclosed();
private slots:
void on_pushButton_clicked();

void on_pushButton_2_clicked();

private:
    Ui::ServicePage1 *ui;
    QString roomid;
};

#endif // SERVICEPAGE1_H
