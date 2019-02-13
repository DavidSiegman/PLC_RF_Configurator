#include "myformabstractclass.h"

myFormAbstractClass::myFormAbstractClass(QWidget *parent) : QWidget(parent){
    this->setWindowIcon(QIcon(":/images/icons/images/AppIcon.ico"));
}
void myFormAbstractClass::Set_In_Firmware_Information(FirmwareInformationClass *FirmwareInformation)
{
    In_Firmware_Information = FirmwareInformation;
}
FirmwareInformationClass* myFormAbstractClass::Get_In_Firmware_Information(void)
{
    return In_Firmware_Information;
}
void myFormAbstractClass::SetProgress(uint progress){

}
void myFormAbstractClass::Set_Geometry(QRect new_value){
    this->setGeometry(new_value);
}
void myFormAbstractClass::ForceCloseHandler(void){
    emit Stop_Send_Data();
    emit Get_Geometry(this->geometry());
    emit ForcedClosed();
    this->deleteLater();
}
void myFormAbstractClass::isStopped(void){

}
void myFormAbstractClass::isRF_Reset(void){

}
void myFormAbstractClass::Reset_ClickHandler(void){
    emit StartSendingProcess(SEND_RF_RESET, CONFIG_SEND_CONTROL);
}
void myFormAbstractClass::Back_ClickHandler(void){
    emit Stop_Send_Data();
    emit Get_Console(NULL);
}
void myFormAbstractClass::Next_ClickHandler(void){
    emit Stop_Send_Data();
    emit Get_Console(NULL);
    emit Next(this->geometry());
}
void myFormAbstractClass::Setting_ClickHandler(void){
    emit Settings(this);
}

void myFormAbstractClass::Stop_ClickHandler(void){
    emit Stop_Send_Data();
}
uchar myFormAbstractClass::Get_resizing_going(void){
    return this->resizing_going;
}

void  myFormAbstractClass::Set_resizing_going(uchar new_value){
    this->resizing_going = (new_value & 1);
}
void myFormAbstractClass::Set_ConnectionType(uchar new_value){
    this->ConnectionType = new_value;
}
uchar myFormAbstractClass::Get_ConnectionType(void){
    return this->ConnectionType;
}
