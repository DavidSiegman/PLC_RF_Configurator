#ifndef MESS_ENUM
#define MESS_ENUM
// ==================================================
// Все возможные сообщения передаваемые между слотами
// ==================================================
enum
{
    NONE = 0,
    CONFIG_SEND_CONTROL,
    CONFIG_SEND_WHITOUT_REPEAT,
    MANUAL_SEND_CONTROL,
    COM_OPEN,
    COM_CLOSE,
    COM_TX,
    COM_RX,
    TCP_OPEN,
    TCP_CLOSE,
    TCP_TX,
    TCP_RX,
    PLC_READ_DATA,
    RF_READ_DATA,
    RF_OLD_READ_DATA,
    IN_INTERFACE_USO,
    IN_INTERFACE_RF_PLC,
    CONNECT_HANDLING,
    SEND_AOPEN,
    SEND_BF_03_00_AC_00, // чтение первой части параметров SI4463
    SEND_BF_03_21_88_00, // чтение второй части параметров SI4463
    SEND_BF_AF_00_AC_00, // запись первой части параметров SI4463
    SEND_BF_8B_21_88_00, // запись второй части параметров SI4463
    SEND_RF_RESET,
    SEND_SNIFER_MODE,
    SEND_UPLINC_MODE,
    SEND_CRC_CHECK_MODE,
    SEND_BROADCASTING_MODE,
    SEND_READ_NODE_TYPE,
    SEND_WRITE_NODE_TYPE,
    SEND_READ_SWITCH_LEVEL,
    SEND_WRITE_SWITCH_LEVEL,
    SEND_READ_SWITCH_TIMEOUT,
    SEND_WRITE_SWITCH_TIMEOUT,
    SEND_READ_RX_TIMEOUT,
    SEND_WRITE_RX_TIMEOUT,
    SEND_READ_TX_TIMEOUT,
    SEND_WRITE_TX_TIMEOUT,
    SEND_READ_RSSI,
    SEND_READ_RSSI_CURRENT,
    SEND_RELOAD_DEVICE,
    SEND_WRITE_RF_PARAMETERS,
    SEND_LOAD_PROPERTYS_TO_FLASH,
    SEND_READ_PROPERTYS_FROM_FLASH,
    SEND_LOAD_CALIBPROPS_TO_FLASH,
    SEND_READ_CALIBPROPS_FROM_FLASH
};

#endif // MESS_ENUM

