#ifndef SI4463_PROPERTYS_TABLEMODEL_H
#define SI4463_PROPERTYS_TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <SI4463/si4463_propertys_type.h>
#include "SI4463/si4463class.h"

class SI4463_PROPERTYS_TABLEMODEL : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SI4463_PROPERTYS_TABLEMODEL();

private:
    TableFilling();

};

#endif // SI4463_PROPERTYS_TABLEMODEL_H
