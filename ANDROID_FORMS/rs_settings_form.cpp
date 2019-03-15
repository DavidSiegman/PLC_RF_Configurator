#include "rs_settings_form.h"
#include "connections_form.h"

RS_Settings_Form::RS_Settings_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::RS_Settings_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style + ToolTip_Style);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->btnRSToPLCRet->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnPLCToRSRet->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnRSToRFRet->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnRFToRSRet->setStyleSheet(Basic_ToolButtons_Style);

    ui->Read->setStyleSheet(Basic_PushButtons_Style);
    ui->Stop->setStyleSheet(Basic_PushButtons_Style);
    ui->Reset->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);

    ui->Back->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->Next->setStyleSheet(PushButtons_Style+ToolTip_Style);

    ui->RS_Mode->setStyleSheet(Background_White);
    ui->RS_Speed->setStyleSheet(Background_White);

    ui->console->setStyleSheet(ToolTip_Style);

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
}
void RS_Settings_Form::on_ClearConsole_clicked(){
    WriteLogToFile(ui->console);
    ui->console->clear();
}
RS_Settings_Form::~RS_Settings_Form(){
    emit Get_Console(NULL);
    delete ui;
}
void RS_Settings_Form::on_Back_clicked(){
    WriteLogToFile(ui->console);
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
}
void RS_Settings_Form::on_Next_clicked(){
    WriteLogToFile(ui->console);
    this->Next_ClickHandler();
}
void RS_Settings_Form::ForceClose(void){
    WriteLogToFile(ui->console);
    this->ForceCloseHandler();
}
void RS_Settings_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void RS_Settings_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void RS_Settings_Form::on_Stop_clicked(){
    this->Stop_ClickHandler();
}
void RS_Settings_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->RS_Mode_Widget->setEnabled(false);
    ui->RS_Debug_Widget->setEnabled(false);
    ui->RS_Settings_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    this->Reset_ClickHandler();
}
void RS_Settings_Form::isStopped(void){
    ui->Stop->setEnabled(false);
    ui->RS_Mode_Widget->setEnabled(true);
    ui->RS_Debug_Widget->setEnabled(true);
    ui->RS_Settings_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void RS_Settings_Form::isRF_Reset(void){
    ui->Stop->setEnabled(false);
    ui->RS_Mode_Widget->setEnabled(true);
    ui->RS_Debug_Widget->setEnabled(true);
    ui->RS_Settings_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);

    this->Back_ClickHandler();
}
void RS_Settings_Form::resizeEvent(QResizeEvent *event){
    emit isCreated();
    this->Set_resizing_going(1);

    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    int text_size_3 = resize_calculating.get_text_size_3();
    int text_size_4 = resize_calculating.get_text_size_4();
    int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1   = ui->label_1->font();  font_1.setPixelSize(text_size_1);
    QFont font_2   = ui->label_2->font();  font_2.setPixelSize(text_size_2);
    QFont font_2_1 = ui->label_2->font();  font_2_1.setPixelSize(text_size_4);
    QFont font_3   = ui->Read->font();     font_3.setPixelSize(text_size_3);
    QFont font_4_1 = ui->label_5->font();  font_4_1.setPixelSize(text_size_4);
    QFont font_4_2 = ui->label_5->font();  font_4_2.setPixelSize(text_size_5);
    QFont font_5   = ui->console->font();  font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2_1);
    ui->label_3->setFont(font_2_1);
    ui->label_4->setFont(font_2_1);
    ui->label_5->setFont(font_3);
    ui->label_6->setFont(font_3);
    ui->label_7->setFont(font_3);
    ui->label_8->setFont(font_3);
    ui->label_9->setFont(font_4_1);
    ui->label_10->setFont(font_4_1);
    ui->label_11->setFont(font_4_1);
    ui->label_12->setFont(font_4_1);
    ui->label_13->setFont(font_2_1);

    ui->Read->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->RS_Mode->setFont(font_4_1);
    int current_index = ui->RS_Mode->currentIndex();
    ui->RS_Mode->clear();
    ui->RS_Mode->addItem("Интерфейс связи");
    ui->RS_Mode->addItem("Интерфейс отладки");
    ui->RS_Mode->setCurrentIndex(current_index);

    ui->RS_Speed->setFont(font_4_1);
    current_index = ui->RS_Speed->currentIndex();
    ui->RS_Speed->clear();
    ui->RS_Speed->addItem("300 [bps]");
    ui->RS_Speed->addItem("600 [bps]");
    ui->RS_Speed->addItem("1200 [bps]");
    ui->RS_Speed->addItem("2400 [bps]");
    ui->RS_Speed->addItem("4800 [bps]");
    ui->RS_Speed->addItem("9600 [bps]");
    ui->RS_Speed->addItem("19200 [bps]");
    ui->RS_Speed->addItem("38400 [bps]");
    ui->RS_Speed->addItem("57600 [bps]");
    ui->RS_Speed->addItem("115200 [bps]");
    ui->RS_Speed->addItem("256000 [bps]");
    ui->RS_Speed->setCurrentIndex(current_index);

    ui->console->setFont(font_5);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->label_1->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    DeviceVersionHandling();
    emit Get_Console(ui->console);
    this->Set_resizing_going(0);
}
void RS_Settings_Form::DeviceVersionHandling(void){
    FirmwareInformationClass* In_Firmware_Information = myFormAbstractClass::Get_In_Firmware_Information();
    if (In_Firmware_Information->getDevice_Name() == RF_PLC_MODEM){

    }else if (In_Firmware_Information->getDevice_Name() == RF_PLC_SNIFFER){

    }
}
void RS_Settings_Form::Set_Out_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass* new_value){
    Out_PLC_RF433_Modem_Properties = new_value;
}
void RS_Settings_Form::Set_In_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass* new_value){
    In_PLC_RF433_Modem_Properties = new_value;

    setInterfaces_ControlToUI(In_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control());
    setDebug_ControlToUI(In_PLC_RF433_Modem_Properties->getPLC_RF433_Debug_Control());

    Out_PLC_RF433_Modem_Properties->setPLC_RF433_Debug_Control(In_PLC_RF433_Modem_Properties->getPLC_RF433_Debug_Control());
    Out_PLC_RF433_Modem_Properties->setPLC_RF433_Interfaces_Control(In_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control());
}
void RS_Settings_Form::on_RS_Mode_currentIndexChanged(int index){
    if ((index >= 0)&&(index < 2)&&(this->Get_resizing_going() == 0)){
        emit Get_Console(ui->console);
        Out_PLC_RF433_Modem_Properties->setRS_USE_AS_DEBUG_OUTPUT((uchar)(index));
        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_RS_Speed_currentIndexChanged(int index){
    if ((index >= 0)&&(index < 11)&&(this->Get_resizing_going() == 0)){
        emit Get_Console(ui->console);
        Out_PLC_RF433_Modem_Properties->setRS_BAUDRATE((uchar)(index));
        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_btnRSToPLCRet_released()
{
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (ui->btnRSToPLCRet->isChecked() == true){
            Out_PLC_RF433_Modem_Properties->setRS_TO_PLC_RET_EN(1);
        }else{
            Out_PLC_RF433_Modem_Properties->setRS_TO_PLC_RET_EN(0);
        }
        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_btnPLCToRSRet_released()
{
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (ui->btnPLCToRSRet->isChecked() == true){
            Out_PLC_RF433_Modem_Properties->setPLC_TO_RS_RET_EN(1);
        }else{
            Out_PLC_RF433_Modem_Properties->setPLC_TO_RS_RET_EN(0);
        }
        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_btnRSToRFRet_released()
{
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (ui->btnRSToRFRet->isChecked() == true){
            Out_PLC_RF433_Modem_Properties->setRS_TO_RF_RET_EN(1);
        }else{
            Out_PLC_RF433_Modem_Properties->setRS_TO_RF_RET_EN(0);
        }
        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_btnRFToRSRet_released()
{
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (ui->btnRFToRSRet->isChecked() == true){
            Out_PLC_RF433_Modem_Properties->setRF_TO_RS_RET_EN(1);
        }else{
            Out_PLC_RF433_Modem_Properties->setRF_TO_RS_RET_EN(0);
        }
        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_RSToPLCUp_Link_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setRS_TO_PLC_UP_LINK(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setRS_TO_PLC_UP_LINK(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_RSToRFUp_Link_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setRS_TO_RF_UP_LINK(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setRS_TO_RF_UP_LINK(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugGlobalEnable_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setDEBUG_GLOBAL_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setDEBUG_GLOBAL_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugInterfaceControl_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setINTERFACES_CONTROL_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setINTERFACES_CONTROL_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugRetranslationHandling_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setRETRANSLATION_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setRETRANSLATION_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugToHostHandling_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setINTERFACES_TO_UART_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setINTERFACES_TO_UART_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugFromHostHandling_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setUART_TO_INTERFACES_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setUART_TO_INTERFACES_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugPLCInititalisation_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setPLC_INIT_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setPLC_INIT_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugPLCUART_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setPLC_UART_RX_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setPLC_UART_RX_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugPLCHandling_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setPLC_RX_TX_DATA_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setPLC_RX_TX_DATA_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugRSEnable_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setRS_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setRS_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugRFEnable_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setSI4463_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setSI4463_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugSI4463Initialisation_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setSI4463_INIT_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setSI4463_INIT_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugSPIEnable_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setSPI_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setSPI_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugHOSTUART_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setHOST_UART_RX_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setHOST_UART_RX_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugFlashEnable_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setFLASH_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setFLASH_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void RS_Settings_Form::on_DebugFlashFull_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setFLASH_FULL_DATA_DEBUG_EN(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setFLASH_FULL_DATA_DEBUG_EN(1);
        }

        ui->Stop->setEnabled(true);
        ui->RS_Mode_Widget->setEnabled(false);
        ui->RS_Debug_Widget->setEnabled(false);
        ui->RS_Settings_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_DEBUG_CONTROL,CONFIG_SEND_CONTROL);
    }
}

void RS_Settings_Form::setInterfaces_ControlToUI(Interfaces_Control_Type Interfaces_Control){
    if (ui->RS_Mode->currentIndex() != (Interfaces_Control.Field.RS_USE_AS_DEBUG_OUTPUT&1)){
        ui->RS_Mode->setCurrentIndex((int)(Interfaces_Control.Field.RS_USE_AS_DEBUG_OUTPUT&1));
    }
    if (ui->RS_Mode->currentIndex() == 0){
        ui->RS_Settings_Widget->setVisible(true);
        ui->RS_Debug_Widget->setVisible(false);
        ui->RS_Speed->setCurrentIndex(Interfaces_Control.Field.RS_BAUDRATE&0xF);
    }else{
        ui->RS_Settings_Widget->setVisible(false);
        ui->RS_Debug_Widget->setVisible(true);
        ui->RS_Speed->setCurrentIndex(10);
    }
    if (Interfaces_Control.Field.RS_TO_PLC_RET_EN == 1){
        ui->btnRSToPLCRet->setChecked(true);
    }else{
        ui->btnRSToPLCRet->setChecked(false);
    }
    if (Interfaces_Control.Field.PLC_TO_RS_RET_EN == 1){
        ui->btnPLCToRSRet->setChecked(true);
    }else{
        ui->btnPLCToRSRet->setChecked(false);
    }
    if (Interfaces_Control.Field.RS_TO_RF_RET_EN == 1){
        ui->btnRSToRFRet->setChecked(true);
    }else{
        ui->btnRSToRFRet->setChecked(false);
    }
    if (Interfaces_Control.Field.RF_TO_RS_RET_EN == 1){
        ui->btnRFToRSRet->setChecked(true);
    }else{
        ui->btnRFToRSRet->setChecked(false);
    }
    if (Interfaces_Control.Field.RS_TO_PLC_UP_LINK == 1){
        ui->RSToPLCUp_Link->setChecked(true);
    }else{
        ui->RSToPLCUp_Link->setChecked(false);
    }
    if (Interfaces_Control.Field.RS_TO_RF_UP_LINK == 1){
        ui->RSToRFUp_Link->setChecked(true);
    }else{
        ui->RSToRFUp_Link->setChecked(false);
    }
    if ((Interfaces_Control.Field.PLC_EN != INTERFACE_ENABLE) ||
        (Interfaces_Control.Field.PLC_INIT_OK != INTERFACE_OK_INIT)){
        ui->btnRSToPLCRet->setEnabled(false);
        ui->btnPLCToRSRet->setEnabled(false);
        ui->RSToPLCUp_Link->setEnabled(false);
    }
    if ((Interfaces_Control.Field.RF_EN != INTERFACE_ENABLE) ||
        (Interfaces_Control.Field.RF_INIT_OK != INTERFACE_OK_INIT)){
        ui->btnRSToRFRet->setEnabled(false);
        ui->btnRFToRSRet->setEnabled(false);
        ui->RSToRFUp_Link->setEnabled(false);
    }
}
void RS_Settings_Form::setDebug_ControlToUI(Debug_Control_Type Debug_Control){
    if(Debug_Control.Field.DEBUG_GLOBAL_EN == 1){
        ui->DebugGlobalEnable->setChecked(true);
    }
    if(Debug_Control.Field.INTERFACES_CONTROL_DEBUG_EN == 1){
        ui->DebugInterfaceControl->setChecked(true);
    }
    if(Debug_Control.Field.RETRANSLATION_DEBUG_EN == 1){
        ui->DebugRetranslationHandling->setChecked(true);
    }
    if(Debug_Control.Field.INTERFACES_TO_UART_DEBUG_EN == 1){
        ui->DebugToHostHandling->setChecked(true);
    }
    if(Debug_Control.Field.UART_TO_INTERFACES_DEBUG_EN == 1){
        ui->DebugFromHostHandling->setChecked(true);
    }
    if(Debug_Control.Field.PLC_INIT_DEBUG_EN == 1){
        ui->DebugPLCInititalisation->setChecked(true);
    }
    if(Debug_Control.Field.PLC_UART_RX_DEBUG_EN == 1){
        ui->DebugPLCUART->setChecked(true);
    }
    if(Debug_Control.Field.PLC_RX_TX_DATA_DEBUG_EN == 1){
        ui->DebugPLCHandling->setChecked(true);
    }
    if(Debug_Control.Field.RS_DEBUG_EN == 1){
        ui->DebugRSEnable->setChecked(true);
    }
    if(Debug_Control.Field.SI4463_DEBUG_EN == 1){
        ui->DebugRFEnable->setChecked(true);
    }
    if(Debug_Control.Field.SI4463_INIT_DEBUG_EN == 1){
        ui->DebugSI4463Initialisation->setChecked(true);
    }
    if(Debug_Control.Field.SPI_DEBUG_EN == 1){
        ui->DebugSPIEnable->setChecked(true);
    }
    if(Debug_Control.Field.HOST_UART_RX_DEBUG_EN == 1){
        ui->DebugHOSTUART->setChecked(true);
    }
    if(Debug_Control.Field.FLASH_DEBUG_EN == 1){
        ui->DebugFlashEnable->setChecked(true);
    }
    if(Debug_Control.Field.FLASH_FULL_DATA_DEBUG_EN == 1){
        ui->DebugFlashFull->setChecked(true);
    }
}

void RS_Settings_Form::isInterfaces_Control(){
    ui->Stop->setEnabled(false);
    ui->RS_Mode_Widget->setEnabled(true);
    ui->RS_Debug_Widget->setEnabled(true);
    ui->RS_Settings_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void RS_Settings_Form::isDebug_Control(){
    ui->Stop->setEnabled(false);
    ui->RS_Mode_Widget->setEnabled(true);
    ui->RS_Debug_Widget->setEnabled(true);
    ui->RS_Settings_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
