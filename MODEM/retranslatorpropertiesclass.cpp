#include "retranslatorpropertiesclass.h"

RetranslatorPropertiesClass::RetranslatorPropertiesClass()
{
    Clear_Data();
}

void RetranslatorPropertiesClass::Clear_Data()
{
    this->Retranslator_Properties_Data.Retranslator_Mode                  = 0;
    this->Retranslator_Properties_Data.Retranslator_Level                 = 0;
    *((unsigned int*)&(this->Retranslator_Properties_Data.Retranslator_Mask)) = this->Retranslator_Properties_Data.Retranslator_Level;
    this->Retranslator_Properties_Data.Retranslator_Timeout               = 0;
    this->Retranslator_Properties_Data.Retranslation_Table.clear();
    this->Retranslator_Properties_Data.Retranslation_Table_Current_Index  = 0;
}

uchar      RetranslatorPropertiesClass::getRetranslator_Mode()
{
    return Retranslator_Properties_Data.Retranslator_Mode;
}
void       RetranslatorPropertiesClass::setRetranslator_Mode(uchar new_value)
{
    Retranslator_Properties_Data.Retranslator_Mode = new_value;
}

uint       RetranslatorPropertiesClass::getRetranslator_Level()
{
    return Retranslator_Properties_Data.Retranslator_Level;
}
void       RetranslatorPropertiesClass::setRetranslator_Level(uint new_value)
{
    Retranslator_Properties_Data.Retranslator_Level = new_value;
}

uint       RetranslatorPropertiesClass::getRetranslator_Timeout()
{
    return Retranslator_Properties_Data.Retranslator_Timeout;
}
void       RetranslatorPropertiesClass::setRetranslator_Timeout(uint new_value)
{
    Retranslator_Properties_Data.Retranslator_Timeout = new_value;
}

QList<QString>  RetranslatorPropertiesClass::getRetranslator_Table()
{
    return Retranslator_Properties_Data.Retranslation_Table;
}
void            RetranslatorPropertiesClass::setRetranslator_Table(QList<QString> new_value)
{
    Retranslator_Properties_Data.Retranslation_Table = new_value;
}

void       RetranslatorPropertiesClass::addNewItemToRetranslation_Table(QString string)
{
    //this->current_index = this->model->rowCount();
    //QStandardItem *item = new QStandardItem(string);
    //this->model->setItem(this->current_index, 0, item);
    if (Retranslator_Properties_Data.Retranslation_Table_Current_Index <= 100)
    {
        Retranslator_Properties_Data.Retranslation_Table.append(string);
        Retranslator_Properties_Data.Retranslation_Table_Current_Index += 1;
    }
}
void       RetranslatorPropertiesClass::delCurrentItemFromRetranslation_Table()
{
    if (Retranslator_Properties_Data.Retranslation_Table_Current_Index <= 100)
    {
        Retranslator_Properties_Data.Retranslation_Table_Current_Index -= 1;
    }
    else
    {
        Retranslator_Properties_Data.Retranslation_Table_Current_Index = 0;
    }
    Retranslator_Properties_Data.Retranslation_Table.removeAt(Retranslator_Properties_Data.Retranslation_Table_Current_Index);
    //this->model->removeRow(this->current_index);
    //if ((this->current_index == 0)&&(this->model->rowCount() == 0))
    //{
    //    this->model->removeColumn(this->current_index);
    //}
}
void       RetranslatorPropertiesClass::clearRetranslation_Table()
{
    Retranslator_Properties_Data.Retranslation_Table_Current_Index = 0;
    Retranslator_Properties_Data.Retranslation_Table.clear();
    //this->model->clear();
}
uchar      RetranslatorPropertiesClass::getRetranslator_Table_Current_Index()
{
    return Retranslator_Properties_Data.Retranslation_Table_Current_Index;
}
void       RetranslatorPropertiesClass::setRetranslator_Table_Current_Index(uchar new_value)
{
    Retranslator_Properties_Data.Retranslation_Table_Current_Index = new_value;
}
