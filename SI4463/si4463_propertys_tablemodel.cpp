#include "si4463_propertys_tablemodel.h"

SI4463_PROPERTYS_TABLEMODEL::SI4463_PROPERTYS_TABLEMODEL()
{
    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Название свойства");
    horizontalHeader.append("Hex Значение");
    this->setHeaderData(0,Qt::Horizontal,horizontalHeader);
}
