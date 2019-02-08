#include "connecthandlerclass.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

ConnectHandlerClass::ConnectHandlerClass(DataLogic_Class *DataLogic,MODEMClass *MODEM,UPDATE *nUPDATE,QObject *parent) : QObject(parent)
{
    this->DataLogic = DataLogic;
    this->MODEM     = MODEM;
    this->nUPDATE   = nUPDATE;

    connect(this,SIGNAL(SendComand(uint,uint)),this->DataLogic,SLOT(ComandHandling(uint,uint)));
    connect(this->DataLogic,SIGNAL(outConnect(uint,uint,uint)),this,SLOT(ConnectHandling(uint,uint,uint)));
}

void ConnectHandlerClass::STOP(){
    emit SendLog(QString::fromUtf8(">> ======= Запрос остановлен\r"),NONE);
}

void ConnectHandlerClass::StartMonitor(){
   emit SendLog(QString::fromUtf8("\r>> ======= Старт RSSI Монитор\r"),NONE);
   Monitor = new MonitorClass(DataLogic->Delay_Time,1);
   connect(Monitor,SIGNAL(SendComand(uint,uint)),this->DataLogic,SLOT(ComandHandling(uint,uint)));
   connect(this,SIGNAL(MonitorStart()),          Monitor,SLOT(startMonitor()));
   connect(this,SIGNAL(MonitorStop()),           Monitor,SLOT(stopMonitor()));
   emit MonitorStart();
}

void ConnectHandlerClass::StopMonitor(){
    emit SendLog(QString::fromUtf8(">> ======= Стоп RSSI Монитор\r"),NONE);
    emit MonitorStop();
}

void ConnectHandlerClass::SetModuleType(uchar new_value)
{
    this->ModuleType = new_value;
}
void ConnectHandlerClass::SetInterface(uchar new_value)
{
    this->Interface = new_value;
}

uint ConnectHandlerClass::EnableModuleChoiceMode(FirmwareInformationClass* device)
{
    uint result = 0;
    if (this->Interface == COM_USO_INTERFACE){
       if (this->ModuleType == ADDITIONAL_MODULE_TYPE){
           result = SEND_CHOICE_ADDITIONAL_MODULE;
       }
       else{
           result = SEND_CHOICE_MAIN_MODULE;
       }
    }
    if ((device->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0) ||
        (device->getDevice_Name().compare(RF_SNIFFER_SI4463) == 0) ||
        (device->getDevice_Name().compare(RF_PLC_SNIFFER) == 0) ||
        (device->getDevice_Name().compare(TERMINAL) == 0)
       ){
        result = 0;
    }
    return result;
}


void ConnectHandlerClass::StartSendingProcess(uint SelectComandQueue){
    // Обнуляем индексы
    ConnectHandler.CommandsQueueCurrentIndex = 0;
    ConnectHandler.CommandsQueuePreIndex     = 0;
    ConnectHandler.CommandsNumber            = 0;

    // Информация об устройстве
    FirmwareInformationClass* In_Firmware_Information = MODEM->getIn_Firmware_Information();

    uint ModuleChoice = EnableModuleChoiceMode(In_Firmware_Information);
    if (ModuleChoice != NONE){
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = ModuleChoice; // выбор модуля
    }

    switch (SelectComandQueue){
    case SEND_AOPEN:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Подключение к устройству\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_AOPEN;   // запрос версии ПО
        break;
    }
    case SEND_READ_ALL_DATA:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Считываем основные параметры\r"),NONE);
        // Вычитываем различные наборы параметров в зависимости от устройства
        if(In_Firmware_Information->getDevice_Name().compare(PLC_MODEM) == 0){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_PLC_FREQ_PARAMS;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_MODE;
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4432) == 0){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SI4432_PARAMETERS;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_MODE;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_LEVEL;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TIMEOUT;
            if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
                 (In_Firmware_Information->getBootloader_Version() >= 4)) ||
                ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
                 (In_Firmware_Information->getUpgradable_Version() >= 4))){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SI4432_09_REGISTER;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_RX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_TX_TIMEOUT;
            }
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4463) == 0){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_PROPERTYS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_CALIBPROPS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_MODE;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_LEVEL;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_RX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_TX_TIMEOUT;
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_MODEM) == 0){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_PROPERTYS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_CALIBPROPS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_MODE;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_LEVEL;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_RX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_TX_TIMEOUT;
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SI4432_PARAMETERS;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SI4432_09_REGISTER;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_RX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_TX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_MASK_DESTINATION;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TABLE_ELEMENT;
            if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
                 (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
                ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
                 (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SNIFER_MODE;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_UPLINK_MODE;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_CRC_CHECK_MODE;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_BROADCASTING_MODE;
            }
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4463) == 0){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_PROPERTYS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_CALIBPROPS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_LEVEL;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_RX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_TX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TABLE_ELEMENT;
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_SNIFFER) == 0){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_PROPERTYS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_CALIBPROPS_FROM_FLASH;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_LEVEL;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_RX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_TX_TIMEOUT;
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TABLE_ELEMENT;
        }
        else if (In_Firmware_Information->getDevice_Name().compare(TERMINAL) == 0){

        }
        else if (In_Firmware_Information->getDevice_Name().compare(GSM_MODEM) == 0){

        }

        break;
    }
    case SEND_WRITE_SWITCH_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима ретрансляции\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SWITCH_MODE;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_MODE;
        break;
    }
    case SEND_WRITE_SWITCH_LEVEL:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись маски сети\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SWITCH_LEVEL;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_LEVEL;
        break;
    }
    case SEND_WRITE_SWITCH_TIMEOUT:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись таймаута ретрасляции\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SWITCH_TIMEOUT;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TIMEOUT;
        break;
    }
    case SEND_READ_LRSSI_AFC:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Чтение уровня сигнала RSSI\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_LRSSI_AFC;
        break;
    }
    case SEND_WRITE_SI4432_PARAMETERS:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись радио-настроек\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SI4432_PARAMETERS;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SI4432_PARAMETERS;
        if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version() >= 4)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version() >= 4)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version_Sniffer() >= 8)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 8))){
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SI4432_09_REGISTER;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SI4432_09_REGISTER;
        }
        break;
    }
    case SEND_WRITE_RFSI4463_PARAMETERS:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись радио-настроек\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_AF_00_AC_00;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_8B_21_88_00;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_LOAD_PROPERTYS_TO_FLASH;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_AF_00_AC_00;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_8B_21_88_00;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_LOAD_CALIBPROPS_TO_FLASH;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_PROPERTYS_FROM_FLASH;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_CALIBPROPS_FROM_FLASH;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_00_AC_00;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_BF_03_21_88_00;
        break;
    }
    case SEND_RF_RESET:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Команда сброса\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_RF_RESET;
        break;
    }
    case SEND_WRITE_SNIFER_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SNIFER_MODE;
        if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SNIFER_MODE;
        }
        break;
    }
    case SEND_WRITE_UPLINK_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись бита направления Up_Link\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_UPLINK_MODE;
        if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_UPLINK_MODE;
        }
        break;
    }
    case SEND_WRITE_CRC_CHECK_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима проверки CRC\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_CRC_CHECK_MODE;
        if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_CRC_CHECK_MODE;
        }
        break;
    }
    case SEND_WRITE_BROADCASTING_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима широковещания\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_BROADCASTING_MODE;
        if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
            ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_BROADCASTING_MODE;
        }
        break;
    }
    case SEND_WRITE_MASK_DESTINATION:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима широковещания\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_MASK_DESTINATION;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_MASK_DESTINATION;
        break;
    }
    case SEND_WRITE_SWITCH_TABLE_ELEMENT:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись таблицы ретрансляции\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_DELET_SWITCH_TABLE;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SWITCH_TABLE_ELEMENT;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_LOAD_SWITCH_TABLE_TO_FLASH;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TABLE_ELEMENT;
        MODEM->getIn_Retranslator_Properties()->clearRetranslation_Table();
        MODEM->getIn_Retranslator_Properties()->setRetranslator_Table_Current_Index(0);
        MODEM->getOut_Retranslator_Properties()->setRetranslator_Table_Current_Index(0);
        break;
    }
    case SEND_READ_SWITCH_TABLE_ELEMENT:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Чтение таблицы ретрансляции\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_SWITCH_TABLE_ELEMENT;
        MODEM->getIn_Retranslator_Properties()->clearRetranslation_Table();
        MODEM->getIn_Retranslator_Properties()->setRetranslator_Table_Current_Index(0);
        MODEM->getOut_Retranslator_Properties()->setRetranslator_Table_Current_Index(0);
        break;
    }
    case SEND_DELET_SWITCH_TABLE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Удаление таблицы ретрансляции\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_DELET_SWITCH_TABLE;
        MODEM->getIn_Retranslator_Properties()->clearRetranslation_Table();
        MODEM->getIn_Retranslator_Properties()->setRetranslator_Table_Current_Index(0);
        MODEM->getOut_Retranslator_Properties()->setRetranslator_Table_Current_Index(0);
        break;
    }
    case UPDATE_HANDLING:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Обновление ПО\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_ENABLE_BOOT;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_READ_WRITED_PAGES;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_FIRMWARE_DATA;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_WRITE_SECTOR;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_AOPEN;
        break;
    }
    case DELETE_HANDLING:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Удаление ПО\r"),NONE);
        // Формируем очередь команд
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_ENABLE_BOOT;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_DELETE_FIRMWARE;
        ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = SEND_AOPEN;
        break;
    }
    }
    ConnectHandler.CommandsQueue[ConnectHandler.CommandsNumber++] = NONE;
    emit Progress(0);
    ConnectHandling(SelectComandQueue,0,0);
}

void ConnectHandlerClass::EmitCurrentSignal(uint SelectComandQueue)
{
    emit Progress(100);
    switch (SelectComandQueue)
    {
    case SEND_AOPEN:{
         // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Устройство определено\r"),NONE);
        StartSendingProcess(SEND_READ_ALL_DATA);
        break;
    }
    case SEND_READ_ALL_DATA:{
         // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Чтение параметров завершено успешно\r"),NONE);
        emit isAOPEN();
        break;
    }
    case SEND_WRITE_SWITCH_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима ретрансляции прошла успешно\r"),NONE);
        emit isSWITCH_MODE();
        break;
    }
    case SEND_WRITE_SWITCH_LEVEL:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись маски сети прошла успешно\r"),NONE);
        emit isSWITCH_LEVEL();
        break;
    }
    case SEND_WRITE_SWITCH_TIMEOUT:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись таймаута ретрасляции прошла успешно\r"),NONE);
        emit isSWITCH_TIMEOUT();
        break;
    }
    case SEND_READ_LRSSI_AFC:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Чтение уровня сигнала RSSI завершено успешно\r"),NONE);
        emit isLRSSI_AFC();
        break;
    }
    case SEND_WRITE_SI4432_PARAMETERS:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись радио-настроек прошла успешно\\r"),NONE);
        emit isRFSI4432_PARAMETERS();
        break;
    }
    case SEND_WRITE_RFSI4463_PARAMETERS:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись радио-настроек прошла успешно\r"),NONE);
        emit isRFSI4463_PARAMETERS();
        break;
    }
    case SEND_RF_RESET:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Сброс выполнен\r"),NONE);
        emit isRF_RESET();
        break;
    }
    case SEND_WRITE_SNIFER_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима прошла успешно\r"),NONE);
        emit isSNIFER_MODE();
        break;
    }
    case SEND_WRITE_UPLINK_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись бита направления Up_Link прошла успешно\r"),NONE);
        emit isUPLINK_MODE();
        break;
    }
    case SEND_WRITE_CRC_CHECK_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима проверки CRC прошла успешно\r"),NONE);
        emit isCRC_CHECK_MODE();
        break;
    }
    case SEND_WRITE_BROADCASTING_MODE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись режима широковещания прошла успешно\r"),NONE);
        emit isBROADCASTING_MODE();
        break;
    }
    case SEND_WRITE_MASK_DESTINATION:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись маски прошла успешно\r"),NONE);
        emit isMASK_DESTINATION();
        break;
    }
    case SEND_WRITE_SWITCH_TABLE_ELEMENT:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Запись таблицы ретрансляции прошла успешно\r"),NONE);
        emit isSWITCH_TABLE();
        break;
    }
    case SEND_READ_SWITCH_TABLE_ELEMENT:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Чтение таблицы ретрансляции завершено успешно\r"),NONE);
        emit isSWITCH_TABLE();
        break;
    }
    case SEND_DELET_SWITCH_TABLE:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Удаление таблицы ретрансляции завершено успешно\r"),NONE);
        emit isDELET_SWITCH_TABLE();
        break;
    }
    case UPDATE_HANDLING:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Обновление ПО прошло успешно\r"),NONE);
        emit isUPDATED();
        break;
    }
    case DELETE_HANDLING:{
        // Выводим сообщение в Лог
        emit SendLog(QString::fromUtf8(">> ======= Удаление ПО прошло успешно\r"),NONE);
        emit isDELETED();
        break;
    }
    }
}

void ConnectHandlerClass::ConnectHandling(uint n, uint state, uint repeate)
{
   // Информация об устройстве
   FirmwareInformationClass* In_Firmware_Information = MODEM->getIn_Firmware_Information();

   DataLogic->DataLogicMode = n;
   if (state == 0){
       if ((ConnectHandler.CommandsQueue[0] == SEND_CHOICE_ADDITIONAL_MODULE) ||
           (ConnectHandler.CommandsQueue[0] == SEND_CHOICE_MAIN_MODULE)){
           if (ConnectHandler.CommandsQueueCurrentIndex != 0){
               ConnectHandler.CommandsQueuePreIndex = ConnectHandler.CommandsQueueCurrentIndex - 1;
               ConnectHandler.CommandsQueueCurrentIndex = 0;
           }
           else
           {
               ConnectHandler.CommandsQueueCurrentIndex = ConnectHandler.CommandsQueuePreIndex;
           }
       }
       emit SendComand(ConnectHandler.CommandsQueue[ConnectHandler.CommandsQueueCurrentIndex],CONFIG_SEND_CONTROL);
    }
    else if (state == 1){
        // если нужно перед каждой командой выбирать модуль
        if ((ConnectHandler.CommandsQueue[0] == SEND_CHOICE_ADDITIONAL_MODULE) ||
            (ConnectHandler.CommandsQueue[0] == SEND_CHOICE_MAIN_MODULE)){
            ConnectHandler.CommandsQueue[0] = EnableModuleChoiceMode(In_Firmware_Information); // выбор модуля
            if (ConnectHandler.CommandsQueueCurrentIndex == 0){
                ConnectHandler.CommandsQueuePreIndex++;
                ConnectHandler.CommandsQueueCurrentIndex = ConnectHandler.CommandsQueuePreIndex;
            }
            else if ((ConnectHandler.CommandsQueueCurrentIndex > 0) &&
                     (ConnectHandler.CommandsQueueCurrentIndex < (ConnectHandler.CommandsNumber - 2))){
                emit Progress(ConnectHandler.CommandsQueueCurrentIndex * 100 / ConnectHandler.CommandsNumber);
                ConnectHandler.CommandsQueueCurrentIndex = 0;
            }
            else {
                ConnectHandler.CommandsQueueCurrentIndex = ConnectHandler.CommandsNumber - 1;
            }
        }
        else {
            emit Progress(ConnectHandler.CommandsQueueCurrentIndex * 100 / ConnectHandler.CommandsNumber);
            ConnectHandler.CommandsQueueCurrentIndex++;
        }

        if (ConnectHandler.CommandsQueue[ConnectHandler.CommandsQueueCurrentIndex] != NONE){
            emit SendComand(ConnectHandler.CommandsQueue[ConnectHandler.CommandsQueueCurrentIndex],CONFIG_SEND_CONTROL);
        }
        else
        {
            EmitCurrentSignal(n);
        }
    }
}
