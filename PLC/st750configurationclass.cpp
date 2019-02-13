#include "st750configurationclass.h"

ST750ConfigurationClass::ST750ConfigurationClass(){
    setST750_LOWF(0);
    setST750_HIGHF(0);
}

void              ST750ConfigurationClass::setPLC_Config_struct(PLC_Config_struct new_data){
    ST750_Configuration_Data = new_data;
}
PLC_Config_struct  ST750ConfigurationClass::getPLC_Config_struct(void){
    return ST750_Configuration_Data;
}

void            ST750ConfigurationClass::setST750_LOWF  (unsigned int LOWF){
    ST750_Configuration_Data.LOWF = LOWF;
}
unsigned int   ST750ConfigurationClass::getST750_LOWF  (){
    return ST750_Configuration_Data.LOWF;
}
void            ST750ConfigurationClass::setST750_HIGHF  (unsigned int HIGHF){
    ST750_Configuration_Data.HIGHF = HIGHF;
}
unsigned int   ST750ConfigurationClass::getST750_HIGHF  (){
    return ST750_Configuration_Data.HIGHF;
}

