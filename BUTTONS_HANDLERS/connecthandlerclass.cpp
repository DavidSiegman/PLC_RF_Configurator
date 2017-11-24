#include "connecthandlerclass.h"


QString String2_2(
                     "QWidget{"
                     "background-color: rgb(186, 229, 202);"
                     "}"
                 );
QString String2_3(
                     "QWidget{"
                     "background: rgba(100,50,00,0);"
                     "}"
                 );

ConnectHandlerClass::ConnectHandlerClass(Ui::MainWindow *ui,DataLogic_Class *DataLogic,MODEMClass *MODEM,QObject *parent) : QObject(parent)
{
    ReadDataProgress = 0;

    this->ui        = ui;
    this->DataLogic = DataLogic;
    this->MODEM     = MODEM;
    connect(this,SIGNAL(SendComand(uint,uint)),this->DataLogic,SLOT(ComandHandling(uint,uint)));
    connect(this->DataLogic,SIGNAL(outConnect(uint,uint)),this,SLOT(ConnectHandling(uint,uint)));


    NetTab       = this->ui->NetTab;
    PLCTab       = this->ui->PLCTab;
    RFTab        = this->ui->RFTab;
    RFOldTab     = this->ui->RFOldTab;
    SniferTab    = this->ui->SniferTab;
    RFMonitorTab = this->ui->MonitorTab;

    this->ui->tabWidget->removeTab(6);
    this->ui->tabWidget->removeTab(5);
    this->ui->tabWidget->removeTab(4);
    this->ui->tabWidget->removeTab(3);
    this->ui->tabWidget->removeTab(2);
    this->ui->tabWidget->removeTab(1);
}

void ConnectHandlerClass::aOPEN()
{
    QString s = ui->Connect->text();
    ui->progressBar->setValue(0);

    if (s.compare("Соединение") == 0)
    {
        ui->RSSIWidget->setEnabled(false);
        ui->MANUAL_ENTER->setEnabled(false);
        ui->tabWidget->setEnabled(false);
        ui->Connect->setText("Отключение");
        if (ui->Interface->currentIndex() == 1)
        {DataLogic->setSerialNumberMode(ui->SN->text(), true);}
        else{DataLogic->setSerialNumberMode(ui->SN->text(), false);}
        ReadDataProgress = 0;
        MODEM->SwitchTable.clear();
        emit SendLog(QString::fromUtf8(">> ======= Подключение к устройству\r"),NONE);
        ConnectHandling(CONNECT_HANDLING,1);
    }
    else if (s.compare("Отключение") == 0)
    {
        ui->boot_v->setText("");
        ui->fw_v->setText("");
        ui->DeviceType->setText("");
        ui->boot_v->setStyleSheet(String2_3);
        ui->fw_v->setStyleSheet(String2_3);

        ui->RSSIWidget->setEnabled(true);
        ui->MANUAL_ENTER->setEnabled(true);
        ui->Interface->setEnabled(true);
        if (ui->Interface->currentIndex() == 1)
        {ui->SN->setEnabled(true);}
        ui->tabWidget->setEnabled(true);
        ui->Connect->setText("Соединение");
        ui->tabWidget->removeTab(6);
        ui->tabWidget->removeTab(5);
        ui->tabWidget->removeTab(4);
        ui->tabWidget->removeTab(3);
        ui->tabWidget->removeTab(2);
        ui->tabWidget->removeTab(1);
        MODEM->SwitchTable.clear();
        emit SendLog(QString::fromUtf8(">> ======= Устройство отключено\r"),NONE);
    }
}
void ConnectHandlerClass::isAOPEN()
{
    ui->boot_v->setText(MODEM->boot_ver);
    ui->fw_v->setText(MODEM->fw_ver);

    if (MODEM->curr_ver == 0)
    {
        ui->boot_v->setStyleSheet(String2_2);
        ui->fw_v->setStyleSheet(String2_3);
    }
    else if (MODEM->curr_ver == 1)
    {
        ui->boot_v->setStyleSheet(String2_3);
        ui->fw_v->setStyleSheet(String2_2);
    }
    ui->RSSIWidget->setEnabled(true);
    ui->Interface->setEnabled(false);
    ui->SN->setEnabled(false);

    if ((MODEM->BOOT_VERSION == 0))
    {
        ui->tabWidget->addTab(SniferTab,     "USB/RF Преобразователь");
        if ((MODEM->BOOT_VERSION_SNIFER > 0)&&(MODEM->BOOT_VERSION_SNIFER < 20))
        {
            ui->tabWidget->addTab(RFOldTab,      "Настройки RF");
            ui->DeviceType->setText("USB/RF Преобразователь (Snifer)(Микросхема SI4432)");
        }
        else if(MODEM->BOOT_VERSION_SNIFER >= 20)
        {
            ui->tabWidget->addTab(RFTab,         "Настройки RF");
            ui->DeviceType->setText("USB/RF Преобразователь (Snifer)(Микросхема SI4463)");
            ui->NetLevel->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
            if(MODEM->SwitchTable.length() == 0)
            {
                ui->DeviceMonitorSN->setText("0");
            }
            else
            {
                ui->DeviceMonitorSN->setText(MODEM->SwitchTable.at(0));
            }
        }
        ui->tabWidget->addTab(RFMonitorTab,  "RF RSSI Монитор");
    }
    if ((MODEM->BOOT_VERSION > 0)&(MODEM->BOOT_VERSION < 3))
    {
        ui->tabWidget->addTab(NetTab,        "Настройки Сети");
        ui->tabWidget->addTab(PLCTab,        "Настройки PLC");
    }
    if ((MODEM->BOOT_VERSION >= 3) & (MODEM->BOOT_VERSION < 5))
    {
        ui->tabWidget->addTab(NetTab,        "Настройки Сети");
        ui->tabWidget->addTab(RFOldTab,      "Настройки RF");
        ui->DeviceType->setText("RF-Модуль (Микросхема SI4432)");
        ui->SWITCHLVL->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
        ui->SWITCHTM->setText(QString("%1").arg(MODEM->SWITCH_TIMEOUT));
    }
    else if ((MODEM->BOOT_VERSION >= 5) & (MODEM->BOOT_VERSION < 6))
    {
        ui->tabWidget->addTab(NetTab,        "Настройки Сети");
        ui->tabWidget->addTab(RFTab,         "Настройки RF");
        ui->tabWidget->addTab(RFMonitorTab,  "RF RSSI Монитор");
        ui->DeviceType->setText("RF-Модуль (Микросхема SI4463)");
        ui->SWITCHLVL->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
        ui->SWITCHTM->setText(QString("%1").arg(MODEM->SWITCH_TIMEOUT));
    }

    if (MODEM->SWITCH_MODE == 0)
    {
        ui->SWITCH->setChecked(false);
        ui->SwitchPropWidget->setEnabled(false);
    }
    else
    {
        ui->SWITCH->setChecked(true);
        ui->SwitchPropWidget->setEnabled(true);
    }
    ui->RXTM->setText(QString("%1").arg(MODEM->RX_TIMEOUT));
    ui->TXTM->setText(QString("%1").arg(MODEM->TX_TIMEOUT));
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::SetSWITCH_MODE()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);

    ReadDataProgress = 0;

    if(ui->SWITCH->isChecked())
    {
        MODEM->SWITCH_MODE = 1;
        ui->SWITCH->setChecked(true);
        ui->SwitchPropWidget->setEnabled(true);
    }
    else
    {
        MODEM->SWITCH_MODE = 0;
        ui->SWITCH->setChecked(false);
        ui->SwitchPropWidget->setEnabled(false);
    }
    ConnectHandling(SEND_WRITE_NODE_TYPE,1);
}
void ConnectHandlerClass::isSWITCH_MODE()
{
    if(ui->SWITCH->isChecked())
    {
        MODEM->SWITCH_MODE = 1;

        ui->SWITCH->setChecked(true);
        ui->SwitchPropWidget->setEnabled(true);
    }
    else
    {
        MODEM->SWITCH_MODE = 0;

        ui->SWITCH->setChecked(false);
        ui->SwitchPropWidget->setEnabled(false);
    }
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::SetSWITCH_PROP()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    if ((MODEM->BOOT_VERSION == 0))
    {
        if ((MODEM->BOOT_VERSION_SNIFER > 0)&&(MODEM->BOOT_VERSION_SNIFER < 20))
        {

        }
        else if(MODEM->BOOT_VERSION_SNIFER >= 20)
        {
            MODEM->SWITCH_LEVEL   = ui->NetLevel->text().toInt();
            MODEM->SWITCH_TIMEOUT = 10;
        }
    }
    else if ((MODEM->BOOT_VERSION > 0)&(MODEM->BOOT_VERSION < 3))
    {

    }
    else if ((MODEM->BOOT_VERSION >= 3) & (MODEM->BOOT_VERSION < 5))
    {
        MODEM->SWITCH_LEVEL   = ui->SWITCHLVL->text().toInt();
        MODEM->SWITCH_TIMEOUT = ui->SWITCHTM->text().toInt();
    }
    else if ((MODEM->BOOT_VERSION >= 5) & (MODEM->BOOT_VERSION < 6))
    {
        MODEM->SWITCH_LEVEL   = ui->SWITCHLVL->text().toInt();
        MODEM->SWITCH_TIMEOUT = ui->SWITCHTM->text().toInt();
    }

    ReadDataProgress = 0;
    ConnectHandling(SEND_WRITE_SWITCH_LEVEL,1);
}
void ConnectHandlerClass::isSWITCH_PROP()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);

    if ((MODEM->BOOT_VERSION == 0))
    {
        if ((MODEM->BOOT_VERSION_SNIFER > 0)&&(MODEM->BOOT_VERSION_SNIFER < 20))
        {

        }
        else if(MODEM->BOOT_VERSION_SNIFER >= 20)
        {
            ui->NetLevel->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
        }
    }
    else if ((MODEM->BOOT_VERSION > 0)&(MODEM->BOOT_VERSION < 3))
    {

    }
    else if ((MODEM->BOOT_VERSION >= 3) & (MODEM->BOOT_VERSION < 5))
    {
        ui->SWITCHLVL->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
        ui->SWITCHTM->setText(QString("%1").arg(MODEM->SWITCH_TIMEOUT));
    }
    else if ((MODEM->BOOT_VERSION >= 5) & (MODEM->BOOT_VERSION < 6))
    {
        ui->SWITCHLVL->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
        ui->SWITCHTM->setText(QString("%1").arg(MODEM->SWITCH_TIMEOUT));
    }
}

void ConnectHandlerClass::ReadCURRENT_RSSI()
{
    if(ui->MANUAL_ENTER->isEnabled()) // если ручной ввод
    {
        ui->CRC_OUT->setChecked(true);
        ui->cEnterText->setText("FF FF FF FF BB 00");
        ui->cBtnSend->animateClick(1);
    }
    else                              // если активен конфигуратор
    {

    }
}
void ConnectHandlerClass::isCURRENT_RSSI()
{

}

void ConnectHandlerClass::ReadLRSSI_AFC()
{
    if(ui->MANUAL_ENTER->isEnabled()) // если ручной ввод
    {
        ui->CRC_OUT->setChecked(true);
        ui->cEnterText->setText("FF FF FF FF E5 00");
        ui->cBtnSend->animateClick(1);
    }
    else                              // если активен конфигуратор
    {

    }
}
void ConnectHandlerClass::isLRSSI_AFC()
{

}

void ConnectHandlerClass::WriteRF_PARAMS()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ConnectHandling(SEND_WRITE_RF_PARAMETERS,1);
}
void ConnectHandlerClass::isRF_PARAMS()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::SendRF_RESET()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ConnectHandling(SEND_RF_RESET,1);
}
void ConnectHandlerClass::isRF_RESET()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::SendSNIFER_MODE()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ConnectHandling(SEND_SNIFER_MODE,1);
}
void ConnectHandlerClass::isSNIFER_MODE()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::SendUPLINC_MODE()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ConnectHandling(SEND_UPLINC_MODE,1);
}
void ConnectHandlerClass::isUPLINC_MODE()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::SendCRC_DISABLE_MODE()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ConnectHandling(SEND_CRC_CHECK_MODE,1);
}
void ConnectHandlerClass::isCRC_DISABLE_MODE()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::SendBROADCAST_MODE()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ConnectHandling(SEND_BROADCASTING_MODE,1);
}
void ConnectHandlerClass::isBROADCAST_MODE()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::WriteSWITCH_TABLE()
{
    ui->RSSIWidget->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ConnectHandling(SEND_WRITE_SWITCH_TABLE_ELEMENT,1);
}
void ConnectHandlerClass::isSWITCH_TABLE()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
}

void ConnectHandlerClass::StartMonitor()
{
    if ((ui->MonitorStart->isEnabled() == true)&&(ui->MonitorStop->isEnabled() == false))
    {
        emit SendLog(QString::fromUtf8("\r>> ======= Старт RSSI Монитор\r"),NONE);

        ui->MonitorStart->setEnabled(false);
        ui->MonitorStop->setEnabled(true);
        ui->RSSIWidget->setEnabled(false);
        ui->MonitorTimeout->setEnabled(false);
        ui->progressBar->setValue(0);

        uint timeout = ui->MonitorTimeout->text().toInt();
        uint parameter = ui->Interface->currentIndex();

        Monitor = new MonitorClass(timeout,parameter);
        connect(Monitor,SIGNAL(SendComand(uint,uint)),this->DataLogic,SLOT(ComandHandling(uint,uint)));
        connect(this,SIGNAL(MonitorStart()),Monitor,SLOT(startMonitor()));
        connect(this,SIGNAL(MonitorStop()),Monitor,SLOT(stopMonitor()));

        emit MonitorStart();
    }
}
void ConnectHandlerClass::StopMonitor()
{
    if ((ui->MonitorStart->isEnabled() == false)&&(ui->MonitorStop->isEnabled() == true))
    {
        emit SendLog(QString::fromUtf8(">> ======= Стоп RSSI Монитор\r"),NONE);

        ui->MonitorStart->setEnabled(true);
        ui->MonitorStop->setEnabled(false);
        ui->RSSIWidget->setEnabled(true);
        ui->MonitorTimeout->setEnabled(true);
        ui->progressBar->setValue(0);

        emit MonitorStop();
    }
}

void ConnectHandlerClass::ConnectHandling(uint n, uint state)
{
    DataLogic->DataLogicMode = n;
    if (n == CONNECT_HANDLING)
    {
        if (ReadDataProgress == 0)
        {
            ui->progressBar->setValue(0);
            emit SendLog(QString::fromUtf8("\r>> ======= Запрос версии ПО\r"),NONE);
            emit SendComand(SEND_AOPEN,CONFIG_SEND_CONTROL);
            ReadDataProgress = 1;
        }
        else
        {
            if ((MODEM->BOOT_VERSION == 0))
            {
                ui->tabWidget->addTab(SniferTab,     "USB/RF Преобразователь");
                if ((MODEM->BOOT_VERSION_SNIFER > 0)&&(MODEM->BOOT_VERSION_SNIFER < 20))
                {
                    n = RF_SNIFFER_OLD_READ_DATA;
                }
                else if(MODEM->BOOT_VERSION_SNIFER >= 20)
                {
                    n = RF_SNIFFER_READ_DATA;
                }
                ui->tabWidget->addTab(RFMonitorTab,  "RF RSSI Монитор");
            }
            else if ((MODEM->BOOT_VERSION > 0)&(MODEM->BOOT_VERSION < 3))
            {
                n = PLC_READ_DATA;
            }
            else if ((MODEM->BOOT_VERSION >= 3) & (MODEM->BOOT_VERSION < 5))
            {
                n = RF_OLD_READ_DATA;
            }
            else if ((MODEM->BOOT_VERSION >= 5) & (MODEM->BOOT_VERSION < 6))
            {
                n = RF_READ_DATA;
            }

            switch (n)
            {
            case PLC_READ_DATA:
            {
                switch (ReadDataProgress)
                {
                case 0:
                {
                    ReadDataProgress = 1;
                    break;
                }
                case 1:
                {
                    ReadDataProgress = 0;
                    break;
                }
                }

                break;
            }
            case RF_READ_DATA:
            {
                switch (ReadDataProgress)
                {
                case 0:
                {
                    ReadDataProgress = 1;
                    break;
                }
                case 1:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(8);
                        emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров из буфера\r"),NONE);
                        emit SendComand(SEND_READ_PROPERTYS_FROM_FLASH,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 2;
                    }
                    break;
                }
                case 2:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(16);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                        emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 3;
                    }
                    break;
                }
                case 3:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(24);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                        emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 4;
                    }
                    break;
                }
                case 4:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(32);
                        emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров калибровки из буфера\r"),NONE);
                        emit SendComand(SEND_READ_CALIBPROPS_FROM_FLASH,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 5;
                    }
                    break;
                }
                case 5:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(40);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                        emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 6;
                    }
                    break;
                }
                case 6:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(48);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                        emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 7;
                    }
                    break;
                }
                case 7:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(56);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание сетевых наcтроек\r"),NONE);
                        emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 8;
                    }
                    break;
                }
                case 8:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(64);
                        emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 9;
                    }
                    break;
                }
                case 9:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(72);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов\r"),NONE);
                        emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 10;
                    }
                    break;
                }
                case 10:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(80);
                        emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 11;
                    }
                    break;
                }
                case 11:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(88);
                        emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 12;
                    }
                    break;
                }
                case 12:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(100);
                        emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                        isAOPEN();
                        ReadDataProgress = 0;
                    }
                    break;
                }
                }
                break;
            }
            case RF_OLD_READ_DATA:
            {
                switch (ReadDataProgress)
                {
                case 0:
                {
                    ReadDataProgress = 1;
                    break;
                }
                case 1:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(8);
                        emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров из буфера\r"),NONE);
                        emit SendComand(SEND_READ_SI4432_PARAMETERS,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 2;
                    }
                    break;
                }
                case 2:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(56);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание сетевых наcтроек\r"),NONE);
                        emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 3;
                    }
                    break;
                }
                case 3:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(64);
                        emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 4;
                    }
                    break;
                }
                case 4:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(72);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов\r"),NONE);
                        emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                        if (MODEM->BOOT_VERSION >= 4)
                        {
                            ReadDataProgress = 5;
                        }
                        else
                        {
                            ReadDataProgress = 7;
                        }
                    }
                    break;
                }
                case 5:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(80);
                        emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 6;
                    }
                    break;
                }
                case 6:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(88);
                        emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 7;
                    }
                    break;
                }
                case 7:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(100);
                        emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                        isAOPEN();
                        ReadDataProgress = 0;
                    }
                    break;
                }
                }
                break; 
            }
            case RF_SNIFFER_OLD_READ_DATA:
            {
                break;
            }
            case RF_SNIFFER_READ_DATA:
            {
                switch (ReadDataProgress)
                {
                case 0:
                {
                    ReadDataProgress = 1;
                    break;
                }
                case 1:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(8);
                        emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров из буфера\r"),NONE);
                        emit SendComand(SEND_READ_PROPERTYS_FROM_FLASH,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 2;
                    }
                    break;
                }
                case 2:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(16);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                        emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 3;
                    }
                    break;
                }
                case 3:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(24);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(0);
                        emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 4;
                    }
                    break;
                }
                case 4:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(32);
                        emit SendLog(QString::fromUtf8("\r>> ======= Загрузка параметров калибровки из буфера\r"),NONE);
                        emit SendComand(SEND_READ_CALIBPROPS_FROM_FLASH,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 5;
                    }
                    break;
                }
                case 5:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(40);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                        emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 6;
                    }
                    break;
                }
                case 6:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(48);
                        DataLogic->setCurrentSI4463_PROPERTYS_structur(1);
                        emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 7;
                    }
                    break;
                }
                case 7:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(64);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание уровня сети RF\r"),NONE);
                        emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 8;
                    }
                    break;
                }
                case 8:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(80);
                        emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов RF\r"),NONE);
                        emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 9;
                    }
                    break;
                }
                case 9:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(88);
                        emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 10;
                    }
                    break;
                }
                case 10:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(88);
                        emit SendComand(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                        ReadDataProgress = 11;
                    }
                    break;
                }
                case 11:
                {
                    if (state != 0)
                    {
                        ui->progressBar->setValue(100);
                        emit SendLog(QString::fromUtf8(">> ======= Открытие сеанса связи завершилось успешно\r"),NONE);
                        isAOPEN();
                        ReadDataProgress = 0;
                    }
                    break;
                }
                }
            break;
            }
            }
        }
    }
    else if (n == SEND_WRITE_NODE_TYPE)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись режима сети\r"),NONE);
                emit SendComand(SEND_WRITE_NODE_TYPE,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(50);
                emit SendLog(QString::fromUtf8("\r>> ======= Чтение режима сети\r"),NONE);
                emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                ReadDataProgress = 2;
            }
            break;
        }
        case 2:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Установка режима прошла успешно\r"),NONE);
                isSWITCH_MODE();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_WRITE_SWITCH_LEVEL)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                if (MODEM->BOOT_VERSION >= 4)
                {
                    ui->progressBar->setValue(0);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись уровня ретранслятора\r"),NONE);
                    emit SendComand(SEND_WRITE_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 1;
                }
                else
                {
                    ui->progressBar->setValue(60);
                    emit SendLog(QString::fromUtf8("\r>> ======= Запись задержки ретранслятора\r"),NONE);
                    emit SendComand(SEND_WRITE_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 3;
                }
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(30);
                emit SendLog(QString::fromUtf8("\r>> ======= Чтение уровня ретранслятора\r"),NONE);
                emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                if (MODEM->BOOT_VERSION == 0)
                {
                    ReadDataProgress = 4;
                }
                else
                {
                    ReadDataProgress = 2;
                }
            }
            break;
        }
        case 2:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(60);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись задержки ретранслятора\r"),NONE);
                emit SendComand(SEND_WRITE_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                ReadDataProgress = 3;
            }
            break;
        }
        case 3:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(90);
                emit SendLog(QString::fromUtf8("\r>> ======= Чтение задержки ретранслятора\r"),NONE);
                emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                ReadDataProgress = 4;
            }
            break;
        }
        case 4:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Установка параметров прошла успешно\r"),NONE);
                isSWITCH_PROP();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_WRITE_RF_PARAMETERS)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(16);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись основных параметров радио-модуля в RAM\r"),NONE);
                DataLogic->setCurrentSI4463_PROPERTYS_structur(2);
                emit SendComand(SEND_BF_AF_00_AC_00,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(32);
                DataLogic->setCurrentSI4463_PROPERTYS_structur(2);
                emit SendComand(SEND_BF_8B_21_88_00,CONFIG_SEND_CONTROL);
                ReadDataProgress = 2;
            }
            break;
        }
        case 2:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(48);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно"),NONE);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись основных параметров радио-модуля во FLASH\r"),NONE);
                emit SendComand(SEND_LOAD_PROPERTYS_TO_FLASH,CONFIG_SEND_CONTROL);
                ReadDataProgress = 3;
            }
            break;
        }
        case 3:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(64);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись параметров IQ калибровки радио-модуля в RAM\r"),NONE);
                DataLogic->setCurrentSI4463_PROPERTYS_structur(3);
                emit SendComand(SEND_BF_AF_00_AC_00,CONFIG_SEND_CONTROL);
                ReadDataProgress = 4;
            }
            break;
        }
        case 4:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(80);
                DataLogic->setCurrentSI4463_PROPERTYS_structur(3);
                emit SendComand(SEND_BF_8B_21_88_00,CONFIG_SEND_CONTROL);
                ReadDataProgress = 5;
            }
            break;
        }
        case 5:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(96);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно"),NONE);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись параметров IQ калибровки радио-модуля во FLASH\r"),NONE);
                emit SendComand(SEND_LOAD_CALIBPROPS_TO_FLASH,CONFIG_SEND_CONTROL);
                ReadDataProgress = 6;
            }
            break;
        }
        case 6:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                isRF_PARAMS();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_RF_RESET)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Перезагрузка радио-модуля\r"),NONE);
                emit SendComand(SEND_RF_RESET,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Модуль перезагружен успешно\r"),NONE);
                isRF_RESET();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_SNIFER_MODE)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись режима работы USB/RF преобразователя\r"),NONE);
                emit SendComand(SEND_SNIFER_MODE,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                isSNIFER_MODE();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_UPLINC_MODE)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Установка UP_Link\r"),NONE);
                emit SendComand(SEND_UPLINC_MODE,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                isUPLINC_MODE();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_CRC_CHECK_MODE)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись режима проверки CRC\r"),NONE);
                emit SendComand(SEND_CRC_CHECK_MODE,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                isCRC_DISABLE_MODE();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_BROADCASTING_MODE)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись режима широковещания\r"),NONE);
                emit SendComand(SEND_BROADCASTING_MODE,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                isBROADCAST_MODE();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
    else if (n == SEND_WRITE_SWITCH_TABLE_ELEMENT)
    {
        switch (ReadDataProgress)
        {
        case 0:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись таблицы в RAM\r"),NONE);
                emit SendComand(SEND_WRITE_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                ReadDataProgress = 1;
            }
            break;
        }
        case 1:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Запись таблицы во Flash\r"),NONE);
                emit SendComand(SEND_LOAD_SWITCH_TABLE_TO_FLASH,CONFIG_SEND_CONTROL);
                ReadDataProgress = 2;
            }
            break;
        }
        case 2:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(0);
                emit SendLog(QString::fromUtf8("\r>> ======= Чтение таблицы\r"),NONE);
                emit SendComand(SEND_READ_SWITCH_TABLE_ELEMENT,CONFIG_SEND_CONTROL);
                ReadDataProgress = 3;
            }
            break;
        }
        case 3:
        {
            if (state != 0)
            {
                ui->progressBar->setValue(100);
                emit SendLog(QString::fromUtf8(">> ======= Запись прошла успешно\r"),NONE);
                isBROADCAST_MODE();
                ReadDataProgress = 0;
            }
            break;
        }
        }
    }
}
