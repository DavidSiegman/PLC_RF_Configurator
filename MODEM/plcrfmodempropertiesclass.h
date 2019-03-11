#ifndef PlcRfModemPropertiesClass_H
#define PlcRfModemPropertiesClass_H

#include <Qt>

enum
{
    INTERFACE_DISABLE = 0,
    INTERFACE_ENABLE
};
enum
{
    INTERFACE_NOT_INIT = 0,
    INTERFACE_OK_INIT
};

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

typedef union{
    struct{
        unsigned  Modem_Mode:  			      2; // байт 1
        unsigned  PLC_EN:      			      1;
        unsigned  RF_EN:       			      1;
        unsigned  RS_EN:       			      1;
        unsigned  PLC_TO_PLC_RET_EN:          1;
        unsigned  PLC_TO_RF_RET_EN:           1;
        unsigned  RF_TO_RF_RET_EN:            1;
        unsigned  RF_TO_PLC_RET_EN:           1; // байт 2
        unsigned  RS_TO_RF_RET_EN:            1;
        unsigned  RF_TO_RS_RET_EN:            1;
        unsigned  RS_TO_PLC_RET_EN:           1;
        unsigned  PLC_TO_RS_RET_EN:           1;
        unsigned  RS_USE_AS_DEBUG_OUTPUT:     1;
        unsigned  RS_TO_RF_UP_LINK:           1;
        unsigned  RS_TO_PLC_UP_LINK:          1;
        unsigned  MODBUS_CRC_CHECK_DISABLE:   1; // байт 3
        unsigned  UNUSED_0:                   3; // байт 4
        unsigned  RS_BAUDRATE:                4;
        unsigned  UNUSED_1:                   4; // байт 4
        unsigned  EEPROM_INIT_OK:             1; // не хранится во FLASH
        unsigned  PLC_INIT_OK:                1; // не хранится во FLASH
        unsigned  RF_INIT_OK:                 1; // не хранится во FLASH
        unsigned  RS_INIT_OK:                 1; // не хранится во FLASH
    }Field;
    unsigned int Word;
}Interfaces_Control_Type;

typedef union Debug_Control_Type_Def{
    struct{
        // бит глобального включения отладочного интерфейса
        unsigned DEBUG_GLOBAL_EN:             1;
        // биты включения отладочных сообщений PLC
        unsigned PLC_INIT_DEBUG_EN:           1;
        unsigned PLC_UART_RX_DEBUG_EN:        1;
        unsigned PLC_RX_TX_DATA_DEBUG_EN:     1;

        // биты включения отладочных сообщений SPI и RF
        unsigned SPI_DEBUG_EN:                1;
        unsigned SI4463_INIT_DEBUG_EN:        1;
        unsigned SI4463_DEBUG_EN:             1;

        // биты включения отладочных сообщений HOST
        unsigned HOST_UART_RX_DEBUG_EN:       1;

        // биты включения отладочных сообщений FLASH
        unsigned FLASH_DEBUG_EN:              1;
        unsigned FLASH_FULL_DATA_DEBUG_EN:    1;

        // биты включения отладочных сообщений INTERFACES_CONTROL
        unsigned INTERFACES_CONTROL_DEBUG_EN: 1;
        unsigned UART_TO_INTERFACES_DEBUG_EN: 1;
        unsigned INTERFACES_TO_UART_DEBUG_EN: 1;
        unsigned RETRANSLATION_DEBUG_EN:      1;

        // биты включения отладочных сообщений RS
        unsigned RS_DEBUG_EN: 1;
    }Field;
    unsigned int Word;
}Debug_Control_Type;

class PlcRfModemPropertiesClass
{
public:
    PlcRfModemPropertiesClass();

    void            Clear_Data();

    Interfaces_Control_Type getPLC_RF433_Interfaces_Control(void);
    Debug_Control_Type      getPLC_RF433_Debug_Control(void);
    void setPLC_RF433_Interfaces_Control(Interfaces_Control_Type);
    void setPLC_RF433_Debug_Control(Debug_Control_Type);

    unsigned char  getModem_Mode(void);
    unsigned char  getPLC_EN(void);
    unsigned char  getRF_EN(void);
    unsigned char  getRS_EN(void);
    unsigned char  getPLC_TO_PLC_RET_EN(void);
    unsigned char  getPLC_TO_RF_RET_EN(void);
    unsigned char  getRF_TO_RF_RET_EN(void);
    unsigned char  getRF_TO_PLC_RET_EN(void);
    unsigned char  getRS_TO_RF_RET_EN(void);
    unsigned char  getRF_TO_RS_RET_EN(void);
    unsigned char  getRS_TO_PLC_RET_EN(void);
    unsigned char  getPLC_TO_RS_RET_EN(void);
    unsigned char  getRS_USE_AS_DEBUG_OUTPUT(void);
    unsigned char  getRS_TO_RF_UP_LINK(void);
    unsigned char  getRS_TO_PLC_UP_LINK(void);
    unsigned char  getMODBUS_CRC_CHECK_DISABLE(void);
    unsigned char  getRS_BAUDRATE(void);

    unsigned char  getEEPROM_INIT_OK(void);
    unsigned char  getPLC_INIT_OK(void);
    unsigned char  getRF_INIT_OK(void);
    unsigned char  getRS_INIT_OK(void);

    unsigned char  getDEBUG_GLOBAL_EN(void);
    unsigned char  getPLC_INIT_DEBUG_EN(void);
    unsigned char  getPLC_UART_RX_DEBUG_EN(void);
    unsigned char  getPLC_RX_TX_DATA_DEBUG_EN(void);
    unsigned char  getSPI_DEBUG_EN(void);
    unsigned char  getSI4463_INIT_DEBUG_EN(void);
    unsigned char  getSI4463_DEBUG_EN(void);
    unsigned char  getHOST_UART_RX_DEBUG_EN(void);
    unsigned char  getFLASH_DEBUG_EN(void);
    unsigned char  getFLASH_FULL_DATA_DEBUG_EN(void);
    unsigned char  getINTERFACES_CONTROL_DEBUG_EN(void);
    unsigned char  getUART_TO_INTERFACES_DEBUG_EN(void);
    unsigned char  getINTERFACES_TO_UART_DEBUG_EN(void);
    unsigned char  getRETRANSLATION_DEBUG_EN(void);
    unsigned char  getRS_DEBUG_EN(void);

    void setModem_Mode(unsigned char);
    void setPLC_EN(unsigned char);
    void setRF_EN(unsigned char);
    void setRS_EN(unsigned char);
    void setPLC_TO_PLC_RET_EN(unsigned char);
    void setPLC_TO_RF_RET_EN(unsigned char);
    void setRF_TO_RF_RET_EN(unsigned char);
    void setRF_TO_PLC_RET_EN(unsigned char);
    void setRS_TO_RF_RET_EN(unsigned char);
    void setRF_TO_RS_RET_EN(unsigned char);
    void setRS_TO_PLC_RET_EN(unsigned char);
    void setPLC_TO_RS_RET_EN(unsigned char);
    void setRS_USE_AS_DEBUG_OUTPUT(unsigned char);
    void setRS_TO_RF_UP_LINK(unsigned char);
    void setRS_TO_PLC_UP_LINK(unsigned char);
    void setMODBUS_CRC_CHECK_DISABLE(unsigned char);
    void setRS_BAUDRATE(unsigned char);

    void setEEPROM_INIT_OK(unsigned char);
    void setPLC_INIT_OK(unsigned char);
    void setRF_INIT_OK(unsigned char);
    void setRS_INIT_OK(unsigned char);

    void setDEBUG_GLOBAL_EN(unsigned char);
    void setPLC_INIT_DEBUG_EN(unsigned char);
    void setPLC_UART_RX_DEBUG_EN(unsigned char);
    void setPLC_RX_TX_DATA_DEBUG_EN(unsigned char);
    void setSPI_DEBUG_EN(unsigned char);
    void setSI4463_INIT_DEBUG_EN(unsigned char);
    void setSI4463_DEBUG_EN(unsigned char);
    void setHOST_UART_RX_DEBUG_EN(unsigned char);
    void setFLASH_DEBUG_EN(unsigned char);
    void setFLASH_FULL_DATA_DEBUG_EN(unsigned char);
    void setINTERFACES_CONTROL_DEBUG_EN(unsigned char);
    void setUART_TO_INTERFACES_DEBUG_EN(unsigned char);
    void setINTERFACES_TO_UART_DEBUG_EN(unsigned char);
    void setRETRANSLATION_DEBUG_EN(unsigned char);
    void setRS_DEBUG_EN(unsigned char);

    RealTime        getLastAOPENTime();
    void            setLastAOPENTime(RealTime);

private:
    // used in RF433/PLC Modules
    Interfaces_Control_Type PLC_RF433_Interfaces_Control;
    Debug_Control_Type      PLC_RF433_DEBUG_Control;
    RealTime                LastAOPENTime;
};

#endif // PlcRfModemPropertiesClass_H
