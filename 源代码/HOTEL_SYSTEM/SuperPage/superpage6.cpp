#include "superpage6.h"
#include "ui_superpage6.h"

superPage6::superPage6(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::superPage6)
{
    ui->setupUi(this);
}

superPage6::~superPage6()
{
    delete ui;
}
