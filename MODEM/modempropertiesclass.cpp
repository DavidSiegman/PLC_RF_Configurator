#include "modempropertiesclass.h"

ModemPropertiesClass::ModemPropertiesClass(){
    Clear_Data();
}

void ModemPropertiesClass::Clear_Data(){
    this->Modem_Properties_Data.RF_RX_Timeout                             = 0;
    this->Modem_Properties_Data.RF_TX_Timeout                             = 0;
    this->Modem_Properties_Data.PLC_RX_Timeout                            = 0;
    this->Modem_Properties_Data.PLC_TX_Timeout                            = 0;
    this->Modem_Properties_Data.LED_Logic                                 = 0;
    this->Modem_Properties_Data.Reset_Device_Timeout                      = 0;
}

uint       ModemPropertiesClass::getRF_RX_Timeout(){
    return Modem_Properties_Data.RF_RX_Timeout;
}
void       ModemPropertiesClass::setRF_RX_Timeout(uint new_value){
    Modem_Properties_Data.RF_RX_Timeout = new_value;
}
uint       ModemPropertiesClass::getRF_TX_Timeout(){
    return Modem_Properties_Data.RF_TX_Timeout;
}
void       ModemPropertiesClass::setRF_TX_Timeout(uint new_value){
    Modem_Properties_Data.RF_TX_Timeout = new_value;
}
uint       ModemPropertiesClass::getPLC_RX_Timeout(){
    return Modem_Properties_Data.PLC_RX_Timeout;
}
void       ModemPropertiesClass::setPLC_RX_Timeout(uint new_value){
    Modem_Properties_Data.PLC_RX_Timeout = new_value;
}
uint       ModemPropertiesClass::getPLC_TX_Timeout(){
    return Modem_Properties_Data.PLC_TX_Timeout;
}
void       ModemPropertiesClass::setPLC_TX_Timeout(uint new_value){
    Modem_Properties_Data.PLC_TX_Timeout = new_value;
}
uchar      ModemPropertiesClass::getLED_Logic(){
    return Modem_Properties_Data.LED_Logic;
}
void       ModemPropertiesClass::setLED_Logic(uchar new_value){
    Modem_Properties_Data.LED_Logic = new_value;
}
uint       ModemPropertiesClass::getReset_Device_Timeout(){
    return Modem_Properties_Data.Reset_Device_Timeout;
}
void       ModemPropertiesClass::setReset_Device_Timeout(uint new_value){
    Modem_Properties_Data.Reset_Device_Timeout = new_value;
}
RealTime   ModemPropertiesClass::getLastAOPENTime(){
    return Modem_Properties_Data.LastAOPENTime;
}
void       ModemPropertiesClass::setLastAOPENTime(RealTime new_value){
    Modem_Properties_Data.LastAOPENTime = new_value;
}

