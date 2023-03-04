#ifndef REGISTERUSER_H
#define REGISTERUSER_H

#include <QWidget>

namespace Ui {
class registeruser;
}

class registeruser : public QWidget
{
    Q_OBJECT

public:
    explicit registeruser(QWidget *parent = nullptr);
    ~registeruser();

private slots:
    void on_clear_pushButton_clicked();

    void on_register_pushButton_clicked();

private:
    Ui::registeruser *ui;
};

#endif // REGISTERUSER_H
