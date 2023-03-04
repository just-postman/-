#ifndef CLIENTPAGE3_H
#define CLIENTPAGE3_H

#include <QWidget>

namespace Ui {
class clientPage3;
}

class clientPage3 : public QWidget
{
    Q_OBJECT

public:
    explicit clientPage3(QWidget *parent = nullptr);
    ~clientPage3();

private:
    Ui::clientPage3 *ui;
};

#endif // CLIENTPAGE3_H
