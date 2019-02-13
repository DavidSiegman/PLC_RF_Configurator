#ifndef MESS_ENUM
#define MESS_ENUM

// ================================================================
// Все возможные сообщения передаваемые между слотами и энумераторы
// ================================================================

enum
{
    COM_USO_INTERFACE = 0,
    PLC_RF_INTERFACE
};
enum
{
    ADDITIONAL_MODULE_TYPE = 0,
    MAIN_MODULE_TYPE
};
enum
{
    CONFIG_SEND_CONTROL = 1,
    CONFIG_SEND_WHITOUT_REPEAT,
    MANUAL_SEND_CONTROL,
    MANUAL_CYCLIC_SEND_CONTROL,
    MONITOR_SEND_CONTROL
};
enum
{
    IN_INTERFACE_USO = 1,
    IN_INTERFACE_RF_PLC,
    IN_SNIFER_PLUS_PREAMBLE
};
enum
{
    COM_OPEN = 1,
    COM_CLOSE,
    COM_TX,
    COM_RX,
    TCP_OPEN,
    TCP_CLOSE,
    TCP_TX,
    TCP_RX
};

enum
{
    NONE = 0,
    CONNECT_HANDLING,
    UPDATE_HANDLING,
    DELETE_HANDLING,
    SEND_AOPEN,
    SEND_READ_ALL_DATA,
    SEND_BF_03_00_AC_00,             // чтение первой части параметров SI4463
    SEND_BF_03_21_88_00,             // чтение второй части параметров SI4463
    SEND_BF_AF_00_AC_00,             // запись первой части параметров SI4463
    SEND_BF_8B_21_88_00,             // запись второй части параметров SI4463
    SEND_RF_RESET,
    SEND_READ_SNIFER_MODE,
    SEND_WRITE_SNIFER_MODE,
    SEND_READ_UPLINK_MODE,
    SEND_WRITE_UPLINK_MODE,
    SEND_READ_CRC_CHECK_MODE,
    SEND_WRITE_CRC_CHECK_MODE,
    SEND_READ_BROADCASTING_MODE,
    SEND_WRITE_BROADCASTING_MODE,
    SEND_READ_SWITCH_TABLE_ELEMENT,
    SEND_WRITE_SWITCH_TABLE_ELEMENT,
    SEND_LOAD_SWITCH_TABLE_TO_FLASH,
    SEND_DELET_SWITCH_TABLE,
    SEND_READ_SWITCH_MODE,
    SEND_WRITE_SWITCH_MODE,
    SEND_READ_SWITCH_LEVEL,
    SEND_WRITE_SWITCH_LEVEL,
    SEND_READ_SWITCH_TIMEOUT,
    SEND_WRITE_SWITCH_TIMEOUT,
    SEND_READ_RX_TIMEOUT,
    SEND_WRITE_RX_TIMEOUT,
    SEND_READ_TX_TIMEOUT,
    SEND_WRITE_TX_TIMEOUT,
    SEND_READ_LRSSI_AFC,
    SEND_READ_LRSSI_AFC_CURRENT,
    SEND_RELOAD_DEVICE,
    SEND_WRITE_RFSI4463_PARAMETERS,
    SEND_LOAD_PROPERTYS_TO_FLASH,
    SEND_READ_PROPERTYS_FROM_FLASH,
    SEND_LOAD_CALIBPROPS_TO_FLASH,
    SEND_READ_CALIBPROPS_FROM_FLASH,
    SEND_READ_SI4432_PARAMETERS,
    SEND_WRITE_SI4432_PARAMETERS,
    SEND_READ_SI4432_REGISTER,
    SEND_WRITE_SI4432_REGISTER,
    SEND_READ_SI4432_09_REGISTER,
    SEND_WRITE_SI4432_09_REGISTER,
    SEND_READ_ST750_PARAMETERS,
    SEND_WRITE_ST750_PARAMETERS,
    SEND_READ_MASK_DESTINATION,
    SEND_WRITE_MASK_DESTINATION,
    SEND_ENABLE_BOOT,
    SEND_FIRMWARE_DATA,
    SEND_READ_WRITED_PAGES,
    SEND_WRITE_SECTOR,
    SEND_DELETE_FIRMWARE,
    SEND_CHOICE_ADDITIONAL_MODULE,
    SEND_CHOICE_MAIN_MODULE
};

#endif // MESS_ENUM


