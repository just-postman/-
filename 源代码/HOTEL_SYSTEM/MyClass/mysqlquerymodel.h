#ifndef MYSQLQUERYMODEL_H
#define MYSQLQUERYMODEL_H

#include <QWidget>
#include<QSqlQueryModel>
namespace Ui {
class mysqlQueryModel;
}

class mysqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit mysqlQueryModel(QWidget *parent = nullptr);
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
    ~mysqlQueryModel();
private:
    Ui::mysqlQueryModel *ui;
};

#endif // MYSQLQUERYMODEL_H
