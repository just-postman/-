#ifndef SUPERPAGE2EDIT_H
#define SUPERPAGE2EDIT_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDateTime>
namespace Ui {
class superPage2Edit;
}

class superPage2Edit : public QWidget
{
    Q_OBJECT

public:
    explicit superPage2Edit(QWidget *parent = nullptr,QString workid="");
    ~superPage2Edit();
    void fullinfo();//填充编辑框
private slots:
    void on_update_pushButton_clicked();

    void on_clear_pushButton_clicked();

private:
    Ui::superPage2Edit *ui;
    QString workid;
};

#endif // SUPERPAGE2EDIT_H
