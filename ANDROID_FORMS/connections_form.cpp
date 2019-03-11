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
    this->setWindowTitle(WINDOW_TITLE);

    //TextInfoReading();

    this->setWindowIcon(QIcon(":/images/icons/images/AppIcon.ico"));
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
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->COMConnect->setStyleSheet(Basic_PushButtons_Style);
    ui->TCPConnect->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);
    ui->RSSIMonitor->setStyleSheet(Basic_PushButtons_Style);
    ui->PGAMonitor->setStyleSheet(Basic_PushButtons_Style);

    ui->btnHandsEnter->setStyleSheet(PushButtons_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style);
    ui->btnNext->setStyleSheet(PushButtons_Style);
    ui->Next_Widget->setEnabled(true);

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
    PLCConfig                 = new PLCClass();
    newUPDATE                 = new UPDATE();

    DataLogic                 = new DataLogic_Class(oCRC16,timer_COMBufferClear,SI4463Config,SI4432Config,
                                                    PLCConfig,MODEM,newPort,newTCP,newUPDATE,this);           // Создаём Объект обработки сообщений
    ConnectHandler            = new ConnectHandlerClass(DataLogic, MODEM, newUPDATE);

    settings_form             = NULL;
    hands_enter_form          = NULL;
    open_connection_form      = NULL;
    net_settings_form         = NULL;
    sniffer_settings_form     = NULL;
    si4432_settings_form      = NULL;
    si4463_settings_form      = NULL;
    si4463_registers_form     = NULL;
    firmware_updating_form    = NULL;
    retranslation_table_form  = NULL;
    rssimonitor_form          = NULL;
    plc_settings_form         = NULL;
    about_form                = NULL;
    interfaces_control_form   = NULL;
    plc_rf_netsettings_form   = NULL;
    rs_settings_form          = NULL;

    connect(newPort,           SIGNAL(COM_Started()),                  this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(newPort,           SIGNAL(COM_Log(QString,uint)),          this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    connect(newPort,           SIGNAL(COM_Opend()),                    this, SLOT(COM_IsOpend()));
    connect(newPort,           SIGNAL(COM_Error()),                    this, SLOT(COM_Error()));
    connect(newPort,           SIGNAL(COM_Closed()),                   this, SLOT(COM_IsClosed()));

    connect(newTCP,            SIGNAL(TCP_Log(QString,uint)),          this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    connect(newTCP,            SIGNAL(TCP_Connected()),                this, SLOT(TCP_IsConnected()));
    connect(newTCP,            SIGNAL(TCP_Error()),                    this, SLOT(TCP_Error()));
    connect(newTCP,            SIGNAL(TCP_Disconnected()),             this, SLOT(TCP_IsDisconnected()));

    connect(DataLogic,         SIGNAL(SendLog(QString,uint)),          this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,         SIGNAL(LogForPrint(QString,uint)),      this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,         SIGNAL(DataForPrint(QByteArray,uint)),  this, SLOT(Print(QByteArray,uint)));

    connect(DataLogic,         SIGNAL(STOPPED()),                      ConnectHandler,SLOT(StopMonitor()));
    connect(DataLogic,         SIGNAL(STOPPED()),                      ConnectHandler,SLOT(STOP()));
    connect(DataLogic,         SIGNAL(noANSWER()),                     ConnectHandler,SLOT(StopMonitor()));
    connect(DataLogic,         SIGNAL(noANSWER()),                     ConnectHandler,SLOT(STOP()));

    connect(ConnectHandler,    SIGNAL(SendLog(QString,uint)),          this, SLOT(Print_Log(QString,uint)));
    connect(ConnectHandler,    SIGNAL(isRF_RESET()),                   this, SLOT(RF_Reset_Handler()));

    connect(ui->btnNext,       SIGNAL(clicked()),                      this, SLOT(Create_And_Show_Open_Connection_Form()));
    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),                  ui->console, SLOT(clear()));

    connect(newParcer,         SIGNAL(PARCE_End()),                    SI4463Config,SLOT(request_Prameters_handling()));

    DataLogic->setRepeatNumber(settings.value(CONNECTION_SETTINGS_REPEATE).toInt());
    DataLogic->setRepeatTimeout(settings.value(CONNECTION_SETTINGS_PERIODE).toInt());

    ui->IPInput->setText(settings.value(TCP_SETTINGS_IP).toString());
    ui->PORTInput->setText(settings.value(TCP_SETTINGS_PORT).toString());

    ui->PortNameBox->installEventFilter(this);

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
    QFont font_2 = ui->label_2->font();    font_2.setPixelSize(text_size_4);
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
    ui->RSSIMonitor->setFont(font_3);
    ui->PGAMonitor->setFont(font_3);

    ui->console->setFont(font_5);

    ui->btnNext->setIconSize(icons_size); ui->btnNext->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnHandsEnter->setIconSize(icons_size); ui->btnHandsEnter->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

bool Connections_Form::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->PortNameBox && event->type() == QEvent::MouseButtonPress){
       if (ui->PortNameBox->isEnabled()){
           ui->PortNameBox->clear();
           foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
              ui->PortNameBox->addItem(info.portName());
              ui->COMConnect->setEnabled(true);
           }
       }
    }
    if (event->type() == QEvent::TouchUpdate){
        QTouchDevice touchscreen;
    }
    return false;
}

Connections_Form::~Connections_Form(){
    delete ui;
}

void Connections_Form::on_TCPConnect_clicked(){
    Set_ActiveConsole(ui->console);

    if(ui->TCPConnect->text() == "Подключить"){
        newPort->COM_Close();
        newTCP->TCP_SetIP(ui->IPInput->text());
        newTCP->TCP_SetPORT(ui->PORTInput->text().toInt());
        newTCP->TCP_Connect();
    }
    else{
        newTCP->TCP_Disconnect();
    }
}

void Connections_Form::on_COMConnect_clicked(){
    Set_ActiveConsole(ui->console);

    if(ui->COMConnect->text() == "Открыть"){
        newTCP->TCP_Disconnect();
        newPort->COM_Open();
    }
    else{
        newPort->COM_Close();
    }
}

void Connections_Form::start_COM_Init(void){
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
void Connections_Form::TCP_IsConnected(void){
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(TCP_SETTINGS_IP, ui->IPInput->text());
    settings.setValue(TCP_SETTINGS_PORT, ui->PORTInput->text());
    settings.sync();

    ui->TCPConnect->setText("Отключить");
    ui->btnHandsEnter->setEnabled(true);
    ui->btnNext->setEnabled(true);
    ui->RSSIMonitor->setEnabled(true);
    ui->PGAMonitor->setEnabled(true);
    ui->COM_Widget->setEnabled(false);
    ui->IPInput->setEnabled(false);
    ui->PORTInput->setEnabled(false);

    this->ConnectionType = TCP_ConnectionType;
}
void Connections_Form::TCP_Error(void){
    Set_ActiveConsole(ui->console);
}
void Connections_Form::TCP_IsDisconnected(void){
    ui->TCPConnect->setText("Подключить");
    ui->btnHandsEnter->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->RSSIMonitor->setEnabled(false);
    ui->PGAMonitor->setEnabled(false);
    ui->COM_Widget->setEnabled(true);
    ui->IPInput->setEnabled(true);
    ui->PORTInput->setEnabled(true);
}
void Connections_Form::COM_IsOpend(void){
    ui->COMConnect->setText("Закрыть");
    ui->btnHandsEnter->setEnabled(true);
    ui->btnNext->setEnabled(true);
    ui->RSSIMonitor->setEnabled(true);
    ui->PGAMonitor->setEnabled(true);
    ui->TCP_Widget->setEnabled(false);
    ui->PortNameBox->setEnabled(false);

    this->ConnectionType = COM_ConnectionType;
}
void Connections_Form::COM_Error(void){
    Set_ActiveConsole(ui->console);
}
void Connections_Form::COM_IsClosed(void){
    ui->COMConnect->setText("Открыть");
    ui->btnHandsEnter->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->RSSIMonitor->setEnabled(false);
    ui->PGAMonitor->setEnabled(false);
    ui->TCP_Widget->setEnabled(true);
    ui->PortNameBox->setEnabled(true);
}
void Connections_Form::Set_Geometry(QRect new_value){
    this->setGeometry(new_value);
}
void Connections_Form::Start_Parcer(QString file_name){
    newParcer->PARCE_Start(file_name, SI4463Config);
}
uchar Connections_Form::Get_ConnectionType(void){
    return this->ConnectionType;
}
void Connections_Form::Define_Next_Form(QRect curren_geometry)
{
    FirmwareInformationClass *In_Firmware_Information = MODEM->getIn_Firmware_Information();

    if((rssimonitor_form != NULL)&&(rssimonitor_form->isHidden() == false)){
        rssimonitor_form->deleteLater();
        rssimonitor_form = NULL;
        this->setGeometry(curren_geometry);
        this->show();
    }

    if (In_Firmware_Information->getDevice_Name().compare(PLC_MODEM) == 0)
    {
        if((open_connection_form != NULL)&&(open_connection_form->isHidden() == false)){
            open_connection_form->hide();
            Create_And_Show_Net_Settings_Form(curren_geometry);
        }
        else if((net_settings_form != NULL)&&(net_settings_form->isHidden() == false)){
            net_settings_form->hide();
            Create_And_Show_PLC_Settings_Form(curren_geometry);
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4432) == 0){
        if((open_connection_form != NULL)&&(open_connection_form->isHidden() == false)){
            open_connection_form->hide();
            Create_And_Show_Net_Settings_Form(curren_geometry);
        }
        else if((net_settings_form != NULL)&&(net_settings_form->isHidden() == false)){
            net_settings_form->hide();
            Create_And_Show_SI4432_Settings_Form(curren_geometry);
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0){
        if((open_connection_form != NULL)&&(open_connection_form->isHidden() == false)){
            open_connection_form->hide();
            Create_And_Show_Sniffer_Settings_Form(curren_geometry);
        }
        else if((sniffer_settings_form != NULL)&&(sniffer_settings_form->isHidden() == false)){
            sniffer_settings_form->hide();
            Create_And_Show_SI4432_Settings_Form(curren_geometry);
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_MODEM) == 0){
        if((open_connection_form != NULL)&&(open_connection_form->isHidden() == false)){
            open_connection_form->hide();
            Create_And_Show_Interfaces_Control_Form(curren_geometry);
        }
        else if((interfaces_control_form != NULL)&&(interfaces_control_form->isHidden() == false)){
            interfaces_control_form->hide();
            Create_And_Show_PLC_RF_NetSettings_Form(curren_geometry);
        }else if((plc_rf_netsettings_form != NULL)&&(plc_rf_netsettings_form->isHidden() == false)){
            plc_rf_netsettings_form->hide();
            Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
            // если PLC включен и инициализирован
            if ((interfaces.Field.PLC_EN == INTERFACE_ENABLE) && (interfaces.Field.PLC_INIT_OK == INTERFACE_OK_INIT)){
                Create_And_Show_PLC_Settings_Form(curren_geometry);
            // если PLC не включен или не инициализирован, а RF включен и инициализирован
            }else if (((interfaces.Field.PLC_EN != INTERFACE_ENABLE) || (interfaces.Field.PLC_INIT_OK != INTERFACE_OK_INIT)) &&
                      ((interfaces.Field.RF_EN == INTERFACE_ENABLE) && (interfaces.Field.RF_INIT_OK == INTERFACE_OK_INIT))){
                Create_And_Show_SI4463_Settings_Form(curren_geometry);
            }else if (((interfaces.Field.PLC_EN != INTERFACE_ENABLE) || (interfaces.Field.PLC_INIT_OK != INTERFACE_OK_INIT)) &&
                      ((interfaces.Field.RF_EN != INTERFACE_ENABLE) || (interfaces.Field.RF_INIT_OK != INTERFACE_OK_INIT))   &&
                      ((interfaces.Field.RS_EN == INTERFACE_ENABLE) || (interfaces.Field.RS_INIT_OK == INTERFACE_OK_INIT)) ){
                Create_And_Show_RS_Settings_Form(curren_geometry);
            }
        }else if((plc_settings_form != NULL)&&(plc_settings_form->isHidden() == false)){
            plc_settings_form->hide();
            Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
            // если PLC включен и инициализирован
            if ((interfaces.Field.RF_EN == INTERFACE_ENABLE) && (interfaces.Field.RF_INIT_OK == INTERFACE_OK_INIT)){
                Create_And_Show_SI4463_Settings_Form(curren_geometry);
            }else if (((interfaces.Field.RF_EN != INTERFACE_ENABLE) || (interfaces.Field.RF_INIT_OK != INTERFACE_OK_INIT))   &&
                      ((interfaces.Field.RS_EN == INTERFACE_ENABLE) || (interfaces.Field.RS_INIT_OK == INTERFACE_OK_INIT)) ){
                Create_And_Show_RS_Settings_Form(curren_geometry);
            }
        }else if((si4463_settings_form != NULL)&&(si4463_settings_form->isHidden() == false)){
            si4463_settings_form->hide();
            Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
            // если PLC включен и инициализирован
            if ((interfaces.Field.RS_EN == INTERFACE_ENABLE) || (interfaces.Field.RS_INIT_OK == INTERFACE_OK_INIT)){
                Create_And_Show_RS_Settings_Form(curren_geometry);
            }
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_SNIFFER) == 0){
        if((open_connection_form != NULL)&&(open_connection_form->isHidden() == false)){
            open_connection_form->hide();
            Create_And_Show_Interfaces_Control_Form(curren_geometry);
        }
        else if((interfaces_control_form != NULL)&&(interfaces_control_form->isHidden() == false)){
            interfaces_control_form->hide();
            Create_And_Show_PLC_RF_NetSettings_Form(curren_geometry);
        }
        else if((plc_rf_netsettings_form != NULL)&&(plc_rf_netsettings_form->isHidden() == false)){
            plc_rf_netsettings_form->hide();
            Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();

            if ((interfaces.Field.PLC_EN == INTERFACE_ENABLE) && (interfaces.Field.PLC_INIT_OK == INTERFACE_OK_INIT)){
                Create_And_Show_PLC_Settings_Form(curren_geometry);
            }else if (((interfaces.Field.PLC_EN != INTERFACE_ENABLE) || (interfaces.Field.PLC_INIT_OK != INTERFACE_OK_INIT)) &&
                      ((interfaces.Field.RF_EN == INTERFACE_ENABLE) && (interfaces.Field.RF_INIT_OK == INTERFACE_OK_INIT))){
                Create_And_Show_SI4463_Settings_Form(curren_geometry);
            }else if (((interfaces.Field.PLC_EN != INTERFACE_ENABLE) || (interfaces.Field.PLC_INIT_OK != INTERFACE_OK_INIT)) &&
                      ((interfaces.Field.RF_EN != INTERFACE_ENABLE) || (interfaces.Field.RF_INIT_OK != INTERFACE_OK_INIT))   &&
                      ((interfaces.Field.RS_EN == INTERFACE_ENABLE) || (interfaces.Field.RS_INIT_OK == INTERFACE_OK_INIT)) ){
                Create_And_Show_RS_Settings_Form(curren_geometry);
            }
        }else if((plc_settings_form != NULL)&&(plc_settings_form->isHidden() == false)){
            plc_settings_form->hide();
            Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
            // если PLC включен и инициализирован
            if ((interfaces.Field.RF_EN == INTERFACE_ENABLE) && (interfaces.Field.RF_INIT_OK == INTERFACE_OK_INIT)){
                Create_And_Show_SI4463_Settings_Form(curren_geometry);
            }else if (((interfaces.Field.RF_EN != INTERFACE_ENABLE) || (interfaces.Field.RF_INIT_OK != INTERFACE_OK_INIT))   &&
                      ((interfaces.Field.RS_EN == INTERFACE_ENABLE) || (interfaces.Field.RS_INIT_OK == INTERFACE_OK_INIT)) ){
                Create_And_Show_RS_Settings_Form(curren_geometry);
            }
        }else if((si4463_settings_form != NULL)&&(si4463_settings_form->isHidden() == false)){
            si4463_settings_form->hide();
            Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
            // если PLC включен и инициализирован
            if ((interfaces.Field.RS_EN == INTERFACE_ENABLE) || (interfaces.Field.RS_INIT_OK == INTERFACE_OK_INIT)){
                Create_And_Show_RS_Settings_Form(curren_geometry);
            }
        }
    }
    else if (In_Firmware_Information->getDevice_Name().compare(TERMINAL) == 0){

    }
}
void Connections_Form::Define_Pre_Form(QRect curren_geometry)
{
    FirmwareInformationClass *In_Firmware_Information = MODEM->getIn_Firmware_Information();
    if((open_connection_form != NULL)&&(open_connection_form->isHidden() == false)){
        open_connection_form->deleteLater();
        open_connection_form = NULL;
        this->setGeometry(curren_geometry);
        this->show();
    }
    else if((rssimonitor_form != NULL)&&(rssimonitor_form->isHidden() == false)){
        rssimonitor_form->deleteLater();
        rssimonitor_form = NULL;
        this->setGeometry(curren_geometry);
        this->show();
    }
    else if((firmware_updating_form != NULL)&&(firmware_updating_form->isHidden() == false)){
        firmware_updating_form->deleteLater();
        firmware_updating_form = NULL;
        open_connection_form->setGeometry(curren_geometry);
        open_connection_form->show();
    }
    else if((retranslation_table_form != NULL)&&(retranslation_table_form->isHidden() == false)){
        retranslation_table_form->deleteLater();
        retranslation_table_form = NULL;
        net_settings_form->setGeometry(curren_geometry);
        net_settings_form->show();
    }
    else {
        if (In_Firmware_Information->getDevice_Name().compare(PLC_MODEM) == 0){
            if((net_settings_form != NULL)&&(net_settings_form->isHidden() == false)){
                net_settings_form->deleteLater();
                net_settings_form = NULL;
                open_connection_form->setGeometry(curren_geometry);
                open_connection_form->show();
            }
            else if((plc_settings_form != NULL)&&(plc_settings_form->isHidden() == false)){
                plc_settings_form->deleteLater();
                plc_settings_form = NULL;
                net_settings_form->setGeometry(curren_geometry);
                net_settings_form->show();
            }
            else if((settings_form != NULL)&&(settings_form->isHidden() == false)){
                settings_form->deleteLater();
                settings_form = NULL;
            }
        }
        else if(In_Firmware_Information->getDevice_Name().compare(RF_MODEM_SI4432) == 0){
            if((net_settings_form != NULL)&&(net_settings_form->isHidden() == false)){
                net_settings_form->deleteLater();
                net_settings_form = NULL;
                open_connection_form->setGeometry(curren_geometry);
                open_connection_form->show();
            }
            else if((si4432_settings_form != NULL)&&(si4432_settings_form->isHidden() == false)){
                si4432_settings_form->deleteLater();
                si4432_settings_form = NULL;
                net_settings_form->setGeometry(curren_geometry);
                net_settings_form->show();
            }
            else if((settings_form != NULL)&&(settings_form->isHidden() == false)){
                settings_form->deleteLater();
                settings_form = NULL;
            }
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_SNIFFER_SI4432) == 0){
            if((sniffer_settings_form != NULL)&&(sniffer_settings_form->isHidden() == false)){
                sniffer_settings_form->deleteLater();
                sniffer_settings_form = NULL;
                open_connection_form->setGeometry(curren_geometry);
                open_connection_form->show();
            }
            else if((si4432_settings_form != NULL)&&(si4432_settings_form->isHidden() == false)){
                si4432_settings_form->deleteLater();
                si4432_settings_form = NULL;
                sniffer_settings_form->setGeometry(curren_geometry);
                sniffer_settings_form->show();
            }
            else if((settings_form != NULL)&&(settings_form->isHidden() == false)){
                settings_form->deleteLater();
                settings_form = NULL;
            }
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_MODEM) == 0){
            if((interfaces_control_form != NULL)&&(interfaces_control_form->isHidden() == false)){
                interfaces_control_form->deleteLater();
                interfaces_control_form = NULL;
                open_connection_form->setGeometry(curren_geometry);
                open_connection_form->show();
            }
            else if((plc_rf_netsettings_form != NULL)&&(plc_rf_netsettings_form->isHidden() == false)){
                plc_rf_netsettings_form->deleteLater();
                plc_rf_netsettings_form = NULL;
                interfaces_control_form->setGeometry(curren_geometry);
                interfaces_control_form->show();
            }
            else if((plc_settings_form != NULL)&&(plc_settings_form->isHidden() == false)){
                plc_settings_form->deleteLater();
                plc_settings_form = NULL;
                plc_rf_netsettings_form->setGeometry(curren_geometry);
                plc_rf_netsettings_form->show();
            }
            else if((si4463_settings_form != NULL)&&(si4463_settings_form->isHidden() == false)){
                si4463_settings_form->deleteLater();
                si4463_settings_form = NULL;
                Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
                if ((interfaces.Field.PLC_EN == INTERFACE_ENABLE) && (interfaces.Field.PLC_INIT_OK == INTERFACE_OK_INIT)){
                    if (plc_settings_form != NULL){
                        plc_settings_form->setGeometry(curren_geometry);
                        plc_settings_form->show();
                    }
                }else{
                    if (plc_rf_netsettings_form != NULL){
                        plc_rf_netsettings_form->setGeometry(curren_geometry);
                        plc_rf_netsettings_form->show();
                    }
                }
            }
            else if((rs_settings_form != NULL)&&(rs_settings_form->isHidden() == false)){
                rs_settings_form->deleteLater();
                rs_settings_form = NULL;
                Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
                if ((interfaces.Field.RF_EN == INTERFACE_ENABLE) && (interfaces.Field.RF_INIT_OK == INTERFACE_OK_INIT)){
                    if (si4463_settings_form != NULL){
                        si4463_settings_form->setGeometry(curren_geometry);
                        si4463_settings_form->show();
                    }
                }else if (((interfaces.Field.RF_EN != INTERFACE_ENABLE) || (interfaces.Field.RF_INIT_OK != INTERFACE_OK_INIT)) &&
                          ((interfaces.Field.PLC_EN == INTERFACE_ENABLE) && (interfaces.Field.PLC_INIT_OK == INTERFACE_OK_INIT))){
                    if (plc_settings_form != NULL){
                        plc_settings_form->setGeometry(curren_geometry);
                        plc_settings_form->show();
                    }
                }else{
                    if (plc_rf_netsettings_form != NULL){
                        plc_rf_netsettings_form->setGeometry(curren_geometry);
                        plc_rf_netsettings_form->show();
                    }
                }
            }
            else if((settings_form != NULL)&&(settings_form->isHidden() == false)){
                settings_form->deleteLater();
                settings_form = NULL;
            }
        }
        else if (In_Firmware_Information->getDevice_Name().compare(RF_PLC_SNIFFER) == 0){
            if((interfaces_control_form != NULL)&&(interfaces_control_form->isHidden() == false)){
                interfaces_control_form->deleteLater();
                interfaces_control_form = NULL;
                open_connection_form->setGeometry(curren_geometry);
                open_connection_form->show();
            }
            else if((plc_rf_netsettings_form != NULL)&&(plc_rf_netsettings_form->isHidden() == false)){
                plc_rf_netsettings_form->deleteLater();
                plc_rf_netsettings_form = NULL;
                interfaces_control_form->setGeometry(curren_geometry);
                interfaces_control_form->show();
            }
            else if((plc_settings_form != NULL)&&(plc_settings_form->isHidden() == false)){
                plc_settings_form->deleteLater();
                plc_settings_form = NULL;
                plc_rf_netsettings_form->setGeometry(curren_geometry);
                plc_rf_netsettings_form->show();
            }
            else if((si4463_settings_form != NULL)&&(si4463_settings_form->isHidden() == false)){
                si4463_settings_form->deleteLater();
                si4463_settings_form = NULL;
                Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
                if ((interfaces.Field.PLC_EN == INTERFACE_ENABLE) && (interfaces.Field.PLC_INIT_OK == INTERFACE_OK_INIT)){
                    if (plc_settings_form != NULL){
                        plc_settings_form->setGeometry(curren_geometry);
                        plc_settings_form->show();
                    }
                }else{
                    if (plc_rf_netsettings_form != NULL){
                        plc_rf_netsettings_form->setGeometry(curren_geometry);
                        plc_rf_netsettings_form->show();
                    }
                }
            }
            else if((rs_settings_form != NULL)&&(rs_settings_form->isHidden() == false)){
                rs_settings_form->deleteLater();
                rs_settings_form = NULL;
                Interfaces_Control_Type interfaces = MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control();
                if ((interfaces.Field.RF_EN == INTERFACE_ENABLE) && (interfaces.Field.RF_INIT_OK == INTERFACE_OK_INIT)){
                    if (si4463_settings_form != NULL){
                        si4463_settings_form->setGeometry(curren_geometry);
                        si4463_settings_form->show();
                    }
                }else if (((interfaces.Field.RF_EN != INTERFACE_ENABLE) || (interfaces.Field.RF_INIT_OK != INTERFACE_OK_INIT)) &&
                          ((interfaces.Field.PLC_EN == INTERFACE_ENABLE) && (interfaces.Field.PLC_INIT_OK == INTERFACE_OK_INIT))){
                    if (plc_settings_form != NULL){
                        plc_settings_form->setGeometry(curren_geometry);
                        plc_settings_form->show();
                    }
                }else{
                    if (plc_rf_netsettings_form != NULL){
                        plc_rf_netsettings_form->setGeometry(curren_geometry);
                        plc_rf_netsettings_form->show();
                    }
                }
            }
            else if ((settings_form != NULL)&&(settings_form->isHidden() == false)){
                settings_form->deleteLater();
                settings_form = NULL;
            }
        }
        else if (In_Firmware_Information->getDevice_Name().compare(TERMINAL) == 0){

        }
    }
}
void Connections_Form::RF_Reset_Handler(void){
    QRect Geometry;
    if (open_connection_form != NULL){
        Geometry = open_connection_form->geometry();
    }
    if (sniffer_settings_form != NULL){
        Geometry = sniffer_settings_form->geometry();
        sniffer_settings_form->deleteLater();
        sniffer_settings_form = NULL;
    }
    if (firmware_updating_form != NULL){
        Geometry = firmware_updating_form->geometry();
        firmware_updating_form->deleteLater();
        firmware_updating_form = NULL;
    }
    if (net_settings_form != NULL){
        Geometry = net_settings_form->geometry();
        net_settings_form->deleteLater();
        net_settings_form = NULL;
    }
    if (plc_settings_form != NULL){
        Geometry = plc_settings_form->geometry();
        plc_settings_form->deleteLater();
        plc_settings_form = NULL;
    }
    if (retranslation_table_form != NULL){
        Geometry = retranslation_table_form->geometry();
        retranslation_table_form->deleteLater();
        retranslation_table_form = NULL;
    }
    if (si4432_settings_form != NULL){
        Geometry = si4432_settings_form->geometry();
        si4432_settings_form->deleteLater();
        si4432_settings_form = NULL;
    }
    if (si4463_settings_form != NULL){
        Geometry = si4463_settings_form->geometry();
        si4463_settings_form->deleteLater();
        si4463_settings_form = NULL;
    }
    if (interfaces_control_form != NULL){
        Geometry = interfaces_control_form->geometry();
        interfaces_control_form->deleteLater();
        interfaces_control_form = NULL;
    }
    if (plc_rf_netsettings_form != NULL){
        Geometry = plc_rf_netsettings_form->geometry();
        plc_rf_netsettings_form->deleteLater();
        plc_rf_netsettings_form = NULL;
    }
    if (rs_settings_form != NULL){
        Geometry = rs_settings_form->geometry();
        rs_settings_form->deleteLater();
        rs_settings_form = NULL;
    }
    if ((rssimonitor_form == NULL)&&(open_connection_form != NULL)){
        open_connection_form->setGeometry(Geometry);
        open_connection_form->show();
    }
}
void Connections_Form::Create_And_Show_Settings_Form(QWidget *parent){
    settings_form = new Settings_Form;
    connect(this->newPort,SIGNAL(COM_Error()),                               settings_form,         SLOT(ForceClose()));
    connect(this->newTCP, SIGNAL(TCP_Error()),                               settings_form,         SLOT(ForceClose()));
    connect(settings_form,SIGNAL(ForcedClosed()),                            this,                  SLOT(show()));
    connect(settings_form,SIGNAL(Get_Geometry(QRect)),                       this,                  SLOT(Set_Geometry(QRect)));

    connect(settings_form,SIGNAL(Cancel(QRect)),                             parent,                SLOT(Set_Geometry(QRect)));
    connect(settings_form,SIGNAL(Cancel(QRect)),                             parent,                SLOT(show()));
    connect(settings_form,SIGNAL(GetRepeatNumber(uint)),                     DataLogic,             SLOT(setRepeatNumber(uint)));
    connect(settings_form,SIGNAL(GetRepeatTimeout(uint)),                    DataLogic,             SLOT(setRepeatTimeout(uint)));

    connect(settings_form,SIGNAL(Open_AboutWindow(QWidget*)),                this,                  SLOT(Create_And_Show_About_Form(QWidget*)));

    parent->hide();
    settings_form->setGeometry(parent->geometry());
    settings_form->show();
}
void Connections_Form::Create_And_Show_About_Form(QWidget *parent){
    about_form = new About_Form;
    connect(this->newPort,SIGNAL(COM_Error()),                               about_form,            SLOT(ForceClose()));
    connect(this->newTCP, SIGNAL(TCP_Error()),                               about_form,            SLOT(ForceClose()));
    connect(about_form,SIGNAL(ForcedClosed()),                               this,                  SLOT(show()));
    connect(about_form,SIGNAL(Get_Geometry(QRect)),                          this,                  SLOT(Set_Geometry(QRect)));

    connect(about_form,SIGNAL(Cancel(QRect)),                                parent,                SLOT(Set_Geometry(QRect)));
    connect(about_form,SIGNAL(Cancel(QRect)),                                parent,                SLOT(show()));

    parent->hide();
    about_form->setGeometry(parent->geometry());
    about_form->show();
}

void Connections_Form::Create_And_Show_Hands_Enter_Form(QWidget *parent){
    hands_enter_form = new Hands_Enter_Form;
    connect(this->newPort,   SIGNAL(COM_Error()),                            hands_enter_form,      SLOT(ForceClose()));
    connect(this->newTCP,    SIGNAL(TCP_Error()),                            hands_enter_form,      SLOT(ForceClose()));
    connect(hands_enter_form,SIGNAL(ForcedClosed()),                         this,                  SLOT(show()));
    connect(hands_enter_form,SIGNAL(Get_Geometry(QRect)),                    this,                  SLOT(Set_Geometry(QRect)));

    connect(hands_enter_form,SIGNAL(Cancel(QRect)),                          parent,                SLOT(show()));
    connect(hands_enter_form,SIGNAL(Get_Geometry(QRect)),                    parent,                SLOT(Set_Geometry(QRect)));
    connect(hands_enter_form,SIGNAL(Send_Data(QByteArray,uint)),             DataLogic,             SLOT(SEND_DATA(QByteArray,uint)));
    connect(hands_enter_form,SIGNAL(Get_Console(QPlainTextEdit*)),           this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(hands_enter_form,SIGNAL(Settings(QWidget*)),                     this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));

    parent->hide();
    hands_enter_form->setGeometry(parent->geometry());
    hands_enter_form->show();
}
void Connections_Form::Create_And_Show_Open_Connection_Form(void){
    open_connection_form = new Open_Connection_Form;

    connect(this->newPort,       SIGNAL(COM_Error()),                        open_connection_form,  SLOT(ForceClose()));
    connect(this->newTCP,        SIGNAL(TCP_Error()),                        open_connection_form,  SLOT(ForceClose()));
    connect(open_connection_form,SIGNAL(ForcedClosed()),                     this,                  SLOT(show()));
    connect(open_connection_form,SIGNAL(Get_Geometry(QRect)),                this,                  SLOT(Set_Geometry(QRect)));

    connect(open_connection_form,SIGNAL(Get_Console(QPlainTextEdit*)),       this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(open_connection_form,SIGNAL(Cancel(QRect)),                      this,                  SLOT(Define_Pre_Form(QRect)));
    connect(open_connection_form,SIGNAL(Next(QRect)),                        this,                  SLOT(Define_Next_Form(QRect)));

    connect(open_connection_form,SIGNAL(Settings(QWidget*)),                 this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(open_connection_form,SIGNAL(Updating(QWidget*)),                 this,                  SLOT(Create_And_Show_Firmware_Updating_Form(QWidget*)));

    connect(open_connection_form,SIGNAL(ClearAllData()),                     MODEM,                 SLOT(ClearAllData()));
    connect(MODEM,               SIGNAL(sIn_Firmware_Information(FirmwareInformationClass*)), open_connection_form,  SLOT(Set_In_Firmware_Information(FirmwareInformationClass *)));

    connect(open_connection_form,SIGNAL(SendModuleType(uchar)),              ConnectHandler,        SLOT(SetModuleType(uchar)));
    connect(open_connection_form,SIGNAL(SendInterface(uchar)),               ConnectHandler,        SLOT(SetInterface(uchar)));
    connect(open_connection_form,SIGNAL(StartSendingProcess(uint,uint)),     ConnectHandler,        SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,      SIGNAL(isAOPEN()),                          open_connection_form,  SLOT(isOPEND()));
    connect(ConnectHandler,      SIGNAL(isRF_RESET()),                       open_connection_form,  SLOT(isRF_Reset()));
    connect(ConnectHandler,      SIGNAL(Progress(uint)),                     open_connection_form,  SLOT(SetProgress(uint)));

    connect(open_connection_form,SIGNAL(SendSerialNumber(QString,bool)),     DataLogic,             SLOT(setSerialNumberMode(QString,bool)));
    connect(open_connection_form,SIGNAL(Stop_Send_Data()),                   DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,           SIGNAL(STOPPED()),                          open_connection_form,  SLOT(isStopped()));
    connect(DataLogic,           SIGNAL(noANSWER()),                         open_connection_form,  SLOT(isStopped()));

    open_connection_form->setGeometry(this->geometry());
    this->hide();
    open_connection_form->Set_ConnectionType(Get_ConnectionType());
    open_connection_form->show();
}

void Connections_Form::Create_And_Show_Net_Settings_Form(QRect current_geometry){
    net_settings_form = new Net_Settings_Form;

    connect(this->newPort,    SIGNAL(COM_Error()),                          net_settings_form,     SLOT(ForceClose()));
    connect(this->newTCP,     SIGNAL(TCP_Error()),                          net_settings_form,     SLOT(ForceClose()));
    connect(net_settings_form,SIGNAL(ForcedClosed()),                       this,                  SLOT(show()));
    connect(net_settings_form,SIGNAL(Get_Geometry(QRect)),                  this,                  SLOT(Set_Geometry(QRect)));

    connect(net_settings_form,SIGNAL(Get_Console(QPlainTextEdit*)),         this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(net_settings_form,SIGNAL(Cancel(QRect)),                        this,                  SLOT(Define_Pre_Form(QRect)));
    connect(net_settings_form,SIGNAL(Next(QRect)),                          this,                  SLOT(Define_Next_Form(QRect)));

    connect(net_settings_form,SIGNAL(Settings(QWidget*)),                   this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(net_settings_form,SIGNAL(Retranslation_Table(QWidget*)),        this,                  SLOT(Create_And_Show_Retranslation_Table_Form(QWidget*)));

    connect(net_settings_form,SIGNAL(isCreated()),                          MODEM,                 SLOT(ChangedOut_Retranslator_Properties()));
    connect(net_settings_form,SIGNAL(isCreated()),                          MODEM,                 SLOT(ChangedIn_Retranslator_Properties()));
    connect(MODEM, SIGNAL(sIn_Retranslator_Properties(RetranslatorPropertiesClass*)), net_settings_form, SLOT(Set_In_Retranslator_Properties(RetranslatorPropertiesClass*)));
    connect(MODEM, SIGNAL(sOut_Retranslator_Properties(RetranslatorPropertiesClass*)),net_settings_form, SLOT(Set_Out_Retranslator_Properties(RetranslatorPropertiesClass*)));

    connect(net_settings_form,SIGNAL(StartSendingProcess(uint,uint)),       ConnectHandler,        SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,   SIGNAL(Progress(uint)),                       net_settings_form,     SLOT(SetProgress(uint)));
    connect(ConnectHandler,   SIGNAL(isSWITCH_MODE()),                      net_settings_form,     SLOT(isSwitchMode()));
    connect(ConnectHandler,   SIGNAL(isSWITCH_LEVEL()),                     net_settings_form,     SLOT(isSwitchLevel()));
    connect(ConnectHandler,   SIGNAL(isSWITCH_TIMEOUT()),                   net_settings_form,     SLOT(isSwitchTimeout()));
    connect(ConnectHandler,   SIGNAL(isRF_RESET()),                         net_settings_form,     SLOT(isRF_Reset()));

    connect(net_settings_form,SIGNAL(Stop_Send_Data()),                     DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,        SIGNAL(STOPPED()),                            net_settings_form,     SLOT(isStopped()));
    connect(DataLogic,        SIGNAL(noANSWER()),                           net_settings_form,     SLOT(isStopped()));

    this->hide();

    net_settings_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    net_settings_form->setGeometry(current_geometry);
    net_settings_form->show();
}
void Connections_Form::Create_And_Show_PLC_Settings_Form(QRect current_geometry){
    plc_settings_form = new PLC_Settings_Form;

    connect(this->newPort,        SIGNAL(COM_Error()),                      plc_settings_form,     SLOT(ForceClose()));
    connect(this->newTCP,         SIGNAL(TCP_Error()),                      plc_settings_form,     SLOT(ForceClose()));
    connect(plc_settings_form,    SIGNAL(ForcedClosed()),                   this,                  SLOT(show()));
    connect(plc_settings_form,    SIGNAL(Get_Geometry(QRect)),              this,                  SLOT(Set_Geometry(QRect)));

    connect(plc_settings_form,    SIGNAL(Cancel(QRect)),                    this,                  SLOT(Define_Pre_Form(QRect)));
    connect(plc_settings_form,    SIGNAL(Next(QRect)),                      this,                  SLOT(Define_Next_Form(QRect)));
    connect(plc_settings_form,    SIGNAL(Settings(QWidget*)),               this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(plc_settings_form,    SIGNAL(Get_Console(QPlainTextEdit*)),     this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));

    connect(plc_settings_form,    SIGNAL(isCreated()),                      PLCConfig,             SLOT(ChangedOut_ST750_PLC_Config()));
    connect(plc_settings_form,    SIGNAL(isCreated()),                      PLCConfig,             SLOT(ChangedIn_ST750_PLC_Config()));
    connect(PLCConfig,SIGNAL(sIn_ST750_Parameters  (ST750ConfigurationClass*)),      plc_settings_form, SLOT(setIn_ST750_Parameters(ST750ConfigurationClass*)));
    connect(PLCConfig,SIGNAL(sOut_ST750_Parameters  (ST750ConfigurationClass*)),     plc_settings_form, SLOT(setOut_ST750_Parameters(ST750ConfigurationClass*)));

    connect(plc_settings_form,    SIGNAL(StartSendingProcess(uint,uint)),   ConnectHandler,        SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,       SIGNAL(isPLCST750_PARAMETERS()),          plc_settings_form,     SLOT(isST750_Parameters()));
    connect(ConnectHandler,       SIGNAL(isRF_RESET()),                     plc_settings_form,     SLOT(isRF_Reset()));
    connect(ConnectHandler,       SIGNAL(Progress(uint)),                   plc_settings_form,     SLOT(SetProgress(uint)));

    connect(plc_settings_form,    SIGNAL(Stop_Send_Data()),                 DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,            SIGNAL(STOPPED()),                        plc_settings_form,     SLOT(isStopped()));
    connect(DataLogic,            SIGNAL(noANSWER()),                       plc_settings_form,     SLOT(isStopped()));

    this->hide();
    plc_settings_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    plc_settings_form->Set_In_Interfaces_Control(MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control());
    plc_settings_form->setGeometry(current_geometry);
    plc_settings_form ->show();
}
void Connections_Form::Create_And_Show_Sniffer_Settings_Form(QRect current_geometry){
    sniffer_settings_form = new Sniffer_Settings_Form;

    connect(this->newPort,        SIGNAL(COM_Error()),                      sniffer_settings_form, SLOT(ForceClose()));
    connect(this->newTCP,         SIGNAL(TCP_Error()),                      sniffer_settings_form, SLOT(ForceClose()));
    connect(sniffer_settings_form,SIGNAL(ForcedClosed()),                   this,                  SLOT(show()));
    connect(sniffer_settings_form,SIGNAL(Get_Geometry(QRect)),              this,                  SLOT(Set_Geometry(QRect)));

    connect(sniffer_settings_form,SIGNAL(Cancel(QRect)),                    this,                  SLOT(Define_Pre_Form(QRect)));
    connect(sniffer_settings_form,SIGNAL(Next(QRect)),                      this,                  SLOT(Define_Next_Form(QRect)));
    connect(sniffer_settings_form,SIGNAL(Settings(QWidget*)),               this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(sniffer_settings_form,SIGNAL(Get_Console(QPlainTextEdit*)),     this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));

    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(ChangedOut_Sniffer_Properties()));
    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(ChangedIn_Sniffer_Properties()));
    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(ChangedOut_Retranslator_Properties()));
    connect(sniffer_settings_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(ChangedIn_Retranslator_Properties()));
    connect(MODEM, SIGNAL(sIn_Sniffer_Properties(SnifferPropertiesClass*)),            sniffer_settings_form, SLOT(Set_In_Sniffer_Properties(SnifferPropertiesClass*)));
    connect(MODEM, SIGNAL(sOut_Sniffer_Properties(SnifferPropertiesClass*)),           sniffer_settings_form, SLOT(Set_Out_Sniffer_Properties(SnifferPropertiesClass*)));
    connect(MODEM, SIGNAL(sIn_Retranslator_Properties(RetranslatorPropertiesClass*)),  sniffer_settings_form, SLOT(Set_In_Retranslator_Properties(RetranslatorPropertiesClass*)));
    connect(MODEM, SIGNAL(sOut_Retranslator_Properties(RetranslatorPropertiesClass*)), sniffer_settings_form, SLOT(Set_Out_Retranslator_Properties(RetranslatorPropertiesClass*)));

    connect(sniffer_settings_form,SIGNAL(StartSendingProcess(uint,uint)),   ConnectHandler,        SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,       SIGNAL(isSNIFER_MODE()),                  sniffer_settings_form, SLOT(isSnifferMode()));
    connect(ConnectHandler,       SIGNAL(isUPLINK_MODE()),                  sniffer_settings_form, SLOT(isUpLink_Mode()));
    connect(ConnectHandler,       SIGNAL(isBROADCASTING_MODE()),            sniffer_settings_form, SLOT(isBroadcasting_Mode()));
    connect(ConnectHandler,       SIGNAL(isCRC_CHECK_MODE()),               sniffer_settings_form, SLOT(isCRC_Disable_Mode()));
    connect(ConnectHandler,       SIGNAL(isMASK_DESTINATION()),             sniffer_settings_form, SLOT(isMask_Destination()));
    connect(ConnectHandler,       SIGNAL(isSWITCH_TABLE()),                 sniffer_settings_form, SLOT(isSwitch_Table()));
    connect(ConnectHandler,       SIGNAL(isDELET_SWITCH_TABLE()),           sniffer_settings_form, SLOT(isDelet_Switch_Table()));
    connect(ConnectHandler,       SIGNAL(isRF_RESET()),                     sniffer_settings_form, SLOT(isRF_Reset()));
    connect(ConnectHandler,       SIGNAL(Progress(uint)),                   sniffer_settings_form, SLOT(SetProgress(uint)));

    connect(sniffer_settings_form,SIGNAL(Stop_Send_Data()),                 DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,            SIGNAL(STOPPED()),                        sniffer_settings_form, SLOT(isStopped()));
    connect(DataLogic,            SIGNAL(noANSWER()),                       sniffer_settings_form, SLOT(isStopped()));

    this->hide();
    sniffer_settings_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    sniffer_settings_form->setGeometry(current_geometry);
    sniffer_settings_form->show();
}
void Connections_Form::Create_And_Show_SI4432_Settings_Form(QRect current_geometry){
    si4432_settings_form = new SI4432_Settings_Form;

    connect(this->newPort,        SIGNAL(COM_Error()),                          si4432_settings_form, SLOT(ForceClose()));
    connect(this->newTCP,         SIGNAL(TCP_Error()),                          si4432_settings_form, SLOT(ForceClose()));
    connect(si4432_settings_form, SIGNAL(ForcedClosed()),                       this,                 SLOT(show()));
    connect(si4432_settings_form, SIGNAL(Get_Geometry(QRect)),                  this,                 SLOT(Set_Geometry(QRect)));

    connect(si4432_settings_form, SIGNAL(Cancel(QRect)),                        this,                 SLOT(Define_Pre_Form(QRect)));
    connect(si4432_settings_form, SIGNAL(Next(QRect)),                          this,                 SLOT(Define_Next_Form(QRect)));
    connect(si4432_settings_form, SIGNAL(Settings(QWidget*)),                   this,                 SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(si4432_settings_form, SIGNAL(Get_Console(QPlainTextEdit*)),         this,                 SLOT(Set_ActiveConsole(QPlainTextEdit*)));

    connect(si4432_settings_form, SIGNAL(isCreated()),                          SI4432Config,         SLOT(ChangedOut_SI4432_RF_Config()));
    connect(si4432_settings_form, SIGNAL(isCreated()),                          SI4432Config,         SLOT(ChangedIn_SI4432_RF_Config()));
    connect(SI4432Config,SIGNAL(sIn_SI4432_Parameters(SI4432ConfigurationClass*)),      si4432_settings_form, SLOT(setIn_SI4432_Parameters(SI4432ConfigurationClass*)));
    connect(SI4432Config,SIGNAL(sOut_SI4432_Parameters(SI4432ConfigurationClass*)),     si4432_settings_form, SLOT(setOut_SI4432_Parameters(SI4432ConfigurationClass*)));

    connect(si4432_settings_form, SIGNAL(StartSendingProcess(uint,uint)),       ConnectHandler,       SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,       SIGNAL(isRFSI4432_PARAMETERS()),              si4432_settings_form, SLOT(isSI4432_Parameters()));
    connect(ConnectHandler,       SIGNAL(isRF_RESET()),                         si4432_settings_form, SLOT(isRF_Reset()));
    connect(ConnectHandler,       SIGNAL(Progress(uint)),                       si4432_settings_form, SLOT(SetProgress(uint)));

    connect(si4432_settings_form, SIGNAL(Stop_Send_Data()),                     DataLogic,            SLOT(STOP_SEND_DATA()));
    connect(DataLogic,            SIGNAL(STOPPED()),                            si4432_settings_form, SLOT(isStopped()));
    connect(DataLogic,            SIGNAL(noANSWER()),                           si4432_settings_form, SLOT(isStopped()));

    this->hide();
    si4432_settings_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    si4432_settings_form->setGeometry(current_geometry);
    si4432_settings_form->show();
}
void Connections_Form::Create_And_Show_SI4463_Settings_Form(QRect current_geometry){
    si4463_settings_form = new SI4463_Settings_Form;

    connect(this->newPort,        SIGNAL(COM_Error()),                      si4463_settings_form,  SLOT(ForceClose()));
    connect(this->newTCP,         SIGNAL(TCP_Error()),                      si4463_settings_form,  SLOT(ForceClose()));
    connect(si4463_settings_form, SIGNAL(ForcedClosed()),                   this,                  SLOT(show()));
    connect(si4463_settings_form, SIGNAL(Get_Geometry(QRect)),              this,                  SLOT(Set_Geometry(QRect)));

    connect(si4463_settings_form, SIGNAL(Cancel(QRect)),                    this,                  SLOT(Define_Pre_Form(QRect)));
    connect(si4463_settings_form, SIGNAL(Next(QRect)),                      this,                  SLOT(Define_Next_Form(QRect)));
    connect(si4463_settings_form, SIGNAL(Settings(QWidget*)),               this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(si4463_settings_form, SIGNAL(Open_RegistersWindow(QWidget*)),   this,                  SLOT(Create_And_Show_SI4463_Registers_Form(QWidget*)));
    connect(si4463_settings_form, SIGNAL(Get_Console(QPlainTextEdit*)),     this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(si4463_settings_form, SIGNAL(Start_Parcer(QString)),            this,                  SLOT(Start_Parcer(QString)));

    connect(si4463_settings_form, SIGNAL(isCreated()),                      SI4463Config,          SLOT(request_Model_handling()));
    connect(si4463_settings_form, SIGNAL(isCreated()),                      SI4463Config,          SLOT(request_currentPrameters_handling()));
    connect(SI4463Config,         SIGNAL(get_Model(QStandardItemModel*)),   si4463_settings_form,  SLOT(Set_Model(QStandardItemModel*)));
    connect(SI4463Config,         SIGNAL(get_Prameters(QList<Params>*)),    si4463_settings_form,  SLOT(Set_Prameters(QList<Params>*)));

    connect(si4463_settings_form, SIGNAL(StartSendingProcess(uint,uint)),   ConnectHandler,        SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,       SIGNAL(isRFSI4463_PARAMETERS()),          si4463_settings_form,  SLOT(isSI4463_Parameters()));
    connect(ConnectHandler,       SIGNAL(isRF_RESET()),                     si4463_settings_form,  SLOT(isRF_Reset()));
    connect(ConnectHandler,       SIGNAL(Progress(uint)),                   si4463_settings_form,  SLOT(SetProgress(uint)));

    connect(si4463_settings_form, SIGNAL(Stop_Send_Data()),                 DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,            SIGNAL(STOPPED()),                        si4463_settings_form,  SLOT(isStopped()));
    connect(DataLogic,            SIGNAL(noANSWER()),                       si4463_settings_form,  SLOT(isStopped()));

    this->hide();
    si4463_settings_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    si4463_settings_form->Set_In_Interfaces_Control(MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control());
    si4463_settings_form->setGeometry(current_geometry);
    si4463_settings_form->show();
}
void Connections_Form::Create_And_Show_Firmware_Updating_Form(QWidget *parent){
    firmware_updating_form = new Firmware_Updating_Form;

    connect(this->newPort,         SIGNAL(COM_Error()),                      firmware_updating_form,SLOT(ForceClose()));
    connect(this->newTCP,          SIGNAL(TCP_Error()),                      firmware_updating_form,SLOT(ForceClose()));
    connect(firmware_updating_form,SIGNAL(ForcedClosed()),                   this,                  SLOT(show()));
    connect(firmware_updating_form,SIGNAL(Get_Geometry(QRect)),              this,                  SLOT(Set_Geometry(QRect)));

    connect(firmware_updating_form,SIGNAL(Cancel(QRect)),                    this,                  SLOT(Define_Pre_Form(QRect)));
    connect(firmware_updating_form,SIGNAL(Next(QRect)),                      this,                  SLOT(Define_Next_Form(QRect)));
    connect(firmware_updating_form,SIGNAL(Get_Console(QPlainTextEdit*)),     this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(firmware_updating_form,SIGNAL(Settings(QWidget*)),               this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));

    connect(firmware_updating_form,SIGNAL(Get_FirmwareData(QString,QByteArray)),newUPDATE,          SLOT(setDATA(QString,QByteArray)));

    connect(firmware_updating_form,SIGNAL(isCreated()),                      MODEM,                 SLOT(ChangedIn_Firmware_Information()));
    connect(MODEM,                 SIGNAL(sIn_Firmware_Information(FirmwareInformationClass*)), firmware_updating_form,  SLOT(Set_In_Firmware_Information(FirmwareInformationClass *)));

    connect(firmware_updating_form,SIGNAL(StartSendingProcess(uint,uint)),   ConnectHandler,        SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,        SIGNAL(isUPDATED()),                      firmware_updating_form,SLOT(isUpdated()));
    connect(ConnectHandler,        SIGNAL(isDELETED()),                      firmware_updating_form,SLOT(isDeleted()));
    connect(ConnectHandler,        SIGNAL(isRF_RESET()),                     firmware_updating_form,SLOT(isRF_Reset()));
    connect(ConnectHandler,        SIGNAL(Progress(uint)),                   firmware_updating_form,SLOT(SetProgress(uint)));

    connect(firmware_updating_form,SIGNAL(Stop_Send_Data()),                 DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(DataLogic,             SIGNAL(STOPPED()),                        firmware_updating_form,SLOT(isStopped()));
    connect(DataLogic,             SIGNAL(noANSWER()),                       firmware_updating_form,SLOT(isStopped()));
    connect(DataLogic,             SIGNAL(outPROGRESS(uint)),                firmware_updating_form,SLOT(SetProgress(uint)));

    parent->hide();
    firmware_updating_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    firmware_updating_form->setGeometry(parent->geometry());
    firmware_updating_form->show();
}

void Connections_Form::Create_And_Show_Retranslation_Table_Form(QWidget *parent){
    retranslation_table_form = new Retranslation_Table_Form;

    connect(this->newPort,           SIGNAL(COM_Error()),                      si4463_settings_form,    SLOT(ForceClose()));
    connect(this->newTCP,            SIGNAL(TCP_Error()),                      si4463_settings_form,    SLOT(ForceClose()));
    connect(retranslation_table_form,SIGNAL(ForcedClosed()),                   this,                    SLOT(show()));
    connect(retranslation_table_form,SIGNAL(Get_Geometry(QRect)),              this,                    SLOT(Set_Geometry(QRect)));

    connect(retranslation_table_form,SIGNAL(Cancel(QRect)),                    this,                    SLOT(Define_Pre_Form(QRect)));
    connect(retranslation_table_form,SIGNAL(Next(QRect)),                      this,                    SLOT(Define_Next_Form(QRect)));
    connect(retranslation_table_form,SIGNAL(Get_Console(QPlainTextEdit*)),     this,                    SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(retranslation_table_form,SIGNAL(Settings(QWidget*)),               this,                    SLOT(Create_And_Show_Settings_Form(QWidget*)));

    connect(retranslation_table_form,SIGNAL(isCreated()),                      MODEM,                   SLOT(ChangedOut_Retranslator_Properties()));
    connect(retranslation_table_form,SIGNAL(isCreated()),                      MODEM,                   SLOT(ChangedIn_Retranslator_Properties()));
    connect(MODEM,                   SIGNAL(sIn_Retranslator_Properties(RetranslatorPropertiesClass*)), retranslation_table_form,  SLOT(Set_In_Retranslator_Properties(RetranslatorPropertiesClass *)));
    connect(MODEM,                   SIGNAL(sOut_Retranslator_Properties(RetranslatorPropertiesClass*)),retranslation_table_form,  SLOT(Set_Out_Retranslator_Properties(RetranslatorPropertiesClass *)));

    connect(retranslation_table_form,SIGNAL(StartSendingProcess(uint,uint)),   ConnectHandler,          SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,          SIGNAL(isSWITCH_TABLE()),                 retranslation_table_form,SLOT(isSwitch_Table()));
    connect(ConnectHandler,          SIGNAL(isSWITCH_TABLE()),                 retranslation_table_form,SLOT(isSwitch_Table()));
    connect(ConnectHandler,          SIGNAL(isDELET_SWITCH_TABLE()),           retranslation_table_form,SLOT(isDelet_Switch_Table()));
    connect(ConnectHandler,          SIGNAL(isRF_RESET()),                     retranslation_table_form,SLOT(isRF_Reset()));
    connect(ConnectHandler,          SIGNAL(Progress(uint)),                   retranslation_table_form,SLOT(SetProgress(uint)));

    connect(retranslation_table_form,SIGNAL(Stop_Send_Data()),                 DataLogic,               SLOT(STOP_SEND_DATA()));
    connect(DataLogic,               SIGNAL(STOPPED()),                        retranslation_table_form,SLOT(isStopped()));
    connect(DataLogic,               SIGNAL(noANSWER()),                       retranslation_table_form,SLOT(isStopped()));
    connect(DataLogic,               SIGNAL(outPROGRESS(uint)),                retranslation_table_form,SLOT(SetProgress(uint)));

    parent->hide();
    retranslation_table_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    retranslation_table_form->setGeometry(parent->geometry());
    retranslation_table_form->show();
}
void Connections_Form::Create_And_Show_SI4463_Registers_Form(QWidget *parent){
    si4463_registers_form = new SI4463_Registers_Form;
    connect(si4463_registers_form,SIGNAL(Cancel()),                         parent,                  SLOT(show()));
    connect(si4463_registers_form,SIGNAL(Get_Geometry(QRect)),              parent,                  SLOT(Set_Geometry(QRect)));
    connect(si4463_registers_form,SIGNAL(Get_Console(QPlainTextEdit*)),     this,                    SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(si4463_registers_form,SIGNAL(Settings(QWidget*)),               this,                    SLOT(Create_And_Show_Settings_Form(QWidget*)));

    connect(si4463_registers_form,SIGNAL(isCreated()),                      SI4463Config,            SLOT(request_Model_handling()));
    connect(SI4463Config,         SIGNAL(get_Model(QStandardItemModel*)),   si4463_registers_form,   SLOT(Set_Model(QStandardItemModel*)));

    parent->hide();
    si4463_registers_form->setGeometry(parent->geometry());
    si4463_registers_form->show();
}
void Connections_Form::Create_And_Show_RSSIMonitor_Form(uchar Mode_Form, QWidget *parent){
    rssimonitor_form = new RSSIMonitor_Form(Mode_Form);
    connect(this->newPort,   SIGNAL(COM_Error()),                           rssimonitor_form,      SLOT(ForceClose()));
    connect(this->newTCP,    SIGNAL(TCP_Error()),                           rssimonitor_form,      SLOT(ForceClose()));
    connect(rssimonitor_form,SIGNAL(ForcedClosed()),                        this,                  SLOT(show()));
    connect(rssimonitor_form,SIGNAL(Get_Geometry(QRect)),                   this,                  SLOT(Set_Geometry(QRect)));

    connect(rssimonitor_form,SIGNAL(Cancel(QRect)),                         this,                  SLOT(Define_Pre_Form(QRect)));
    connect(rssimonitor_form,SIGNAL(Next(QRect)),                           this,                  SLOT(Define_Next_Form(QRect)));
    connect(rssimonitor_form,SIGNAL(Settings(QWidget*)),                    this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(rssimonitor_form,SIGNAL(Get_Console(QPlainTextEdit*)),          this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));

    connect(rssimonitor_form,SIGNAL(StartSendingProcess(uint,uint)),        ConnectHandler,        SLOT(StartSendingProcess(uint,uint)));
    connect(rssimonitor_form,SIGNAL(SendModuleType(uchar)),                 ConnectHandler,        SLOT(SetModuleType(uchar)));
    connect(rssimonitor_form,SIGNAL(SendInterface(uchar)),                  ConnectHandler,        SLOT(SetInterface(uchar)));
    connect(rssimonitor_form,SIGNAL(StartRSSIMonitor(uint)),                ConnectHandler,        SLOT(StartMonitor(uint)));
    connect(rssimonitor_form,SIGNAL(StopRSSIMonitor()),                     ConnectHandler,        SLOT(StopMonitor()));
    connect(ConnectHandler,  SIGNAL(isRF_RESET()),                          rssimonitor_form,      SLOT(isRF_Reset()));

    connect(rssimonitor_form,SIGNAL(Stop_Send_Data()),                      DataLogic,             SLOT(STOP_SEND_DATA()));
    connect(rssimonitor_form,SIGNAL(SendSerialNumber(QString,bool)),        DataLogic,             SLOT(setSerialNumberMode(QString,bool)));
    connect(DataLogic,       SIGNAL(STOPPED()),                             rssimonitor_form,      SLOT(isStopped()));
    connect(DataLogic,       SIGNAL(noANSWER()),                            rssimonitor_form,      SLOT(isStopped()));
    connect(DataLogic,       SIGNAL(RSSI_RequestSended()),                  rssimonitor_form,      SLOT(RSSI_RequestSended()));

    connect(DataLogic,       SIGNAL(outLRSSI_AFC(signed short,signed short,signed short,double)),  rssimonitor_form,      SLOT(isLatchRSSI_AFC(signed short,signed short,signed short,double)));
    connect(DataLogic,       SIGNAL(outLPGA(signed short,double)),                                 rssimonitor_form,      SLOT(isLatchPGA(signed short,double)));

    parent->hide();
    rssimonitor_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    rssimonitor_form->setGeometry(parent->geometry());
    rssimonitor_form->Set_ConnectionType(Get_ConnectionType());
    rssimonitor_form->show();
}
void Connections_Form::Create_And_Show_Interfaces_Control_Form(QRect current_geometry){
    interfaces_control_form = new Interfaces_Control_Form;

    connect(this->newPort,          SIGNAL(COM_Error()),                        interfaces_control_form,  SLOT(ForceClose()));
    connect(this->newTCP,           SIGNAL(TCP_Error()),                        interfaces_control_form,  SLOT(ForceClose()));
    connect(interfaces_control_form,SIGNAL(ForcedClosed()),                     this,                  SLOT(show()));
    connect(interfaces_control_form,SIGNAL(Get_Geometry(QRect)),                this,                  SLOT(Set_Geometry(QRect)));

    connect(interfaces_control_form,SIGNAL(Get_Console(QPlainTextEdit*)),       this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(interfaces_control_form,SIGNAL(Cancel(QRect)),                      this,                  SLOT(Define_Pre_Form(QRect)));
    connect(interfaces_control_form,SIGNAL(Next(QRect)),                        this,                  SLOT(Define_Next_Form(QRect)));

    connect(interfaces_control_form,SIGNAL(Settings(QWidget*)),                 this,                  SLOT(Create_And_Show_Settings_Form(QWidget*)));
    connect(interfaces_control_form,SIGNAL(Updating(QWidget*)),                 this,                  SLOT(Create_And_Show_Firmware_Updating_Form(QWidget*)));

    connect(interfaces_control_form,SIGNAL(isCreated()),                        MODEM,                 SLOT(ChangedOut_PLC_RF433_Modem_Properties()));
    connect(interfaces_control_form,SIGNAL(isCreated()),                        MODEM,                 SLOT(ChangedIn_PLC_RF433_Modem_Properties()));
    connect(MODEM,                  SIGNAL(sIn_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass*)), interfaces_control_form,  SLOT(Set_In_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass *)));
    connect(MODEM,                  SIGNAL(sOut_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass*)),interfaces_control_form,  SLOT(Set_Out_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass *)));

    connect(interfaces_control_form,SIGNAL(StartSendingProcess(uint,uint)),     ConnectHandler,           SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,         SIGNAL(isAOPEN()),                          interfaces_control_form,  SLOT(isOPEND()));
    connect(ConnectHandler,         SIGNAL(isRF_RESET()),                       interfaces_control_form,  SLOT(isRF_Reset()));
    connect(ConnectHandler,         SIGNAL(isINTERFACES_CONTROL()),             interfaces_control_form,  SLOT(isInterfaces_Control()));
    connect(ConnectHandler,         SIGNAL(Progress(uint)),                     interfaces_control_form,  SLOT(SetProgress(uint)));

    connect(interfaces_control_form,SIGNAL(SendSerialNumber(QString,bool)),     DataLogic,                SLOT(setSerialNumberMode(QString,bool)));
    connect(interfaces_control_form,SIGNAL(Stop_Send_Data()),                   DataLogic,                SLOT(STOP_SEND_DATA()));
    connect(DataLogic,              SIGNAL(STOPPED()),                          interfaces_control_form,  SLOT(isStopped()));
    connect(DataLogic,              SIGNAL(noANSWER()),                         interfaces_control_form,  SLOT(isStopped()));

    interfaces_control_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    interfaces_control_form->setGeometry(current_geometry);
    this->hide();
    interfaces_control_form->Set_ConnectionType(Get_ConnectionType());
    interfaces_control_form->show();
}
void Connections_Form::Create_And_Show_PLC_RF_NetSettings_Form(QRect current_geometry){
    plc_rf_netsettings_form = new PLC_RF_NetSettings_Form;

    connect(this->newPort,          SIGNAL(COM_Error()),                        plc_rf_netsettings_form,SLOT(ForceClose()));
    connect(this->newTCP,           SIGNAL(TCP_Error()),                        plc_rf_netsettings_form,SLOT(ForceClose()));
    connect(plc_rf_netsettings_form,SIGNAL(ForcedClosed()),                     this,                   SLOT(show()));
    connect(plc_rf_netsettings_form,SIGNAL(Get_Geometry(QRect)),                this,                   SLOT(Set_Geometry(QRect)));

    connect(plc_rf_netsettings_form,SIGNAL(Get_Console(QPlainTextEdit*)),       this,                   SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(plc_rf_netsettings_form,SIGNAL(Cancel(QRect)),                      this,                   SLOT(Define_Pre_Form(QRect)));
    connect(plc_rf_netsettings_form,SIGNAL(Next(QRect)),                        this,                   SLOT(Define_Next_Form(QRect)));

    connect(plc_rf_netsettings_form,SIGNAL(Settings(QWidget*)),                 this,                   SLOT(Create_And_Show_Settings_Form(QWidget*)));

    connect(plc_rf_netsettings_form,SIGNAL(isCreated()),                        MODEM,                  SLOT(ChangedOut_Retranslator_Properties()));
    connect(plc_rf_netsettings_form,SIGNAL(isCreated()),                        MODEM,                  SLOT(ChangedIn_Retranslator_Properties()));
    connect(plc_rf_netsettings_form,SIGNAL(isCreated()),                        MODEM,                  SLOT(ChangedOut_Sniffer_Properties()));
    connect(plc_rf_netsettings_form,SIGNAL(isCreated()),                        MODEM,                  SLOT(ChangedIn_Sniffer_Properties()));
    connect(plc_rf_netsettings_form,SIGNAL(isCreated()),                        MODEM,                  SLOT(ChangedOut_PLC_RF433_Modem_Properties()));
    connect(plc_rf_netsettings_form,SIGNAL(isCreated()),                        MODEM,                  SLOT(ChangedIn_PLC_RF433_Modem_Properties()));
    connect(MODEM, SIGNAL(sIn_Retranslator_Properties(RetranslatorPropertiesClass*)),  plc_rf_netsettings_form, SLOT(Set_In_Retranslator_Properties(RetranslatorPropertiesClass*)));
    connect(MODEM, SIGNAL(sOut_Retranslator_Properties(RetranslatorPropertiesClass*)), plc_rf_netsettings_form, SLOT(Set_Out_Retranslator_Properties(RetranslatorPropertiesClass*)));
    connect(MODEM, SIGNAL(sIn_Sniffer_Properties(SnifferPropertiesClass*)),            plc_rf_netsettings_form, SLOT(Set_In_Sniffer_Properties(SnifferPropertiesClass*)));
    connect(MODEM, SIGNAL(sOut_Sniffer_Properties(SnifferPropertiesClass*)),           plc_rf_netsettings_form, SLOT(Set_Out_Sniffer_Properties(SnifferPropertiesClass*)));
    connect(MODEM, SIGNAL(sIn_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass*)), plc_rf_netsettings_form, SLOT(Set_In_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass *)));
    connect(MODEM, SIGNAL(sOut_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass*)),plc_rf_netsettings_form, SLOT(Set_Out_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass *)));

    connect(plc_rf_netsettings_form,SIGNAL(StartSendingProcess(uint,uint)),     ConnectHandler,         SLOT(StartSendingProcess(uint,uint)));
    connect(ConnectHandler,         SIGNAL(isRF_RESET()),                       plc_rf_netsettings_form,SLOT(isRF_Reset()));
    connect(ConnectHandler,         SIGNAL(isINTERFACES_CONTROL()),             plc_rf_netsettings_form,SLOT(isInterfaces_Control()));
    connect(ConnectHandler,         SIGNAL(isUPLINK_MODE()),                    plc_rf_netsettings_form,SLOT(isUpLink_Mode()));
    connect(ConnectHandler,         SIGNAL(isBROADCASTING_MODE()),              plc_rf_netsettings_form,SLOT(isBroadcasting_Mode()));
    connect(ConnectHandler,         SIGNAL(isCRC_CHECK_MODE()),                 plc_rf_netsettings_form,SLOT(isCRC_Disable_Mode()));
    connect(ConnectHandler,         SIGNAL(isMASK_DESTINATION()),               plc_rf_netsettings_form,SLOT(isMask_Destination()));
    connect(ConnectHandler,         SIGNAL(isSWITCH_MODE()),                    plc_rf_netsettings_form,SLOT(isSwitchMode()));
    connect(ConnectHandler,         SIGNAL(isSWITCH_LEVEL()),                   plc_rf_netsettings_form,SLOT(isSwitchLevel()));
    connect(ConnectHandler,         SIGNAL(isSWITCH_TIMEOUT()),                 plc_rf_netsettings_form,SLOT(isSwitchTimeout()));
    connect(ConnectHandler,         SIGNAL(Progress(uint)),                     plc_rf_netsettings_form,SLOT(SetProgress(uint)));

    connect(plc_rf_netsettings_form,SIGNAL(Stop_Send_Data()),                   DataLogic,              SLOT(STOP_SEND_DATA()));
    connect(DataLogic,              SIGNAL(STOPPED()),                          plc_rf_netsettings_form,SLOT(isStopped()));
    connect(DataLogic,              SIGNAL(noANSWER()),                         plc_rf_netsettings_form,SLOT(isStopped()));

    plc_rf_netsettings_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    plc_rf_netsettings_form->setGeometry(current_geometry);
    this->hide();
    plc_rf_netsettings_form->Set_ConnectionType(Get_ConnectionType());
    plc_rf_netsettings_form->show();
}
void Connections_Form::Create_And_Show_RS_Settings_Form(QRect current_geometry){
    rs_settings_form = new RS_Settings_Form;

    connect(this->newPort,          SIGNAL(COM_Error()),                        rs_settings_form,SLOT(ForceClose()));
    connect(this->newTCP,           SIGNAL(TCP_Error()),                        rs_settings_form,SLOT(ForceClose()));
    connect(rs_settings_form,SIGNAL(ForcedClosed()),                            this,            SLOT(show()));
    connect(rs_settings_form,SIGNAL(Get_Geometry(QRect)),                       this,            SLOT(Set_Geometry(QRect)));

    connect(rs_settings_form,SIGNAL(Get_Console(QPlainTextEdit*)),              this,            SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(rs_settings_form,SIGNAL(Cancel(QRect)),                             this,            SLOT(Define_Pre_Form(QRect)));
    connect(rs_settings_form,SIGNAL(Next(QRect)),                               this,            SLOT(Define_Next_Form(QRect)));

    connect(rs_settings_form,SIGNAL(Settings(QWidget*)),                        this,            SLOT(Create_And_Show_Settings_Form(QWidget*)));

    connect(rs_settings_form,SIGNAL(isCreated()),MODEM,                  SLOT(ChangedOut_PLC_RF433_Modem_Properties()));
    connect(rs_settings_form,SIGNAL(isCreated()),MODEM,                  SLOT(ChangedIn_PLC_RF433_Modem_Properties()));
    connect(MODEM, SIGNAL(sIn_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass*)), rs_settings_form, SLOT(Set_In_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass *)));
    connect(MODEM, SIGNAL(sOut_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass*)),rs_settings_form, SLOT(Set_Out_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass *)));

    connect(rs_settings_form,SIGNAL(StartSendingProcess(uint,uint)),            ConnectHandler,  SLOT(StartSendingProcess(uint,uint)));

    connect(ConnectHandler,         SIGNAL(isRF_RESET()),                       rs_settings_form,SLOT(isRF_Reset()));
    connect(ConnectHandler,         SIGNAL(isINTERFACES_CONTROL()),             rs_settings_form,SLOT(isInterfaces_Control()));
    connect(ConnectHandler,         SIGNAL(isDEBUG_CONTROL()),                  rs_settings_form,SLOT(isDebug_Control()));

    connect(ConnectHandler,         SIGNAL(Progress(uint)),                     rs_settings_form,SLOT(SetProgress(uint)));

    connect(rs_settings_form,       SIGNAL(Stop_Send_Data()),                   DataLogic,       SLOT(STOP_SEND_DATA()));
    connect(DataLogic,              SIGNAL(STOPPED()),                          rs_settings_form,SLOT(isStopped()));
    connect(DataLogic,              SIGNAL(noANSWER()),                         rs_settings_form,SLOT(isStopped()));

    rs_settings_form->Set_In_Firmware_Information(MODEM->getIn_Firmware_Information());
    rs_settings_form->Set_In_Interfaces_Control(MODEM->getIn_PLC_RF433_Modem_Properties()->getPLC_RF433_Interfaces_Control());
    rs_settings_form->setGeometry(current_geometry);
    this->hide();
    rs_settings_form->Set_ConnectionType(Get_ConnectionType());
    rs_settings_form->show();
}

//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void Connections_Form::Print(QByteArray data, uint n)
{
    QString s = "Print data";
    qDebug() << s;

    QByteArray d;
    d.append(data);

    if (ActiveConsole == NULL){
        ActiveConsole = ui->console;
    }
    if (ActiveConsole != NULL){
        ActiveConsole->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        switch (n){
            case COM_TX:{
                ActiveConsole->textCursor().insertText("TX >> " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
                break;
            }
            case COM_RX:{
                ActiveConsole->textCursor().insertText("RX << " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
                break;
            }
        }
        QString str;str += '\r';
        ActiveConsole->textCursor().insertText(str); // Вывод текста в консоль
        ActiveConsole->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor); // Scroll
    }
}
//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void Connections_Form::Print_Log(QString data, uint n){
    if (ActiveConsole == NULL){
        ActiveConsole = ui->console;
    }
    if (ActiveConsole != NULL){
        ActiveConsole->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        ActiveConsole->textCursor().insertText(data); // Вывод текста в консоль
        ActiveConsole->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);  // Scroll
    }
}
void Connections_Form::Set_ActiveConsole(QPlainTextEdit * new_active_console){
    ActiveConsole = new_active_console;
}
void Connections_Form::on_PortNameBox_currentIndexChanged(const QString &arg1){
   newPort->COM_SetPortName(arg1);
}
void Connections_Form::on_btnSettings_clicked(){
    Create_And_Show_Settings_Form(this);
}
void Connections_Form::on_btnHandsEnter_clicked(){
    Create_And_Show_Hands_Enter_Form(this);
}
void Connections_Form::on_RSSIMonitor_clicked(){
    Create_And_Show_RSSIMonitor_Form(RSSI_MODE_FORM, this);
}
void Connections_Form::on_PGAMonitor_clicked(){
    Create_And_Show_RSSIMonitor_Form(PGA_MODE_FORM, this);
}

void Connections_Form::on_IPInput_textEdited(const QString &arg1){
    QList<uint> Ints;
    uchar Ints_number = 0;

    ui->IPInput->setStyleSheet(Background_Red);
    ui->TCPConnect->setEnabled(false);
    //ui->btnHandsEnter->setEnabled(false);
    //ui->btnNext->setEnabled(false);

    int pos = 0;
    QRegExp cload_RegExp = QRegExp("\\d+");

    while ((pos = cload_RegExp.indexIn(arg1,pos)) != -1)
    {
        Ints.append(cload_RegExp.cap(0).toInt());
        pos += cload_RegExp.matchedLength();
        Ints_number++;
    }
    if ((Ints_number == 4)&&(Ints.at(0) <= 255)&&(Ints.at(1) <= 255)&&
                            (Ints.at(2) <= 255)&&(Ints.at(3) <= 255)
       ){
       int cursorPosition = ui->IPInput->cursorPosition();
       ui->IPInput->setText(QString::number(Ints.at(0))+"."+QString::number(Ints.at(1))+"."+
                            QString::number(Ints.at(2))+"."+QString::number(Ints.at(3)));
       ui->IPInput->setCursorPosition(cursorPosition);
       ui->IPInput->setStyleSheet(Background_White);
       ui->TCPConnect->setEnabled(true);
       //ui->btnHandsEnter->setEnabled(true);
       //ui->btnNext->setEnabled(true);
    }
}

void Connections_Form::on_PORTInput_textChanged(const QString &arg1){
    QList<uint> Ints;
    uchar Ints_number = 0;

    ui->PORTInput->setStyleSheet(Background_Red);
    ui->TCPConnect->setEnabled(false);
    //ui->btnHandsEnter->setEnabled(false);
    //ui->btnNext->setEnabled(false);

    int pos = 0;
    QRegExp cload_RegExp = QRegExp("\\d+");

    while ((pos = cload_RegExp.indexIn(arg1,pos)) != -1)
    {
        Ints.append(cload_RegExp.cap(0).toInt());
        pos += cload_RegExp.matchedLength();
        Ints_number++;
    }
    if ((Ints_number == 1)&&(Ints.at(0) <= 0xFFFF)
       ){
       int cursorPosition = ui->IPInput->cursorPosition();
       ui->PORTInput->setText(QString::number(Ints.at(0)));
       ui->PORTInput->setCursorPosition(cursorPosition);
       ui->PORTInput->setStyleSheet(Background_White);
       ui->TCPConnect->setEnabled(true);
       //ui->btnHandsEnter->setEnabled(true);
       //ui->btnNext->setEnabled(true);
    }
}

