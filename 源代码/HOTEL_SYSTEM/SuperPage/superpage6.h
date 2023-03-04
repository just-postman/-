#ifndef SUPERPAGE6_H
#define SUPERPAGE6_H

#include <QWidget>

namespace Ui {
class superPage6;
}

class superPage6 : public QWidget
{
    Q_OBJECT

public:
    explicit superPage6(QWidget *parent = nullptr);
    ~superPage6();

private:
    Ui::superPage6 *ui;
};

#endif // SUPERPAGE6_H
