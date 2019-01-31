#include "connecthandlerclass.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

ConnectHandlerClass::ConnectHandlerClass(DataLogic_Class *DataLogic,MODEMClass *MODEM,UPDATE *nUPDATE,QObject *parent) : QObject(parent)
{
    ReadDataProgress = 0;
    preReadDataProgress = 0;

    this->DataLogic = DataLogic;
    this->MODEM     = MODEM;
    this->nUPDATE   = nUPDATE;

    connect(this,SIGNAL(SendComand(uint,uint)),this->DataLogic,SLOT(ComandHandling(uint,uint)));
    connect(this->DataLogic,SIGNAL(outConnect(uint,uint,uint)),this,SLOT(ConnectHandling(uint,uint,uint)));
}

void ConnectHandlerClass::STOP(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    emit SendLog(QString::fromUtf8(">> ======= Запрос остановлен\r"),NONE);
}
void ConnectHandlerClass::aOPEN(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    //MODEM->SwitchTable.clear();
    emit SendLog(QString::fromUtf8(">> ======= Подключение к устройству\r"),NONE);
    ConnectHandling(CONNECT_HANDLING,1,0);
}
void ConnectHandlerClass::SetSWITCH_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_NODE_TYPE,1,0);
}
void ConnectHandlerClass::SetSWITCH_MASK(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_SWITCH_LEVEL,1,0);
}
void ConnectHandlerClass::SetSWITCH_LEVEL(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_SWITCH_LEVEL,1,0);
}
void ConnectHandlerClass::SetSWITCH_TIMEOUT(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_SWITCH_TIMEOUT,1,0);
}
void ConnectHandlerClass::SetSWITCH_PROP(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_SWITCH_LEVEL,1,0);
}
void ConnectHandlerClass::ReadCURRENT_RSSI(){
    /*
    if(ui->MANUAL_ENTER->isEnabled()) // если ручной ввод
    {

    }
    else                              // если активен конфигуратор
    {

    }
    */
}
void ConnectHandlerClass::ReadLRSSI_AFC(){
    /*
    if(ui->MANUAL_ENTER->isEnabled()) // если ручной ввод
    {

    }
    else                              // если активен конфигуратор
    {

    }
    */
}

void ConnectHandlerClass::WriteRF_PARAMS(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_RF_PARAMETERS,1,0);
}
void ConnectHandlerClass::WriteRFSI4432_PARAMS(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_SI4432_PARAMETERS,1,0);
}
void ConnectHandlerClass::SendRF_RESET(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_RF_RESET,1,0);
}
void ConnectHandlerClass::SendReadSNIFER_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_SNIFER_MODE,1,0);
}
void ConnectHandlerClass::SendWriteSNIFER_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_SNIFER_MODE,1,0);
}
void ConnectHandlerClass::SendReadUPLINC_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_UPLINC_MODE,1,0);
}
void ConnectHandlerClass::SendWriteUPLINC_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_UPLINC_MODE,1,0);
}
void ConnectHandlerClass::SendReadCRC_DISABLE_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_CRC_CHECK_MODE,1,0);
}
void ConnectHandlerClass::SendWriteCRC_DISABLE_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_CRC_CHECK_MODE,1,0);
}
void ConnectHandlerClass::SendReadBROADCAST_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_BROADCASTING_MODE,1,0);
}
void ConnectHandlerClass::SendWriteBROADCAST_MODE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_BROADCASTING_MODE,1,0);
}
void ConnectHandlerClass::WriteSWITCH_TABLE(){
    RetranslatorPropertiesClass*  Out_Retranslator_Properties = MODEM->getOut_Retranslator_Properties();
    if (Out_Retranslator_Properties->getRetranslator_Table().length() > 0){
        Out_Retranslator_Properties->setRetranslator_Table_Current_Index(0);
        SetModuleTypeStatus = 0;
        SetReadDataProgress(0);
        ConnectHandling(SEND_WRITE_SWITCH_TABLE_ELEMENT,1,0);
    }
}
void ConnectHandlerClass::ReadSWITCH_TABLE(){
    RetranslatorPropertiesClass*  In_Retranslator_Properties = MODEM->getIn_Retranslator_Properties();
    SetModuleTypeStatus = 0;
    SetReadDataProgress(5);
    In_Retranslator_Properties->clearRetranslation_Table();
    In_Retranslator_Properties->setRetranslator_Table_Current_Index(0);
    ConnectHandling(SEND_WRITE_SWITCH_TABLE_ELEMENT,1,0);
}
void ConnectHandlerClass::SendSWITCH_TABLE_DELETE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_DELET_SWITCH_TABLE_FROM_FLASH,1,0);
}
void ConnectHandlerClass::WriteMASK_DESTINATION(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(SEND_WRITE_MASK_DESTINATION,1,0);
}

void ConnectHandlerClass::StartMonitor(){
   emit SendLog(QString::fromUtf8("\r>> ======= Старт RSSI Монитор\r"),NONE);
   //Monitor = new MonitorClass(timeout,parameter);
   //connect(Monitor,SIGNAL(SendComand(uint,uint)),this->DataLogic,SLOT(ComandHandling(uint,uint)));
   //connect(Monitor,SIGNAL(SendComand(uint,uint)),this,SLOT(MonitorComandCounter(uint,uint)));
   //connect(this,SIGNAL(MonitorStart()),Monitor,SLOT(startMonitor()));
   //connect(this,SIGNAL(MonitorStop()),Monitor,SLOT(stopMonitor()));
   emit MonitorStart();
}

void ConnectHandlerClass::MonitorComandCounter(uint n, uint state){

}

void ConnectHandlerClass::StopMonitor(){
    emit SendLog(QString::fromUtf8(">> ======= Стоп RSSI Монитор\r"),NONE);
    emit MonitorStop();
}
void ConnectHandlerClass::StartUPDATE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(UPDATE_HANDLING,1,0);
}
void ConnectHandlerClass::StartDELETE(){
    SetModuleTypeStatus = 0;
    SetReadDataProgress(0);
    ConnectHandling(DELETE_HANDLING,1,0);
}
void ConnectHandlerClass::SetModuleType(uchar new_value)
{
    this->ModuleType = new_value;
}
void ConnectHandlerClass::SetInterface(uchar new_value)
{
    this->Interface = new_value;
}
void ConnectHandlerClass::SetReadDataProgress(uint new_value){
   this->preReadDataProgress = this->ReadDataProgress;
   this->ReadDataProgress = new_value;
}
uint ConnectHandlerClass::GetPreeReadDataProgress(void){
   return this->preReadDataProgress;
}
void ConnectHandlerClass::ConnectHandling(uint n, uint state, uint repeate){
    FirmwareInformationClass* In_Firmware_Information = MODEM->getIn_Firmware_Information();
    DataLogic->DataLogicMode = n;

    if (repeate == 1){
        if (SetModuleTypeStatus != 2)
        {
            SetReadDataProgress(GetPreeReadDataProgress());
        }
        SetModuleTypeStatus = 1;
    }

    if ((this->Interface == COM_USO_INTERFACE) && (SetModuleTypeStatus == 0)){
        SetModuleTypeStatus = 1;
    }
    if (this->Interface != COM_USO_INTERFACE){
        SetModuleTypeStatus = 2;
    }
    if ((In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0) ||
        (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4463) == 0) ||
        (In_Firmware_Information->getDevice_Name().compare(RF_PLC_SNIFFER) == 0)){
        SetModuleTypeStatus = 2;
    }
    if (SetModuleTypeStatus == 1){
        //emit Progress(0);
        emit SendLog(QString::fromUtf8("\r>> ======= Выбор модуля\r"),NONE);
        if (this->ModuleType == ADDITIONAL_MODULE_TYPE){
            emit SendComand(SEND_CHOICE_ADDITIONAL_MODULE,CONFIG_SEND_CONTROL);
        }
        else if (this->ModuleType == MAIN_MODULE_TYPE){
            emit SendComand(SEND_CHOICE_MAIN_MODULE,CONFIG_SEND_CONTROL);
        }
        SetModuleTypeStatus = 2;
    }
    else if ((SetModuleTypeStatus == 2) || (SetModuleTypeStatus == 0))
    {
        SetModuleTypeStatus = 1;
        if (n == CONNECT_HANDLING){
            if (ReadDataProgress == 0){
                emit Progress(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Запрос версии ПО\r"),NONE);
                emit SendComand(SEND_AOPEN,CONFIG_SEND_CONTROL);
                SetReadDataProgress(1);
            }
            else{
                if(In_Firmware_Information->getDevice_Name().compare(PLC_MODEM) == 0){
                    n = PLC_READ_DATA;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4432) == 0){
                    n = RF_MODEM_SI4432_READ_DATA;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4463) == 0){
                    n = RF_MODEM_SI4463_READ_DATA;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_MODEM) == 0){
                    //n = RF_PLC_MODEM_READ_DATA;
                    n = RF_MODEM_SI4463_READ_DATA;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0){
                    n = RF_SNIFFER_SI4432_READ_DATA;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4463) == 0){
                    n = RF_SNIFFER_SI4463_READ_DATA;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_SNIFFER) == 0){
                    //n = RF_PLC_SNIFFER_READ_DATA;
                    n = RF_SNIFFER_SI4463_READ_DATA;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(TERMINAL) == 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                    emit isAOPEN();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                else if (In_Firmware_Information->getDevice_Name().compare(GSM_MODEM) == 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                    emit isAOPEN();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                switch (n){          // ==================================================================================
                case PLC_READ_DATA:{ // Параметры PLC модуля =============================================================
                                     // ==================================================================================
                    switch (ReadDataProgress){
                    case 0:{
                        SetReadDataProgress(1);
                        break;
                    }
                    case 1:{
                        if (state != 0){
                            emit Progress(8);
                            emit SendLog(QString::fromUtf8("\r>> ======= Чтение частоты PLC\r"),NONE);
                            emit SendComand(SEND_READ_PLC_FREQ_PARAMS,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(2);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 2:{
                        if (state != 0){
                            emit Progress(56);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание сетевых наcтроек\r"),NONE);
                            emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(3);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 3:{
                        if (state != 0){
                            emit Progress(100);
                            emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                            emit isAOPEN();
                            SetReadDataProgress(0);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    }

                    break;
                }                                 // ==================================================================================
                case RF_MODEM_SI4463_READ_DATA:{  // Параметры радиомодуля на SI4463 ==================================================
                                                  // ==================================================================================
                    switch (ReadDataProgress){
                    case 0:{
                        SetReadDataProgress(1);
                        break;
                    }
                    case 1:{
                        if (state != 0){
                            emit Progress(8);
                            emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров из буфера\r"),NONE);
                            emit SendComand(SEND_READ_PROPERTYS_FROM_FLASH,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(2);
                        }
                        break;
                    }
                    case 2:{
                        if (state != 0){
                            emit Progress(16);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                            emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(3);
                        }
                        break;
                    }
                    case 3:{
                        if (state != 0){
                            emit Progress(24);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                            emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(4);
                        }
                        break;
                    }
                    case 4:{
                        if (state != 0){
                            emit Progress(32);
                            emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров калибровки из буфера\r"),NONE);
                            emit SendComand(SEND_READ_CALIBPROPS_FROM_FLASH,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(5);
                        }
                        break;
                    }
                    case 5:{
                        if (state != 0){
                            emit Progress(40);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                            emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(6);
                        }
                        break;
                    }
                    case 6:{
                        if (state != 0){
                            emit Progress(48);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                            emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(7);
                        }
                        break;
                    }
                    case 7:{
                        if (state != 0){
                            emit Progress(56);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание сетевых наcтроек\r"),NONE);
                            emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(8);
                        }
                        break;
                    }
                    case 8:{
                        if (state != 0){
                            emit Progress(64);
                            emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(9);
                        }
                        break;
                    }
                    case 9:{
                        if (state != 0){
                            emit Progress(72);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов\r"),NONE);
                            emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(10);
                        }
                        break;
                    }
                    case 10:{
                        if (state != 0){
                            emit Progress(80);
                            emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(11);
                        }
                        break;
                    }
                    case 11:{
                        if (state != 0){
                            emit Progress(88);
                            emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(12);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 12:{
                        if (state != 0){
                            emit Progress(100);
                            emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                            emit isAOPEN();
                            SetReadDataProgress(0);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    }
                    break;
                }                                // ==================================================================================
                case RF_MODEM_SI4432_READ_DATA:{ // параметры радиомодуля на SI4432 ==================================================
                                                 // ==================================================================================
                    switch (ReadDataProgress){
                    case 0:{
                        SetReadDataProgress(1);
                        break;
                    }
                    case 1:{
                        if (state != 0){
                            emit Progress(8);
                            emit SendLog(QString::fromUtf8("\r>> ======= Считывание настроек радио микросхемы\r"),NONE);
                            emit SendComand(SEND_READ_SI4432_PARAMETERS,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(2);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 2:{
                        if (state != 0){
                            emit Progress(56);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание сетевых наcтроек\r"),NONE);
                            emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(3);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 3:{
                        if (state != 0){
                            emit Progress(64);
                            emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(4);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 4:{
                        if (state != 0){
                            emit Progress(72);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов\r"),NONE);
                            emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                            if (In_Firmware_Information->getBootloader_Version() >= 4){
                                SetReadDataProgress(5);
                                //SetModuleTypeStatus = 2;
                            }
                            else{
                                SetReadDataProgress(7);
                                SetModuleTypeStatus = 2;
                            }
                        }
                        break;
                    }
                    case 5:
                    {
                        if (state != 0){
                            emit Progress(80);
                            emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(6);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 6:
                    {
                        if (state != 0){
                            emit Progress(88);
                            emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(7);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 7:
                    {
                        if (state != 0){
                            emit Progress(100);
                            emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                            emit isAOPEN();
                            SetReadDataProgress(0);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    }
                    break;
                }                                 // ==================================================================================
                case RF_SNIFFER_SI4432_READ_DATA:{// Параметры снифера на SI4432 ======================================================
                                                  // ==================================================================================
                    switch (ReadDataProgress){
                    case 0:{
                        SetReadDataProgress(1);
                        break;
                    }
                    case 1:{
                        if (state != 0){
                            emit Progress(10);
                            emit SendLog(QString::fromUtf8("\r>> ======= Считывание настроек радио микросхемы\r"),NONE);
                            emit SendComand(SEND_READ_SI4432_PARAMETERS,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(2);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 2:{
                        if (state != 0){
                            emit Progress(20);
                            emit SendLog(QString::fromUtf8("\r>> ======= Чтение регистра 0x09 нагрузочной ёмкости\r"),NONE);
                            emit SendComand(SEND_READ_SI4432_09_REGISTER,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(3);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 3:{
                        if (state != 0){
                            emit Progress(30);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание сетевых наcтроек\r"),NONE);
                            emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(4);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 4:{
                        if (state != 0){
                            emit Progress(40);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов\r"),NONE);
                            emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(5);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 5:{
                        if (state != 0){
                            emit Progress(50);
                            emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(6);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 6:{
                        if (state != 0){
                            emit Progress(60);
                            emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                            if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
                                 (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
                                ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
                                 (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
                                SetReadDataProgress(7);
                                //SetModuleTypeStatus = 2;
                            }
                            else
                            {
                                SetReadDataProgress(11);
                                //SetModuleTypeStatus = 2;
                            }

                        }
                        break;
                    }
                    case 7:{
                        if (state != 0){
                            emit Progress(70);
                            emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима\r"),NONE);
                            emit SendComand(SEND_READ_SNIFER_MODE,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(8);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 8:{
                        if (state != 0){
                            emit Progress(70);
                            emit SendLog(QString::fromUtf8("\r>> ======= Чтение бита направления Up_Link\r"),NONE);
                            emit SendComand(SEND_READ_UPLINC_MODE,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(9);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 9:{
                        if (state != 0){
                            emit Progress(70);
                            emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима CRC Check disable\r"),NONE);
                            emit SendComand(SEND_READ_CRC_CHECK_MODE,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(10);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 10:{
                        if (state != 0){
                            emit Progress(70);
                            emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима Broadcasting\r"),NONE);
                            emit SendComand(SEND_READ_BROADCASTING_MODE,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(11);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 11:{
                        if (state != 0){
                            emit Progress(70);
                            emit SendLog(QString::fromUtf8("\r>> ======= Чтение маски назначения\r"),NONE);
                            emit SendComand(SEND_READ_MASK_DESTINATION,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(12);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 12:{
                        emit Progress(70);
                        emit SendLog(QString::fromUtf8("\r>> ======= Чтение номера прибора\r"),NONE);
                        RetranslatorPropertiesClass*  In_Retranslator_Properties = MODEM->getIn_Retranslator_Properties();
                        In_Retranslator_Properties->clearRetranslation_Table();
                        In_Retranslator_Properties->setRetranslator_Table_Current_Index(0);
                        emit SendComand(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                        SetReadDataProgress(13);
                        SetModuleTypeStatus = 2;
                        break;
                    }
                    case 13:{
                        if (state != 0){
                            emit Progress(100);
                            emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                            emit isAOPEN();
                            SetReadDataProgress(14);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    }
                    break;
                }                                  // ==================================================================================
                case RF_SNIFFER_SI4463_READ_DATA:{ // Параметры снифера на SI4463 ======================================================
                                                   // ==================================================================================
                    switch (ReadDataProgress){
                    case 0:{
                        SetReadDataProgress(1);
                        break;
                    }
                    case 1:{
                        if (state != 0){
                            emit Progress(8);
                            emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров из буфера\r"),NONE);
                            emit SendComand(SEND_READ_PROPERTYS_FROM_FLASH,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(2);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 2:{
                        if (state != 0){
                            emit Progress(16);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                            emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(3);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 3:{
                        if (state != 0){
                            emit Progress(24);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                            emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(4);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 4:{
                        if (state != 0){
                            emit Progress(32);
                            emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров калибровки из буфера\r"),NONE);
                            emit SendComand(SEND_READ_CALIBPROPS_FROM_FLASH,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(5);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 5:{
                        if (state != 0){
                            emit Progress(40);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                            emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(6);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 6:{
                        if (state != 0){
                            emit Progress(48);
                            DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                            emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(7);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 7:{
                        if (state != 0){
                            emit Progress(64);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание уровня сети RF\r"),NONE);
                            emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(8);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 8:{
                        if (state != 0){
                            emit Progress(80);
                            emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов RF\r"),NONE);
                            emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(9);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 9:{
                        if (state != 0){
                            emit Progress(88);
                            emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(10);
                            //SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 10:{
                        if (state != 0){
                            emit Progress(88);
                            emit SendComand(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                            SetReadDataProgress(11);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    case 11:{
                        if (state != 0){
                            emit Progress(100);
                            emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                            emit isAOPEN();
                            SetReadDataProgress(0);
                            SetModuleTypeStatus = 2;
                        }
                        break;
                    }
                    }
                break;
                }
                }
            }
        }
        else if (n == SEND_WRITE_NODE_TYPE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись режима сети\r"),NONE);
                    emit SendComand(SEND_WRITE_NODE_TYPE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима сети\r"),NONE);
                    emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Установка режима прошла успешно\r"),NONE);
                    emit isSWITCH_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_SWITCH_LEVEL){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись уровня/маски ретранслятора\r"),NONE);
                    emit SendComand(SEND_WRITE_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение уровня/маски ретранслятора\r"),NONE);
                    emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Установка уровня/маски прошла успешно\r"),NONE);
                    emit isSWITCH_LEVEL();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_SWITCH_TIMEOUT){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись таймаута ретранслятора\r"),NONE);
                    emit SendComand(SEND_WRITE_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение таймаута ретранслятора\r"),NONE);
                    emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Установка таймаута прошла успешно\r"),NONE);
                    emit isSWITCH_TIMEOUT();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_RF_PARAMETERS){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(16);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись основных параметров радио-модуля в RAM\r"),NONE);
                    DataLogic->setCurrentSI4463_PROPERTYS_structur(2);
                    emit SendComand(SEND_BF_AF_00_AC_00,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(32);
                    DataLogic->setCurrentSI4463_PROPERTYS_structur(2);
                    emit SendComand(SEND_BF_8B_21_88_00,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(48);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно"),NONE);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись основных параметров радио-модуля во FLASH\r"),NONE);
                    emit SendComand(SEND_LOAD_PROPERTYS_TO_FLASH,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(3);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 3:{
                if (state != 0){
                    emit Progress(64);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись параметров IQ калибровки радио-модуля в RAM\r"),NONE);
                    DataLogic->setCurrentSI4463_PROPERTYS_structur(3);
                    emit SendComand(SEND_BF_AF_00_AC_00,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(4);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 4:{
                if (state != 0){
                    emit Progress(80);
                    DataLogic->setCurrentSI4463_PROPERTYS_structur(3);
                    emit SendComand(SEND_BF_8B_21_88_00,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(5);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 5:{
                if (state != 0){
                    emit Progress(96);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно"),NONE);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись параметров IQ калибровки радио-модуля во FLASH\r"),NONE);
                    emit SendComand(SEND_LOAD_CALIBPROPS_TO_FLASH,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(6);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 6:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                    emit isRF_PARAMS();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_SI4432_PARAMETERS){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись параметров SI4432\r"),NONE);
                    emit SendComand(SEND_WRITE_SI4432_PARAMETERS,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно"),NONE);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение параметров SI4432\r"),NONE);
                    emit SendComand(SEND_READ_SI4432_PARAMETERS,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Чтение прошло успешно\r"),NONE);
                    emit isRFSI4432_PARAMS();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_RF_RESET){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0)
                {
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Перезагрузка радио-модуля\r"),NONE);
                    emit SendComand(SEND_RF_RESET,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Модуль перезагружен успешно\r"),NONE);
                    emit isRF_RESET();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_READ_SNIFER_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима работы USB/RF преобразователя\r"),NONE);
                    emit SendComand(SEND_READ_SNIFER_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Чтение прошло успешно\r"),NONE);
                    emit isSNIFER_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_SNIFER_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись режима работы USB/RF преобразователя\r"),NONE);
                    emit SendComand(SEND_WRITE_SNIFER_MODE,CONFIG_SEND_CONTROL);
                    if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
                         (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
                        ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
                         (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
                        SetReadDataProgress(1);
                        //SetModuleTypeStatus = 2;
                    }
                    else
                    {
                        SetReadDataProgress(2);
                        SetModuleTypeStatus = 2;
                    }
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима работы USB/RF преобразователя\r"),NONE);
                    emit SendComand(SEND_READ_SNIFER_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                    emit isSNIFER_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_READ_UPLINC_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение UP_Link\r"),NONE);
                    emit SendComand(SEND_READ_UPLINC_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Чтение прошло успешно\r"),NONE);
                    emit isUPLINC_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_UPLINC_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Установка UP_Link\r"),NONE);
                    emit SendComand(SEND_WRITE_UPLINC_MODE,CONFIG_SEND_CONTROL);
                    if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
                         (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
                        ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
                         (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
                        SetReadDataProgress(1);
                        //SetModuleTypeStatus = 2;
                    }
                    else
                    {
                        SetReadDataProgress(2);
                        SetModuleTypeStatus = 2;
                    }
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение UP_Link\r"),NONE);
                    emit SendComand(SEND_READ_UPLINC_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                    emit isUPLINC_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_READ_CRC_CHECK_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима проверки CRC\r"),NONE);
                    emit SendComand(SEND_READ_CRC_CHECK_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Чтение прошло успешно\r"),NONE);
                    isCRC_DISABLE_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_CRC_CHECK_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись режима проверки CRC\r"),NONE);
                    emit SendComand(SEND_WRITE_CRC_CHECK_MODE,CONFIG_SEND_CONTROL);
                    if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
                         (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
                        ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
                         (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
                        SetReadDataProgress(1);
                        //SetModuleTypeStatus = 2;
                    }
                    else
                    {
                        SetReadDataProgress(2);
                        SetModuleTypeStatus = 2;
                    }
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима проверки CRC\r"),NONE);
                    emit SendComand(SEND_READ_CRC_CHECK_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                    isCRC_DISABLE_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_READ_BROADCASTING_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима широковещания\r"),NONE);
                    emit SendComand(SEND_READ_BROADCASTING_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Чтение прошло успешно\r"),NONE);
                    emit isBROADCAST_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_BROADCASTING_MODE){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись режима широковещания\r"),NONE);
                    emit SendComand(SEND_WRITE_BROADCASTING_MODE,CONFIG_SEND_CONTROL);
                    if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
                         (In_Firmware_Information->getBootloader_Version_Sniffer() >= 9)) ||
                        ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
                         (In_Firmware_Information->getUpgradable_Version_Sniffer() >= 9))){
                        SetReadDataProgress(1);
                        //SetModuleTypeStatus = 2;
                    }
                    else
                    {
                        SetReadDataProgress(2);
                        SetModuleTypeStatus = 2;
                    }
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима широковещания\r"),NONE);
                    emit SendComand(SEND_READ_BROADCASTING_MODE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                    emit isBROADCAST_MODE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_SWITCH_TABLE_ELEMENT){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Стирание таблицы ретрансляции\r"),NONE);
                    emit SendComand(SEND_DELET_SWITCH_TABLE_FROM_FLASH,CONFIG_SEND_CONTROL);
                   SetReadDataProgress(1);
                   //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(20);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись таблицы в RAM\r"),NONE);
                    emit SendComand(SEND_WRITE_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state == 1){
                    /*
                    if (state != 0){
                        emit SendComand(SEND_WRITE_SECTOR,CONFIG_SEND_CONTROL);
                        SetReadDataProgress(4);
                        SetModuleTypeStatus = 2;
                    }
                    */
                    emit SendLog(QString::fromUtf8("\r>> ======= Выбор модуля\r"),NONE);
                    if (this->ModuleType == ADDITIONAL_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_ADDITIONAL_MODULE,CONFIG_SEND_CONTROL);
                    }
                    else if (this->ModuleType == MAIN_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_MAIN_MODULE,CONFIG_SEND_CONTROL);
                    }
                    SetReadDataProgress(3);
                    SetModuleTypeStatus = 2;
                }
                else if (state == 2)
                {
                    emit SendLog(QString::fromUtf8("\r>> ======= Выбор модуля\r"),NONE);
                    if (this->ModuleType == ADDITIONAL_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_ADDITIONAL_MODULE,CONFIG_SEND_CONTROL);
                    }
                    else if (this->ModuleType == MAIN_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_MAIN_MODULE,CONFIG_SEND_CONTROL);
                    }
                    SetReadDataProgress(4);
                    SetModuleTypeStatus = 2;

                }
                break;
            }
            case 3:{
                if (state != 0){
                    emit SendComand(SEND_WRITE_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 4:{
                if (state != 0){
                    emit Progress(40);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись таблицы во Flash\r"),NONE);
                    emit SendComand(SEND_LOAD_SWITCH_TABLE_TO_FLASH,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(5);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 5:{
                if (state != 0){
                    RetranslatorPropertiesClass*  In_Retranslator_Properties = MODEM->getIn_Retranslator_Properties();
                    In_Retranslator_Properties->clearRetranslation_Table();
                    In_Retranslator_Properties->setRetranslator_Table_Current_Index(0);
                    emit Progress(70);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение таблицы\r"),NONE);
                    emit SendComand(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(6);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 6:{
                if (state == 1){
                    /*
                    if (state != 0){
                        emit SendComand(SEND_WRITE_SECTOR,CONFIG_SEND_CONTROL);
                        SetReadDataProgress(4);
                        SetModuleTypeStatus = 2;
                    }
                    */
                    emit SendLog(QString::fromUtf8("\r>> ======= Выбор модуля\r"),NONE);
                    if (this->ModuleType == ADDITIONAL_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_ADDITIONAL_MODULE,CONFIG_SEND_CONTROL);
                    }
                    else if (this->ModuleType == MAIN_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_MAIN_MODULE,CONFIG_SEND_CONTROL);
                    }
                    SetReadDataProgress(7);
                    SetModuleTypeStatus = 2;
                }
                else if (state == 2)
                {
                    if (state != 0){
                        emit Progress(100);
                        emit SendLog(QString::fromUtf8(">> ======= Запись/чтение прошла(о) успешно\r"),NONE);
                        emit isSWITCH_TABLE();
                        SetReadDataProgress(0);
                        SetModuleTypeStatus = 2;
                    }
                }
                break;
            }
            case 7:{
                if (state != 0){
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение ячейки\r"),NONE);
                    emit SendComand(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(6);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_DELET_SWITCH_TABLE_FROM_FLASH){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Стирание таблицы ретрансляции\r"),NONE);
                    emit SendComand(SEND_DELET_SWITCH_TABLE_FROM_FLASH,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                    emit isSWITCH_TABLE_DELETE();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == SEND_WRITE_MASK_DESTINATION){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись маски назначения\r"),NONE);
                    emit SendComand(SEND_WRITE_MASK_DESTINATION,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(50);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно"),NONE);
                    emit SendLog(QString::fromUtf8("\r>> ======= Чтение маски назначения\r"),NONE);
                    emit SendComand(SEND_READ_MASK_DESTINATION,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Чтение прошло успешно\r"),NONE);
                    emit isMASK_DESTINATION();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == UPDATE_HANDLING){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Переключение в BOOT\r"),NONE);
                    emit SendComand(SEND_ENABLE_BOOT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(3);
                    emit SendLog(QString::fromUtf8("\r>> ======= Cчитываем записанные страницы\r"),NONE);
                    emit SendComand(SEND_READ_WRITED_PAGES,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                if (state != 0){
                    emit Progress(2);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись информации о прошивке\r"),NONE);
                    emit SendComand(SEND_FIRMWARE_DATA,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(3);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 3:{
                if (state != 0){
                    emit Progress(5);
                    emit SendLog(QString::fromUtf8("\r>> ======= Старт прошивки\r"),NONE);
                    emit SendComand(SEND_WRITE_SECTOR,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(4);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 4:{
                if (state == 1){
                    /*
                    if (state != 0){
                        emit SendComand(SEND_WRITE_SECTOR,CONFIG_SEND_CONTROL);
                        SetReadDataProgress(4);
                        SetModuleTypeStatus = 2;
                    }
                    */
                    emit SendLog(QString::fromUtf8("\r>> ======= Выбор модуля\r"),NONE);
                    if (this->ModuleType == ADDITIONAL_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_ADDITIONAL_MODULE,CONFIG_SEND_CONTROL);
                    }
                    else if (this->ModuleType == MAIN_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_MAIN_MODULE,CONFIG_SEND_CONTROL);
                    }
                    SetReadDataProgress(5);
                    SetModuleTypeStatus = 2;
                }
                else if (state == 2)
                {
                    emit SendLog(QString::fromUtf8("\r>> ======= Выбор модуля\r"),NONE);
                    if (this->ModuleType == ADDITIONAL_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_ADDITIONAL_MODULE,CONFIG_SEND_CONTROL);
                    }
                    else if (this->ModuleType == MAIN_MODULE_TYPE){
                        emit SendComand(SEND_CHOICE_MAIN_MODULE,CONFIG_SEND_CONTROL);
                    }
                    SetReadDataProgress(6);
                    SetModuleTypeStatus = 2;

                }
                else{
                    emit SendLog(QString::fromUtf8(">> =======  Блок не записан, повтор\r"),NONE);
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Переключение в BOOT\r"),NONE);
                    emit SendComand(SEND_ENABLE_BOOT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 5:{
                if (state != 0){
                    emit SendComand(SEND_WRITE_SECTOR,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(4);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            case 6:{
                if (state != 0){
                    emit Progress(95);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запрос версии ПО\r"),NONE);
                    emit SendComand(SEND_AOPEN,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(7);
                    SetModuleTypeStatus = 2;
                }
                else{
                    emit SendLog(QString::fromUtf8(">> =======  Блок не записан, повтор\r"),NONE);
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Переключение в BOOT\r"),NONE);
                    emit SendComand(SEND_ENABLE_BOOT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }

                break;
            }
            case 7:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                    emit isUPDATED();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                else{
                    emit SendLog(QString::fromUtf8(">> =======  Блок не записан, повтор\r"),NONE);
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Переключение в BOOT\r"),NONE);
                    emit SendComand(SEND_ENABLE_BOOT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
        else if (n == DELETE_HANDLING){
            switch (ReadDataProgress){
            case 0:{
                if (state != 0){
                    emit Progress(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Переключение в BOOT\r"),NONE);
                    emit SendComand(SEND_ENABLE_BOOT,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(1);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 1:{
                if (state != 0){
                    emit Progress(3);
                    emit SendLog(QString::fromUtf8("\r>> ======= Cчитываем записанные страницы\r"),NONE);
                    emit SendComand(SEND_DELETE_FIRMWARE,CONFIG_SEND_CONTROL);
                    SetReadDataProgress(2);
                    //SetModuleTypeStatus = 2;
                }
                break;
            }
            case 2:{
                emit Progress(95);
                emit SendLog(QString::fromUtf8("\r>> ======= Запрос версии ПО\r"),NONE);
                emit SendComand(SEND_AOPEN,CONFIG_SEND_CONTROL);
                SetReadDataProgress(3);
                SetModuleTypeStatus = 2;
                break;
            }
            case 3:{
                if (state != 0){
                    emit Progress(100);
                    emit SendLog(QString::fromUtf8(">> ======= Стирание прошло успешно\r"),NONE);
                    emit isDELETED();
                    SetReadDataProgress(0);
                    SetModuleTypeStatus = 2;
                }
                break;
            }
            }
        }
    }
}
