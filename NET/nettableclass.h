#ifndef NETTABLECLASS_H
#define NETTABLECLASS_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>

class NetTableClass : public QObject
{
    Q_OBJECT
public:
    explicit NetTableClass(QTableView *NetTable,QObject *parent = nullptr);
private:
    QTableView *NetTable;
    QStandardItemModel *model;
signals:

public slots:
    void addNewItem(QString string);
    void delNewItem();
};

#endif // NETTABLECLASS_H
