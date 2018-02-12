#include "plcclass.h"

PLCClass::PLCClass(Ui::MainWindow *ui,QObject *parent) : QObject(parent)
{
    this->ui = ui;

    PLC_Parameters = new PLC_Config_struct;
}

PLC_Config_struct*        PLCClass::aSI4432_PLC_Config_struct(void)
{
    return PLC_Parameters;
}

void           PLCClass::PLC_SET_LOWF  (unsigned int LOWF)
{
    this->PLC_Parameters->LOWF = LOWF;
    this->ui->PLC_LowF->setValue(LOWF);
}
unsigned int   PLCClass::PLC_GET_LOWF  (void)
{
    return this->PLC_Parameters->LOWF;
}
void           PLCClass::PLC_SET_HIGHF (unsigned int HIGHF)
{
    this->PLC_Parameters->HIGHF = HIGHF;
    this->ui->PLC_HighF->setValue(HIGHF);
}
unsigned int   PLCClass::PLC_SET_HIGHF (void)
{
    return this->PLC_Parameters->HIGHF;
}

