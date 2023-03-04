#ifndef RESETPASSWORD_H
#define RESETPASSWORD_H

#include <QWidget>
#include<QMessageBox>
#include<QSqlQuery>
namespace Ui {
class resetPassword;
}

class resetPassword : public QWidget
{
    Q_OBJECT

public:
    explicit resetPassword(QWidget *parent = nullptr,QString workid="");
    ~resetPassword();

private slots:
    void on_pushButton_clicked();

private:
    Ui::resetPassword *ui;
    QString workid;
};

#endif // RESETPASSWORD_H
