#ifndef SUPERPAGE5DETAIL_H
#define SUPERPAGE5DETAIL_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDateTime>
namespace Ui {
class superPage5Detail;
}

class superPage5Detail : public QWidget
{
    Q_OBJECT

public:
    explicit superPage5Detail(QWidget *parent = nullptr,QString id=0);
    ~superPage5Detail();
    void showinfo();
private:
    Ui::superPage5Detail *ui;
    QString id;
};

#endif // SUPERPAGE5DETAIL_H
