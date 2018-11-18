#include "modempropertiesclass.h"

ModemPropertiesClass::ModemPropertiesClass()
{
    this->Modem_Properties_Data.RX_Timeout                                = 0;
    this->Modem_Properties_Data.TX_Timeout                                = 0;
    this->Modem_Properties_Data.LED_Logic                                 = 0;
    this->Modem_Properties_Data.Reset_Device_Timeout                      = 0;
}


uint       ModemPropertiesClass::getRX_Timeout()
{
    return Modem_Properties_Data.RX_Timeout;
}
void       ModemPropertiesClass::setRX_Timeout(uint new_value)
{
    Modem_Properties_Data.RX_Timeout = new_value;
}

uint       ModemPropertiesClass::getTX_Timeout()
{
    return Modem_Properties_Data.TX_Timeout;
}
void       ModemPropertiesClass::setTX_Timeout(uint new_value)
{
    Modem_Properties_Data.TX_Timeout = new_value;
}

uchar      ModemPropertiesClass::getLED_Logic()
{
    return Modem_Properties_Data.LED_Logic;
}
void       ModemPropertiesClass::setLED_Logic(uchar new_value)
{
    Modem_Properties_Data.LED_Logic = new_value;
}

uint       ModemPropertiesClass::getReset_Device_Timeout()
{
    return Modem_Properties_Data.Reset_Device_Timeout;
}
void       ModemPropertiesClass::setReset_Device_Timeout(uint new_value)
{
    Modem_Properties_Data.Reset_Device_Timeout = new_value;
}


