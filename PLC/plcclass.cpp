#include "plcclass.h"

PLCClass::PLCClass(Ui::MainWindow *ui,QObject *parent) : QObject(parent){
    //this->ui = ui;
    //PLC_Parameters = new PLC_Config_struct;
}

PLCClass::PLCClass(QObject *parent) : QObject(parent){
    In_ST750_Parameters  = new ST750ConfigurationClass();
    Out_ST750_Parameters = new ST750ConfigurationClass();
}

ST750ConfigurationClass*  PLCClass::getIn_ST750_PLC_Config(void){
    return In_ST750_Parameters;
}
void                       PLCClass::ChangedIn_ST750_PLC_Config(void){
    emit   sIn_ST750_Parameters (In_ST750_Parameters);
}
ST750ConfigurationClass*  PLCClass::getOut_ST750_PLC_Config(void){
    return Out_ST750_Parameters;
}
void                       PLCClass::ChangedOut_ST750_PLC_Config(void){
    emit   sOut_ST750_Parameters (Out_ST750_Parameters);
}
