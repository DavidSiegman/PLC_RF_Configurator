#include "modemclass.h"

MODEMClass::MODEMClass(Ui::MainWindow *ui, QObject *parent) : QObject(parent)
{

}

MODEMClass::MODEMClass(QObject *parent)
{
    In_Firmware_Information     = new FirmwareInformationClass();

    In_Retranslator_Properties  = new RetranslatorPropertiesClass();
    Out_Retranslator_Properties = new RetranslatorPropertiesClass();

    In_Sniffer_Properties       = new SnifferPropertiesClass();
    Out_Sniffer_Properties      = new SnifferPropertiesClass();

    In_Modem_Properties         = new ModemPropertiesClass();
    Out_Modem_Properties        = new ModemPropertiesClass();
}
FirmwareInformationClass* MODEMClass::getIn_Firmware_Information(void){
    return this->In_Firmware_Information;
}
void                      MODEMClass::ChangedIn_Firmware_Information(void){
    emit sIn_Firmware_Information(this->In_Firmware_Information);
}
RetranslatorPropertiesClass*  MODEMClass::getIn_Retranslator_Properties(void){
    return this->In_Retranslator_Properties;
}
void                          MODEMClass::ChangedIn_Retranslator_Properties(void){
    emit sIn_Retranslator_Properties(this->In_Retranslator_Properties);
}
RetranslatorPropertiesClass*  MODEMClass::getOut_Retranslator_Properties(void){
    return this->Out_Retranslator_Properties;
}
void                          MODEMClass::ChangedOut_Retranslator_Properties(void){
    emit sOut_Retranslator_Properties(this->Out_Retranslator_Properties);
}
SnifferPropertiesClass*       MODEMClass::getIn_Sniffer_Properties(void){
    return this->In_Sniffer_Properties;
}
void                          MODEMClass::ChangedIn_Sniffer_Properties(void){
    emit sIn_Sniffer_Properties(this->In_Sniffer_Properties);
}
SnifferPropertiesClass*       MODEMClass::getOut_Sniffer_Properties(void){
    return this->Out_Sniffer_Properties;
}
void                          MODEMClass::ChangedOut_Sniffer_Properties(void){
    emit sOut_Sniffer_Properties(this->Out_Sniffer_Properties);
}
ModemPropertiesClass*         MODEMClass::getIn_Modem_Properties(void){
    return this->In_Modem_Properties;
}
void                          MODEMClass::ChangedIn_Modem_Properties(void){
    emit sIn_Modem_Properties(this->In_Modem_Properties);
}
ModemPropertiesClass*         MODEMClass::getOut_Modem_Properties(void){
    return this->Out_Modem_Properties;
}
void                          MODEMClass::ChangedOut_Modem_Properties(void){
    emit sOut_Modem_Properties(this->Out_Modem_Properties);
}
void                          MODEMClass::ClearAllData(){
    In_Firmware_Information->Clear_Data();

    In_Retranslator_Properties->Clear_Data();
    Out_Retranslator_Properties->Clear_Data();

    In_Sniffer_Properties->Clear_Data();
    Out_Sniffer_Properties->Clear_Data();

    In_Modem_Properties->Clear_Data();
    Out_Modem_Properties->Clear_Data();
}


