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
    connect(this->DataLogic,SIGNAL(outConnect(uint)),this,SLOT(ConnectHandling(uint)));


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
        emit SendLog(QString::fromUtf8(">> ======= Подключение к устройству\r"),NONE);
        ConnectHandling(CONNECT_HANDLING);
    }
    else if (s.compare("Отключение") == 0)
    {
        ui->boot_v->setText("");
        ui->fw_v->setText("");
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

    ui->tabWidget->addTab(NetTab,            "Настройки Сети");
    if ((MODEM->BOOT_VERSION > 0)&(MODEM->BOOT_VERSION < 3))
    {
        ui->tabWidget->addTab(PLCTab,        "Настройки PLC");
    }
    if ((MODEM->BOOT_VERSION >= 3) & (MODEM->BOOT_VERSION < 5))
    {
        ui->tabWidget->addTab(RFOldTab,      "Настройки RF");
    }
    else if ((MODEM->BOOT_VERSION >= 5) & (MODEM->BOOT_VERSION < 6))
    {
        ui->tabWidget->addTab(RFTab,         "Настройки RF");
        ui->tabWidget->addTab(RFMonitorTab,  "RF RSSI Монитор");
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
    ui->SWITCHLVL->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
    ui->SWITCHTM->setText(QString("%1").arg(MODEM->SWITCH_TIMEOUT));
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
    ConnectHandling(SEND_WRITE_NODE_TYPE);
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
    MODEM->SWITCH_LEVEL   = ui->SWITCHLVL->text().toInt();
    MODEM->SWITCH_TIMEOUT = ui->SWITCHTM->text().toInt();
    ReadDataProgress = 0;
    ConnectHandling(SEND_WRITE_SWITCH_LEVEL);
}
void ConnectHandlerClass::isSWITCH_PROP()
{
    ui->RSSIWidget->setEnabled(true);
    ui->tabWidget->setEnabled(true);
    ui->SWITCHLVL->setText(QString("%1").arg(MODEM->SWITCH_LEVEL));
    ui->SWITCHTM->setText(QString("%1").arg(MODEM->SWITCH_TIMEOUT));
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

void ConnectHandlerClass::ConnectHandling(uint n)
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
            if ((MODEM->BOOT_VERSION > 0)&(MODEM->BOOT_VERSION < 3))
            {
                n = PLC_READ_DATA;
            }
            if ((MODEM->BOOT_VERSION >= 3) & (MODEM->BOOT_VERSION < 5))
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
                    ui->progressBar->setValue(10);
                    emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание параметров RF\r"),NONE);
                    emit SendComand(SEND_BF_03_00_AC_00,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 2;
                    break;
                }
                case 2:
                {
                    ui->progressBar->setValue(40);
                    emit SendComand(SEND_BF_03_21_88_00,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 3;
                    break;
                }
                case 3:
                {
                    ui->progressBar->setValue(50);
                    emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание сетевых наcтроек\r"),NONE);
                    emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 4;
                    break;
                }
                case 4:
                {
                    ui->progressBar->setValue(60);
                    emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 5;
                    break;
                }
                case 5:
                {
                    ui->progressBar->setValue(70);
                    emit SendLog(QString::fromUtf8("\r>> ======= Cчитывание таймаутов\r"),NONE);
                    emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 6;
                    break;
                }
                case 6:
                {
                    ui->progressBar->setValue(80);
                    emit SendComand(SEND_READ_RX_TIMEOUT,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 7;
                    break;
                }
                case 7:
                {
                    ui->progressBar->setValue(90);
                    emit SendComand(SEND_READ_TX_TIMEOUT,CONFIG_SEND_CONTROL);
                    ReadDataProgress = 8;
                    break;
                }
                case 8:
                {
                    ui->progressBar->setValue(100);
                    isAOPEN();
                    ReadDataProgress = 0;
                    break;
                }
                }
                break;
            }
            case RF_OLD_READ_DATA:
            {
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
            ui->progressBar->setValue(0);
            emit SendComand(SEND_WRITE_NODE_TYPE,CONFIG_SEND_CONTROL);
            ReadDataProgress = 1;
            break;
        }
        case 1:
        {
            ui->progressBar->setValue(50);
            emit SendComand(SEND_READ_NODE_TYPE,CONFIG_SEND_CONTROL);
            ReadDataProgress = 2;
            break;
        }
        case 2:
        {
            ui->progressBar->setValue(100);
            isSWITCH_MODE();
            ReadDataProgress = 0;
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
            ui->progressBar->setValue(0);
            emit SendComand(SEND_WRITE_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
            ReadDataProgress = 1;
            break;
        }
        case 1:
        {
            ui->progressBar->setValue(30);
            emit SendComand(SEND_READ_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
            ReadDataProgress = 2;
            break;
        }
        case 2:
        {
            ui->progressBar->setValue(60);
            emit SendComand(SEND_WRITE_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
            ReadDataProgress = 3;
            break;
        }
        case 3:
        {
            ui->progressBar->setValue(90);
            emit SendComand(SEND_READ_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
            ReadDataProgress = 4;
            break;
        }
        case 4:
        {
            ui->progressBar->setValue(100);
            isSWITCH_PROP();
            ReadDataProgress = 0;
            break;
        }
        }
    }
}
