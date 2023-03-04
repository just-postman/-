#ifndef SUPERPAGE1EDIT_H
#define SUPERPAGE1EDIT_H

#include <QWidget>
#include<QDebug>
#include<QSqlQuery>
#include<QFile>
#include<QDialog>
#include<QFileDialog>
#include<QMessageBox>
namespace Ui {
class superPage1Edit;
}

class superPage1Edit : public QWidget
{
    Q_OBJECT

public:
    explicit superPage1Edit(QWidget *parent = nullptr,QString roomid="");
    ~superPage1Edit();
    void closeEvent(QCloseEvent *event) override;
public: signals:
    void pageclosed();
private slots:

    void on_submit_pushButton_clicked();

    void on_file_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

private:
    Ui::superPage1Edit *ui;
    QString roomid;
    QString filepath;
    QString roomtype;
    QString roomstatus;
};

#endif // SUPERPAGE1EDIT_H
