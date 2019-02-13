#include "si4432class.h"
#include <math.h>

SI4432Class::SI4432Class(Ui::MainWindow *ui,QObject *parent) : QObject(parent)
{
    //this->ui = ui;
}
SI4432Class::SI4432Class(QObject *parent) : QObject(parent){
    In_SI4432_Parameters  = new SI4432ConfigurationClass();
    Out_SI4432_Parameters = new SI4432ConfigurationClass();
}

SI4432ConfigurationClass*  SI4432Class::getIn_SI4432_RF_Config(void){
    return In_SI4432_Parameters;
}
void                       SI4432Class::ChangedIn_SI4432_RF_Config(void){
    emit   sIn_SI4432_Parameters (In_SI4432_Parameters);
}
SI4432ConfigurationClass*  SI4432Class::getOut_SI4432_RF_Config(void){
    return Out_SI4432_Parameters;
}
void                       SI4432Class::ChangedOut_SI4432_RF_Config(void){
    emit   sOut_SI4432_Parameters (Out_SI4432_Parameters);
}
RF_RegRead_struct          SI4432Class::getSI4432_RF_RegRead(void){
    return SI4432_RegRead;
}
void                       SI4432Class::setSI4432_RF_RegRead(RF_RegRead_struct new_data){
    SI4432_RegRead = new_data;
}

