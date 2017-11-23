#include "DATALOGIC/datalogic_class.h"

//#include "mainwindow.h"

DataLogic_Class::DataLogic_Class(CRC16_Class *oCRC16, QTimer *t,SI4463Class *SI4463Conf,SI4432Class *SI4432Conf, MODEMClass *MODEM,Port *nPort,TCP *nTCP,QObject *parent) : QObject(parent)
{
    this->CRC16           = oCRC16;
    this->timer           = t;
    this->SI4463Conf      = SI4463Conf;
    this->SI4432Conf      = SI4432Conf;
    this->MODEM           = MODEM;
    this->nPort           = nPort;
    this->nTCP            = nTCP;
    this->addSerialNumber = false;

    this->timerRepeat     = new QTimer();

    connect(this,SIGNAL(OutData(QByteArray)),            this->nPort,SLOT(COM_WriteDATA(QByteArray)));
    connect(this->nPort, SIGNAL(COM_OutDATA(QByteArray)),this, SLOT(In_DataBuffer(QByteArray)));
    connect(this,SIGNAL(OutData(QByteArray)),            this->nTCP,SLOT(TCP_WriteDATA(QByteArray)));
    connect(this->nTCP, SIGNAL(TCP_OutDATA(QByteArray)), this, SLOT(In_DataBuffer(QByteArray)));
    connect(timerRepeat,SIGNAL(timeout()),               this, SLOT(REPEAT_SEND()));

}

void DataLogic_Class::setSerialNumberMode(QString S, bool Enable)
{
    this->SerialNumber    = S;
    this->addSerialNumber = Enable;
}

void DataLogic_Class::setCurrentSI4463_PROPERTYS_structur(uint select)
{
    if (select == 0)
    {
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS();
    }
    else if (select == 1)
    {
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS_CALIB();
    }
    else if (select == 2)
    {
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS_FROM_FILE();
    }
    else if (select == 3)
    {
        this->CurrentSI4463_PROPERTYS_structur = SI4463Conf->aSI4463_PROPERTYS_CALIB_FROM_FILE();
    }

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

        ClearOut_DataBuffer();
        OutDataBuffer.append(InDataBuffer);
        ClearIn_DataBuffer();
        Parce_DataBuffer(OutDataBuffer,NONE);            // Парсинг данных

    }
}

void DataLogic_Class::Parce_DataBuffer(QByteArray data, uint n)
{
    ParceDataBuffer.clear();
    ParceDataBuffer.append(data);

    QByteArray AnswerH;
    for(unsigned int i = 0; i < 6; i++)
    {AnswerH.append((char)(0xFF));}

    QByteArray AnswerHeader;
    AnswerHeader.append(ParceDataBuffer.data(), 6);

    if (AnswerHeader.data() == AnswerH)
    {
        emit DataForPrint(OutDataBuffer,COM_RX);     // Вывод данных в консоль
        ParceData(IN_INTERFACE_USO);
    }
    else
    {
        AnswerHeader.clear();
        AnswerHeader.append(ParceDataBuffer.data()+4, 6);
        if (AnswerHeader.data() == AnswerH)
        {
            emit DataForPrint(OutDataBuffer,COM_RX);     // Вывод данных в консоль
            ParceData(IN_INTERFACE_RF_PLC);
        }
        else
        {
            emit DataForPrint(OutDataBuffer,COM_RX);     // Вывод данных в консоль
            ParceData(IN_SNIFER_PLUS_PREAMBLE);
        }
    }
    ClearOut_DataBuffer();
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
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_RF_RESET:
    {
        int u[2] = {0xE4,0x00};length = 2;
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
    case SEND_READ_RSSI:
    {
        int u[2] = {0xE5,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SWITCH_TIMEOUT:
    {
        int u[3] = {0xE3,0x01,0x00};length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_RELOAD_DEVICE:
    {
        if (MODEM->RESET_DEVICE_TIMEOUT == 0)
        {
            int u[3] = {0xE4,0x00};length = 2;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
        }
        else
        {
            int u[6] = {0xE4,0x04,((int)(MODEM->RESET_DEVICE_TIMEOUT >> 0)  & 0xFF),((int)(MODEM->RESET_DEVICE_TIMEOUT >> 8) & 0xFF),
                                  ((int)(MODEM->RESET_DEVICE_TIMEOUT >> 16) & 0xFF),((int)(MODEM->RESET_DEVICE_TIMEOUT >> 24) & 0xFF)};length = 6;
            for(int i = 0; i < length; i++){data.append((char)u[i]);}
        }
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
    case SEND_BF_AF_00_AC_00:
    {
        int u[5] = {0xBF,0xAF,0x00,0xAC,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        for(int i = 0; i < 0xAC; i++)
        {
            data.append(SI4463Conf->aSI4463_GET_PROPERTYS(0x00, 0x00, i, CurrentSI4463_PROPERTYS_structur));
        }
        break;
    }
    case SEND_BF_8B_21_88_00:
    {
        int u[5] = {0xBF,0x8B,0x21,0x88,0x00};length = 5;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        for(int i = 0; i < 0x88; i++)
        {
            data.append(SI4463Conf->aSI4463_GET_PROPERTYS(0x21, 0x00, i, CurrentSI4463_PROPERTYS_structur));
        }
        break;
    }
    case SEND_READ_RSSI_CURRENT:
    {
        int u[2] = {0xBB,0x00}; length = 2;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_LOAD_PROPERTYS_TO_FLASH:
    {
        int u[18] = {0xBE,0x10,'L','o','a','d','P','r','o','p','s','T','o','F','l','a','s','h'}; length = 18;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_PROPERTYS_FROM_FLASH:
    {
        int u[20] = {0xBE,0x12,'R','e','a','d','P','r','o','p','s','F','r','o','m','F','l','a','s','h'}; length = 20;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_LOAD_CALIBPROPS_TO_FLASH:
    {
        int u[18] = {0xBE,0x10,'L','o','a','d','C','a','l','P','r','T','o','F','l','a','s','h'}; length = 18;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_CALIBPROPS_FROM_FLASH:
    {
        int u[20] = {0xBE,0x12,'R','e','a','d','C','a','l','P','r','F','r','o','m','F','l','a','s','h'}; length = 20;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_SNIFER_MODE:
    {
        int u[3] = {0xD9,0x01,(int)(MODEM->SNIFER_MODE)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_UPLINC_MODE:
    {
        int u[3] = {0xDA,0x01,(int)(MODEM->UP_LINC)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_CRC_CHECK_MODE:
    {
        int u[3] = {0xBC,0x01,(int)(MODEM->CRC_CHECK_DISABLE)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_BROADCASTING_MODE:
    {
        int u[3] = {0xD8,0x01,(int)(MODEM->BROADCAST)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SWITCH_TABLE_ELEMENT:
    {
        int u[3] = {0xEB,0x01,(int)(MODEM->SwitchTable.length()+1)}; length = 3;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_WRITE_SWITCH_TABLE_ELEMENT:
    {
        uint switchelement = MODEM->SwitchTable.at(MODEM->SwitchTable_element_index-1).toInt();
        int u[14] = {0xEA,0x0C,(int)(MODEM->SwitchTable_element_index),(int)(switchelement >> 0)&0xFF,(int)(switchelement >> 8)&0xFF,(int)(switchelement >> 16)&0xFF,(int)(switchelement >> 24)&0xFF,0xF8,0xC9,0xDC,0xA5,0x96,0xE0,0x0C}; length = 14;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_LOAD_SWITCH_TABLE_TO_FLASH:
    {
        int u[9] = {0xE8,0x07,0xCD,0xA5,0xC9,0xF8,0xE0,0xC0,0x96}; length = 9;
        for(int i = 0; i < length; i++){data.append((char)u[i]);}
        break;
    }
    case SEND_READ_SI4432_PARAMETERS:
    {
        int u[2] = {0xE6,0x00}; length = 2;
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

    QByteArray In_Data;
    uchar NumbOfBytes, Comande, ComandState;

    if (n == IN_INTERFACE_USO)
    {
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
        QString s = "Преамбула не определена";
        if (ParceDataBuffer.length() >= 5)
        {
            RF_Preamble.Field.Msg_Length = ParceDataBuffer.at(4);
        }
        if (ParceDataBuffer.length() >= 36)
        {
            for(int i = 4; i < 32; i++)
            {
                RF_Preamble.Byte_Array[i-4] = (uchar)(ParceDataBuffer.at(i));
            }
            s.clear();
            s.append("Длинна пакета: " + QString::number(RF_Preamble.Field.Msg_Length) + "\r");
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
            s.append("Debug: RX_Buffer_current_counter: " + QString::number(RF_Preamble.Field.broadcasting) + "\r");
        }
        if (ParceDataBuffer.length() >= RF_Preamble.Field.Msg_Length + 12)
        {
            In_Data.append(ParceDataBuffer.data()+4+28,RF_Preamble.Field.Msg_Length-26);
        }

        emit LogForPrint(s,NONE);
        emit DataForPrint(In_Data,COM_RX);     // Вывод данных в консоль
    }
    if (n != IN_SNIFER_PLUS_PREAMBLE)
    {
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
                if((MODEM->boot_ver.at(0) == 'R'))
                {
                    QString s; s.append(MODEM->boot_ver.at(2)); s.append(MODEM->boot_ver.at(3));
                    MODEM->BOOT_VERSION_SNIFER = s.toDouble();
                }
                if((MODEM->fw_ver.at(0) == 'R'))
                {
                    QString s; s.append(MODEM->boot_ver.at(2)); s.append(MODEM->boot_ver.at(3));
                    MODEM->FW_VERSION_SNIFER = s.toDouble();
                }

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,1);
            }

            break;
        }
        case 0xF0: // Запрос режима ретрансляции
        {
            MODEM->SWITCH_MODE     = ComandState;

            Repeat_Counter = Repeat_Number;
            timerRepeat->stop();

            emit outConnect(DataLogicMode,1);
            break;
        }
        case 0xEF: // Запись режима ретрансляции
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xEE: // Считывание параметров частоты PLC Модедма
        {
            break;
        }
        case 0xED: // Записть параметров частоты PLC Модедма
        {
            break;
        }
        case 0xEC: // Cчитывание серийного адреса устройства
        {
            break;
        }
        case 0xEB: // Чтение Элемента таблицы ретрансляции
        {
            if((NumbOfBytes == 6)&&(In_Data.length() >= 4))
            {
                uint SWT_Element = ((uint)(In_Data.at(0)) << 0)|((uint)(In_Data.at(1)) << 8)|((uint)(In_Data.at(2)) << 16)|((uint)(In_Data.at(3)) << 24);
                if ((SWT_Element > 0)&&(SWT_Element < 0xFFFFFFFF))
                {
                    //uint curr_index =  MODEM->SwitchTable.length();
                    MODEM->SwitchTable.append(QString::number(SWT_Element));
                    ComandHandling(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                }
                else
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,1);
                }
            }
            break;
        }
        case 0xEA: // Запись Элемента таблицы ретрансляции в буфер для записи
        {
            if (ComandState == 1)
            {
                if((MODEM->SwitchTable_element_index > 0)&&(MODEM->SwitchTable_element_index < MODEM->SwitchTable.length()))
                {
                    MODEM->SwitchTable_element_index++;
                    ComandHandling(SEND_WRITE_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                }
                else
                {
                    MODEM->SwitchTable.clear();
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,ComandState);
                }
            }
            break;
        }
        case 0xE9: // Стирание таблицы ретрансляции из флэш памяти модема
        {
            break;
        }
        case 0xE8: // Запись таблицы ретрансляции во флэш память модема из буфера
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xE5: // Latch RSSI
        {
          signed short RSSI = 0;
          signed short ANT1_RSSI = 0;
          signed short ANT2_RSSI = 0;

          if (In_Data.length() >= 2)
          {
              SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_0 = In_Data.at(0);
              SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_1 = In_Data.at(1);

              RSSI = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_1) << 8)
                                  | (SI4463Conf->aSI4463_INTERUPTS()->Field.LATCH_RSSI.Field.LATCH_RSSI_0);
          }

          signed short AFC = 0;

          if ((NumbOfBytes == 6)&&In_Data.length() >= 4)
          {
              SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0 = In_Data.at(2);
              SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1 = In_Data.at(3);
              AFC = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1) << 8)
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

              AFC = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_3) << 24)
                                | ((SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_2) << 16)
                                | ((SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1) << 8)
                                |  (SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_0);

              Repeat_Counter = Repeat_Number;
              timerRepeat->stop();
              emit outLRSSI_AFC(RSSI,ANT1_RSSI,ANT2_RSSI,(double)(AFC));
          }
          if ((NumbOfBytes == 10)&&(In_Data.length() >= 8))
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
              AFC = ((signed short)(SI4463Conf->aSI4463_INTERUPTS()->Field.AFC_FREQ_OFFSET.Field.AFC_FREQ_OFFSET_1) << 8)
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
          break;
        }
        case 0xE6: // Чтение RF Параметров SI4432
        {
            if (ComandState == 1)
            {
                if (In_Data.length() >= NumbOfBytes-3)
                {
                    SI4432Conf->aSI4463_RF_Config_struct()->RF_CONF_REG_1.reg = (((uint)(In_Data.at(0)) &0xFF) << 0)|(((uint)(In_Data.at(1)) &0xFF) << 8)|(((uint)(In_Data.at(2)) &0xFF) << 16)|(((uint)(In_Data.at(3)) &0xFF) << 24);
                    SI4432Conf->aSI4463_RF_Config_struct()->RF_CONF_REG_2.reg = (((uint)(In_Data.at(4)) &0xFF) << 0)|(((uint)(In_Data.at(5)) &0xFF) << 8)|(((uint)(In_Data.at(6)) &0xFF) << 16)|(((uint)(In_Data.at(7)) &0xFF) << 24);
                    SI4432Conf->aSI4463_RF_Config_struct()->RF_NOM_FREQUENC   = (((uint)(In_Data.at(8)) &0xFF) << 0)|(((uint)(In_Data.at(9)) &0xFF) << 8)|(((uint)(In_Data.at(10))&0xFF) << 16)|(((uint)(In_Data.at(11))&0xFF) << 24);
                    SI4432Conf->aSI4463_RF_Config_struct()->RF_SYNCH_WORD     = (((uint)(In_Data.at(12))&0xFF) << 0)|(((uint)(In_Data.at(13))&0xFF) << 8)|(((uint)(In_Data.at(14))&0xFF) << 16)|(((uint)(In_Data.at(15))&0xFF) << 24);
                    SI4432Conf->aSI4463_RF_Config_struct()->RF_RX_HAEDER      = (((uint)(In_Data.at(16))&0xFF) << 0)|(((uint)(In_Data.at(17))&0xFF) << 8)|(((uint)(In_Data.at(18))&0xFF) << 16)|(((uint)(In_Data.at(19))&0xFF) << 24);
                    SI4432Conf->aSI4463_RF_Config_struct()->RF_TX_HAEDER      = (((uint)(In_Data.at(20))&0xFF) << 0)|(((uint)(In_Data.at(21))&0xFF) << 8)|(((uint)(In_Data.at(22))&0xFF) << 16)|(((uint)(In_Data.at(23))&0xFF) << 24);

                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,ComandState);
                }
            }
            break;
        }
        case 0xE4: // Modem Reset
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xE3:
        {
            if ((NumbOfBytes == 6)&&(In_Data.length() >= 4))
            {
                MODEM->SWITCH_TIMEOUT     = 0;
                MODEM->SWITCH_TIMEOUT    |= *((uint*)(In_Data.data()));

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            else if (NumbOfBytes == 2)
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,ComandState);
                }
            }
            break;
        }
        case 0xE2: // Таймаут RX
        {
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                MODEM->RX_TIMEOUT       = 0;
                MODEM->RX_TIMEOUT      |= *((uint*)(In_Data.data()));

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            else if (NumbOfBytes == 2)
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,ComandState);
                }
            }
            break;
        }
        case 0xE1: // Таймаут TX
        {
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                MODEM->TX_TIMEOUT       = 0;
                MODEM->TX_TIMEOUT      |= *((uint*)(In_Data.data()));

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            else if (NumbOfBytes == 2)
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,ComandState);
                }
            }
            break;
        }
        case 0xE0: // Уровень свича
        {
            if ((NumbOfBytes == 6)&(In_Data.length() >= 4))
            {
                MODEM->SWITCH_LEVEL     = 0;
                MODEM->SWITCH_LEVEL     |= *((uint*)(In_Data.data()));

                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            else if (NumbOfBytes == 2)
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,ComandState);
                }
            }
            break;
        }
        case 0xDA: // Установить UP_Linc в 1 (только для снифера)
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xD9: // Режим пропускания сообщений (только для снифера)
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xD8: // Режим широковещания (только для снифера)
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xBF: // Чтение свойств SI4463 из памяти RF модэма v5+, или запись свойств во буфер
        {
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
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,1);
            }
            else
            {
                if (ComandState == 1)
                {
                    Repeat_Counter = Repeat_Number;
                    timerRepeat->stop();

                    emit outConnect(DataLogicMode,ComandState);
                }
            }
            break;
        }
        case 0xBE: // Запись свойств SI4463 из флэша в RAM и наоборот в RF модэмах v5+
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xBD: // Установка логики мигания светодиодов
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xBC: // Отключение проверки CRC
        {
            if (ComandState == 1)
            {
                Repeat_Counter = Repeat_Number;
                timerRepeat->stop();

                emit outConnect(DataLogicMode,ComandState);
            }
            break;
        }
        case 0xBB: // Current RSSI
        {
          signed short RSSI = 0;
          if(In_Data.length() >= 2)
          {
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
                emit OutData(data_to_write);     // Отправка данных в порт

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
            emit OutData(data_to_write);     // Отправка данных в порт
            break;
        }
        case MANUAL_SEND_CONTROL:
        {
            emit DataForPrint(data,COM_TX);   // Вывод данных в консоль
            emit OutData(data);        // Отправка данных в порт
            break;
        }
    }
}
