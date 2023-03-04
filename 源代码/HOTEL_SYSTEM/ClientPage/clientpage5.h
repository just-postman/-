#ifndef CLIENTPAGE5_H
#define CLIENTPAGE5_H

#include <QWidget>
#include<QDebug>
#include<QButtonGroup>
#include<QMessageBox>
#include<QSqlQuery>
#include<QRegExp>
#include<QRegExpValidator>
#include<QDateTime>
namespace Ui {
class clientPage5;
}

class clientPage5 : public QWidget
{
    Q_OBJECT

public:
    explicit clientPage5(QWidget *parent = nullptr);
    ~clientPage5();
   void setCombobox();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::clientPage5 *ui;
};

#endif // CLIENTPAGE5_H
