#include "snifferpropertiesclass.h"

SnifferPropertiesClass::SnifferPropertiesClass()
{
    this->Sniffer_Properties_Data.Sniffer_Mode                                  = 0;
    this->Sniffer_Properties_Data.UpLink_Value                                  = 0;
    this->Sniffer_Properties_Data.CRC_Check_Disable                             = 0;
    this->Sniffer_Properties_Data.Broadcasting                                  = 0;
    this->Sniffer_Properties_Data.Sniffer_Level_Destination                     = 0;
    *((unsigned int*)&(this->Sniffer_Properties_Data.Sniffer_Mask_Destination)) = this->Sniffer_Properties_Data.Sniffer_Level_Destination;
    this->Sniffer_Properties_Data.Direct_Transfer                               = 0;
}


uchar      SnifferPropertiesClass::getSniffer_Mode()
{
    return Sniffer_Properties_Data.Sniffer_Mode;
}
void       SnifferPropertiesClass::setSniffer_Mode(uchar new_value)
{
    Sniffer_Properties_Data.Sniffer_Mode = new_value;
}

uchar      SnifferPropertiesClass::getUpLink_Value()
{
    return Sniffer_Properties_Data.UpLink_Value;
}
void       SnifferPropertiesClass::setUpLink_Value(uchar new_value)
{
    Sniffer_Properties_Data.UpLink_Value = new_value;
}

uchar      SnifferPropertiesClass::getCRC_Check_Disable()
{
    return Sniffer_Properties_Data.CRC_Check_Disable;
}
void       SnifferPropertiesClass::setCRC_Check_Disable(uchar new_value)
{
    Sniffer_Properties_Data.CRC_Check_Disable = new_value;
}

uchar      SnifferPropertiesClass::getBroadcasting()
{
    return Sniffer_Properties_Data.Broadcasting;
}
void       SnifferPropertiesClass::setBroadcasting(uchar new_value)
{
    Sniffer_Properties_Data.Broadcasting = new_value;
}

uint       SnifferPropertiesClass::getSniffer_Level_Destination()
{
    return Sniffer_Properties_Data.Sniffer_Level_Destination;
}
void       SnifferPropertiesClass::setSniffer_Level_Destination(uint new_value)
{
    Sniffer_Properties_Data.Sniffer_Level_Destination = new_value;
}

uchar      SnifferPropertiesClass::getDirect_Transfer()
{
    return Sniffer_Properties_Data.Direct_Transfer;
}
void       SnifferPropertiesClass::setDirect_Transfer(uchar new_value)
{
    Sniffer_Properties_Data.Direct_Transfer = new_value;
}

