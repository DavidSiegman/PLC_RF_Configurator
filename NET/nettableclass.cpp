#include "nettableclass.h"

NetTableClass::NetTableClass(QTableView *NetTable,QObject *parent) : QObject(parent)
{
    this->NetTable       = NetTable;

    this->model          = new QStandardItemModel();

    this->NetTable       ->setModel(this->model);
    this->NetTable       ->resizeRowsToContents();
    this->NetTable       ->resizeColumnsToContents();
}

void NetTableClass::addNewItem(QString string)
{
    QStandardItem *item = new QStandardItem(string);
    model->setItem(0, 0, item);
}

void NetTableClass::delNewItem()
{

}
