#include "modemclass.h"

MODEMClass::MODEMClass(Ui::MainWindow *ui, QObject *parent) : QObject(parent)
{

}

MODEMClass::MODEMClass(QObject *parent)
{
    this->MODEM_Propertys.BOOTLOADER_CRC32.clear();
    this->MODEM_Propertys.BOOTLOADER_VERSION              = 0;
    this->MODEM_Propertys.BOOTLOADER_VERSION_SNIFER       = 0;
    this->MODEM_Propertys.BOOTLOADER_VERSION_TERMINAL     = 0;
    this->MODEM_Propertys.BROADCAST                       = 0;
    this->MODEM_Propertys.CRC_CHECK_DISABLE               = 0;
    this->MODEM_Propertys.CURRENT_FIRMWARE_VERSION        = 0;
    this->MODEM_Propertys.DIRECT_RET                      = 0;
    this->MODEM_Propertys.LED_LOGIC                       = 0;
    this->MODEM_Propertys.RESET_DEVICE_TIMEOUT            = 0;
    this->MODEM_Propertys.RX_TIMEOUT                      = 0;
    this->MODEM_Propertys.SNIFER_MODE                     = 0;
    this->MODEM_Propertys.String_BOOTLOADER_VERSION       = "";
    this->MODEM_Propertys.String_UPGRADABLE_VERSION       = "";
    this->MODEM_Propertys.SwitchTable.clear();
    this->MODEM_Propertys.SWITCH_LEVEL                    = 0;
    this->MODEM_Propertys.SWITCH_LEVEL_DESTINATION        = 0;
    this->MODEM_Propertys.SWITCH_MODE                     = 0;
    this->MODEM_Propertys.SWITCH_TIMEOUT                  = 0;
    this->MODEM_Propertys.TX_TIMEOUT                      = 0;
    this->MODEM_Propertys.UPGRADABLE_CRC32.clear();
    this->MODEM_Propertys.UPGRADABLE_SIZE                 = 0;
    this->MODEM_Propertys.UPGRADABLE_VERSION              = 0;
    this->MODEM_Propertys.UPGRADABLE_VERSION_SNIFER       = 0;
    this->MODEM_Propertys.UPGRADABLE_VERSION_TERMINAL     = 0;
    this->MODEM_Propertys.UP_LINC                         = 0;

    this->MODEM_Propertys.SWITCH_MASK                     = (RF_Switch_Mask*)&(this->MODEM_Propertys.SWITCH_LEVEL);

    this->MODEM_Propertys.SWITCH_MASK_DESTINATION         = (RF_Switch_Mask*)&(this->MODEM_Propertys.SWITCH_LEVEL_DESTINATION);

    this->model          = new QStandardItemModel();

    this->current_index = 0;
}

MODEMClass_Propertys MODEMClass::getMODEM_Propertys(void)
{
    return this->MODEM_Propertys;
}
void MODEMClass::setMODEM_Propertys(MODEMClass_Propertys new_value)
{
    this->MODEM_Propertys = new_value;
}

void MODEMClass::addNewItem(QString string)
{
    this->current_index = this->model->rowCount();
    QStandardItem *item = new QStandardItem(string);
    this->model->setItem(this->current_index, 0, item);
    this->MODEM_Propertys.SwitchTable.append(string);
    this->current_index++;
}

void MODEMClass::delNewItem()
{
    if (this->current_index <= 100)
    {
        this->current_index--;
    }
    else
    {
        this->current_index = 0;
    }
    this->model->removeRow(this->current_index);
    this->MODEM_Propertys.SwitchTable.removeAt(this->current_index);
    if ((this->current_index == 0)&&(this->model->rowCount() == 0))
    {
        this->model->removeColumn(this->current_index);
    }
}

void MODEMClass::setCurrent_Index(uchar index)
{
    this->current_index = index;
}
uchar MODEMClass::getCurrent_Index()
{
    return this->current_index;
}

void MODEMClass::clearNetTable()
{
    this->current_index = 0;
    this->MODEM_Propertys.SwitchTable.clear();
    this->model->clear();
}

uchar      MODEMClass::getCURRENT_FIRMWARE_VERSION(void)
{
    emit CURRENT_FIRMWARE_VERSION(this->MODEM_Propertys.CURRENT_FIRMWARE_VERSION);
    return this->MODEM_Propertys.CURRENT_FIRMWARE_VERSION;
}
void       MODEMClass::setCURRENT_FIRMWARE_VERSION(uchar new_value)
{
    this->MODEM_Propertys.CURRENT_FIRMWARE_VERSION = new_value;
    emit CURRENT_FIRMWARE_VERSION(this->MODEM_Propertys.CURRENT_FIRMWARE_VERSION);
}

QString    MODEMClass::getString_BOOTLOADER_VERSION(void)
{
    emit String_BOOTLOADER_VERSION(this->MODEM_Propertys.String_BOOTLOADER_VERSION);
    return this->MODEM_Propertys.String_BOOTLOADER_VERSION;
}
void       MODEMClass::setString_BOOTLOADER_VERSION(QString new_value)
{
    this->MODEM_Propertys.String_BOOTLOADER_VERSION = new_value;
    emit String_BOOTLOADER_VERSION(this->MODEM_Propertys.String_BOOTLOADER_VERSION);
}

QString    MODEMClass::getString_UPGRADABLE_VERSION(void)
{
    emit String_UPGRADABLE_VERSION(this->MODEM_Propertys.String_UPGRADABLE_VERSION);
    return this->MODEM_Propertys.String_UPGRADABLE_VERSION;
}
void       MODEMClass::setString_UPGRADABLE_VERSION(QString new_value)
{
    this->MODEM_Propertys.String_UPGRADABLE_VERSION = new_value;
    emit String_UPGRADABLE_VERSION(this->MODEM_Propertys.String_UPGRADABLE_VERSION);
}

double     MODEMClass::getBOOTLOADER_VERSION(void)
{
    emit BOOTLOADER_VERSION(this->MODEM_Propertys.BOOTLOADER_VERSION);
    return this->MODEM_Propertys.BOOTLOADER_VERSION;
}
void       MODEMClass::setBOOTLOADER_VERSION(double new_value)
{
    this->MODEM_Propertys.BOOTLOADER_VERSION = new_value;
    emit BOOTLOADER_VERSION(this->MODEM_Propertys.BOOTLOADER_VERSION);
}

double     MODEMClass::getUPGRADABLE_VERSION(void)
{
    emit UPGRADABLE_VERSION(this->MODEM_Propertys.UPGRADABLE_VERSION);
    return this->MODEM_Propertys.UPGRADABLE_VERSION;
}
void       MODEMClass::setUPGRADABLE_VERSION(double new_value)
{
    this->MODEM_Propertys.UPGRADABLE_VERSION = new_value;
    emit UPGRADABLE_VERSION(this->MODEM_Propertys.UPGRADABLE_VERSION);
}

double     MODEMClass::getBOOTLOADER_VERSION_SNIFER(void)
{
    emit BOOTLOADER_VERSION_SNIFER(this->MODEM_Propertys.BOOTLOADER_VERSION_SNIFER);
    return this->MODEM_Propertys.BOOTLOADER_VERSION_SNIFER;
}
void       MODEMClass::setBOOTLOADER_VERSION_SNIFER(double new_value)
{
    this->MODEM_Propertys.BOOTLOADER_VERSION_SNIFER = new_value;
    emit BOOTLOADER_VERSION_SNIFER(this->MODEM_Propertys.BOOTLOADER_VERSION_SNIFER);
}

double     MODEMClass::getUPGRADABLE_VERSION_SNIFER(void)
{
    emit UPGRADABLE_VERSION_SNIFER(this->MODEM_Propertys.UPGRADABLE_VERSION_SNIFER);
    return this->MODEM_Propertys.UPGRADABLE_VERSION_SNIFER;
}
void       MODEMClass::setUPGRADABLE_VERSION_SNIFER(double new_value)
{
    this->MODEM_Propertys.UPGRADABLE_VERSION_SNIFER = new_value;
    emit UPGRADABLE_VERSION_SNIFER(this->MODEM_Propertys.UPGRADABLE_VERSION_SNIFER);
}

double     MODEMClass::getBOOTLOADER_VERSION_TERMINAL(void)
{
    emit BOOTLOADER_VERSION_TERMINAL(this->MODEM_Propertys.BOOTLOADER_VERSION_TERMINAL);
    return this->MODEM_Propertys.BOOTLOADER_VERSION_TERMINAL;
}
void       MODEMClass::setBOOTLOADER_VERSION_TERMINAL(double new_value)
{
    this->MODEM_Propertys.BOOTLOADER_VERSION_TERMINAL = new_value;
    emit BOOTLOADER_VERSION_TERMINAL(this->MODEM_Propertys.BOOTLOADER_VERSION_TERMINAL);
}

double     MODEMClass::getUPGRADABLE_VERSION_TERMINAL(void)
{
    emit UPGRADABLE_VERSION_TERMINAL(this->MODEM_Propertys.UPGRADABLE_VERSION_TERMINAL);
    return this->MODEM_Propertys.UPGRADABLE_VERSION_TERMINAL;
}
void       MODEMClass::setUPGRADABLE_VERSION_TERMINAL(double new_value)
{
    this->MODEM_Propertys.UPGRADABLE_VERSION_TERMINAL = new_value;
    emit UPGRADABLE_VERSION_TERMINAL(this->MODEM_Propertys.UPGRADABLE_VERSION_TERMINAL);
}

uint       MODEMClass::getBOOTLOADER_SIZE(void)
{
    emit BOOTLOADER_SIZE(this->MODEM_Propertys.BOOTLOADER_SIZE);
    return this->MODEM_Propertys.BOOTLOADER_SIZE;
}
void       MODEMClass::setBOOTLOADER_SIZE(uint new_value)
{
    this->MODEM_Propertys.BOOTLOADER_SIZE = new_value;
    emit BOOTLOADER_SIZE(this->MODEM_Propertys.BOOTLOADER_SIZE);
}

uint       MODEMClass::getUPGRADABLE_SIZE(void)
{
    emit UPGRADABLE_SIZE(this->MODEM_Propertys.UPGRADABLE_SIZE);
    return this->MODEM_Propertys.UPGRADABLE_SIZE;
}
void       MODEMClass::setUPGRADABLE_SIZE(uint new_value)
{
    this->MODEM_Propertys.UPGRADABLE_SIZE = new_value;
    emit UPGRADABLE_SIZE(this->MODEM_Propertys.UPGRADABLE_SIZE);
}

QByteArray MODEMClass::getBOOTLOADER_CRC32(void)
{
    emit BOOTLOADER_CRC32(this->MODEM_Propertys.BOOTLOADER_CRC32);
    return this->MODEM_Propertys.BOOTLOADER_CRC32;
}
void       MODEMClass::setBOOTLOADER_CRC32(QByteArray new_value)
{
    this->MODEM_Propertys.BOOTLOADER_CRC32 = new_value;
    emit BOOTLOADER_CRC32(this->MODEM_Propertys.BOOTLOADER_CRC32);
}

QByteArray MODEMClass::getUPGRADABLE_CRC32(void)
{
    emit UPGRADABLE_CRC32(this->MODEM_Propertys.UPGRADABLE_CRC32);
    return this->MODEM_Propertys.UPGRADABLE_CRC32;
}
void       MODEMClass::setUPGRADABLE_CRC32(QByteArray new_value)
{
    this->MODEM_Propertys.UPGRADABLE_CRC32 = new_value;
    emit UPGRADABLE_CRC32(this->MODEM_Propertys.UPGRADABLE_CRC32);
}

uchar      MODEMClass::getSWITCH_MODE(void)
{
    emit SWITCH_MODE(this->MODEM_Propertys.SWITCH_MODE);
    return this->MODEM_Propertys.SWITCH_MODE;
}
void       MODEMClass::setSWITCH_MODE(uchar new_value)
{
    this->MODEM_Propertys.SWITCH_MODE = new_value;
    emit SWITCH_MODE(this->MODEM_Propertys.SWITCH_MODE);
}

uint       MODEMClass::getSWITCH_TIMEOUT(void)
{
    emit SWITCH_TIMEOUT(this->MODEM_Propertys.SWITCH_TIMEOUT);
    return this->MODEM_Propertys.SWITCH_TIMEOUT;
}
void       MODEMClass::setSWITCH_TIMEOUT(uint new_value)
{
    this->MODEM_Propertys.SWITCH_TIMEOUT = new_value;
    emit SWITCH_TIMEOUT(this->MODEM_Propertys.SWITCH_TIMEOUT);
}

uint       MODEMClass::getSWITCH_LEVEL(void)
{
    emit SWITCH_LEVEL(this->MODEM_Propertys.SWITCH_LEVEL);
    return this->MODEM_Propertys.SWITCH_LEVEL;
}
void       MODEMClass::setSWITCH_LEVEL(uint new_value)
{
    this->MODEM_Propertys.SWITCH_LEVEL = new_value;
    emit SWITCH_LEVEL(this->MODEM_Propertys.SWITCH_LEVEL);
}

uint       MODEMClass::getSWITCH_LEVEL_DESTINATION(void)
{

}
void       MODEMClass::setSWITCH_LEVEL_DESTINATION(uint)
{

}

uint       MODEMClass::getRX_TIMEOUT(void)
{

}
void       MODEMClass::setRX_TIMEOUT(uint)
{

}

uint       MODEMClass::getTX_TIMEOUT(void)
{

}
void       MODEMClass::setTX_TIMEOUT(uint)
{

}

uchar       MODEMClass::getLED_LOGIC(void)
{

}
void       MODEMClass::setLED_LOGIC(uchar)
{

}


uchar       MODEMClass::getCRC_CHECK_DISABLE(void)
{

}
void       MODEMClass::setCRC_CHECK_DISABLE(uchar)
{

}

uint       MODEMClass::getRESET_DEVICE_TIMEOUT(void)
{

}
void       MODEMClass::setRESET_DEVICE_TIMEOUT(uint)
{

}

uchar       MODEMClass::getUP_LINC(void)
{

}
void       MODEMClass::setUP_LINC(uchar)
{

}

uchar       MODEMClass::getDIRECT_RET(void)
{

}
void       MODEMClass::setDIRECT_RET(uchar)
{

}

uint       MODEMClass::getBROADCAST(void)
{

}
void       MODEMClass::setBROADCAST(uint)
{

}

uchar       MODEMClass::getSNIFER_MODE(void)
{

}
void       MODEMClass::setSNIFER_MODE(uchar)
{

}

QList<QString>  MODEMClass::getSwitchTable(void)
{

}
void  MODEMClass::setSwitchTable(QList<QString>)
{

}
