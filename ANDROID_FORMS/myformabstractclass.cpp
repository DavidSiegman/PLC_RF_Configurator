#include "myformabstractclass.h"

myFormAbstractClass::myFormAbstractClass(QWidget *parent) : QWidget(parent){

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
    emit Send_RF_Reset();
}
void myFormAbstractClass::Back_ClickHandler(void){
    emit Get_Console(NULL);
    emit Cancel(this->geometry());
}
void myFormAbstractClass::Next_ClickHandler(void){
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
