#ifndef MODEMPROPERTIESCLASS_H
#define MODEMPROPERTIESCLASS_H

#include <Qt>

typedef struct Modem_Properties_Type
{

    uint                  RX_Timeout;
    uint                  TX_Timeout;
    uchar                 LED_Logic;
    uint                  Reset_Device_Timeout;

}Modem_Properties;

class ModemPropertiesClass
{
public:
    ModemPropertiesClass();

    uint            getRX_Timeout();
    void            setRX_Timeout(uint);

    uint            getTX_Timeout();
    void            setTX_Timeout(uint);

    uchar           getLED_Logic();
    void            setLED_Logic(uchar);

    uint            getReset_Device_Timeout();
    void            setReset_Device_Timeout(uint);
private:
    Modem_Properties Modem_Properties_Data;
};

#endif // MODEMPROPERTIESCLASS_H
