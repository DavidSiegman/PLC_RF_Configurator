#include "modemclass.h"

MODEMClass::MODEMClass(QObject *parent) : QObject(parent)
{
    curr_ver = 0; SWITCH_MODE = 0;
    SWITCH_LEVEL = 0; SWITCH_TIMEOUT = 0; RX_TIMEOUT = 0; TX_TIMEOUT = 0; LED_LOGIC = 0; CRC_CHECK_DISABLE = 0;
    RESET_DEVICE_TIMEOUT = 0; UP_LINC = 0; DIRECT_RET = 0; BROADCAST = 0;
    boot_ver = 0; fw_ver = 0;
    BOOT_VERSION = 0; FW_VERSION = 0;
}

