#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>

namespace Ui {
class registerPage;
}

class registerPage : public QWidget
{
    Q_OBJECT

public:
    explicit registerPage(QWidget *parent = nullptr);
    ~registerPage();

private slots:
    void on_clear_pushButton_clicked();

    void on_register_pushButton_clicked();

private:
    Ui::registerPage *ui;
};

#endif // REGISTERPAGE_H
