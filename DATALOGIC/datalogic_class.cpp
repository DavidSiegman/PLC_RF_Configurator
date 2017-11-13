#include "DATALOGIC/datalogic_class.h"
#include "mainwindow.h"

DataLogic_Class::DataLogic_Class(CRC16_Class *oCRC16, QTimer *t,SI4463Class *SI4463Conf,MODEMClass *MODEM,Port *nPort,QObject *parent) : QObject(parent)
{
    this->CRC16           = oCRC16;
    this->timer           = t;
    this->SI4463Conf      = SI4463Conf;
    this->MODEM           = MODEM;
    this->nPort           = nPort;
    this->addSerialNumber = false;

    this->timerRepeat     = new QTimer();

    connect(this,SIGNAL(writeDataToCOM(QByteArray)),this->nPort,SLOT(WriteToPort(QByteArray)));
    connect(this->nPort, SIGNAL(outPort(QByteArray)),this, SLOT(In_DataBuffer(QByteArray)));
    connect(timerRepeat,SIGNAL(timeout()), this, SLOT(REPEAT_SEND()));
}

void DataLogic_Class::setSerialNumberMode(QString S, bool Enable)
{
    this->SerialNumber    = S;
    this->addSerialNumber = Enable;
}
void DataLogic_Class::ClearIn_DataBuffer(void)
{
    InDataBuffer.clear();
    this->timer->stop();
                                                        // ====================================
                                                        QString s = "Stop timer - Buff clear";
                                                        qDebug() << s;
                                                        // ====================================
}
void DataLogic_Class::ClearOut_DataBuffer(void)
{
    OutDataBuffer.clear();
}
void DataLogic_Class::In_DataBuffer(QByteArray data)
{
    InDataBuffer.append(data);
    int length = InDataBuffer.length();
                                                        // ====================================
                                                        QString s = "Input bytes: "; s += QString("%1").arg(length);
                                                        qDebug() << s;
                                                        // ====================================

    this->timer->start(50);
                                                        // ====================================
                                                        s = "Start timer 50 ms";
                                                        qDebug() << s;
                                                        // ====================================

    if(CRC16->Check_Byte_Stream_CRC16(&InDataBuffer) && (length > 4))
                    {                                   // ====================================
                                                        QString s = "Stop timer - CRC Correct";
                                                        qDebug() << s;
                                                        // ====================================

        this->timer->stop();
        Repeat_Counter = Repeat_Number;
        timerRepeat->stop();

        ClearOut_DataBuffer();
        OutDataBuffer.append(InDataBuffer);
        ClearIn_DataBuffer();
        emit DataForPrint(OutDataBuffer,COM_RX);        // Вывод данных в консоль
        Parce_DataBuffer(OutDataBuffer,NONE);           // Парсинг данных

    }
}

void DataLogic_Class::Parce_DataBuffer(QByteArray data, uint n)
{
    ParceDataBuffer.clear();
    ParceDataBuffer.append(data);
    ClearOut_DataBuffer();

    QByteArray AnswerH;
    for(unsigned int i = 0; i < 6; i++)
    {AnswerH.append((char)(0xFF));}

    QByteArray AnswerHeader;
    AnswerHeader.append(ParceDataBuffer.data(), 6);

    if (AnswerHeader.data() == AnswerH)
    {
        ParceData(IN_INTERFACE_USO);
    }
    else
    {
        AnswerHeader.clear();
        AnswerHeader.append(ParceDataBuffer.data()+4, 6);
        if (AnswerHeader.data() == AnswerH)
        {
            ParceData(IN_INTERFACE_RF_PLC);
        }
    }
}

void DataLogic_Class::ComandHandling(uint n, uint m)
{
    QByteArray data;
    data.append((char)(0xFF));
    data.append((char)(0xFF));
    data.append((char)(0xFF));
    data.append((char)(0xFF));
    int length = 0;
    switch (n)
    {
        case SEND_AOPEN:
        {
            int u[2] = {0xFF,0x00};length = 2;
            for(uint i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_BF_03_00_AC_00:
        {
            int u[5] = {0xBF,0x03,0x00,0xAC,0x00};length = 5;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_BF_03_21_88_00:
        {
            int u[5] = {0xBF,0x03,0x21,0x88,0x00};length = 5;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_READ_NODE_TYPE:
        {
            int u[2] = {0xF0,0x00};length = 2;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_WRITE_NODE_TYPE:
        {
            int u[10] = {0xEF,0x07,MODEM->SWITCH_MODE,0xE0,0x96,0xF8,0xA5,0xC9,0xDC,0x0C}; length = 10;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_READ_SWITCH_LEVEL:
        {
            int u[3] = {0xE0,0x01,0x00};length = 3;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_WRITE_SWITCH_LEVEL:
        {
            int u[6] = {0xE0,0x04,((int)(MODEM->SWITCH_LEVEL >> 0)  & 0xFF),((int)(MODEM->SWITCH_LEVEL >> 8) & 0xFF),
                                  ((int)(MODEM->SWITCH_LEVEL >> 16) & 0xFF),((int)(MODEM->SWITCH_LEVEL >> 24) & 0xFF)};length = 6;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_READ_SWITCH_TIMEOUT:
        {
            int u[3] = {0xE3,0x01,0x00};length = 3;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_WRITE_SWITCH_TIMEOUT:
        {
            int u[6] = {0xE3,0x04,((int)(MODEM->SWITCH_TIMEOUT >> 0)  & 0xFF),((int)(MODEM->SWITCH_TIMEOUT >> 8) & 0xFF),
                                  ((int)(MODEM->SWITCH_TIMEOUT >> 16) & 0xFF),((int)(MODEM->SWITCH_TIMEOUT >> 24) & 0xFF)};length = 6;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_READ_RX_TIMEOUT:
        {
            int u[3] = {0xE2,0x01,0x00};length = 3;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_READ_TX_TIMEOUT:
        {
            int u[3] = {0xE1,0x01,0x00}; length = 3;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_READ_RSSI_CURRENT:
        {
            int u[2] = {0xBB,0x00}; length = 2;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
        case SEND_READ_RSSI:
        {
            int u[2] = {0xE5,0x00}; length = 2;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
            break;
        }
    }
    CRC16->CRC16_Add_To_ByteArray(&data);
    emit SEND_DATA(data,m);
}

void DataLogic_Class::ParceData(uint n)
{
    QString s = "Parce data";
    qDebug() << s;

    QByteArray AnswerH;
    for(unsigned int i = 0; i < 6; i++)
    {AnswerH.append((char)(0xFF));}

    QByteArray AnswerHeader, In_Data;
    uchar NumbOfBytes, Comande, ComandState;
    if (ParceDataBuffer.length() >= 6)
    {
        AnswerHeader.append(ParceDataBuffer.data(), 6);
    }
    if (n == IN_INTERFACE_USO)
    {
        if (ParceDataBuffer.length() >= 9+NumbOfBytes-2)
        {
            NumbOfBytes = ParceDataBuffer.at(6);
            Comande     = ParceDataBuffer.at(7);
            ComandState = ParceDataBuffer.at(8);
            In_Data.append(ParceDataBuffer.data()+9,NumbOfBytes-2);
        }
    }
    else if (n == IN_INTERFACE_RF_PLC)
    {
        if (ParceDataBuffer.length() >= 9+4+NumbOfBytes-2)
        {
            NumbOfBytes = ParceDataBuffer.at(6+4);
            Comande     = ParceDataBuffer.at(7+4);
            ComandState = ParceDataBuffer.at(8+4);
            In_Data.append(ParceDataBuffer.data()+9+4,NumbOfBytes-2);
        }
    }
    switch (Comande)
    {
        case 0xFF: // Запрос версий ПО
        {
            if (In_Data.length() >= 10+4)
            {
                MODEM->curr_ver     = ComandState;
                MODEM->boot_ver     = QString::fromUtf8(In_Data.data(),4);
                MODEM->fw_ver       = QString::fromUtf8(In_Data.data()+10,4);
                MODEM->BOOT_VERSION = MODEM->boot_ver.toDouble();
                MODEM->FW_VERSION   = MODEM->fw_ver.toDouble();
            }
            emit outConnect(DataLogicMode);
            break;
        }
        case 0xF0: // Запрос режима ретрансляции
        {
            MODEM->SWITCH_MODE     = ComandState;
            emit outConnect(DataLogicMode);
            break;
        }
        case 0xEF:
        {
            emit outConnect(DataLogicMode);
            break;
        }
        case 0xE5: // Latch RSSI
        {
            signed short RSSI = 0;
            if (In_Data.length() >= 2)
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_0 = In_Data.at(0);
                SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_1 = In_Data.at(1);
                RSSI = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_1) << 8)
                                       | (SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_0);
            }
            signed int   AFC = 0;
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0 = In_Data.at(2);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1 = In_Data.at(3);
                AFC = ((signed int)(SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_1) << 8)
                                 | (SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_0);
                if ((AFC & (1 << 15)))
                {
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2 = 0xFF;
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3 = 0xFF;
                    AFC |= 0xFFFF0000;
                }
                else
                {
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2 = 0x00;
                    SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3 = 0x00;
                    AFC &= ~0xFFFF0000;
                }
                emit outLRSSI_AFC(RSSI, (double)(AFC));
            }
            else if ((NumbOfBytes == 8)&(In_Data.length() >= 6))
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0 = In_Data.at(2);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1 = In_Data.at(3);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2 = In_Data.at(4);
                SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3 = In_Data.at(5);
                AFC = ((signed int)(SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3) << 24)
                                | ((SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2) << 16)
                                | ((SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1) << 8)
                                | ((SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0) << 0);
                emit outLRSSI_AFC(RSSI, (double)(AFC)/1000);
            }
            else
            {
                emit outLRSSI_AFC(RSSI, (double)(AFC));
            }
            break;
        }
        case 0xE3: // Таймаут свича
        {
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                MODEM->SWITCH_TIMEOUT     = 0;
                MODEM->SWITCH_TIMEOUT    |= *((uint*)(In_Data.data()));;
            }
            emit outConnect(DataLogicMode);
            break;
        }
        case 0xE2: // Таймаут RX
        {
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                MODEM->RX_TIMEOUT       = 0;
                MODEM->RX_TIMEOUT      |= *((uint*)(In_Data.data()));;
            }
            emit outConnect(DataLogicMode);
            break;
        }
        case 0xE1: // Таймаут TX
        {
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                MODEM->TX_TIMEOUT       = 0;
                MODEM->TX_TIMEOUT      |= *((uint*)(In_Data.data()));;
            }
            emit outConnect(DataLogicMode);
            break;
        }
        case 0xE0: // Уровень свича
        {
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                MODEM->SWITCH_LEVEL     = 0;
                MODEM->SWITCH_LEVEL     |= *((uint*)(In_Data.data()));
            }
            emit outConnect(DataLogicMode);
            break;
        }
        case 0xBF:
        {
             if (In_Data.length() >= 2)
             {
                 uchar GROUP       = ComandState;
                 uchar NUM_PROPS   = In_Data.at(0);
                 uchar START_PROP  = In_Data.at(1);
                 uchar *group_adress = SI4463Conf->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP);
                 if ((NumbOfBytes - 4) == NUM_PROPS)
                 {
                     if (In_Data.length() >= NUM_PROPS+1)
                     {
                         for (uint i = 0; i < NUM_PROPS; i++)
                         {
                             *(uchar*)(group_adress) = *(In_Data.data()+i+2);
                             group_adress++;
                         }
                     }
                 }
             }
             emit outConnect(DataLogicMode);
             break;
        }
        case 0xBB: // Current RSSI
        {
            if (In_Data.length() >= 2)
            {
                SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_0 = In_Data.at(0);
                SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_1 = In_Data.at(1);
                signed short RSSI = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_1) << 8)
                                      | (SI4463Conf->aSI4463_INTERUPTS()->Field.CURR_RSSI.Field.CURR_RSSI_0);
            }
            emit outCurrentRSSI(RSSI);
            break;
        }
    }
    ParceDataBuffer.clear();
}

void DataLogic_Class::REPEAT_SEND()
{
    SEND_DATA(repeat_data, CONFIG_SEND_CONTROL);
}

//+++++++++++++[Процедура ОТПРАВКИ СООБЩЕНИЙ]++++++++++++++++++++++++++++++++++++++++

void DataLogic_Class::SEND_DATA(QByteArray data, uint n)
{
    switch (n)
    {
        case CONFIG_SEND_CONTROL:
        {
            if (Repeat_Counter > 0)
            {
                QByteArray data_to_write; // Текстовая переменная
                repeat_data = data;
                int sn = 0;
                if (addSerialNumber)
                {
                    sn = this->SerialNumber.toInt();
                    data_to_write.append((char)(sn >> 0));
                    data_to_write.append((char)(sn >> 8));
                    data_to_write.append((char)(sn >> 16));
                    data_to_write.append((char)(sn >> 24));
                }

                data_to_write.append(data);

                if (addSerialNumber)
                {
                    CRC16->CRC16_Add_To_ByteArray(&data_to_write);
                }

                emit DataForPrint(data_to_write,COM_TX);
                emit writeDataToCOM(data_to_write);     // Отправка данных в порт

                timerRepeat->start(Delay_Time);
                Repeat_Counter--;
            }
            else
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();
                emit noANSWER();
            }
            break;
        }
        case CONFIG_SEND_WHITOUT_REPEAT:
        {
            QByteArray data_to_write; // Текстовая переменная
            repeat_data = data;

            int sn = 0;
            if (addSerialNumber)
            {
                sn = this->SerialNumber.toInt();
                data_to_write.append((char)(sn >> 0));
                data_to_write.append((char)(sn >> 8));
                data_to_write.append((char)(sn >> 16));
                data_to_write.append((char)(sn >> 24));
            }

            data_to_write.append(data);

            if (addSerialNumber)
            {
                CRC16->CRC16_Add_To_ByteArray(&data_to_write);
            }

            emit DataForPrint(data_to_write,COM_TX);
            emit writeDataToCOM(data_to_write);     // Отправка данных в порт
            break;
        }
        case MANUAL_SEND_CONTROL:
        {
            emit DataForPrint(data,COM_TX);   // Вывод данных в консоль
            emit writeDataToCOM(data);        // Отправка данных в порт
            break;
        }
    }
}
