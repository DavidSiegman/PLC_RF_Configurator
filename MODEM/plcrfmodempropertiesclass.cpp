#include "PlcRfModemPropertiesClass.h"

PlcRfModemPropertiesClass::PlcRfModemPropertiesClass(){
    Clear_Data();
}
void            PlcRfModemPropertiesClass::Clear_Data(){
    this->PLC_RF433_Interfaces_Control.Word         = 0;
    this->PLC_RF433_DEBUG_Control.Word              = 0;
}

Interfaces_Control_Type PlcRfModemPropertiesClass::getPLC_RF433_Interfaces_Control(void){
    return this->PLC_RF433_Interfaces_Control;
}
void                    PlcRfModemPropertiesClass::setPLC_RF433_Interfaces_Control(Interfaces_Control_Type new_value){
    this->PLC_RF433_Interfaces_Control = new_value;
}
Debug_Control_Type      PlcRfModemPropertiesClass::getPLC_RF433_Debug_Control(void){
    return this->PLC_RF433_DEBUG_Control;
}
void                    PlcRfModemPropertiesClass::setPLC_RF433_Debug_Control(Debug_Control_Type new_value){
    this->PLC_RF433_DEBUG_Control = new_value;
}
unsigned char  PlcRfModemPropertiesClass::getModem_Mode(void){
    return this->PLC_RF433_Interfaces_Control.Field.Modem_Mode;
}
void           PlcRfModemPropertiesClass::setModem_Mode(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.Modem_Mode = (new_value & 3);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.PLC_EN;
}
void           PlcRfModemPropertiesClass::setPLC_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.PLC_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRF_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.RF_EN;
}
void           PlcRfModemPropertiesClass::setRF_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RF_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_EN;
}
void           PlcRfModemPropertiesClass::setRS_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_TO_PLC_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.PLC_TO_PLC_RET_EN;
}
void           PlcRfModemPropertiesClass::setPLC_TO_PLC_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.PLC_TO_PLC_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_TO_RF_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.PLC_TO_RF_RET_EN;
}
void           PlcRfModemPropertiesClass::setPLC_TO_RF_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.PLC_TO_RF_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRF_TO_RF_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.RF_TO_RF_RET_EN;
}
void           PlcRfModemPropertiesClass::setRF_TO_RF_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RF_TO_RF_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRF_TO_PLC_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.RF_TO_PLC_RET_EN;
}
void           PlcRfModemPropertiesClass::setRF_TO_PLC_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RF_TO_PLC_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_TO_RF_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_TO_RF_RET_EN;
}
void           PlcRfModemPropertiesClass::setRS_TO_RF_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_TO_RF_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRF_TO_RS_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.RF_TO_RS_RET_EN;
}
void           PlcRfModemPropertiesClass::setRF_TO_RS_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RF_TO_RS_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_TO_PLC_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_TO_PLC_RET_EN;
}
void           PlcRfModemPropertiesClass::setRS_TO_PLC_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_TO_PLC_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_TO_RS_RET_EN(void){
    return this->PLC_RF433_Interfaces_Control.Field.PLC_TO_RS_RET_EN;
}
void           PlcRfModemPropertiesClass::setPLC_TO_RS_RET_EN(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.PLC_TO_RS_RET_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_USE_AS_DEBUG_OUTPUT(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_USE_AS_DEBUG_OUTPUT;
}
void           PlcRfModemPropertiesClass::setRS_USE_AS_DEBUG_OUTPUT(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_USE_AS_DEBUG_OUTPUT = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_TO_RF_UP_LINK(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_TO_RF_UP_LINK;
}
void           PlcRfModemPropertiesClass::setRS_TO_RF_UP_LINK(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_TO_RF_UP_LINK = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_TO_PLC_UP_LINK(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_TO_PLC_UP_LINK;
}
void           PlcRfModemPropertiesClass::setRS_TO_PLC_UP_LINK(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_TO_PLC_UP_LINK = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getMODBUS_CRC_CHECK_DISABLE(void){
    return this->PLC_RF433_Interfaces_Control.Field.MODBUS_CRC_CHECK_DISABLE;
}
void           PlcRfModemPropertiesClass::setMODBUS_CRC_CHECK_DISABLE(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.MODBUS_CRC_CHECK_DISABLE = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_BAUDRATE(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_BAUDRATE;
}
void           PlcRfModemPropertiesClass::setRS_BAUDRATE(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_BAUDRATE = (new_value & 0xF);
}

unsigned char  PlcRfModemPropertiesClass::getEEPROM_INIT_OK(void){
    return this->PLC_RF433_Interfaces_Control.Field.EEPROM_INIT_OK;
}
void           PlcRfModemPropertiesClass::setEEPROM_INIT_OK(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.EEPROM_INIT_OK = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_INIT_OK(void){
    return this->PLC_RF433_Interfaces_Control.Field.PLC_INIT_OK;
}
void           PlcRfModemPropertiesClass::setPLC_INIT_OK(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.PLC_INIT_OK = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRF_INIT_OK(void){
    return this->PLC_RF433_Interfaces_Control.Field.RF_INIT_OK;
}
void           PlcRfModemPropertiesClass::setRF_INIT_OK(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RF_INIT_OK = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_INIT_OK(void){
    return this->PLC_RF433_Interfaces_Control.Field.RS_INIT_OK;
}
void           PlcRfModemPropertiesClass::setRS_INIT_OK(unsigned char new_value){
    this->PLC_RF433_Interfaces_Control.Field.RS_INIT_OK = (new_value & 1);
}

unsigned char  PlcRfModemPropertiesClass::getDEBUG_GLOBAL_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.DEBUG_GLOBAL_EN;
}
void           PlcRfModemPropertiesClass::setDEBUG_GLOBAL_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.DEBUG_GLOBAL_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_INIT_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.PLC_INIT_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setPLC_INIT_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.PLC_INIT_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_UART_RX_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.PLC_UART_RX_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setPLC_UART_RX_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.PLC_UART_RX_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getPLC_RX_TX_DATA_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.PLC_RX_TX_DATA_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setPLC_RX_TX_DATA_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.PLC_RX_TX_DATA_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getSPI_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.SPI_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setSPI_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.SPI_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getSI4463_INIT_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.SI4463_INIT_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setSI4463_INIT_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.SI4463_INIT_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getSI4463_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.SI4463_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setSI4463_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.SI4463_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getHOST_UART_RX_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.HOST_UART_RX_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setHOST_UART_RX_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.HOST_UART_RX_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getFLASH_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.FLASH_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setFLASH_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.FLASH_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getFLASH_FULL_DATA_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.FLASH_FULL_DATA_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setFLASH_FULL_DATA_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.FLASH_FULL_DATA_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getINTERFACES_CONTROL_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.INTERFACES_CONTROL_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setINTERFACES_CONTROL_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.INTERFACES_CONTROL_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getUART_TO_INTERFACES_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.UART_TO_INTERFACES_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setUART_TO_INTERFACES_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.UART_TO_INTERFACES_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getINTERFACES_TO_UART_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.INTERFACES_TO_UART_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setINTERFACES_TO_UART_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.INTERFACES_TO_UART_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRETRANSLATION_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.RETRANSLATION_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setRETRANSLATION_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.RETRANSLATION_DEBUG_EN = (new_value & 1);
}
unsigned char  PlcRfModemPropertiesClass::getRS_DEBUG_EN(void){
    return this->PLC_RF433_DEBUG_Control.Field.RS_DEBUG_EN;
}
void           PlcRfModemPropertiesClass::setRS_DEBUG_EN(unsigned char new_value){
    this->PLC_RF433_DEBUG_Control.Field.RS_DEBUG_EN = (new_value & 1);
}
RealTime   PlcRfModemPropertiesClass::getLastAOPENTime(){
    return this->LastAOPENTime;
}
void       PlcRfModemPropertiesClass::setLastAOPENTime(RealTime new_value){
    this->LastAOPENTime = new_value;
}
