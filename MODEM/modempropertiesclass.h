#ifndef MODEMPROPERTIESCLASS_H
#define MODEMPROPERTIESCLASS_H

#include <Qt>

typedef union RealTime_Type{
    struct{
        unsigned          Seconds: 8;
        unsigned          Minutes: 8;
        unsigned          Hours:   8;
        unsigned          WeekDay: 8;
        unsigned          Day:     8;
        unsigned          Month:   8;
        unsigned          Year:    8;
        unsigned          Unused:  8;
    }Filed;
    uint Words[2];
}RealTime;

typedef struct Modem_Properties_Type{
    uint          RF_RX_Timeout;
    uint          RF_TX_Timeout;
    uint          PLC_RX_Timeout;
    uint          PLC_TX_Timeout;
    uchar         LED_Logic;
    uint          Reset_Device_Timeout;
    RealTime      LastAOPENTime;
}Modem_Properties;

class ModemPropertiesClass
{
public:
    ModemPropertiesClass();

    void            Clear_Data();

    uint            getRF_RX_Timeout();
    void            setRF_RX_Timeout(uint);

    uint            getRF_TX_Timeout();
    void            setRF_TX_Timeout(uint);

    uint            getPLC_RX_Timeout();
    void            setPLC_RX_Timeout(uint);

    uint            getPLC_TX_Timeout();
    void            setPLC_TX_Timeout(uint);

    uchar           getLED_Logic();
    void            setLED_Logic(uchar);

    uint            getReset_Device_Timeout();
    void            setReset_Device_Timeout(uint);

    RealTime        getLastAOPENTime();
    void            setLastAOPENTime(RealTime);

private:

    Modem_Properties        Modem_Properties_Data;
};

#endif // MODEMPROPERTIESCLASS_H
