#include "connections_form.h"
#include "settings_form.h"
#include "ui_connections_form.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QTouchEvent>
#include "OTHER_FUNCTIONS/barr_to_string.h"

Connections_Form::Connections_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connections_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    if (settings.value(CONNECTION_SETTINGS_REPEATE).toString() == "")
    {
        settings.setValue(CONNECTION_SETTINGS_REPEATE, "3");
        settings.sync();
    }
    if (settings.value(CONNECTION_SETTINGS_PERIODE).toString() == "")
    {
        settings.setValue(CONNECTION_SETTINGS_PERIODE, "3000");
        settings.sync();
    }

    ui->IPInput->setText(settings.value(TCP_SETTINGS_IP).toString());
    ui->PORTInput->setText(settings.value(TCP_SETTINGS_PORT).toString());

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->COMConnect->setStyleSheet(Basic_Buttons_Style);
    ui->TCPConnect->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->btnHandsEnter->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->btnNext->setStyleSheet(Buttons_Style);

    ui->PortNameBox->setStyleSheet(Background_White);
    ui->IPInput->setStyleSheet(Background_White);
    ui->PORTInput->setStyleSheet(Background_White);

    SysInfo              = new QSysInfo;
    QString product_name = SysInfo->prettyProductName();

    RegSystemName        = QRegExp("[A-Za-z]+");
    RegSystemName.indexIn(product_name,0);

    if (RegSystemName.cap(0).compare("Android") == 0)
    {
        setWindowState(Qt::WindowMaximized);
    }
    else if (RegSystemName.cap(0).compare("Windows") == 0)
    {
        this->setWindowModality(Qt::WindowModal);
        //this->setFixedSize (340,560);
    }

    timer_COMBufferClear      = new QTimer();
    timer_ConnectionsPanel    = new QTimer();
    MODEM                     = new MODEMClass();
    newPort                   = new Port();                                                                   // Создаем Поток обработки портов
    newTCP                    = new TCP();
    oCRC16                    = new CRC16_Class();                                                            // Создаём Объект расчёта CRC
    newParcer                 = new ParceClass();
    SI4463Config              = new SI4463Class();
    SI4432Config              = new SI4432Class();
    //PLCConfig                 = new PLCClass(ui);
    newUPDATE                 = new UPDATE();

    DataLogic                 = new DataLogic_Class(oCRC16,timer_COMBufferClear,SI4463Config,SI4432Config,
                                                    PLCConfig,MODEM,newPort,newTCP,newUPDATE,this);           // Создаём Объект обработки сообщений
    ConnectHandler            = new ConnectHandlerClass(DataLogic, MODEM, newUPDATE);

    connect(newPort,  SIGNAL(COM_Started()),                  this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(newPort,  SIGNAL(COM_Log(QString,uint)),          this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    connect(newPort,  SIGNAL(COM_Opend()),                    this, SLOT(COM_Is_Opend()));

    connect(newTCP,   SIGNAL(TCP_Log(QString,uint)),          this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    connect(newTCP,   SIGNAL(TCP_Connected()),                this, SLOT(TCP_Is_Connected()));

    connect(DataLogic,SIGNAL(SendLog(QString,uint)),          this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,SIGNAL(LogForPrint(QString,uint)),      this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,SIGNAL(DataForPrint(QByteArray,uint)),  this, SLOT(Print(QByteArray,uint)));

    connect(DataLogic,SIGNAL(STOPPED()),                      ConnectHandler,SLOT(StopMonitor()));
    connect(DataLogic,SIGNAL(STOPPED()),                      ConnectHandler,SLOT(STOP()));
    connect(DataLogic,SIGNAL(noANSWER()),                     ConnectHandler,SLOT(StopMonitor()));
    connect(DataLogic,SIGNAL(noANSWER()),                     ConnectHandler,SLOT(STOP()));

    connect(ConnectHandler,    SIGNAL(SendLog(QString,uint)), this, SLOT(Print_Log(QString,uint)));

    connect(ui->btnNext,       SIGNAL(clicked()),             this, SLOT(Create_And_Show_Open_Connection_Form()));
    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));

    connect(newParcer,         SIGNAL(PARCE_End()),           SI4463Config,SLOT(request_Prameters_handling()));

    DataLogic->setRepeatNumber(settings.value(CONNECTION_SETTINGS_REPEATE).toInt());
    DataLogic->setRepeatTimeout(settings.value(CONNECTION_SETTINGS_PERIODE).toInt());

    ui->PortNameBox           ->installEventFilter(this);

    newPort->start();
    newTCP ->start();
}
void Connections_Form::resizeEvent(QResizeEvent *event)
{

    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    int text_size_3 = resize_calculating.get_text_size_3();
    int text_size_4 = resize_calculating.get_text_size_4();
    int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1 = ui->label_1->font();    font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->label_2->font();    font_2.setPixelSize(text_size_2);
    QFont font_3 = ui->COMConnect->font(); font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->label_4->font();    font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();    font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);
    ui->label_3->setFont(font_2);
    ui->label_4->setFont(font_4);
    ui->label_5->setFont(font_4);
    ui->label_6->setFont(font_4);

    ui->PortNameBox->setFont(font_3);
    ui->COMConnect->setFont(font_3);
    ui->IPInput->setFont(font_3);
    ui->PORTInput->setFont(font_3);
    ui->TCPConnect->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->console->setFont(font_5);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->btnNext->setIconSize(icons_size); ui->btnNext->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnHandsEnter->setIconSize(icons_size); ui->btnHandsEnter->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}


bool Connections_Form::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->PortNameBox && event->type() == QEvent::MouseButtonPress)
    {
       if (ui->PortNameBox->isEnabled())
       {
           ui->PortNameBox->clear();
           foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
           {
              ui->PortNameBox->addItem(info.portName());
              ui->COMConnect->setEnabled(true);
           }
       }
    }
    if (event->type() == QEvent::TouchUpdate)
    {
        QTouchDevice touchscreen;
    }
    return false;
}

Connections_Form::~Connections_Form()
{
    delete ui;
}

void Connections_Form::on_TCPConnect_clicked()
{
    Set_ActiveConsole(ui->console);

    if(ui->TCPConnect->text() == "Подключить")
    {
        newPort->COM_Disconnect();
        newTCP->TCP_SetIP(ui->IPInput->text());
        newTCP->TCP_SetPORT(ui->PORTInput->text().toInt());
        newTCP->TCP_Connect();

        ui->TCPConnect->setText("Отключить");
    }
    else
    {
        newTCP->TCP_Disconnect();

        ui->TCPConnect->setText("Подключить");
        ui->btnHandsEnter->setEnabled(false);
        ui->btnNext->setEnabled(false);
        ui->COMConnect->setEnabled(true);
        ui->PortNameBox->setEnabled(true);
        ui->IPInput->setEnabled(true);
        ui->PORTInput->setEnabled(true);
    }
}

void Connections_Form::on_COMConnect_clicked()
{
    Set_ActiveConsole(ui->console);

    if(ui->COMConnect->text() == "Открыть")
    {
        newTCP->TCP_Disconnect();
        newPort->COM_Connect();

        ui->COMConnect->setText("Закрыть");
    }
    else
    {
        newPort->COM_Disconnect();

        ui->COMConnect->setText("Открыть");
        ui->btnHandsEnter->setEnabled(false);
        ui->btnNext->setEnabled(false);
        ui->TCPConnect->setEnabled(true);
        ui->PortNameBox->setEnabled(true);
        ui->IPInput->setEnabled(true);
        ui->PORTInput->setEnabled(true);
    }
}

void Connections_Form::start_COM_Init(void)
{
    newPort->COM_SetBaudRate(QSerialPort::Baud9600);
    newPort->COM_SetDataBits(QSerialPort::Data8);
    newPort->COM_SetParity(QSerialPort::NoParity);
    //newPort->COM_SetParity(QSerialPort::EvenParity);
    //newPort->COM_SetParity(QSerialPort::OddParity);
    //newPort->COM_SetParity(QSerialPort::MarkParity);
    //newPort->COM_SetParity(QSerialPort::SpaceParity);
    newPort->COM_SetStopBits(QSerialPort::OneStop);
    //newPort->COM_SetStopBits(QSerialPort::OneAndHalfStop);
    //newPort->COM_SetStopBits(QSerialPort::TwoStop);
    newPort->COM_SetFlowControl(QSerialPort::NoFlowControl);
    //newPort->COM_SetFlowControl(QSerialPort::HardwareControl);
    //newPort->COM_SetFlowControl(QSerialPort::SoftwareControl);
}

void Connections_Form::TCP_Is_Connected(void)
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(TCP_SETTINGS_IP, ui->IPInput->text());
    settings.setValue(TCP_SETTINGS_PORT, ui->PORTInput->text());
    settings.sync();

    ui->btnHandsEnter->setEnabled(true);
    ui->btnNext->setEnabled(true);
    ui->COMConnect->setEnabled(false);
    ui->PortNameBox->setEnabled(false);
    ui->IPInput->setEnabled(false);
    ui->PORTInput->setEnabled(false);
}
void Connections_Form::COM_Is_Opend(void)
{
    ui->btnHandsEnter->setEnabled(true);
    ui->btnNext->setEnabled(true);
    ui->TCPConnect->setEnabled(false);
    ui->PortNameBox->setEnabled(false);
    ui->IPInput->setEnabled(false);
    ui->PORTInput->setEnabled(false);
}

void Connections_Form::Set_Geometry(QRect new_value)
{
    this->setGeometry(new_value);
}

void Connections_Form::Start_Parcer(QString file_name)
{
    newParcer->PARCE_Start(file_name, SI4463Config);
}

void Connections_Form::Define_Next_Form(QRect curren_geometry)
{
    FirmwareInformationClass *In_Firmware_Information = MODEM->getIn_Firmware_Information();

    if (In_Firmware_Information->getDevice_Name().compare(PLC_MODEM) == 0)
    {

    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4432) == 0)
    {
        if(open_connection_form->isHidden() == false)
        {
            open_connection_form->hide();
            Create_And_Show_Net_Settings_Form(curren_geometry);
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0)
    {
        if(open_connection_form->isHidden() == false)
        {
            open_connection_form->hide();
            Create_And_Show_Sniffer_Settings_Form(curren_geometry);
        }
        else if(sniffer_settings_form->isHidden() == false)
        {
            sniffer_settings_form->hide();
            Create_And_Show_SI4432_Settings_Form(curren_geometry);
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_MODEM) == 0)
    {

    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_SNIFFER) == 0)
    {
        if(open_connection_form->isHidden() == false)
        {
            open_connection_form->hide();
            Create_And_Show_Sniffer_Settings_Form(curren_geometry);
        }
        else if(sniffer_settings_form->isHidden() == false)
        {
            sniffer_settings_form->hide();
            Create_And_Show_SI4463_Settings_Form(curren_geometry);
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(TERMINAL) == 0)
    {

    }
}
void Connections_Form::Define_Pre_Form(QRect curren_geometry)
{
    FirmwareInformationClass *In_Firmware_Information = MODEM->getIn_Firmware_Information();

    if (In_Firmware_Information->getDevice_Name().compare(PLC_MODEM) == 0)
    {

    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4432) == 0)
    {

    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0)
    {
        if(sniffer_settings_form->isHidden() == false)
        {
            sniffer_settings_form->deleteLater();
            open_connection_form->setGeometry(curren_geometry);
            open_connection_form->show();
        }
        else if(si4432_settings_form->isHidden() == false)
        {
            si4432_settings_form->deleteLater();
            sniffer_settings_form->setGeometry(curren_geometry);
            sniffer_settings_form->show();
        }
        else if (settings_form->isHidden() == false)
        {
            settings_form->deleteLater();
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_MODEM) == 0)
    {

    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_SNIFFER) == 0)
    {
        if(sniffer_settings_form->isHidden() == false)
        {
            sniffer_settings_form->deleteLater();
            open_connection_form->setGeometry(curren_geometry);
            open_connection_form->show();
        }
        else if(si4463_settings_form->isHidden() == false)
        {
            si4463_settings_form->deleteLater();
            sniffer_settings_form->setGeometry(curren_geometry);
            sniffer_settings_form->show();
        }
        else if (settings_form->isHidden() == false)
        {
            settings_form->deleteLater();
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(TERMINAL) == 0)
    {

    }
}

void Connections_Form::Create_And_Show_Settings_Form(QWidget *parent)
{
    settings_form = new Settings_Form;
    connect(settings_form,SIGNAL(Cancel()),                                  parent,                SLOT(show()));
    connect(settings_form,SIGNAL(Get_Geometry(QRect)),                       parent,                SLOT(Set_Geometry(QRect)));
    connect(settings_form,SIGNAL(GetRepeatNumber(uint)),                     DataLogic,             SLOT(setRepeatNumber(uint)));
    connect(settings_form,SIGNAL(GetRepeatTimeout(uint)),                    DataLogic,             SLOT(setRepeatTimeout(uint)));

    parent->hide();
    settings_form->setGeometry(parent->geometry());
    settings_form->show();
}

void Connections_Form::Create_And_Show_Hands_Enter_Form(QWidget *parent)
{
    hands_enter_form = new Hands_Enter_Form;
    connect(hands_enter_form,SIGNAL(Cancel()),                               parent,                SLOT(show()));
    connect(hands_enter_form,SIGNAL(Get_Geometry(QRect)),                    parent,                SLOT(Set_Geometry(QRect)));
    connect(hands_enter_form,SIGNAL(Send_Data(QByteArray,uint)),             DataLogic,             SLOT(SEND_DATA(QByteArray,uint)));
    connect(hands_enter_form,SIGNAL(Get_Console(QPlainTextEdit*)),           this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));

    parent->hide();
    hands_enter_form->setGeometry(parent->geometry());
    hands_enter_form->show();
}

void Connections_Form::Create_And_Show_Open_Connection_Form(void)
{
    open_connection_form = new Open_Connection_Form;

    connect(open_connection_form,SIGNAL(Cancel()),                           this,                  SLOT(show()));
    connect(open_connection_form,SIGNAL(Get_Geometry(QRect)),                this,                  SLOT(Set_Geometry(QRect)));
    connect(open_connection_form,SIGNAL(Get_Console(QPlainTextEdit*)),       this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(open_connection_form,SIGNAL(Next(QRect)),                        this,                  SLOT(Define_Next_Form(QRect)));
    connect(open_connection_form,SIGNAL(Settings(QWidget*)),                 this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(open_connection_form,SIGNAL(Updating(QWidget*)),                 this,                  SLOT(Create_And_Show_Firmware_Updating_Form(QWidget*)));
    connect(open_connection_form,SIGNAL(SendSerialNumber(QString,bool)),     DataLogic,             SLOT(setSerialNumberMode(QString,bool)));
    connect(open_connection_form,SIGNAL(STOP_SEND_DATA()),                   DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(open_connection_form,SIGNAL(SEND_RF_RESET()),                    ConnectHandler,        SLOT(SendRF_RESET()));
    connect(open_connection_form,SIGNAL(AOPEN()),                            ConnectHandler,        SLOT(aOPEN()));
    connect(ConnectHandler,      SIGNAL(isAOPEN()),                          open_connection_form,  SLOT(isOPEND()));
    connect(ConnectHandler,      SIGNAL(isRF_RESET()),                       open_connection_form,  SLOT(isRESET()));
    connect(ConnectHandler,      SIGNAL(Progress(uint)),                     open_connection_form,  SLOT(SetProgress(uint)));
    connect(DataLogic,           SIGNAL(STOPPED()),                          open_connection_form,  SLOT(isSTOPPED()));
    connect(MODEM,               SIGNAL(sIn_Firmware_Information(FirmwareInformationClass*)), open_connection_form,  SLOT(Set_In_Firmware_Information(FirmwareInformationClass *)));

    open_connection_form->setGeometry(this->geometry());
    this->hide();
    open_connection_form->show();
}

void Connections_Form::Create_And_Show_Net_Settings_Form(QRect current_geometry)
{
    net_settings_form = new Net_Settings_Form;

    connect(net_settings_form,SIGNAL(Cancel(QRect)),                        this,                  SLOT(Define_Pre_Form(QRect)));
    connect(net_settings_form,SIGNAL(Next(QRect)),                          this,                  SLOT(Define_Next_Form(QRect)));
    connect(net_settings_form,SIGNAL(Get_Console(QPlainTextEdit*)),         this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(net_settings_form,SIGNAL(Send_Data(QByteArray,uint)),           DataLogic,             SLOT(SEND_DATA(QByteArray,uint)));
    connect(net_settings_form,SIGNAL(isCreated()),                          MODEM,                 SLOT(getSWITCH_MODE()));
    connect(net_settings_form,SIGNAL(isCreated()),                          MODEM,                 SLOT(getSWITCH_LEVEL()));
    connect(net_settings_form,SIGNAL(isCreated()),                          MODEM,                 SLOT(getSWITCH_TIMEOUT()));
    connect(MODEM,            SIGNAL(SWITCH_MODE(uchar)),                   net_settings_form,     SLOT(SetSwitchModeToUI(uchar)));
    connect(MODEM,            SIGNAL(SWITCH_LEVEL(uint)),                   net_settings_form,     SLOT(SetSwitchLevelToUI(uint)));
    connect(MODEM,            SIGNAL(SWITCH_TIMEOUT(uint)),                 net_settings_form,     SLOT(SetSwitchTimeoutToUI(uint)));

    this->hide();
    net_settings_form->setGeometry(current_geometry);
    net_settings_form ->show();
}

void Connections_Form::Create_And_Show_Sniffer_Settings_Form(QRect current_geometry)
{
    sniffer_settings_form = new Sniffer_Settings_Form;

    connect(sniffer_settings_form,SIGNAL(Cancel(QRect)),                    this,                  SLOT(Define_Pre_Form(QRect)));
    connect(sniffer_settings_form,SIGNAL(Next(QRect)),                      this,                  SLOT(Define_Next_Form(QRect)));
    connect(sniffer_settings_form,SIGNAL(Settings(QWidget*)),               this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(sniffer_settings_form,SIGNAL(Get_Console(QPlainTextEdit*)),     this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(sniffer_settings_form,SIGNAL(Stop_Send_Data()),                 DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,            SIGNAL(STOPPED()),                        sniffer_settings_form, SLOT(isSTOPPED()));

    connect(ConnectHandler,       SIGNAL(Progress(uint)),                   sniffer_settings_form, SLOT(SetProgress(uint)));

    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(getOut_Sniffer_Properties()));
    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(getIn_Sniffer_Properties()));
    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(getOut_Retranslator_Properties()));
    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(getIn_Retranslator_Properties()));

    connect(MODEM, SIGNAL(sIn_Sniffer_Properties(SnifferPropertiesClass*)),  sniffer_settings_form, SLOT(Set_In_Sniffer_Properties(SnifferPropertiesClass*)));
    connect(MODEM, SIGNAL(sOut_Sniffer_Properties(SnifferPropertiesClass*)), sniffer_settings_form, SLOT(Set_Out_Sniffer_Properties(SnifferPropertiesClass*)));
    connect(MODEM, SIGNAL(sIn_Retranslator_Properties(RetranslatorPropertiesClass*)), sniffer_settings_form, SLOT(Set_In_Retranslator_Properties(RetranslatorPropertiesClass*)));
    connect(MODEM, SIGNAL(sOut_Retranslator_Properties(RetranslatorPropertiesClass*)), sniffer_settings_form, SLOT(Set_Out_Retranslator_Properties(RetranslatorPropertiesClass*)));

    connect(sniffer_settings_form,SIGNAL(Send_Sniffer_Mode()),              ConnectHandler,        SLOT(SendSNIFER_MODE()));
    connect(ConnectHandler,       SIGNAL(isSNIFER_MODE()),                  sniffer_settings_form, SLOT(isSnifferMode()));
    connect(sniffer_settings_form,SIGNAL(Send_UpLink_Mode()),               ConnectHandler,        SLOT(SendUPLINC_MODE()));
    connect(ConnectHandler,       SIGNAL(isUPLINC_MODE()),                  sniffer_settings_form, SLOT(isUpLink_Mode()));
    connect(sniffer_settings_form,SIGNAL(Send_Broadcasting_Mode()),         ConnectHandler,        SLOT(SendBROADCAST_MODE()));
    connect(ConnectHandler,       SIGNAL(isBROADCAST_MODE()),               sniffer_settings_form, SLOT(isBroadcasting_Mode()));
    connect(sniffer_settings_form,SIGNAL(Send_CRC_Disable_Mode()),          ConnectHandler,        SLOT(SendCRC_DISABLE_MODE()));
    connect(ConnectHandler,       SIGNAL(isCRC_DISABLE_MODE()),             sniffer_settings_form, SLOT(isCRC_Disable_Mode()));
    connect(sniffer_settings_form,SIGNAL(Send_Mask_Destination()),          ConnectHandler,        SLOT(WriteMASK_DESTINATION()));
    connect(ConnectHandler,       SIGNAL(isMASK_DESTINATION()),             sniffer_settings_form, SLOT(isMask_Destination()));
    connect(sniffer_settings_form,SIGNAL(Send_Write_Switch_Table()),        ConnectHandler,        SLOT(WriteSWITCH_TABLE()));
    connect(ConnectHandler,       SIGNAL(isSWITCH_TABLE()),                 sniffer_settings_form, SLOT(isSwitch_Table()));
    connect(sniffer_settings_form,SIGNAL(Send_Clear_Switch_Table()),        ConnectHandler,        SLOT(SendSWITCH_TABLE_DELETE()));
    connect(ConnectHandler,       SIGNAL(isSWITCH_TABLE_DELETE()),          sniffer_settings_form, SLOT(isSwitch_Table_Delete()));
    connect(sniffer_settings_form,SIGNAL(Send_RF_Reset()),                  ConnectHandler,        SLOT(SendRF_RESET()));
    connect(ConnectHandler,       SIGNAL(isRF_RESET()),                     sniffer_settings_form, SLOT(isRF_Reset()));

    this->hide();
    sniffer_settings_form->setGeometry(current_geometry);
    sniffer_settings_form->show();
}

void Connections_Form::Create_And_Show_SI4432_Settings_Form(QRect current_geometry)
{
    si4432_settings_form = new SI4432_Settings_Form;

    connect(si4432_settings_form,SIGNAL(Cancel(QRect)),                        this,                 SLOT(Define_Pre_Form(QRect)));
    connect(si4432_settings_form,SIGNAL(Next(QRect)),                          this,                 SLOT(Define_Next_Form(QRect)));
    connect(si4432_settings_form,SIGNAL(Settings(QWidget*)),                   this,                 SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(si4432_settings_form,SIGNAL(Get_Console(QPlainTextEdit*)),         this,                 SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(si4432_settings_form,SIGNAL(Stop_Send_Data()),                     DataLogic,            SLOT(STOP_SEND_DATA()));
    connect(DataLogic,           SIGNAL(STOPPED()),                            si4432_settings_form, SLOT(isSTOPPED()));
    connect(si4432_settings_form,SIGNAL(Send_RF_Reset()),                      ConnectHandler,       SLOT(SendRF_RESET()));
    connect(ConnectHandler,      SIGNAL(isRF_RESET()),                         si4432_settings_form, SLOT(isRF_Reset()));

    connect(ConnectHandler,      SIGNAL(Progress(uint)),                       si4432_settings_form,  SLOT(SetProgress(uint)));

    connect(si4432_settings_form,SIGNAL(isCreated()),                          SI4432Config,         SLOT(getOut_SI4432_RF_Config()));
    connect(si4432_settings_form,SIGNAL(isCreated()),                          SI4432Config,         SLOT(getIn_SI4432_RF_Config()));

    connect(SI4432Config,SIGNAL(sIn_SI4432_Parameters(SI4432ConfigurationClass*)),      si4432_settings_form, SLOT(setIn_SI4432_Parameters(SI4432ConfigurationClass*)));
    connect(SI4432Config,SIGNAL(sOut_SI4432_Parameters(SI4432ConfigurationClass*)),     si4432_settings_form, SLOT(setOut_SI4432_Parameters(SI4432ConfigurationClass*)));

    connect(si4432_settings_form,SIGNAL(Write_SI4432_Parameters()),            ConnectHandler,       SLOT(WriteRFSI4432_PARAMS()));
    connect(ConnectHandler,      SIGNAL(isRFSI4432_PARAMS()),                  si4432_settings_form, SLOT(isSI4432_Parameters()));

    this->hide();
    si4432_settings_form->setGeometry(current_geometry);
    si4432_settings_form->show();
}

void Connections_Form::Create_And_Show_SI4463_Settings_Form(QRect current_geometry)
{
    si4463_settings_form = new SI4463_Settings_Form;

    connect(si4463_settings_form,SIGNAL(Cancel(QRect)),                    this,                  SLOT(Define_Pre_Form(QRect)));
    connect(si4463_settings_form,SIGNAL(Next(QRect)),                      this,                  SLOT(Define_Next_Form(QRect)));
    connect(si4463_settings_form,SIGNAL(Settings(QWidget*)),               this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(si4463_settings_form,SIGNAL(Get_Console(QPlainTextEdit*)),     this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(si4463_settings_form,SIGNAL(Stop_Send_Data()),                 DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,           SIGNAL(STOPPED()),                        si4463_settings_form,  SLOT(isSTOPPED()));
    connect(si4463_settings_form,SIGNAL(Send_RF_Reset()),                  ConnectHandler,        SLOT(SendRF_RESET()));
    connect(ConnectHandler,      SIGNAL(isRF_RESET()),                     si4463_settings_form,  SLOT(isRF_Reset()));
    connect(si4463_settings_form,SIGNAL(Write_SI4463_Parameters()),        ConnectHandler,        SLOT(WriteRF_PARAMS()));
    connect(ConnectHandler,      SIGNAL(isRF_PARAMS()),                    si4463_settings_form,  SLOT(isSI4463_Parameters()));

    connect(ConnectHandler,      SIGNAL(Progress(uint)),                   si4463_settings_form,  SLOT(SetProgress(uint)));

    connect(si4463_settings_form,SIGNAL(isCreated()),                      SI4463Config,          SLOT(request_Model_handling()));
    connect(SI4463Config,        SIGNAL(get_Model(QStandardItemModel*)),   si4463_settings_form,  SLOT(Set_Model(QStandardItemModel*)));
    connect(SI4463Config,        SIGNAL(get_Prameters(QList<Params>*)),    si4463_settings_form,  SLOT(Set_Prameters(QList<Params>*)));

    connect(si4463_settings_form,SIGNAL(Start_Parcer(QString)),            this,                  SLOT(Start_Parcer(QString)));

    this->hide();
    si4463_settings_form->setGeometry(current_geometry);
    si4463_settings_form->show();
}

void Connections_Form::Create_And_Show_Firmware_Updating_Form(QWidget *parent)
{
    firmware_updating_form = new Firmware_Updating_Form;

    connect(firmware_updating_form,SIGNAL(Cancel()),                         parent,                SLOT(show()));
    connect(firmware_updating_form,SIGNAL(Get_Geometry(QRect)),              parent,                SLOT(Set_Geometry(QRect)));
    connect(firmware_updating_form,SIGNAL(Get_Console(QPlainTextEdit*)),     this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(firmware_updating_form,SIGNAL(Stop_Send_Data()),                 DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,             SIGNAL(STOPPED()),                        firmware_updating_form,SLOT(isStopped()));
    connect(firmware_updating_form,SIGNAL(Start_Update()),                   ConnectHandler,        SLOT(StartUPDATE()));
    connect(ConnectHandler,        SIGNAL(isUPDATED()),                      firmware_updating_form,SLOT(isUpdated()));
    connect(firmware_updating_form,SIGNAL(Start_Delete()),                   ConnectHandler,        SLOT(StartDELETE()));
    connect(ConnectHandler,        SIGNAL(isDELETED()),                      firmware_updating_form,SLOT(isDeleted()));

    connect(ConnectHandler,        SIGNAL(Progress(uint)),                   firmware_updating_form,SLOT(SetProgress(uint)));
    connect(DataLogic,             SIGNAL(outPROGRESS(uint)),                firmware_updating_form,SLOT(SetProgress(uint)));

    connect(firmware_updating_form,SIGNAL(Get_FirmwareData(QString,QByteArray)),newUPDATE,             SLOT(setDATA(QString,QByteArray)));

    connect(firmware_updating_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(getIn_Firmware_Information()));
    connect(MODEM,                 SIGNAL(sIn_Firmware_Information(FirmwareInformationClass*)), firmware_updating_form,  SLOT(Set_In_Firmware_Information(FirmwareInformationClass *)));

    parent->hide();
    firmware_updating_form->setGeometry(parent->geometry());
    firmware_updating_form->show();
}

//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void Connections_Form::Print(QByteArray data, uint n)
{
    QString s = "Print data";
    qDebug() << s;

    QByteArray d;
    d.append(data);

    switch (n)
    {
        case COM_TX:
        {
            ActiveConsole->textCursor().insertText("TX >> " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
            break;
        }
        case COM_RX:
        {
            ActiveConsole->textCursor().insertText("RX << " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
            break;
        }
    }
    QString str;str += '\r';
    ActiveConsole->textCursor().insertText(str); // Вывод текста в консоль
    ActiveConsole->moveCursor(QTextCursor::End);//Scroll
}

//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void Connections_Form::Print_Log(QString data, uint n)
{
    ActiveConsole->textCursor().insertText(data); // Вывод текста в консоль
    ActiveConsole->moveCursor(QTextCursor::End);  //Scroll
}

void Connections_Form::Set_ActiveConsole(QPlainTextEdit * new_active_console)
{
    ActiveConsole = new_active_console;
}

void Connections_Form::on_PortNameBox_currentIndexChanged(const QString &arg1)
{
   newPort->COM_SetPortName(arg1);
}

void Connections_Form::on_btnSettings_clicked()
{
    Create_And_Show_Settings_Form(this);
}

void Connections_Form::on_btnHandsEnter_clicked()
{
    Create_And_Show_Hands_Enter_Form(this);
}
