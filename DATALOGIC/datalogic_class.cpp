#include "DATALOGIC/datalogic_class.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"
//#include "mainwindow.h"

DataLogic_Class::DataLogic_Class(CRC16_Class *oCRC16,QTimer *t,SI4463Class *SI4463Conf,SI4432Class *SI4432Conf,
                                 PLCClass *PLCConf,MODEMClass *MODEM,Port *nPort,TCP *nTCP,UPDATE *nUPDATE,QObject *parent) : QObject(parent)
{
    this->setParent(parent);
    this->CRC16           = oCRC16;
    this->timer           = t;
    this->SI4463Conf      = SI4463Conf;
    this->SI4432Conf      = SI4432Conf;
    this->PLCConf         = PLCConf;
    this->MODEM           = MODEM;
    this->nPort           = nPort;
    this->nTCP            = nTCP;
    this->nUPDATE         = nUPDATE;
    this->addSerialNumber = false;

    this->timerRepeat           = new QTimer();
    this->timerManualRepeat     = new QTimer();
    this->BOOT_WAIT             = new QTimer();

    connect(this,SIGNAL(OutData(QByteArray)),            this->nPort,SLOT(COM_WriteDATA(QByteArray)));
    connect(this->nPort, SIGNAL(COM_OutDATA(QByteArray)),this, SLOT(In_DataBuffer(QByteArray)));
    connect(this,SIGNAL(OutData(QByteArray)),            this->nTCP,SLOT(TCP_WriteDATA(QByteArray)));
    connect(this->nTCP, SIGNAL(TCP_OutDATA(QByteArray)), this, SLOT(In_DataBuffer(QByteArray)));
    connect(timerRepeat,SIGNAL(timeout()),               this, SLOT(REPEAT_SEND()));
    connect(timerManualRepeat,SIGNAL(timeout()),         this, SLOT(MANUAL_REPEAT_SEND()));
    connect(BOOT_WAIT,SIGNAL(timeout()),                 this, SLOT(BOOT_WAITED()));
    connect(timer,    SIGNAL(timeout()),                 this, SLOT(ClearIn_DataBuffer()));

}

void DataLogic_Class::setSerialNumberMode(QString S, bool Enable){
    this->SerialNumber    = S;
    this->addSerialNumber = Enable;
}

void DataLogic_Class::setRepeatNumber(uint new_value){
    this->Repeat_Number  = new_value;
    this->Repeat_Counter = new_value;
}

void DataLogic_Class::setRepeatTimeout(uint new_value){
    this->Delay_Time     = new_value;
}

void DataLogic_Class::setCurrentSI4463_PROPERTYS_structur(uint select){
    if (select == 0){
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS();
    }
    else if (select == 1){
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS_CALIB();
    }
    else if (select == 2){
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS_FROM_FILE();
    }
    else if (select == 3){
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS_CALIB_FROM_FILE();
    }
}

void DataLogic_Class::ClearIn_DataBuffer(void){
    InDataBuffer.clear();
    this->timer->stop();
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        QString s = "Stop timer - Buff clear";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
}
void DataLogic_Class::ClearOut_DataBuffer(void)
{
    OutDataBuffer.clear();
}
void DataLogic_Class::In_DataBuffer(QByteArray data){
    InDataBuffer.append(data);
    int length = InDataBuffer.length();
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        QString s = "Input bytes: "; s += QString("%1").arg(length);
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
    if(this->timer->isActive()){
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        s = "Timer remainingTime() = "; s += QString("%1").arg(this->timer->remainingTime());
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
       this->timer->stop();
    }
    this->timer->start(25);
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        s = "Start timer 25 ms";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif

    if(CRC16->Check_Byte_Stream_CRC16(&InDataBuffer) && (length > 4)){
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        QString s = "Stop timer - CRC Correct";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
        this->timer->stop();

        this->ParceDataBuffer.clear();
        ParceDataBuffer.append(InDataBuffer);
        ClearIn_DataBuffer();
        if (Stop_Parceing == false){
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        s = "Data parsing";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
            Parce_DataBuffer();
        }
        else{
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        s = "Parsing data buffer clearing";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
            ParceDataBuffer.clear();
            this->Stop_Parceing = false;
        }
    }
}

void DataLogic_Class::Parce_DataBuffer(void)
{
    QByteArray AnswerH;
    for(unsigned int i = 0; i < 6; i++)
    {AnswerH.append((char)(0xFF));}

    QByteArray AnswerHeader;
    AnswerHeader.append(ParceDataBuffer.data(), 6);

    if (AnswerHeader.data() == AnswerH)
    {
        emit DataForPrint(ParceDataBuffer,COM_RX);     // Вывод данных в консоль
        ParceData(IN_INTERFACE_USO);
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        QString s = "ParceData(IN_INTERFACE_USO)";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
    }
    else
    {
        AnswerHeader.clear();
        AnswerHeader.append(ParceDataBuffer.data()+4, 6);
        if (AnswerHeader.data() == AnswerH)
        {
            emit DataForPrint(ParceDataBuffer,COM_RX);     // Вывод данных в консоль
            ParceData(IN_INTERFACE_RF_PLC);
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        QString s = "ParceData(IN_INTERFACE_RF_PLC)";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
        }
        else
        {
            emit DataForPrint(ParceDataBuffer,COM_RX);     // Вывод данных в консоль
            QString string = QByteAray_To_QString(ParceDataBuffer).toUpper();
            QString string2 = "FF FF FF FF C1 03 01 B4 CC ";
            if (string.compare(string2) == 0)
            {
                QByteArray data;
                int u[24] = {0xFF,0xFF,0xFF,0xFF,0x80,0x01,0x03,0x01,0x0F,'P','L','C','/','R','F','_','C','f','_','v','3','.','0','1'};int length = 24;
                for(int i = 0; i < length; i++){data.append((char)u[i]);}
                CRC16->CRC16_Add_To_ByteArray(&data);
                emit SEND_DATA(data,CONFIG_SEND_WHITOUT_REPEAT);
            }
            else if ((ParceDataBuffer.at(0) == 0x01) &&
                     (ParceDataBuffer.at(1) == 0x00) &&
                     (ParceDataBuffer.at(2) == 0x00) &&
                     (ParceDataBuffer.at(3) == 0x00)
                    ){
                ParceData(IN_SNIFER_PLUS_PREAMBLE);
                                                        #ifdef DATA_LOGIC_DEBUG
                                                        // ====================================
                                                        QString s = "ParceData(IN_SNIFER_PLUS_PREAMBLE)";
                                                        qDebug() << s;
                                                        // ====================================
                                                        #endif
            }
            else
            {
                this->Stop_Parceing = false;
            }
        }
    }
}

void DataLogic_Class::ComandHandling(uint SendComand, uint SendMode)
{
    QString s;
    RetranslatorPropertiesClass* Out_Retranslator_Properties = MODEM->getOut_Retranslator_Properties();

    SnifferPropertiesClass*      Out_Sniffer_Properties = MODEM->getOut_Sniffer_Properties();

    ModemPropertiesClass*        Out_Modem_Properties = MODEM->getOut_Modem_Properties();

    PlcRfModemPropertiesClass*   Out_PLC_RF433_Modem_Properties = MODEM->getOut_PLC_RF433_Modem_Properties();

    QByteArray data;
    data.append((char)(0xFF));
    data.append((char)(0xFF));
    data.append((char)(0xFF));
    data.append((char)(0xFF));
    int length = 0;
    switch (SendComand){
    case SEND_AOPEN:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_AOPEN";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xFF,0x00};length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_ENABLE_BOOT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_ENABLE_BOOT";
qDebug() << s;
// ====================================
#endif
        int u[9] = {0xFE,0x07,0xE0,0xDC,0xA5,0xF8,0xC9,0x96,0x0C}; length = 9;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SECTOR:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SECTOR";
qDebug() << s;
// ====================================
#endif
        emit SendLog(QString::fromUtf8("\r>> ======= Записываем Блок: ") +
                     QString::number(nUPDATE->getCurrent_BLOCK()) +
                     QString::fromUtf8(" Сектор: ") +
                     QString::number(nUPDATE->getCurrent_SECTOR()) +
                     QString::fromUtf8(" Байт записано: ") +
                     QString::number(nUPDATE->getWrited_BYTES()) +
                     QString::fromUtf8("\r"),NONE);

        data.append(0xFC);
        nUPDATE->getCurrent_SECTOR_DATA(&data);
        break;
    }
    case SEND_FIRMWARE_DATA:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_FIRMWARE_DATA";
qDebug() << s;
// ====================================
#endif
        QByteArray VERS;
        VERS.append(nUPDATE->getVERSION());
        if (nUPDATE->getSIZE() <= 0xFFFF){
            int u[12] = {0xFB,0x0A,
                        ((int)(VERS.at(0)) & 0xFF),
                        ((int)(VERS.at(1)) & 0xFF),
                        ((int)(VERS.at(2)) & 0xFF),
                        ((int)(VERS.at(3)) & 0xFF),
                        ((int)(nUPDATE->getSIZE()) >> 0   & 0xFF),
                        ((int)(nUPDATE->getSIZE()) >> 8   & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(3)) & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(2)) & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(1)) & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(0)) & 0xFF)
                        }; length = 12;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
        }
        else if ((nUPDATE->getSIZE() > 0xFFFF) &&
                 (nUPDATE->getSIZE() <= 0xFFFFFFFF)){
            int u[14] = {0xFB,0x0C,
                        ((int)(VERS.at(0)) & 0xFF),
                        ((int)(VERS.at(1)) & 0xFF),
                        ((int)(VERS.at(2)) & 0xFF),
                        ((int)(VERS.at(3)) & 0xFF),
                        ((int)(nUPDATE->getSIZE()) >> 0   & 0xFF),
                        ((int)(nUPDATE->getSIZE()) >> 8   & 0xFF),
                        ((int)(nUPDATE->getSIZE()) >> 16  & 0xFF),
                        ((int)(nUPDATE->getSIZE()) >> 24  & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(3)) & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(2)) & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(1)) & 0xFF),
                        ((int)(nUPDATE->getCRC32().at(0)) & 0xFF)
                        }; length = 14;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
        }
        break;
    }
    case SEND_DELETE_FIRMWARE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_DELETE_FIRMWARE";
qDebug() << s;
// ====================================
#endif
        int u[9] = {0xFA,0x07,0xA5,0xDC,0xE0,0x0C,0x96,0xC9,0xF8}; length = 9;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_WRITED_PAGES:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_WRITED_PAGES";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xF9,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_CHOICE_ADDITIONAL_MODULE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_CHOICE_ADDITIONAL_MODULE";
qDebug() << s;
// ====================================
#endif
        int u[9] = {0xF1,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SWITCH_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SWITCH_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xF0,0x00};length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SWITCH_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SWITCH_MODE";
qDebug() << s;
// ====================================
#endif
        uchar Retranslator_Mode = Out_Retranslator_Properties->getRetranslator_Mode();
        int u[10] = {0xEF,0x07,Retranslator_Mode,0xE0,0x96,0xF8,0xA5,0xC9,0xDC,0x0C}; length = 10;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_ST750_FREQ:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_ST750_FREQ";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xEE,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_ST750_PARAMETERS:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_ST750_PARAMETERS";
qDebug() << s;
// ====================================
#endif
        int u[3] = {0xEE,0x01,0x00}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_ST750_FREQ:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_ST750_FREQ";
qDebug() << s;
// ====================================
#endif
        PLC_Config_struct PLC_Config = PLCConf->getOut_ST750_PLC_Config()->getPLC_Config_struct();
        int u[15] = {0xED,0x0D,
                    (int)(PLC_Config.HIGHF >> 0) &0xFF,
                    (int)(PLC_Config.HIGHF >> 8) &0xFF,
                    (int)(PLC_Config.HIGHF >> 16)&0xFF,
                    (int)(PLC_Config.LOWF  >> 0) &0xFF,
                    (int)(PLC_Config.LOWF  >> 8) &0xFF,
                    (int)(PLC_Config.LOWF  >> 16)&0xFF,
                    0x96,0xF8,0x0C,0xDC,0xA5,0xC9,0xE0}; length = 15;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_ST750_PARAMETERS:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_ST750_PARAMETERS";
qDebug() << s;
// ====================================
#endif
        PLC_Config_struct PLC_Config = PLCConf->getOut_ST750_PLC_Config()->getPLC_Config_struct();
        int u[17] = {0xED,0x0F,
                    (int)(PLC_Config.HIGHF >> 0)  & 0xFF,
                    (int)(PLC_Config.HIGHF >> 8)  & 0xFF,
                    (int)(PLC_Config.HIGHF >> 16) & 0xFF,
                    (int)(PLC_Config.LOWF  >> 0)  & 0xFF,
                    (int)(PLC_Config.LOWF  >> 8)  & 0xFF,
                    (int)(PLC_Config.LOWF  >> 16) & 0xFF,
                    (int)(PLC_Config.Transmit_Conditions.HalbWord  >> 0) & 0xFF,
                    (int)(PLC_Config.Transmit_Conditions.HalbWord  >> 8) & 0xFF,
                    0x96,0xF8,0x0C,0xDC,0xA5,0xC9,0xE0}; length = 17;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SWITCH_TABLE_ELEMENT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SWITCH_TABLE_ELEMENT";
qDebug() << s;
// ====================================
#endif
        //QList<QString> Retranslation_Table = MODEM->getOut_Retranslator_Properties()->getRetranslator_Table();
        int u[3] = {0xEB,0x01,(int)(MODEM->getIn_Retranslator_Properties()->getRetranslator_Table().length())}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SWITCH_TABLE_ELEMENT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SWITCH_TABLE_ELEMENT";
qDebug() << s;
// ====================================
#endif
        QList<QString> Retranslation_Table = Out_Retranslator_Properties->getRetranslator_Table();
        uint switchelement = Retranslation_Table.at(Out_Retranslator_Properties->getRetranslator_Table_Current_Index()).toInt();
        int u[14] = {0xEA,0x0C,(int)(Out_Retranslator_Properties->getRetranslator_Table_Current_Index()),
                               (int)(switchelement >> 0) &0xFF,
                               (int)(switchelement >> 8) &0xFF,
                               (int)(switchelement >> 16)&0xFF,
                               (int)(switchelement >> 24)&0xFF,
                     0xF8,0xC9,0xDC,0xA5,0x96,0xE0,0x0C}; length = 14;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}

        break;
    }
    case SEND_DELET_SWITCH_TABLE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_DELET_SWITCH_TABLE";
qDebug() << s;
// ====================================
#endif
        int u[9] = {0xE9,0x07,0x5A,0xCD,0x8F,0x9C,0xC0,0x0E,0x69}; length = 9;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_LOAD_SWITCH_TABLE_TO_FLASH:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_LOAD_SWITCH_TABLE_TO_FLASH";
qDebug() << s;
// ====================================
#endif
        int u[9] = {0xE8,0x07,0xCD,0xA5,0xC9,0xF8,0xE0,0xC0,0x96}; length = 9;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_LAST_AOPEN_TIME:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_LAST_AOPEN_TIME";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xE7,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SI4432_PARAMETERS:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SI4432_PARAMETERS";
qDebug() << s;
// ====================================
#endif
        RF_Config_struct RF_Config = SI4432Conf->getOut_SI4432_RF_Config()->getRF_Config_struct();
        int u[26] = {0xE7,0x18,
                    (int)(RF_Config.RF_CONF_REG_1.reg >> 0) &0xFF,
                    (int)(RF_Config.RF_CONF_REG_1.reg >> 8) &0xFF,
                    (int)(RF_Config.RF_CONF_REG_1.reg >> 16)&0xFF,
                    (int)(RF_Config.RF_CONF_REG_1.reg >> 24)&0xFF,
                    (int)(RF_Config.RF_CONF_REG_2.reg >> 0) &0xFF,
                    (int)(RF_Config.RF_CONF_REG_2.reg >> 8) &0xFF,
                    (int)(RF_Config.RF_CONF_REG_2.reg >> 16)&0xFF,
                    (int)(RF_Config.RF_CONF_REG_2.reg >> 24)&0xFF,
                    (int)(RF_Config.RF_NOM_FREQUENC >> 0)   &0xFF,
                    (int)(RF_Config.RF_NOM_FREQUENC >> 8)   &0xFF,
                    (int)(RF_Config.RF_NOM_FREQUENC >> 16)  &0xFF,
                    (int)(RF_Config.RF_NOM_FREQUENC >> 24)  &0xFF,
                    (int)(RF_Config.RF_SYNCH_WORD >> 0)     &0xFF,
                    (int)(RF_Config.RF_SYNCH_WORD >> 8)     &0xFF,
                    (int)(RF_Config.RF_SYNCH_WORD >> 16)    &0xFF,
                    (int)(RF_Config.RF_SYNCH_WORD >> 24)    &0xFF,
                    (int)(RF_Config.RF_RX_HAEDER  >> 0)     &0xFF,
                    (int)(RF_Config.RF_RX_HAEDER  >> 8)     &0xFF,
                    (int)(RF_Config.RF_RX_HAEDER  >> 16)    &0xFF,
                    (int)(RF_Config.RF_RX_HAEDER  >> 24)    &0xFF,
                    (int)(RF_Config.RF_TX_HAEDER  >> 0)     &0xFF,
                    (int)(RF_Config.RF_TX_HAEDER  >> 8)     &0xFF,
                    (int)(RF_Config.RF_TX_HAEDER  >> 16)    &0xFF,
                    (int)(RF_Config.RF_TX_HAEDER  >> 24)    &0xFF,
                   }; length = 26;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SI4432_PARAMETERS:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SI4432_PARAMETERS";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xE6,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_DEBUG_CONTROL:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_DEBUG_CONTROL";
qDebug() << s;
// ====================================
#endif
        Debug_Control_Type Debug_Control = Out_PLC_RF433_Modem_Properties->getPLC_RF433_Debug_Control();
        int u[6] = {0xE6,0x04,
                    (int)(Debug_Control.Word >> 0)  & 0xFF,
                    (int)(Debug_Control.Word >> 8)  & 0xFF,
                    (int)(Debug_Control.Word >> 16) & 0xFF,
                    (int)(Debug_Control.Word >> 24) & 0xFF
                   }; length = 6;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_LRSSI_AFC:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_LRSSI_AFC";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xE5,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        emit RSSI_RequestSended();
        break;
    }
    case SEND_READ_LPGA:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_LPGA";
qDebug() << s;
// ====================================
#endif
        int u[3] = {0xE5,0x01,0x01}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        emit RSSI_RequestSended();
        break;
    }
    case SEND_RF_RESET:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_RF_RESET";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xE4,0x00};length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_RELOAD_DEVICE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_RELOAD_DEVICE";
qDebug() << s;
// ====================================
#endif
        uint Reset_Device_Timeout = Out_Modem_Properties->getReset_Device_Timeout();
        if (Reset_Device_Timeout == 0){
            int u[3] = {0xE4,0x00};length = 2;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
        }
        else{
            int u[6] = {0xE4,0x04,((int)(Reset_Device_Timeout >> 0)  & 0xFF),((int)(Reset_Device_Timeout >> 8) & 0xFF),
                                  ((int)(Reset_Device_Timeout >> 16) & 0xFF),((int)(Reset_Device_Timeout >> 24) & 0xFF)};length = 6;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
        }
        break;
    }
    case SEND_READ_SWITCH_TIMEOUT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SWITCH_TIMEOUT";
qDebug() << s;
// ====================================
#endif
        int u[3] = {0xE3,0x01,0x00};length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SWITCH_TIMEOUT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SWITCH_TIMEOUT";
qDebug() << s;
// ====================================
#endif
        uint Retranslator_Timeout = Out_Retranslator_Properties->getRetranslator_Timeout();
        int u[6] = {0xE3,0x04,((int)(Retranslator_Timeout >> 0)  & 0xFF),((int)(Retranslator_Timeout >> 8) & 0xFF),
                              ((int)(Retranslator_Timeout >> 16) & 0xFF),((int)(Retranslator_Timeout >> 24) & 0xFF)};length = 6;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_RX_TIMEOUT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_RX_TIMEOUT";
qDebug() << s;
// ====================================
#endif
        int u[3] = {0xE2,0x01,0x00};length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_TX_TIMEOUT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_TX_TIMEOUT";
qDebug() << s;
// ====================================
#endif
        int u[3] = {0xE1,0x01,0x00}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SWITCH_LEVEL:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SWITCH_LEVEL";
qDebug() << s;
// ====================================
#endif
        int u[3] = {0xE0,0x01,0x00};length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SWITCH_LEVEL:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SWITCH_LEVEL";
qDebug() << s;
// ====================================
#endif
        int Retranslator_Level = Out_Retranslator_Properties->getRetranslator_Level();
        int u[6] = {0xE0,0x04,
                    ((Retranslator_Level >> 0)  & 0xFF),
                    ((Retranslator_Level >> 8)  & 0xFF),
                    ((Retranslator_Level >> 16) & 0xFF),
                    ((Retranslator_Level >> 24) & 0xFF)};
        length = 6;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_UPLINK_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_UPLINK_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xDA,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_UPLINK_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_UPLINK_MODE";
qDebug() << s;
// ====================================
#endif
        uchar UpLink_Value = Out_Sniffer_Properties->getUpLink_Value();
        int u[3] = {0xDA,0x01,(int)(UpLink_Value)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SNIFER_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SNIFER_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xD9,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SNIFER_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SNIFER_MODE";
qDebug() << s;
// ====================================
#endif
        uchar Sniffer_Mode = Out_Sniffer_Properties->getSniffer_Mode();
        int u[3] = {0xD9,0x01,(int)(Sniffer_Mode)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_INTERFACES_CONTROL:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_INTERFACES_CONTROL";
qDebug() << s;
// ====================================
#endif
        Interfaces_Control_Type Interfaces_Control = Out_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control();
        int u[6] = {0xD9,0x04,
                    (int)(Interfaces_Control.Word >> 0)  & 0xFF,
                    (int)(Interfaces_Control.Word >> 8)  & 0xFF,
                    (int)(Interfaces_Control.Word >> 16) & 0xFF,
                    (int)(Interfaces_Control.Word >> 24) & 0xFF
                   }; length = 6;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_BROADCASTING_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_BROADCASTING_MODE";
qDebug() << s;
// ====================================
#endif
        uchar Broadcasting = Out_Sniffer_Properties->getBroadcasting();
        int u[3] = {0xD8,0x01,(int)(Broadcasting)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_BROADCASTING_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_BROADCASTING_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xD8,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_MASK_DESTINATION:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_MASK_DESTINATION";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xD6,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_MASK_DESTINATION:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_MASK_DESTINATION";
qDebug() << s;
// ====================================
#endif
        uint Sniffer_Level_Destination =  Out_Sniffer_Properties->getSniffer_Level_Destination();
        int u[6] = {0xD6,0x04,
                   (int)(Sniffer_Level_Destination >> 0)  &0xFF,
                   (int)(Sniffer_Level_Destination >> 8)  &0xFF,
                   (int)(Sniffer_Level_Destination >> 16) &0xFF,
                   (int)(Sniffer_Level_Destination >> 24) &0xFF,
                   }; length = 6;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_BF_03_00_AC_00:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_03_00_AC_00";
qDebug() << s;
// ====================================
#endif
        int u[5] = {0xBF,0x03,0x00,0xAC,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        setCurrentSI4463_PROPERTYS_structur(0);
        break;
    }
    case SEND_BF_03_21_88_00:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_03_21_88_00";
qDebug() << s;
// ====================================
#endif
        int u[5] = {0xBF,0x03,0x21,0x88,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        setCurrentSI4463_PROPERTYS_structur(0);
        break;
    }
    case SEND_BF_03_00_AC_00_CALIB:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_03_00_AC_00_CALIB";
qDebug() << s;
// ====================================
#endif
        int u[5] = {0xBF,0x03,0x00,0xAC,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        setCurrentSI4463_PROPERTYS_structur(1);
        break;
    }
    case SEND_BF_03_21_88_00_CALIB:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_03_21_88_00_CALIB";
qDebug() << s;
// ====================================
#endif
        int u[5] = {0xBF,0x03,0x21,0x88,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        setCurrentSI4463_PROPERTYS_structur(1);
        break;
    }
    case SEND_BF_AF_00_AC_00:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_AF_00_AC_00";
qDebug() << s;
// ====================================
#endif
        setCurrentSI4463_PROPERTYS_structur(2);
        int u[5] = {0xBF,0xAF,0x00,0xAC,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        for(int i = 0; i < 0xAC; i++)
        {
            data.append(SI4463Conf->aSI4463_GET_PROPERTYS(0x00, 0x00, i, CurrentSI4463_PROPERTYS_structur));
        }

        break;
    }
    case SEND_BF_8B_21_88_00:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_8B_21_88_00";
qDebug() << s;
// ====================================
#endif
        setCurrentSI4463_PROPERTYS_structur(2);
        int u[5] = {0xBF,0x8B,0x21,0x88,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        for(int i = 0; i < 0x88; i++)
        {
            data.append(SI4463Conf->aSI4463_GET_PROPERTYS(0x21, 0x00, i, CurrentSI4463_PROPERTYS_structur));
        }

        break;
    }
    case SEND_BF_AF_00_AC_00_CALIB:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_AF_00_AC_00_CALIB";
qDebug() << s;
// ====================================
#endif
        setCurrentSI4463_PROPERTYS_structur(3);
        int u[5] = {0xBF,0xAF,0x00,0xAC,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        for(int i = 0; i < 0xAC; i++)
        {
            data.append(SI4463Conf->aSI4463_GET_PROPERTYS(0x00, 0x00, i, CurrentSI4463_PROPERTYS_structur));
        }

        break;
    }
    case SEND_BF_8B_21_88_00_CALIB:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_BF_8B_21_88_00_CALIB";
qDebug() << s;
// ====================================
#endif
        setCurrentSI4463_PROPERTYS_structur(3);
        int u[5] = {0xBF,0x8B,0x21,0x88,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        for(int i = 0; i < 0x88; i++)
        {
            data.append(SI4463Conf->aSI4463_GET_PROPERTYS(0x21, 0x00, i, CurrentSI4463_PROPERTYS_structur));
        }
        break;
    }
    case SEND_LOAD_PROPERTYS_TO_FLASH:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_LOAD_PROPERTYS_TO_FLASH";
qDebug() << s;
// ====================================
#endif
        int u[18] = {0xBE,0x10,'L','o','a','d','P','r','o','p','s','T','o','F','l','a','s','h'}; length = 18;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_PROPERTYS_FROM_FLASH:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_PROPERTYS_FROM_FLASH";
qDebug() << s;
// ====================================
#endif
        int u[20] = {0xBE,0x12,'R','e','a','d','P','r','o','p','s','F','r','o','m','F','l','a','s','h'}; length = 20;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        setCurrentSI4463_PROPERTYS_structur(0);
        break;
    }
    case SEND_LOAD_CALIBPROPS_TO_FLASH:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_LOAD_CALIBPROPS_TO_FLASH";
qDebug() << s;
// ====================================
#endif
        int u[18] = {0xBE,0x10,'L','o','a','d','C','a','l','P','r','T','o','F','l','a','s','h'}; length = 18;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_CALIBPROPS_FROM_FLASH:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_CALIBPROPS_FROM_FLASH";
qDebug() << s;
// ====================================
#endif
        int u[20] = {0xBE,0x12,'R','e','a','d','C','a','l','P','r','F','r','o','m','F','l','a','s','h'}; length = 20;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        setCurrentSI4463_PROPERTYS_structur(1);
        break;
    }
    case SEND_READ_CRC_CHECK_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_CRC_CHECK_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xBC,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_CRC_CHECK_MODE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_CRC_CHECK_MODE";
qDebug() << s;
// ====================================
#endif
        uchar CRC_Check_Disable = Out_Sniffer_Properties->getCRC_Check_Disable();
        int u[3] = {0xBC,0x01,(int)(CRC_Check_Disable)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_LRSSI_AFC_CURRENT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_LRSSI_AFC_CURRENT";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xBB,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SI4432_REGISTER:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SI4432_REGISTER";
qDebug() << s;
// ====================================
#endif
        RF_RegRead_struct RF_RegRead = SI4432Conf->getSI4432_RF_RegRead();

        int u[4] = {0xBB,0x02,RF_RegRead.MODE,RF_RegRead.REG}; length = 4;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SI4432_REGISTER:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SI4432_REGISTER";
qDebug() << s;
// ====================================
#endif
        RF_RegRead_struct RF_RegRead = SI4432Conf->getSI4432_RF_RegRead();

        int u[5] = {0xBB,0x03,RF_RegRead.MODE,RF_RegRead.REG,RF_RegRead.VALUE}; length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SI4432_09_REGISTER:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SI4432_09_REGISTER";
qDebug() << s;
// ====================================
#endif
        RF_RegRead_struct RF_RegRead;
        RF_RegRead.MODE = 0x00;
        RF_RegRead.REG  = 0x09;
        int u[4] = {0xBB,0x02,RF_RegRead.MODE,RF_RegRead.REG}; length = 4;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SI4432_09_REGISTER:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_SI4432_09_REGISTER";
qDebug() << s;
// ====================================
#endif
        RF_RegRead_struct RF_RegRead;
        RF_RegRead.MODE = 0x01;
        RF_RegRead.REG  = 0x09;
        RF_RegRead.VALUE = (unsigned char)(SI4432Conf->getOut_SI4432_RF_Config()->getSI4432_CLOAD());
        int u[5] = {0xBB,0x03,RF_RegRead.MODE,RF_RegRead.REG,RF_RegRead.VALUE}; length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_UPLINK_MODE_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_UPLINK_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xB7,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_UPLINK_MODE_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_UPLINK_MODE";
qDebug() << s;
// ====================================
#endif
        uchar UpLink_Value = Out_Sniffer_Properties->getUpLink_Value();
        int u[3] = {0xB7,0x01,(int)(UpLink_Value)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_INTERFACES_CONTROL_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_SNIFER_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xB6,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_INTERFACES_CONTROL_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_INTERFACES_CONTROL_NEW";
qDebug() << s;
// ====================================
#endif
        Interfaces_Control_Type Interfaces_Control = Out_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control();
        int u[6] = {0xB6,0x04,
                    (int)(Interfaces_Control.Word >> 0)  & 0xFF,
                    (int)(Interfaces_Control.Word >> 8)  & 0xFF,
                    (int)(Interfaces_Control.Word >> 16) & 0xFF,
                    (int)(Interfaces_Control.Word >> 24) & 0xFF
                   }; length = 6;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_BROADCASTING_MODE_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_BROADCASTING_MODE";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xB5,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_BROADCASTING_MODE_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_BROADCASTING_MODE";
qDebug() << s;
// ====================================
#endif
        uchar Broadcasting = Out_Sniffer_Properties->getBroadcasting();
        int u[3] = {0xB5,0x01,(int)(Broadcasting)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_MASK_DESTINATION_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_READ_MASK_DESTINATION";
qDebug() << s;
// ====================================
#endif
        int u[2] = {0xB3,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_MASK_DESTINATION_NEW:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_WRITE_MASK_DESTINATION";
qDebug() << s;
// ====================================
#endif
        uint Sniffer_Level_Destination =  Out_Sniffer_Properties->getSniffer_Level_Destination();
        int u[6] = {0xB3,0x04,
                   (int)(Sniffer_Level_Destination >> 0)  &0xFF,
                   (int)(Sniffer_Level_Destination >> 8)  &0xFF,
                   (int)(Sniffer_Level_Destination >> 16) &0xFF,
                   (int)(Sniffer_Level_Destination >> 24) &0xFF,
                   }; length = 6;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_CHOICE_MAIN_MODULE:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_CHOICE_MAIN_MODULE";
qDebug() << s;
// ====================================
#endif
        int u[9] = {0xB1,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    }
    this->Stop_Parceing = false;
    if (data.length() > 0){
        CRC16->CRC16_Add_To_ByteArray(&data);
        emit SEND_DATA(data,SendMode);
    }
}

void DataLogic_Class::ParceData(uint n)
{
    QString s;
    QByteArray AnswerH;
    for(unsigned int i = 0; i < 6; i++)
    {AnswerH.append((char)(0xFF));}

    QByteArray In_Data;
    uchar NumbOfBytes, Comande, ComandState;

    if (n == IN_INTERFACE_USO)
    {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "ParceData(IN_INTERFACE_USO)";
qDebug() << s;
// ====================================
#endif
        if (ParceDataBuffer.length() >= 7)
        {
            NumbOfBytes = ParceDataBuffer.at(6);
        }
        if (ParceDataBuffer.length() >= 9+NumbOfBytes-2)
        {
            Comande     = ParceDataBuffer.at(7);
            ComandState = ParceDataBuffer.at(8);
            In_Data.append(ParceDataBuffer.data()+9,NumbOfBytes-2);
        }
    }
    else if (n == IN_INTERFACE_RF_PLC)
    {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "ParceData(IN_INTERFACE_RF_PLC)";
qDebug() << s;
// ====================================
#endif
        if (ParceDataBuffer.length() >= 7+4)
        {
            NumbOfBytes = ParceDataBuffer.at(6+4);
        }
        if (ParceDataBuffer.length() >= 9+4+NumbOfBytes-2)
        {
            Comande     = ParceDataBuffer.at(7+4);
            ComandState = ParceDataBuffer.at(8+4);
            In_Data.append(ParceDataBuffer.data()+9+4,NumbOfBytes-2);
        }
    }
    else if (n == IN_SNIFER_PLUS_PREAMBLE)
    {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "ParceData(IN_SNIFER_PLUS_PREAMBLE)";
qDebug() << s;
// ====================================
#endif
        s = "Преамбула не определена";
        if (ParceDataBuffer.length() >= 5)
        {
            RF_Preamble.Field.Msg_Length = ParceDataBuffer.at(4);
        }
        if (ParceDataBuffer.length() >= 36)
        {
            for(int i = 4; i < 32; i++)
            {
                RF_Preamble.Byte_Array[i-4]     = (uchar)(ParceDataBuffer.at(i));
                RF_Preamble_new.Byte_Array[i-4] = (uchar)(ParceDataBuffer.at(i));
            }
            /* Старая преамбула
            s.clear();
            s.append("Длина пакета: " + QString::number(RF_Preamble.Field.Msg_Length) + "\r");
            s.append("Номер сообщения: " + QString::number(RF_Preamble.Field.Msg_Uniq_Number) + "\r");
            s.append("Уровень сети: " + QString::number(RF_Preamble.Field.Retranslator_Level) + "\r");
            s.append("Уровень сети опрашиваемого прибора: " + QString::number(RF_Preamble.Field.Finish_Retranslator_Level) + "\r");
            s.append("Серийный номер последнего ретранслятора: " + QString::number(RF_Preamble.Field.Last_Retranslator_Net_Address) + "\r");
            s.append("RSSI USB/RF Преобразователя: " + QString::number((double)(RF_Preamble.Field.in_RSSI)/10) + "\r");
            s.append("RSSI опрашиваемого прибора: " + QString::number((double)(RF_Preamble.Field.Finish_RSSI)/10) + "\r");
            s.append("Серийный номер источника: " + QString::number(RF_Preamble.Field.Source_Net_Address) + "\r");
            s.append("Серийный номер приёмника: " + QString::number(RF_Preamble.Field.Destination_Net_Address) + "\r");
            s.append("Направление: " + QString::number((uchar)(RF_Preamble.Field.UP_Link)) + "\r");
            s.append("КОД широковещания: " + QString::number(RF_Preamble.Field.broadcasting) + "\r");
            s.append("Debug: RX_Buffer_current_counter: " + QString::number(RF_Preamble.Field.RX_Buffer_current_counter) + "\r");
            */

            s.clear();
            s.append("Длина пакета: "   + QString::number(RF_Preamble_new.Field.Msg_Length) + "\r");
            s.append("Номер сообщения: " + QString::number(RF_Preamble_new.Field.Msg_Uniq_Number) + "\r");
            s.append("Уровень сети: "    + QString::number(RF_Preamble_new.Field.Retranslator_Level) + "\r");
            s.append("Маска сети: "      + QString::number(RF_Preamble_new.Field.Retranslation_MASK_0.Field.LVL0) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_0.Field.LVL1) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_1.Field.LVL2) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_1.Field.LVL3) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_0.Field.LVL4) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_0.Field.LVL5) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_1.Field.LVL6) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_1.Field.LVL7) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_0.Field.LVL8) + "."
                                         + QString::number(RF_Preamble_new.Field.Retranslation_MASK_1.Field.LVL9) + "."
                     + "\r");
            s.append("Серийный номер источника: "                + QString::number(RF_Preamble_new.Field.Source_Net_Address) + "\r");
            s.append("Серийный номер последнего ретранслятора: " + QString::number(RF_Preamble_new.Field.Last_Retranslator_Net_Address) + "\r");
            s.append("Серийный номер приёмника: "                + QString::number(RF_Preamble_new.Field.Destination_Net_Address) + "\r");
            if (RF_Preamble_new.Field.UP_Link == 0)
            {
                s.append("Направление: "                             + QString::number((uchar)(RF_Preamble_new.Field.UP_Link)) + " >> К счётчику" + "\r");
            }
            else
            {
                s.append("Направление: "                             + QString::number((uchar)(RF_Preamble_new.Field.UP_Link)) + " От счётчика >>" + "\r");
            }
            s.append("RSSI USB/RF Преобразователя: "             + QString::number((double)(RF_Preamble_new.Field.in_RSSI)/10) + "\r");
            s.append("RSSI опрашиваемого прибора: "              + QString::number((double)(RF_Preamble_new.Field.Finish_RSSI)/10) + "\r");
            s.append("КОД широковещания: "                       + QString::number(RF_Preamble_new.Field.broadcasting) + "\r");
        }
        if (ParceDataBuffer.length() >= RF_Preamble.Field.Msg_Length + 12)
        {
            NumbOfBytes = ParceDataBuffer.at(6+4+28+4);
            Comande     = ParceDataBuffer.at(7+4+28+4);
            ComandState = ParceDataBuffer.at(8+4+28+4);
            In_Data.append(ParceDataBuffer.data()+4+28,RF_Preamble.Field.Msg_Length-26);
        }

        emit LogForPrint(s,NONE);
        emit DataForPrint(In_Data,COM_RX);     // Вывод данных в консоль

        In_Data.clear();
        In_Data.append(ParceDataBuffer.data()+9+4+28+4,RF_Preamble.Field.Msg_Length-26-9-4);
        SEND_MODE = MANUAL_SEND_CONTROL;
    }
    //if (n != IN_SNIFER_PLUS_PREAMBLE)
    //{
        switch (Comande)
        {
        case 0xFF: // Запрос версий ПО
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xFF - Запрос версий ПО";
qDebug() << s;
// ====================================
#endif
            QByteArray BOOT_CRC32, FW_CRC32;

            if (In_Data.length() >= 19)
            {
                FirmwareInformationClass      *In_Firmware_Information = MODEM->getIn_Firmware_Information();

                In_Firmware_Information->setCurrent_Firmware_Version(ComandState);
                In_Firmware_Information->setString_Bootloader_Version(QString::fromUtf8(In_Data.data(),4));

                if (NumbOfBytes == 0x16)
                {
                    In_Firmware_Information->setBootloader_Size(((In_Data.at(5) & 0xFF) << 8)|((In_Data.at(4) & 0xFF) << 0));

                    BOOT_CRC32.append(In_Data.at(9));
                    BOOT_CRC32.append(In_Data.at(8));
                    BOOT_CRC32.append(In_Data.at(7));
                    BOOT_CRC32.append(In_Data.at(6));

                    In_Firmware_Information->setBootloader_CRC32(BOOT_CRC32);

                    In_Firmware_Information->setString_Upgradable_Version(QString::fromUtf8(In_Data.data()+10,4));

                    In_Firmware_Information->setUpgradable_Size(((In_Data.at(15) & 0xFF) << 8)|((In_Data.at(14) & 0xFF) << 0));

                    FW_CRC32.append(In_Data.at(19));
                    FW_CRC32.append(In_Data.at(18));
                    FW_CRC32.append(In_Data.at(17));
                    FW_CRC32.append(In_Data.at(16));

                    In_Firmware_Information->setUpgradable_CRC32(FW_CRC32);
                }
                else if (NumbOfBytes == 0x1A)
                {
                    In_Firmware_Information->setBootloader_Size(((In_Data.at(7) & 0xFF) << 24)|((In_Data.at(6) & 0xFF) << 16)|
                                                                ((In_Data.at(5) & 0xFF) << 8)|((In_Data.at(4) & 0xFF) << 0));

                    BOOT_CRC32.append(In_Data.at(11));
                    BOOT_CRC32.append(In_Data.at(10));
                    BOOT_CRC32.append(In_Data.at(9));
                    BOOT_CRC32.append(In_Data.at(8));

                    In_Firmware_Information->setBootloader_CRC32(BOOT_CRC32);

                    In_Firmware_Information->setString_Upgradable_Version(QString::fromUtf8(In_Data.data()+12,4));

                    In_Firmware_Information->setUpgradable_Size(((In_Data.at(19) & 0xFF) << 24)| ((In_Data.at(18) & 0xFF) << 16)|
                                                                ((In_Data.at(17) & 0xFF) << 8) | ((In_Data.at(16) & 0xFF) << 0));

                    FW_CRC32.append(In_Data.at(23));
                    FW_CRC32.append(In_Data.at(22));
                    FW_CRC32.append(In_Data.at(21));
                    FW_CRC32.append(In_Data.at(20));

                    In_Firmware_Information->setUpgradable_CRC32(FW_CRC32);
                }

                MODEM->ChangedIn_Firmware_Information();

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,1,SEND_MODE);
                }
            }

            break;
        }
        case 0xFE: // Перезагрузка в Бутлоадер
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xFE - Перезагрузка в Бутлоадер";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit SendLog(QString::fromUtf8(">> ======= Ожидание перехода в BOOT:"),NONE);
                    if (MODEM->getIn_Firmware_Information()->getCurrent_Firmware_Version() == 0)
                    {
                        BOOT_WAIT_COUNTER = 1;
                    }
                    else
                    {
                        BOOT_WAIT_COUNTER = 5;
                    }
                    emit SendLog(QString::fromUtf8(" > ") + QString::number(BOOT_WAIT_COUNTER),NONE);
                    BOOT_WAIT->start(1000);
                }
            }
            break;
        }
        case 0xFC: // Запись сектора
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xFC - Запись сектора";
qDebug() << s;
// ====================================
#endif
            if (In_Data.length() >= 2)
            {
                if ((ComandState == nUPDATE->getCurrent_BLOCK())&&(In_Data.at(0) == nUPDATE->getCurrent_SECTOR())&&(In_Data.at(1) == 1))
                {
                    if (nUPDATE->getSIZE() > nUPDATE->getWrited_BYTES())
                    {
                        //if (this->stop)
                        //{
                        //    this->stop = false;
                        //    Repeat_Counter = Repeat_Number;
                        //    timerRepeat->stop();

                        //    Repeat_Counter = Repeat_Number;
                        //    nUPDATE->incCurrent_SECTOR();
                        //}
                        //else
                        //{
                            Repeat_Counter = Repeat_Number;
                            uint progr = 90*nUPDATE->getWrited_BYTES()/nUPDATE->getSIZE();
                            emit outPROGRESS(progr);
                            nUPDATE->incCurrent_SECTOR();
                            emit outConnect(DataLogicMode,0,SEND_MODE);
                            //ComandHandling(SEND_WRITE_SECTOR,CONFIG_SEND_CONTROL);
                        //}

                    }
                    else
                    {
                        Repeat_Counter = Repeat_Number;
                        timerRepeat->stop();

                        if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                        {
                            emit SendLog(QString::fromUtf8(">> ======= Ожидание перехода на обновлённую прошивку:"),NONE);
                            if (MODEM->getIn_Firmware_Information()->getBootloader_Version() == 0) {
                                BOOT_WAIT_COUNTER = 5;
                            }
                            else {
                                BOOT_WAIT_COUNTER = 15;
                            }
                            emit SendLog(QString::fromUtf8(" > ") + QString::number(BOOT_WAIT_COUNTER),NONE);
                            BOOT_WAIT->start(1000);
                        }
                    }
                }
                // нет подтверждения удачной записи блока
                else if ((ComandState == nUPDATE->getCurrent_BLOCK())&&(In_Data.at(0) == nUPDATE->getCurrent_SECTOR())&&(In_Data.at(1) != 1))
                {
                    // тогда возвращаемся в самое начало обновления
                    emit outConnect(DataLogicMode,0,SEND_MODE);
                }
            }
            break;
        }
        case 0xFB: // Запись информации о прошивке
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xFB - Запись информации о прошивке";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xFA: // Удаление прошивки
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xFA - Удаление прошивки";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xF9: // Запрос количества записанных страниц и CRC
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xF9 - Запрос количества записанных страниц и CRC";
qDebug() << s;
// ====================================
#endif
            uint IN_PAGES     = 0;
            uint IN_PAGE_SIZE = 0;
            uint IN_CRC32     = 0;
            if (ComandState == 1)
            {
                if (In_Data.length() >= 9)
                {
                    IN_PAGES     = (In_Data.at(0) & 0xFF);
                    IN_PAGE_SIZE = ((In_Data.at(4) & 0xFF) << 24)|((In_Data.at(3) & 0xFF) << 16)|((In_Data.at(2) & 0xFF) << 8)|((In_Data.at(1) & 0xFF) << 0);
                    IN_CRC32     = ((In_Data.at(8) & 0xFF) << 24)|((In_Data.at(7) & 0xFF) << 16)|((In_Data.at(6) & 0xFF) << 8)|((In_Data.at(5) & 0xFF) << 0);
                }
            }
            nUPDATE->Compare_Writed_PAGES_CRC32(IN_PAGES,IN_PAGE_SIZE,IN_CRC32);

            Repeat_Counter = Repeat_Number;
            timerRepeat->stop();

            if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
            {
                emit outConnect(DataLogicMode,1,SEND_MODE);
            }

            break;
        }
        case 0xF1: // Выбор основного интерфейсного модуля
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xF1 - Выбор основного интерфейсного модуля";
qDebug() << s;
// ====================================
#endif
            Repeat_Counter = Repeat_Number;
            timerRepeat->stop();

            if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
            {
                emit outConnect(DataLogicMode,1,SEND_MODE);
            }
            break;
        }
        case 0xF0: // Запрос режима ретрансляции
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xF0 - Запрос режима ретрансляции";
qDebug() << s;
// ====================================
#endif
            if (MODEM->getIn_Retranslator_Properties()->getRetranslator_Mode() != ComandState){
                MODEM->getIn_Retranslator_Properties()->setRetranslator_Mode(ComandState);
                MODEM->ChangedIn_Retranslator_Properties();
            }

            Repeat_Counter = Repeat_Number;
            timerRepeat->stop();

            if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
            {
                emit outConnect(DataLogicMode,1,SEND_MODE);
            }
            break;
        }
        case 0xEF: // Запись режима ретрансляции
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xEF - Запись режима ретрансляции";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xEE: // Считывание параметров PLC Модедма
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xEE - Считывание параметров PLC Модедма";
qDebug() << s;
// ====================================
#endif
            ST750ConfigurationClass      *In_ST750_PLC_Config = PLCConf->getIn_ST750_PLC_Config();
            uint temp = 0;
            TX_Conditions_Type Transmit_Conditions;
            if (In_Data.length() >= 5)
            {
                if (NumbOfBytes == 7){
                    temp = ((In_Data.at(4) & 0xFF) << 16)|((In_Data.at(3) & 0xFF) << 8)|((In_Data.at(2) & 0xFF) << 0);
                    In_ST750_PLC_Config->setST750_LOWF(temp);
                    temp = ((In_Data.at(1) & 0xFF) << 16)|((In_Data.at(0) & 0xFF) << 8)|((ComandState & 0xFF) << 0);
                    In_ST750_PLC_Config->setST750_HIGHF(temp);
                }
                else if (NumbOfBytes == 9){
                    Transmit_Conditions.HalbWord = ((In_Data.at(6) & 0xFF) << 8)|((In_Data.at(5) & 0xFF) << 0);
                    In_ST750_PLC_Config->setST750_Transmit_Conditions(Transmit_Conditions);
                    temp = ((In_Data.at(4) & 0xFF) << 16)|((In_Data.at(3) & 0xFF) << 8)|((In_Data.at(2) & 0xFF) << 0);
                    In_ST750_PLC_Config->setST750_LOWF(temp);
                    temp = ((In_Data.at(1) & 0xFF) << 16)|((In_Data.at(0) & 0xFF) << 8)|((ComandState & 0xFF) << 0);
                    In_ST750_PLC_Config->setST750_HIGHF(temp);
                }

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    PLCConf->ChangedIn_ST750_PLC_Config();
                    emit outConnect(DataLogicMode,1,SEND_MODE);
                }
            }
            break;
        }
        case 0xED: // Записть параметров PLC Модедма
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xED - Записть параметров PLC Модедма";
qDebug() << s;
// ====================================
#endif
            if ((ComandState == 1)||(ComandState == 2))
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,1,SEND_MODE);
                }
            }
            break;
        }
        case 0xEC: // Cчитывание серийного адреса устройства
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xEC - Cчитывание серийного адреса устройства";
qDebug() << s;
// ====================================
#endif
            break;
        }
        case 0xEB: // Чтение Элемента таблицы ретрансляции
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xEB - Чтение Элемента таблицы ретрансляции";
qDebug() << s;
// ====================================
#endif
            if((NumbOfBytes == 6)&&(In_Data.length() >= 4))
            {
                uint SWT_Element = ((In_Data.at(0) & 0xFF) << 0)|((In_Data.at(1)& 0xFF) << 8)|((In_Data.at(2)& 0xFF) << 16)|((In_Data.at(3)& 0xFF) << 24);
                if ((SWT_Element > 0)&&(SWT_Element < 0xFFFFFFFF)&&
                    (MODEM->getIn_Retranslator_Properties()->getRetranslator_Table_Current_Index() < 100))
                {
                    //if (this->stop)
                    //{
                    //    this->stop = false;
                    //    Repeat_Counter = Repeat_Number;
                    //    timerRepeat->stop();

                    //    Repeat_Counter = Repeat_Number;
                    //    MODEM->addNewItem(QString::number(SWT_Element));
                    //}
                    //else
                    //{
                        Repeat_Counter = Repeat_Number;

                        MODEM->getIn_Retranslator_Properties()->addNewItemToRetranslation_Table(QString::number(SWT_Element));
                        MODEM->ChangedIn_Retranslator_Properties();
                        emit outConnect(DataLogicMode,0,SEND_MODE);
                        //ComandHandling(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                    //}
                }
                else
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                    {
                        emit outConnect(DataLogicMode,1,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xEA: // Запись Элемента таблицы ретрансляции в буфер для записи
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xEA - Запись Элемента таблицы ретрансляции в буфер для записи";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if(MODEM->getOut_Retranslator_Properties()->getRetranslator_Table_Current_Index() <
                   MODEM->getOut_Retranslator_Properties()->getRetranslator_Table().length()-1){
                    //if (this->stop)
                    //{
                    //    this->stop = false;
                    //    Repeat_Counter = Repeat_Number;
                    //    timerRepeat->stop();

                    //    uchar temp = MODEM->getCurrent_Index() + 1;
                    //    MODEM->setCurrent_Index(temp);
                    //}
                    //else
                    //{
                        Repeat_Counter = Repeat_Number;

                        uchar temp = MODEM->getOut_Retranslator_Properties()->getRetranslator_Table_Current_Index();
                        temp += 1;
                        MODEM->getOut_Retranslator_Properties()->setRetranslator_Table_Current_Index(temp);
                        emit outConnect(DataLogicMode,0,SEND_MODE);
                        //ComandHandling(SEND_WRITE_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                    //}
                }
                else{
                    MODEM->getOut_Retranslator_Properties()->clearRetranslation_Table();
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();
                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                        emit outConnect(DataLogicMode,1,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xE9: // Стирание таблицы ретрансляции из флэш памяти модема
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE9 - Стирание таблицы ретрансляции из флэш памяти модема";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                MODEM->getIn_Retranslator_Properties()->clearRetranslation_Table();
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xE8: // Запись таблицы ретрансляции во флэш память модема из буфера
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE8 - Запись таблицы ретрансляции во флэш память модема из буфера";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xE7: // Запсиь RF Параметров SI4432
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE7 - Запсиь RF Параметров SI4432";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if (NumbOfBytes == 0x09)
                {
                    RealTime In_LastAOPEN;
                    In_LastAOPEN.Filed.Seconds = In_Data.at(0);
                    In_LastAOPEN.Filed.Minutes = In_Data.at(1);
                    In_LastAOPEN.Filed.Hours   = In_Data.at(2);
                    In_LastAOPEN.Filed.WeekDay = In_Data.at(3);
                    In_LastAOPEN.Filed.Day     = In_Data.at(4);
                    In_LastAOPEN.Filed.Month   = In_Data.at(5);
                    In_LastAOPEN.Filed.Year    = In_Data.at(6);

                    MODEM->getIn_PLC_RF433_Modem_Properties()->setLastAOPENTime(In_LastAOPEN);
                    MODEM->ChangedIn_PLC_RF433_Modem_Properties();
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
           break;
        }
        case 0xE6: // Чтение RF Параметров SI4432
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE6 - Чтение RF Параметров SI4432";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if (In_Data.length() >= NumbOfBytes-3){
                    // если кол-во байт 6 - значит параметры Debug_Control PLC-RF433 Модуля
                    if (NumbOfBytes == 0x06){
                        Debug_Control_Type In_DEBUG_Control;
                        In_DEBUG_Control.Word = (((uint)(In_Data.at(0)) &0xFF) << 0)|(((uint)(In_Data.at(1)) &0xFF) << 8)|(((uint)(In_Data.at(2)) &0xFF) << 16)|(((uint)(In_Data.at(3)) &0xFF) << 24);
                        MODEM->getIn_PLC_RF433_Modem_Properties()->setPLC_RF433_Debug_Control(In_DEBUG_Control);
                        MODEM->ChangedIn_PLC_RF433_Modem_Properties();
                    }
                    else if (NumbOfBytes == 0x1C){
                        RF_Config_struct RF_Config = SI4432Conf->getIn_SI4432_RF_Config()->getRF_Config_struct();

                        RF_Config.RF_CONF_REG_1.reg = (((uint)(In_Data.at(0)) &0xFF) << 0)|(((uint)(In_Data.at(1)) &0xFF) << 8)|(((uint)(In_Data.at(2)) &0xFF) << 16)|(((uint)(In_Data.at(3)) &0xFF) << 24);
                        RF_Config.RF_CONF_REG_2.reg = (((uint)(In_Data.at(4)) &0xFF) << 0)|(((uint)(In_Data.at(5)) &0xFF) << 8)|(((uint)(In_Data.at(6)) &0xFF) << 16)|(((uint)(In_Data.at(7)) &0xFF) << 24);
                        RF_Config.RF_NOM_FREQUENC   = (((uint)(In_Data.at(8)) &0xFF) << 0)|(((uint)(In_Data.at(9)) &0xFF) << 8)|(((uint)(In_Data.at(10))&0xFF) << 16)|(((uint)(In_Data.at(11))&0xFF) << 24);
                        RF_Config.RF_SYNCH_WORD     = (((uint)(In_Data.at(12))&0xFF) << 0)|(((uint)(In_Data.at(13))&0xFF) << 8)|(((uint)(In_Data.at(14))&0xFF) << 16)|(((uint)(In_Data.at(15))&0xFF) << 24);
                        RF_Config.RF_RX_HAEDER      = (((uint)(In_Data.at(16))&0xFF) << 0)|(((uint)(In_Data.at(17))&0xFF) << 8)|(((uint)(In_Data.at(18))&0xFF) << 16)|(((uint)(In_Data.at(19))&0xFF) << 24);
                        RF_Config.RF_TX_HAEDER      = (((uint)(In_Data.at(20))&0xFF) << 0)|(((uint)(In_Data.at(21))&0xFF) << 8)|(((uint)(In_Data.at(22))&0xFF) << 16)|(((uint)(In_Data.at(23))&0xFF) << 24);

                        SI4432Conf->getIn_SI4432_RF_Config()->setRF_Config_struct(RF_Config);
                        SI4432Conf->ChangedIn_SI4432_RF_Config();
                    }
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xE5: // Чтение Latch RSSI
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE5 - Чтение Latch RSSI";
qDebug() << s;
// ====================================
#endif
            signed short RSSI = 100;
            signed short ANT1_RSSI = 100;
            signed short ANT2_RSSI = 100;

            if (In_Data.length() >= 2)
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_0 = In_Data.at(0);
                SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_1 = In_Data.at(1);

                RSSI = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_1) << 8)
                                    | (SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_0);
            }

            signed int AFC = 0;

            if ((NumbOfBytes == 6)&&In_Data.length() >= 4)
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0 = In_Data.at(2);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1 = In_Data.at(3);
                AFC = ((signed int)  (SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1) << 8)
                                   | (SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0);
                if ((AFC & (1 << 15)))
                {
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2 = 0xFF;
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3 = 0xFF;
                    AFC |= 0xFFFF0000;
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outLRSSI_AFC(RSSI,ANT1_RSSI,ANT2_RSSI,(double)(AFC));
            }
            else if ((NumbOfBytes == 8)&&(In_Data.length() >= 6))
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0 = In_Data.at(2);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1 = In_Data.at(3);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2 = In_Data.at(4);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3 = In_Data.at(5);

                AFC = ((signed int) (SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3) << 24)
                                  | ((SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2) << 16)
                                  | ((SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1) << 8)
                                  |  (SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0);

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                ANT1_RSSI = RSSI;
                ANT2_RSSI = 100;
                emit outLRSSI_AFC(RSSI,ANT1_RSSI,ANT2_RSSI,(double)(AFC));
                emit outLPGA(RSSI,(double)(AFC));
            }
            else if ((NumbOfBytes == 10)&&(In_Data.length() >= 8))
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.ANT1_RSSI.Field.ANT1_RSSI_0 = In_Data.at(2);
                SI4463Conf->aSI4463_INTERUPTS()->Field.ANT1_RSSI.Field.ANT1_RSSI_1 = In_Data.at(3);

                SI4463Conf->aSI4463_INTERUPTS()->Field.ANT2_RSSI.Field.ANT2_RSSI_0 = In_Data.at(4);
                SI4463Conf->aSI4463_INTERUPTS()->Field.ANT2_RSSI.Field.ANT2_RSSI_1 = In_Data.at(5);

                ANT1_RSSI = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.ANT1_RSSI.Field.ANT1_RSSI_1) << 8)
                                         | (SI4463Conf->aSI4463_INTERUPTS()->Field.ANT1_RSSI.Field.ANT1_RSSI_0);
                ANT2_RSSI = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.ANT2_RSSI.Field.ANT2_RSSI_1) << 8)
                                         | (SI4463Conf->aSI4463_INTERUPTS()->Field.ANT2_RSSI.Field.ANT2_RSSI_0);

                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0 = In_Data.at(6);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1 = In_Data.at(7);
                AFC = ((signed int)  (SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1) << 8)
                                   | (SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0);
                if ((AFC & (1 << 15)))
                {
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2 = 0xFF;
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3 = 0xFF;
                    AFC |= 0xFFFF0000;
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                emit outLRSSI_AFC(RSSI,ANT1_RSSI,ANT2_RSSI,(double)(AFC));
            }
            else{
                ANT1_RSSI = RSSI;
                ANT2_RSSI = 100;
                emit outLRSSI_AFC(RSSI,ANT1_RSSI,ANT2_RSSI,(double)(AFC));
            }
            break;
        }
        case 0xE4: // Modem Reset
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE4 - Modem Reset";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xE3:
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE3 - SWITCH_TIMEOUT";
qDebug() << s;
// ====================================
#endif
            if ((NumbOfBytes == 6)&&(In_Data.length() >= 4))
            {
                uint SWITCH_TIMEOUT     = 0;
                SWITCH_TIMEOUT    |= *((uint*)(In_Data.data()));

                if (MODEM->getIn_Retranslator_Properties()->getRetranslator_Timeout() != SWITCH_TIMEOUT){
                    MODEM->getIn_Retranslator_Properties()->setRetranslator_Timeout(SWITCH_TIMEOUT);
                    MODEM->ChangedIn_Retranslator_Properties();
                }

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            else if (NumbOfBytes == 2)
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                    {
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xE2: // Таймаут RX
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE2 - RX_TIMEOUT";
qDebug() << s;
// ====================================
#endif
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                uint RX_TIMEOUT       = 0;
                RX_TIMEOUT           |= *((uint*)(In_Data.data()));

                if ( MODEM->getIn_Modem_Properties()->getRF_RX_Timeout() != RX_TIMEOUT){
                    MODEM->getIn_Modem_Properties()->setRF_RX_Timeout(RX_TIMEOUT);
                    MODEM->ChangedIn_Modem_Properties();
                }

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState,SEND_MODE);
            }
            else if (NumbOfBytes == 2)
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                    {
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xE1:{ // Таймаут TX
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE1 - TX_TIMEOUT";
qDebug() << s;
// ====================================
#endif
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4)){
                uint TX_TIMEOUT       = 0;
                TX_TIMEOUT           |= *((uint*)(In_Data.data()));

                if ( MODEM->getIn_Modem_Properties()->getRF_TX_Timeout() != TX_TIMEOUT){
                    MODEM->getIn_Modem_Properties()->setRF_TX_Timeout(TX_TIMEOUT);
                    MODEM->ChangedIn_Modem_Properties();
                }

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            else if (NumbOfBytes == 2){
                if (ComandState == 1){
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xE0:{ // Уровень свича
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xE0 - Уровень свича";
qDebug() << s;
// ====================================
#endif
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4)){
                if (MODEM->getIn_Retranslator_Properties()->getRetranslator_Level() != *((uint*)(In_Data.data()))){
                    MODEM->getIn_Retranslator_Properties()->setRetranslator_Level(*((uint*)(In_Data.data())));
                    MODEM->ChangedIn_Retranslator_Properties();
                }

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            else if (NumbOfBytes == 2){
                if (ComandState == 1){
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xDA:{ // Установить UP_Linc  (только для снифера)
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xDA - Установить UP_Linc";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if (NumbOfBytes == 3){
                    if (MODEM->getIn_Sniffer_Properties()->getUpLink_Value() != (uchar)(In_Data.at(0))){
                        MODEM->getIn_Sniffer_Properties()->setUpLink_Value((uchar)(In_Data.at(0)));
                        MODEM->ChangedIn_Sniffer_Properties();
                    }
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        // Режим пропускания сообщений (только для снифера)
        case 0xD9:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xD9 - Режим пропускания сообщений";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if (NumbOfBytes == 3){
                    if (MODEM->getIn_Sniffer_Properties()->getSniffer_Mode() != (uchar)(In_Data.at(0))){
                        MODEM->getIn_Sniffer_Properties()->setSniffer_Mode((uchar)(In_Data.at(0)));
                        MODEM->ChangedIn_Sniffer_Properties();
                    }
                }
                if (NumbOfBytes == 6){
                    Interfaces_Control_Type In_Interfaces_Control;
                    In_Interfaces_Control.Word = (((uint)(In_Data.at(0)) &0xFF) << 0)|(((uint)(In_Data.at(1)) &0xFF) << 8)|(((uint)(In_Data.at(2)) &0xFF) << 16)|(((uint)(In_Data.at(3)) &0xFF) << 24);
                    MODEM->getIn_PLC_RF433_Modem_Properties()->setPLC_RF433_Interfaces_Control(In_Interfaces_Control);
                    MODEM->ChangedIn_PLC_RF433_Modem_Properties();
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        // Режим широковещания (только для снифера)
        case 0xD8:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xD8 - Режим широковещания";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if (NumbOfBytes == 3){
                    if (MODEM->getIn_Sniffer_Properties()->getBroadcasting() != (uchar)(In_Data.at(0))){
                        MODEM->getIn_Sniffer_Properties()->setBroadcasting((uchar)(In_Data.at(0)));
                        MODEM->ChangedIn_Sniffer_Properties();
                    }
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xD6: // Записать маску назначения (только для снифера)
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xD6 - Записать маску назначения";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if (In_Data.length() >= 4){
                    uint mask = 0;
                    mask |= *((uint*)(In_Data.data()));
                    if (MODEM->getIn_Sniffer_Properties()->getSniffer_Level_Destination() != mask){
                        MODEM->getIn_Sniffer_Properties()->setSniffer_Level_Destination(mask);
                        MODEM->ChangedIn_Sniffer_Properties();
                    }
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xBF: // Чтение свойств SI4463 из памяти RF модэма v5+, или запись свойств в буфер
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xBF - Чтение свойств SI4463 из памяти RF модэма v5+, или запись свойств в буфер";
qDebug() << s;
// ====================================
#endif
            if (NumbOfBytes > 2)
            {
                if (In_Data.length() >= 2)
                {
                    uchar GROUP       = ComandState;
                    uchar NUM_PROPS   = In_Data.at(0);
                    uchar START_PROP  = In_Data.at(1);
                    //uchar *group_adress = SI4463Conf->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP);
                    if ((NumbOfBytes - 4) == NUM_PROPS)
                    {
                        if (In_Data.length() >= NUM_PROPS+1)
                        {
                            for (uint i = 0; i < NUM_PROPS; i++)
                            {
                                SI4463Conf->aSI4463_SET_PROPERTYS(GROUP, START_PROP, i, *(In_Data.data()+i+2),CurrentSI4463_PROPERTYS_structur);
                            }
                        }
                    }
                }
                uint FreqMHZ = GetFreqMHZ(SI4463Conf->aSI4463_PROPERTYS());
                uint DataRate = GetDataRate(SI4463Conf->aSI4463_PROPERTYS());
                uint FDevHz = GetFDevHz(SI4463Conf->aSI4463_PROPERTYS());
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,1,SEND_MODE);
                }
            }
            else
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                    {
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
            }
            break;
        }
        case 0xBE: // Запись свойств SI4463 из флэша в RAM и наоборот в RF модэмах v5+
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xBE - Запись свойств SI4463 из флэша в RAM и наоборот в RF модэмах v5+";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xBD: // Установка логики мигания светодиодов
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xBE - Установка логики мигания светодиодов";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                if (NumbOfBytes == 3)
                {

                }

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xBC: // Отключение проверки CRC
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xBC - Отключение проверки CRC";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1)
            {
                if (NumbOfBytes == 3){
                    if (MODEM->getIn_Sniffer_Properties()->getCRC_Check_Disable() != (uchar)(In_Data.at(0))){
                        MODEM->getIn_Sniffer_Properties()->setCRC_Check_Disable((uchar)(In_Data.at(0)));
                        MODEM->ChangedIn_Sniffer_Properties();
                    }
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                {
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
        case 0xBB: // Current RSSI SI4463 или регистры SI4432
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xBB - Current RSSI SI4463 или регистры SI4432";
qDebug() << s;
// ====================================
#endif
          if(In_Data.length() == 1) //Запись регистров SI4432
          {
              if (ComandState == 1)
              {
                  RF_RegRead_struct RF_RegRead = SI4432Conf->getSI4432_RF_RegRead();

                  RF_RegRead.MODE = 0x01;           // Запись
                  RF_RegRead.REG  = In_Data.at(0);  // Адрес

                  SI4432Conf->setSI4432_RF_RegRead(RF_RegRead);

                  Repeat_Counter = Repeat_Number;
                  timerRepeat->stop();
                  if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                  {
                      emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                  }
              }
          }
          if(In_Data.length() == 2) //Чтение регистров SI4432
          {
              if (ComandState == 1)
              {
                  RF_RegRead_struct RF_RegRead = SI4432Conf->getSI4432_RF_RegRead();

                  RF_RegRead.MODE  = 0x00;          // Чтение
                  RF_RegRead.REG   = In_Data.at(0); // Адрес
                  RF_RegRead.VALUE = In_Data.at(1); // Значение

                  SI4432Conf->setSI4432_RF_RegRead(RF_RegRead);

                  Repeat_Counter = Repeat_Number;
                  timerRepeat->stop();

                  if(RF_RegRead.REG == 0x09)
                  {
                      SI4432Conf->getIn_SI4432_RF_Config()->setSI4432_CLOAD(RF_RegRead.VALUE);
                  }
                  if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
                  {
                      emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                  }
              }
          }
          if(In_Data.length() == 2) // Чтение Current RSSI SI4463
          {
              signed short RSSI = 0;
              SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_0 = In_Data.at(0);
              SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_1 = In_Data.at(1);

              RSSI = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_1) << 8)
                                  | (SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_0);

              Repeat_Counter = Repeat_Number;
              timerRepeat->stop();

              emit outCurrentRSSI(RSSI);
          }
          break;
        }
        case 0xB7:{ // Установить UP_Linc  (только для снифера)
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xB7 - Установить UP_Linc";
qDebug() << s;
// ====================================
#endif
            if (ComandState == 1){
                if (NumbOfBytes == 3){
                    if (MODEM->getIn_Sniffer_Properties()->getUpLink_Value() != (uchar)(In_Data.at(0))){
                        MODEM->getIn_Sniffer_Properties()->setUpLink_Value((uchar)(In_Data.at(0)));
                        MODEM->ChangedIn_Sniffer_Properties();
                    }
                }
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                    emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                }
            }
            break;
        }
            // Режим пропускания сообщений (только для снифера)
            case 0xB6:{
    #ifdef DATA_LOGIC_DEBUG
    // ====================================
    s = "Comande = 0xD9 - Режим пропускания сообщений";
    qDebug() << s;
    // ====================================
    #endif
                if (ComandState == 1){
                    if (NumbOfBytes == 3){
                        if (MODEM->getIn_Sniffer_Properties()->getSniffer_Mode() != (uchar)(In_Data.at(0))){
                            MODEM->getIn_Sniffer_Properties()->setSniffer_Mode((uchar)(In_Data.at(0)));
                            MODEM->ChangedIn_Sniffer_Properties();
                        }
                    }
                    if (NumbOfBytes == 6){
                        Interfaces_Control_Type In_Interfaces_Control;
                        In_Interfaces_Control.Word = (((uint)(In_Data.at(0)) &0xFF) << 0)|(((uint)(In_Data.at(1)) &0xFF) << 8)|(((uint)(In_Data.at(2)) &0xFF) << 16)|(((uint)(In_Data.at(3)) &0xFF) << 24);
                        MODEM->getIn_PLC_RF433_Modem_Properties()->setPLC_RF433_Interfaces_Control(In_Interfaces_Control);
                        MODEM->ChangedIn_PLC_RF433_Modem_Properties();
                    }
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
                break;
            }
            // Режим широковещания (только для снифера)
            case 0xB5:{
    #ifdef DATA_LOGIC_DEBUG
    // ====================================
    s = "Comande = 0xB5 - Режим широковещания";
    qDebug() << s;
    // ====================================
    #endif
                if (ComandState == 1){
                    if (NumbOfBytes == 3){
                        if (MODEM->getIn_Sniffer_Properties()->getBroadcasting() != (uchar)(In_Data.at(0))){
                            MODEM->getIn_Sniffer_Properties()->setBroadcasting((uchar)(In_Data.at(0)));
                            MODEM->ChangedIn_Sniffer_Properties();
                        }
                    }
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();
                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
                break;
            }
            case 0xB3: // Записать маску назначения (только для снифера)
            {
    #ifdef DATA_LOGIC_DEBUG
    // ====================================
    s = "Comande = 0xB3 - Записать маску назначения";
    qDebug() << s;
    // ====================================
    #endif
                if (ComandState == 1){
                    if (In_Data.length() >= 4){
                        uint mask = 0;
                        mask |= *((uint*)(In_Data.data()));
                        if (MODEM->getIn_Sniffer_Properties()->getSniffer_Level_Destination() != mask){
                            MODEM->getIn_Sniffer_Properties()->setSniffer_Level_Destination(mask);
                            MODEM->ChangedIn_Sniffer_Properties();
                        }
                    }
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();
                    if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL)){
                        emit outConnect(DataLogicMode,ComandState,SEND_MODE);
                    }
                }
                break;
            }
        case 0xB1: // Выбор дополнительного интерфейсного модуля
        {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "Comande = 0xB1 - Выбор дополнительного интерфейсного модуля";
qDebug() << s;
// ====================================
#endif
            Repeat_Counter = Repeat_Number;
            timerRepeat->stop();

            if ((SEND_MODE != MANUAL_SEND_CONTROL)&&(SEND_MODE != MANUAL_CYCLIC_SEND_CONTROL))
            {
                emit outConnect(DataLogicMode,1,SEND_MODE);
            }
            break;
        }
        }
    //}
    ParceDataBuffer.clear();
}

void DataLogic_Class::BOOT_WAITED()
{
    BOOT_WAIT_COUNTER--;
    emit SendLog(QString::fromUtf8(" > ") + QString::number(BOOT_WAIT_COUNTER),NONE);
    if (BOOT_WAIT_COUNTER == 0)
    {
        BOOT_WAIT->stop();
        emit SendLog(QString::fromUtf8("\r"),NONE);
        emit outConnect(DataLogicMode,1,SEND_MODE);
    }
    else
    {
        BOOT_WAIT->start(1000);
    }
}

void DataLogic_Class::REPEAT_SEND()
{
    //SEND_DATA(OutDataBuffer, CONFIG_SEND_CONTROL);
    if (Repeat_Counter > 0) {
        emit outConnect(DataLogicMode,0,SEND_MODE);
        timerRepeat->start(Delay_Time);
        Repeat_Counter--;
    }
    else {
        Repeat_Counter = Repeat_Number;
        timerRepeat->stop();
        emit noANSWER();
    }
}
void DataLogic_Class::MANUAL_REPEAT_SEND(){
    SEND_DATA(OutDataBuffer, MANUAL_CYCLIC_SEND_CONTROL);
}
void DataLogic_Class::STOP_SEND_DATA(){
    Repeat_Counter = Repeat_Number;
    timerRepeat->stop();
    BOOT_WAIT->stop();
    this->Stop_Parceing = true;
    emit STOPPED();
}
//+++++++++++++[Процедура ОТПРАВКИ СООБЩЕНИЙ]++++++++++++++++++++++++++++++++++++++++

void DataLogic_Class::SEND_DATA(QByteArray data, uint n){
    QString s;
    SEND_MODE = n;
    switch (n)
    {
    case CONFIG_SEND_CONTROL:
    {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_DATA(data, CONFIG_SEND_CONTROL)";
qDebug() << s;
// ====================================
#endif
        QByteArray data_to_write; // Текстовая переменная
        ClearOut_DataBuffer();
        OutDataBuffer = data;
        int sn = 0;
        if (addSerialNumber){
           sn = this->SerialNumber.toInt();
           data_to_write.append((char)(sn >> 0));
           data_to_write.append((char)(sn >> 8));
           data_to_write.append((char)(sn >> 16));
           data_to_write.append((char)(sn >> 24));
        }
        data_to_write.append(data);
        if (addSerialNumber){
            CRC16->CRC16_Add_To_ByteArray(&data_to_write);
        }
        emit DataForPrint(data_to_write,COM_TX);
        emit OutData(data_to_write);     // Отправка данных в порт

        timerRepeat->start(Delay_Time);
        //Repeat_Counter--;
        break;
    }
    case CONFIG_SEND_WHITOUT_REPEAT:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_DATA(data, CONFIG_SEND_WHITOUT_REPEAT)";
qDebug() << s;
// ====================================
#endif
        QByteArray data_to_write; // Текстовая переменная
        int sn = 0;
        if (addSerialNumber){
            sn = this->SerialNumber.toInt();
            data_to_write.append((char)(sn >> 0));
            data_to_write.append((char)(sn >> 8));
            data_to_write.append((char)(sn >> 16));
            data_to_write.append((char)(sn >> 24));
        }
        data_to_write.append(data);
        if (addSerialNumber){
            CRC16->CRC16_Add_To_ByteArray(&data_to_write);
        }
        emit DataForPrint(data_to_write,COM_TX);
        emit OutData(data_to_write);     // Отправка данных в порт
        timerRepeat->start(Delay_Time);
        Repeat_Counter = 0;
        break;
    }
    case MONITOR_SEND_CONTROL:{
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_DATA(data, MONITOR_SEND_CONTROL)";
qDebug() << s;
// ====================================
#endif
        QByteArray data_to_write; // Текстовая переменная
        int sn = 0;
        if (addSerialNumber){
            sn = this->SerialNumber.toInt();
            data_to_write.append((char)(sn >> 0));
            data_to_write.append((char)(sn >> 8));
            data_to_write.append((char)(sn >> 16));
            data_to_write.append((char)(sn >> 24));
        }
        data_to_write.append(data);
        if (addSerialNumber){
            CRC16->CRC16_Add_To_ByteArray(&data_to_write);
        }
        emit DataForPrint(data_to_write,COM_TX);
        emit OutData(data_to_write);     // Отправка данных в порт
        break;
    }
    case MANUAL_SEND_CONTROL:
    {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_DATA(data, MANUAL_SEND_CONTROL)";
qDebug() << s;
// ====================================
#endif
        emit DataForPrint(data,COM_TX);   // Вывод данных в консоль
        emit OutData(data);               // Отправка данных в порт
        break;
    }

    case MANUAL_CYCLIC_SEND_CONTROL:
    {
#ifdef DATA_LOGIC_DEBUG
// ====================================
s = "SEND_DATA(data, MANUAL_CYCLIC_SEND_CONTROL)";
qDebug() << s;
// ====================================
#endif
        if (Repeat_Counter > 0)
        {
            OutDataBuffer = data;
            emit DataForPrint(data,COM_TX);   // Вывод данных в консоль
            emit OutData(data);               // Отправка данных в порт

            timerManualRepeat->start(Delay_Time);
            //Repeat_Counter--;
        }
        else
        {
            Repeat_Counter = Repeat_Number;
            timerManualRepeat->stop();
            emit noANSWER();
        }
        break;
    }
    }
}
