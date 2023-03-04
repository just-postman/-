#include "mysqlquerymodel.h"
#include "ui_mysqlquerymodel.h"

mysqlQueryModel::mysqlQueryModel(QWidget *parent) :
    QSqlQueryModel(parent),
    ui(new Ui::mysqlQueryModel)
{

}

QVariant mysqlQueryModel::data(const QModelIndex &item, int role) const
{
      if(role==Qt::TextAlignmentRole)//默认代理对齐方式
        {
            QVariant value=(Qt::AlignCenter);
            return value;
        }
        else
            return QSqlQueryModel::data(item,role);

//      switch (role) {

//      }
}

mysqlQueryModel::~mysqlQueryModel()
{
    delete ui;
}
