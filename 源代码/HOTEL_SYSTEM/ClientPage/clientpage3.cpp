#include "clientpage3.h"
#include "ui_clientpage3.h"

clientPage3::clientPage3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientPage3)
{
    ui->setupUi(this);
}

clientPage3::~clientPage3()
{
    delete ui;
}
