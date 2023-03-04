#ifndef SUPERPAGE3EDIT_H
#define SUPERPAGE3EDIT_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include<QDateTime>
namespace Ui {
class superPage3Edit;
}

class superPage3Edit : public QWidget
{
    Q_OBJECT

public:
    explicit superPage3Edit(QWidget *parent = nullptr,QString name="");
    ~superPage3Edit();
    void fillinfo();
private slots:
    void on_clear_pushButton_clicked();

    void on_update_pushButton_clicked();

private:
    Ui::superPage3Edit *ui;
    QString name;
};

#endif // SUPERPAGE3EDIT_H
