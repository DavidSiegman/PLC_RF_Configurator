#include "plc_rf_netsettings_form.h"
#include "connections_form.h"

PLC_RF_NetSettings_Form::PLC_RF_NetSettings_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::PLC_RF_NetSettings_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->btnPLCToPLCRet->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnPLCToRFRet->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnRFToPLCRet->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnRFToRFRet->setStyleSheet(Basic_ToolButtons_Style);
    ui->SetMask->setStyleSheet(Basic_PushButtons_Style);
    ui->SetTimeout->setStyleSheet(Basic_PushButtons_Style);
    ui->SetDestinationMASK->setStyleSheet(Basic_PushButtons_Style);

    ui->Read->setStyleSheet(Basic_PushButtons_Style);
    ui->Stop->setStyleSheet(Basic_PushButtons_Style);
    ui->Reset->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);

    ui->Back->setStyleSheet(PushButtons_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style);
    ui->Next->setStyleSheet(PushButtons_Style);

    ui->Mode->setStyleSheet(Background_White);
    ui->LVL0->setStyleSheet(Background_White);
    ui->LVL1->setStyleSheet(Background_White);
    ui->LVL2->setStyleSheet(Background_White);
    ui->LVL3->setStyleSheet(Background_White);
    ui->LVL4->setStyleSheet(Background_White);
    ui->LVL5->setStyleSheet(Background_White);
    ui->LVL6->setStyleSheet(Background_White);
    ui->LVL7->setStyleSheet(Background_White);
    ui->LVL8->setStyleSheet(Background_White);
    ui->LVL9->setStyleSheet(Background_White);
    ui->LVL0_2->setStyleSheet(Background_White);
    ui->LVL1_2->setStyleSheet(Background_White);
    ui->LVL2_2->setStyleSheet(Background_White);
    ui->LVL3_2->setStyleSheet(Background_White);
    ui->LVL4_2->setStyleSheet(Background_White);
    ui->LVL5_2->setStyleSheet(Background_White);
    ui->LVL6_2->setStyleSheet(Background_White);
    ui->LVL7_2->setStyleSheet(Background_White);
    ui->LVL8_2->setStyleSheet(Background_White);
    ui->LVL9_2->setStyleSheet(Background_White);

    //ui->NetLevel->setStyleSheet(Background_White+Basic_Text_Style);
    ui->SwitchTM->setStyleSheet(Background_White+Basic_Text_Style);

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
    connect(ui->ClearConsole, SIGNAL(clicked(bool)), ui->console, SLOT(clear()));
}

PLC_RF_NetSettings_Form::~PLC_RF_NetSettings_Form(){
    emit Get_Console(NULL);
    delete ui;
}
void PLC_RF_NetSettings_Form::on_Back_clicked(){
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
}
void PLC_RF_NetSettings_Form::on_Next_clicked(){
    this->Next_ClickHandler();
}
void PLC_RF_NetSettings_Form::ForceClose(void){
    this->ForceCloseHandler();
}
void PLC_RF_NetSettings_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void PLC_RF_NetSettings_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void PLC_RF_NetSettings_Form::on_Stop_clicked(){
    this->Stop_ClickHandler();
}
void PLC_RF_NetSettings_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->Mode->setEnabled(false);
    ui->SlaveMode_Widget->setEnabled(false);
    ui->MasterMode_Widget->setEnabled(false);
    ui->CRC_Control_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    this->Reset_ClickHandler();
}
void PLC_RF_NetSettings_Form::isStopped(void){
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isRF_Reset(void){
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);

    this->Back_ClickHandler();
}
void PLC_RF_NetSettings_Form::resizeEvent(QResizeEvent *event){
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
    QFont font_4_1 = ui->label_4->font();  font_4_1.setPixelSize(text_size_4);
    QFont font_4_2 = ui->label_4->font();  font_4_2.setPixelSize(text_size_5);
    QFont font_5   = ui->console->font();  font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2_1);
    ui->label_3->setFont(font_2_1);
    ui->label_4->setFont(font_3);
    ui->label_5->setFont(font_3);
    ui->label_6->setFont(font_3);
    ui->label_7->setFont(font_3);
    ui->label_8->setFont(font_4_1);
    ui->label_9->setFont(font_4_1);
    ui->label_10->setFont(font_4_1);
    ui->label_11->setFont(font_4_1);
    ui->label_12->setFont(font_2_1);
    ui->label_13->setFont(font_2_1);

    ui->SwitchTM->setFont(font_4_1);
    ui->LVL0->setFont(font_4_1);
    ui->LVL1->setFont(font_4_1);
    ui->LVL2->setFont(font_4_1);
    ui->LVL3->setFont(font_4_1);
    ui->LVL4->setFont(font_4_1);
    ui->LVL5->setFont(font_4_1);
    ui->LVL6->setFont(font_4_1);
    ui->LVL7->setFont(font_4_1);
    ui->LVL8->setFont(font_4_1);
    ui->LVL9->setFont(font_4_1);
    ui->LVL0_2->setFont(font_4_1);
    ui->LVL1_2->setFont(font_4_1);
    ui->LVL2_2->setFont(font_4_1);
    ui->LVL3_2->setFont(font_4_1);
    ui->LVL4_2->setFont(font_4_1);
    ui->LVL5_2->setFont(font_4_1);
    ui->LVL6_2->setFont(font_4_1);
    ui->LVL7_2->setFont(font_4_1);
    ui->LVL8_2->setFont(font_4_1);
    ui->LVL9_2->setFont(font_4_1);

    ui->btnPLCToPLCRet->setFont(font_4_1);
    ui->btnPLCToRFRet->setFont(font_4_1);
    ui->btnRFToPLCRet->setFont(font_4_1);
    ui->btnRFToRFRet->setFont(font_4_1);
    ui->SetMask->setFont(font_3);
    ui->SetTimeout->setFont(font_3);
    ui->SetDestinationMASK->setFont(font_3);

    ui->Read->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->Mode->setFont(font_4_1);
    int current_index = ui->Mode->currentIndex();
    ui->Mode->clear();
    ui->Mode->addItem("Master Mode (Milur IC)");
    ui->Mode->addItem("Sniffer Mode");
    ui->Mode->addItem("Sniffer + Preamble Mode");
    ui->Mode->addItem("Slave Mode (Interface module)");
    ui->Mode->setCurrentIndex(current_index);

    ui->console->setFont(font_5);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    DeviceVersionHandling();
    emit Get_Console(ui->console);
    this->Set_resizing_going(0);
}
void PLC_RF_NetSettings_Form::DeviceVersionHandling(void){
    FirmwareInformationClass* In_Firmware_Information = myFormAbstractClass::Get_In_Firmware_Information();
    if (In_Firmware_Information->getDevice_Name() == RF_PLC_MODEM){
        ui->MasterMode_Widget->setVisible(false);
        ui->SlaveMode_Widget->setVisible(true);
    }else if (In_Firmware_Information->getDevice_Name() == RF_PLC_SNIFFER){
        ui->MasterMode_Widget->setVisible(true);
        ui->SlaveMode_Widget->setVisible(false);
    }
}
void PLC_RF_NetSettings_Form::Set_Out_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass* new_value){
    Out_PLC_RF433_Modem_Properties = new_value;
}
void PLC_RF_NetSettings_Form::Set_In_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass* new_value){
    In_PLC_RF433_Modem_Properties = new_value;

    setInterfaces_ControlToUI(In_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control());

    //Out_PLC_RF433_Modem_Properties->setPLC_RF433_Debug_Control(In_PLC_RF433_Modem_Properties->getPLC_RF433_Debug_Control());
    Out_PLC_RF433_Modem_Properties->setPLC_RF433_Interfaces_Control(In_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control());
}
void PLC_RF_NetSettings_Form::Set_Out_Sniffer_Properties(SnifferPropertiesClass* new_data){
    Out_Sniffer_Properties = new_data;
}
void PLC_RF_NetSettings_Form::Set_In_Sniffer_Properties(SnifferPropertiesClass* new_data){
    In_Sniffer_Properties  = new_data;

    Out_Sniffer_Properties->setSniffer_Mode(In_Sniffer_Properties->getSniffer_Mode());
    Out_Sniffer_Properties->setUpLink_Value(In_Sniffer_Properties->getUpLink_Value());
    Out_Sniffer_Properties->setCRC_Check_Disable(In_Sniffer_Properties->getCRC_Check_Disable());
    Out_Sniffer_Properties->setBroadcasting(In_Sniffer_Properties->getBroadcasting());
    Out_Sniffer_Properties->setSniffer_Level_Destination(In_Sniffer_Properties->getSniffer_Level_Destination());
    Out_Sniffer_Properties->setDirect_Transfer(In_Sniffer_Properties->getDirect_Transfer());

    SetMaskDestinationToUI(Get_Mask_Destination());
    SetUpLink_ModeToUI(Get_UpLink());
    SetCRC_Disable_ModeToUI(Get_CRCDisable());
    SetBroadcasting_ModeToUI(Get_Broadcasting());
}
void PLC_RF_NetSettings_Form::Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data){
    Out_Retranslator_Properties = new_data;
}
void PLC_RF_NetSettings_Form::Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data){
    In_Retranslator_Properties = new_data;

    Out_Retranslator_Properties->setRetranslator_Level(In_Retranslator_Properties->getRetranslator_Level());
    Out_Retranslator_Properties->setRetranslator_Mode(In_Retranslator_Properties->getRetranslator_Mode());
    Out_Retranslator_Properties->setRetranslator_Timeout(In_Retranslator_Properties->getRetranslator_Timeout());

    SetSwitchModeToUI(Out_Retranslator_Properties->getRetranslator_Mode());
    //SetSwitchLevelToUI(Out_Retranslator_Properties->getRetranslator_Level());
    SetSwitchTimeoutToUI(Out_Retranslator_Properties->getRetranslator_Timeout());
    SetSwitchMaskToUI(Out_Retranslator_Properties->getRetranslator_Level());
}
void PLC_RF_NetSettings_Form::on_Mode_currentIndexChanged(int index){
    if ((index >= 0)&&(index < 4)&&(this->Get_resizing_going() == 0)){
        emit Get_Console(ui->console);
        Out_PLC_RF433_Modem_Properties->setModem_Mode((uchar)(index));
        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void PLC_RF_NetSettings_Form::on_btnPLCToPLCRet_released()
{
    emit Get_Console(ui->console);
    if (ui->btnPLCToPLCRet->isChecked() == true){
        Out_PLC_RF433_Modem_Properties->setPLC_TO_PLC_RET_EN(1);
    }else{
        Out_PLC_RF433_Modem_Properties->setPLC_TO_PLC_RET_EN(0);
    }
    ui->Stop->setEnabled(true);
    ui->Mode->setEnabled(false);
    ui->SlaveMode_Widget->setEnabled(false);
    ui->MasterMode_Widget->setEnabled(false);
    ui->CRC_Control_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
}
void PLC_RF_NetSettings_Form::on_btnPLCToRFRet_released()
{
    emit Get_Console(ui->console);
    if (ui->btnPLCToRFRet->isChecked() == true){
        Out_PLC_RF433_Modem_Properties->setPLC_TO_RF_RET_EN(1);
    }else{
        Out_PLC_RF433_Modem_Properties->setPLC_TO_RF_RET_EN(0);
    }
    ui->Stop->setEnabled(true);
    ui->Mode->setEnabled(false);
    ui->SlaveMode_Widget->setEnabled(false);
    ui->MasterMode_Widget->setEnabled(false);
    ui->CRC_Control_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
}
void PLC_RF_NetSettings_Form::on_btnRFToPLCRet_released()
{
    emit Get_Console(ui->console);
    if (ui->btnRFToPLCRet->isChecked() == true){
        Out_PLC_RF433_Modem_Properties->setRF_TO_PLC_RET_EN(1);
    }else{
        Out_PLC_RF433_Modem_Properties->setRF_TO_PLC_RET_EN(0);
    }
    ui->Stop->setEnabled(true);
    ui->Mode->setEnabled(false);
    ui->SlaveMode_Widget->setEnabled(false);
    ui->MasterMode_Widget->setEnabled(false);
    ui->CRC_Control_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
}
void PLC_RF_NetSettings_Form::on_btnRFToRFRet_released()
{
    emit Get_Console(ui->console);
    if (ui->btnRFToRFRet->isChecked() == true){
        Out_PLC_RF433_Modem_Properties->setRF_TO_RF_RET_EN(1);
    }else{
        Out_PLC_RF433_Modem_Properties->setRF_TO_RF_RET_EN(0);
    }
    ui->Stop->setEnabled(true);
    ui->Mode->setEnabled(false);
    ui->SlaveMode_Widget->setEnabled(false);
    ui->MasterMode_Widget->setEnabled(false);
    ui->CRC_Control_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
}
void PLC_RF_NetSettings_Form::on_Switch_stateChanged(int arg1){
    if ((arg1 == 0)&&(Get_SwitchMode() != 0)){
        emit Get_Console(ui->console);
        Set_SwitchMode(0);
        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_SWITCH_MODE,CONFIG_SEND_CONTROL);
    }
    else if ((arg1 == 2)&&(Get_SwitchMode() != 1)){
        emit Get_Console(ui->console);
        Set_SwitchMode(1);
        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_SWITCH_MODE,CONFIG_SEND_CONTROL);
    }
}
void PLC_RF_NetSettings_Form::on_SetMask_clicked(){
    emit Get_Console(ui->console);
    ui->Stop->setEnabled(true);
    ui->Mode->setEnabled(false);
    ui->SlaveMode_Widget->setEnabled(false);
    ui->MasterMode_Widget->setEnabled(false);
    ui->CRC_Control_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_SWITCH_LEVEL,CONFIG_SEND_CONTROL);
}
void PLC_RF_NetSettings_Form::on_SetTimeout_clicked(){
    emit Get_Console(ui->console);
    Set_SwitchTimeout(ui->SwitchTM->text().toInt());
    ui->Stop->setEnabled(true);
    ui->Mode->setEnabled(false);
    ui->SlaveMode_Widget->setEnabled(false);
    ui->MasterMode_Widget->setEnabled(false);
    ui->CRC_Control_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_SWITCH_TIMEOUT,CONFIG_SEND_CONTROL);
}
void PLC_RF_NetSettings_Form::on_Up_Link_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Set_UpLink(0);
        }
        else {
            Set_UpLink(1);
        }
        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_UPLINK_MODE,CONFIG_SEND_CONTROL);
    }
}
void PLC_RF_NetSettings_Form::on_Disable_CRC_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Set_CRCDisable(0);
        }
        else{
            Set_CRCDisable(1);
        }

        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_CRC_CHECK_MODE,CONFIG_SEND_CONTROL);
    }
}
void PLC_RF_NetSettings_Form::on_Disable_MODBUS_CRC_stateChanged(int arg1){
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Out_PLC_RF433_Modem_Properties->setMODBUS_CRC_CHECK_DISABLE(0);
        }
        else{
            Out_PLC_RF433_Modem_Properties->setMODBUS_CRC_CHECK_DISABLE(1);
        }

        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
    }
}
void PLC_RF_NetSettings_Form::on_Broadcasting_stateChanged(int arg1)
{
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);
        if (arg1 == 0){
            Set_Broadcasting(0);
        }
        else{
            Set_Broadcasting(1);
        }

        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_BROADCASTING_MODE,CONFIG_SEND_CONTROL);
    }
}
void PLC_RF_NetSettings_Form::on_SetDestinationMASK_clicked()
{
    if (this->Get_resizing_going() == 0){
        emit Get_Console(ui->console);

        ui->Stop->setEnabled(true);
        ui->Mode->setEnabled(false);
        ui->SlaveMode_Widget->setEnabled(false);
        ui->MasterMode_Widget->setEnabled(false);
        ui->CRC_Control_Widget->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);

        emit StartSendingProcess(SEND_WRITE_MASK_DESTINATION,CONFIG_SEND_CONTROL);
    }
}
void PLC_RF_NetSettings_Form::setInterfaces_ControlToUI(Interfaces_Control_Type Interfaces_Control){
    if (ui->Mode->currentIndex() != (Interfaces_Control.Field.Modem_Mode&3)){
        ui->Mode->setCurrentIndex(Interfaces_Control.Field.Modem_Mode&3);
    }
    if (Interfaces_Control.Field.PLC_TO_PLC_RET_EN == 1){
        ui->btnPLCToPLCRet->setChecked(true);
    }else{
        ui->btnPLCToPLCRet->setChecked(false);
    }
    if (Interfaces_Control.Field.PLC_TO_RF_RET_EN == 1){
        ui->btnPLCToRFRet->setChecked(true);
    }else{
        ui->btnPLCToRFRet->setChecked(false);
    }
    if (Interfaces_Control.Field.RF_TO_PLC_RET_EN == 1){
        ui->btnRFToPLCRet->setChecked(true);
    }else{
        ui->btnRFToPLCRet->setChecked(false);
    }
    if (Interfaces_Control.Field.RF_TO_RF_RET_EN == 1){
        ui->btnRFToRFRet->setChecked(true);
    }else{
        ui->btnRFToRFRet->setChecked(false);
    }
    if ((Interfaces_Control.Field.PLC_EN != INTERFACE_ENABLE) || (Interfaces_Control.Field.PLC_INIT_OK != INTERFACE_OK_INIT)){
        ui->btnPLCToPLCRet->setEnabled(false);
    }
    if ((Interfaces_Control.Field.RF_EN != INTERFACE_ENABLE) || (Interfaces_Control.Field.RF_INIT_OK != INTERFACE_OK_INIT)){
        ui->btnRFToRFRet->setEnabled(false);
    }
    if ((Interfaces_Control.Field.PLC_EN != INTERFACE_ENABLE) || (Interfaces_Control.Field.PLC_INIT_OK != INTERFACE_OK_INIT) ||
        (Interfaces_Control.Field.RF_EN != INTERFACE_ENABLE) || (Interfaces_Control.Field.RF_INIT_OK != INTERFACE_OK_INIT)){
        ui->btnPLCToRFRet->setEnabled(false);
        ui->btnRFToPLCRet->setEnabled(false);
    }
    if ((ui->btnPLCToPLCRet->isChecked() == false) &&
        (ui->btnPLCToRFRet->isChecked() == false) &&
        (ui->btnRFToPLCRet->isChecked() == false) &&
        (ui->btnRFToRFRet->isChecked() == false)
       ){
        ui->NetMask_Widget->setEnabled(false);
        ui->Timeout_Widget->setEnabled(false);
    }else{
        if (ui->Switch->isChecked() == true){
            ui->NetMask_Widget->setEnabled(true);
            ui->Timeout_Widget->setEnabled(true);
        }
    }
    // если хотябы один интерфейс актевирован, разблокируем кнопку next
    if (((Interfaces_Control.Field.PLC_EN == INTERFACE_ENABLE) && (Interfaces_Control.Field.PLC_INIT_OK == INTERFACE_OK_INIT)) ||
        ((Interfaces_Control.Field.RF_EN == INTERFACE_ENABLE) && (Interfaces_Control.Field.RF_INIT_OK == INTERFACE_OK_INIT))   ||
        ((Interfaces_Control.Field.RS_EN == INTERFACE_ENABLE) && (Interfaces_Control.Field.RS_INIT_OK == INTERFACE_OK_INIT)) ){
        ui->Next_Widget->setEnabled(true);
        ui->Next->setEnabled(true);
    }else{
        ui->Next_Widget->setEnabled(false);
    }
    if (Interfaces_Control.Field.MODBUS_CRC_CHECK_DISABLE == 1){
        ui->Disable_MODBUS_CRC->setChecked(true);
    }else{
        ui->Disable_MODBUS_CRC->setChecked(false);
    }
}
void PLC_RF_NetSettings_Form::Set_SwitchMode(uchar  new_value)
{
    Out_Retranslator_Properties->setRetranslator_Mode(new_value);
}
uchar PLC_RF_NetSettings_Form::Get_SwitchMode(void)
{
    return Out_Retranslator_Properties->getRetranslator_Mode();
}
void PLC_RF_NetSettings_Form::SetUpLink_ModeToUI(uchar new_value){
    if(((new_value&1) == 0)&&(ui->Up_Link->isChecked() == true)){
        ui->Up_Link->setChecked(false);
    }
    else if (((new_value&1) == 1)&&(ui->Up_Link->isChecked() == false)){
        ui->Up_Link->setChecked(true);
    }
}
void PLC_RF_NetSettings_Form::SetCRC_Disable_ModeToUI(uchar new_value){
    if(((new_value&1) == 0)&&(ui->Disable_CRC->isChecked() == true)){
        ui->Disable_CRC->setChecked(false);
    }
    else if (((new_value&1) == 1)&&(ui->Disable_CRC->isChecked() == false)){
        ui->Disable_CRC->setChecked(true);
    }
}
void PLC_RF_NetSettings_Form::SetMODBUSCRC_Disable_ModeToUI(uchar new_value){
    if(((new_value&1) == 0)&&(ui->Disable_MODBUS_CRC->isChecked() == true)){
        ui->Disable_MODBUS_CRC->setChecked(false);
    }
    else if (((new_value&1) == 1)&&(ui->Disable_MODBUS_CRC->isChecked() == false)){
        ui->Disable_MODBUS_CRC->setChecked(true);
    }
}
void PLC_RF_NetSettings_Form::SetBroadcasting_ModeToUI(uchar new_value){
    if(((new_value&1) == 0)&&(ui->Broadcasting->isChecked() == true)){
        ui->Broadcasting->setChecked(false);
    }
    else if (((new_value&1) == 1)&&(ui->Broadcasting->isChecked() == false)){
        ui->Broadcasting->setChecked(true);
    }
}
void PLC_RF_NetSettings_Form::SetMaskDestinationToUI(uint mask){
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = mask;

    ui->LVL0_2->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL0);
    ui->LVL1_2->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL1);
    ui->LVL2_2->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL2);
    ui->LVL3_2->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL3);
    ui->LVL4_2->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL4);
    ui->LVL5_2->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL5);
    ui->LVL6_2->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL6);
    ui->LVL7_2->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL7);
    ui->LVL8_2->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL8);
    ui->LVL9_2->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL9);
}
void PLC_RF_NetSettings_Form::SetSwitchModeToUI(uchar new_value)
{
    if (new_value == 0){
        ui->Switch->setChecked(false);
        ui->NetMask_Widget->setEnabled(false);
        ui->RF_PLC_Net_Widget->setEnabled(false);
        ui->Timeout_Widget->setEnabled(false);
    }
    else if (new_value == 1){
        ui->Switch->setChecked(true);
        ui->NetMask_Widget->setEnabled(true);
        ui->RF_PLC_Net_Widget->setEnabled(true);
        ui->Timeout_Widget->setEnabled(true);
    }
}
void PLC_RF_NetSettings_Form::SetSwitchTimeoutToUI(uint new_value){
    ui->SwitchTM->setValue(new_value);
}
void PLC_RF_NetSettings_Form::SetSwitchMaskToUI(uint new_value){
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = new_value;

    ui->LVL0->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL0);
    ui->LVL1->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL1);
    ui->LVL2->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL2);
    ui->LVL3->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL3);
    ui->LVL4->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL4);
    ui->LVL5->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL5);
    ui->LVL6->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL6);
    ui->LVL7->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL7);
    ui->LVL8->setValue(new_mask.Field.Retranslation_MASK_0.Field.LVL8);
    ui->LVL9->setValue(new_mask.Field.Retranslation_MASK_1.Field.LVL9);
}

void PLC_RF_NetSettings_Form::isInterfaces_Control(){
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isUpLink_Mode(void)
{
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isCRC_Disable_Mode(void)
{
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isBroadcasting_Mode(void)
{
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isMask_Destination(void)
{
    Out_Sniffer_Properties->setSniffer_Level_Destination(In_Sniffer_Properties->getSniffer_Level_Destination());
    SetMaskDestinationToUI(Get_Mask_Destination());

    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isSwitchMode(){
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isSwitchLevel(){
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::isSwitchTimeout(){
    ui->Stop->setEnabled(false);
    ui->Mode->setEnabled(true);
    ui->SlaveMode_Widget->setEnabled(true);
    ui->MasterMode_Widget->setEnabled(true);
    ui->CRC_Control_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_RF_NetSettings_Form::Set_UpLink(uchar new_value){
    Out_Sniffer_Properties->setUpLink_Value(new_value);
}
uchar PLC_RF_NetSettings_Form::Get_UpLink(void){
    return Out_Sniffer_Properties->getUpLink_Value();
}
void PLC_RF_NetSettings_Form::Set_CRCDisable(uchar new_value){
    Out_Sniffer_Properties->setCRC_Check_Disable(new_value);
}
uchar PLC_RF_NetSettings_Form::Get_CRCDisable(void){
    return Out_Sniffer_Properties->getCRC_Check_Disable();
}
void PLC_RF_NetSettings_Form::Set_Broadcasting(uchar new_value){
    Out_Sniffer_Properties->setBroadcasting(new_value);
}
uchar PLC_RF_NetSettings_Form::Get_Broadcasting(void){
    return Out_Sniffer_Properties->getBroadcasting();
}
void PLC_RF_NetSettings_Form::Set_Mask_Destination(uint new_value){
    Out_Sniffer_Properties->setSniffer_Level_Destination(new_value);
}
uint  PLC_RF_NetSettings_Form::Get_Mask_Destination(void){
    return Out_Sniffer_Properties->getSniffer_Level_Destination();
}
void PLC_RF_NetSettings_Form::Set_SwitchTimeout(uint  new_value)
{
    Out_Retranslator_Properties->setRetranslator_Timeout(new_value);
}
void PLC_RF_NetSettings_Form::Set_SwitchMask(uint  new_value)
{
    Out_Retranslator_Properties->setRetranslator_Level(new_value);
}
uint  PLC_RF_NetSettings_Form::Get_SwitchMask(void)
{
    return Out_Retranslator_Properties->getRetranslator_Level();
}

void PLC_RF_NetSettings_Form::on_LVL0_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL0 = arg1;
    if (arg1 > 0)
    {
        ui->LVL1->setEnabled(true);
    }
    else
    {
        ui->LVL1->setEnabled(false); ui->LVL1->setValue(0);
        ui->LVL2->setEnabled(false); ui->LVL2->setValue(0);
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL1 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL2 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL1_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL1 = arg1;

    if (arg1 > 0)
    {
        ui->LVL2->setEnabled(true);
    }
    else
    {
        ui->LVL2->setEnabled(false); ui->LVL2->setValue(0);
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL2 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL2 = arg1;

    if (arg1 > 0)
    {
        ui->LVL3->setEnabled(true);
    }
    else
    {
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL3_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL3 = arg1;

    if (arg1 > 0)
    {
        ui->LVL4->setEnabled(true);
    }
    else
    {
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL4_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL4 = arg1;

    if (arg1 > 0)
    {
        ui->LVL5->setEnabled(true);
    }
    else
    {
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL5_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL5 = arg1;

    if (arg1 > 0)
    {
        ui->LVL6->setEnabled(true);
    }
    else
    {
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL6_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL6 = arg1;

    if (arg1 > 0)
    {
        ui->LVL7->setEnabled(true);
    }
    else
    {
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL7_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL7 = arg1;

    if (arg1 > 0)
    {
        ui->LVL8->setEnabled(true);
    }
    else
    {
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL8_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL8 = arg1;

    if (arg1 > 0)
    {
        ui->LVL9->setEnabled(true);
    }
    else
    {
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL9_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL9 = arg1;

    Set_SwitchMask(*(uint*)&(new_mask));

    //ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void PLC_RF_NetSettings_Form::on_LVL0_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL0 = arg1;
    if (arg1 > 0)
    {
        ui->LVL1_2->setEnabled(true);
    }
    else
    {
        ui->LVL1_2->setEnabled(false); ui->LVL1_2->setValue(0);
        ui->LVL2_2->setEnabled(false); ui->LVL2_2->setValue(0);
        ui->LVL3_2->setEnabled(false); ui->LVL3_2->setValue(0);
        ui->LVL4_2->setEnabled(false); ui->LVL4_2->setValue(0);
        ui->LVL5_2->setEnabled(false); ui->LVL5_2->setValue(0);
        ui->LVL6_2->setEnabled(false); ui->LVL6_2->setValue(0);
        ui->LVL7_2->setEnabled(false); ui->LVL7_2->setValue(0);
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL1 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL2 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL1_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL1 = arg1;

    if (arg1 > 0)
    {
        ui->LVL2_2->setEnabled(true);
    }
    else
    {
        ui->LVL2_2->setEnabled(false); ui->LVL2_2->setValue(0);
        ui->LVL3_2->setEnabled(false); ui->LVL3_2->setValue(0);
        ui->LVL4_2->setEnabled(false); ui->LVL4_2->setValue(0);
        ui->LVL5_2->setEnabled(false); ui->LVL5_2->setValue(0);
        ui->LVL6_2->setEnabled(false); ui->LVL6_2->setValue(0);
        ui->LVL7_2->setEnabled(false); ui->LVL7_2->setValue(0);
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL2 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL2_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL2 = arg1;

    if (arg1 > 0)
    {
        ui->LVL3_2->setEnabled(true);
    }
    else
    {
        ui->LVL3_2->setEnabled(false); ui->LVL3_2->setValue(0);
        ui->LVL4_2->setEnabled(false); ui->LVL4_2->setValue(0);
        ui->LVL5_2->setEnabled(false); ui->LVL5_2->setValue(0);
        ui->LVL6_2->setEnabled(false); ui->LVL6_2->setValue(0);
        ui->LVL7_2->setEnabled(false); ui->LVL7_2->setValue(0);
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL3 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL3_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL3 = arg1;

    if (arg1 > 0)
    {
        ui->LVL4_2->setEnabled(true);
    }
    else
    {
        ui->LVL4_2->setEnabled(false); ui->LVL4_2->setValue(0);
        ui->LVL5_2->setEnabled(false); ui->LVL5_2->setValue(0);
        ui->LVL6_2->setEnabled(false); ui->LVL6_2->setValue(0);
        ui->LVL7_2->setEnabled(false); ui->LVL7_2->setValue(0);
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL4 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

   // ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL4_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL4 = arg1;

    if (arg1 > 0)
    {
        ui->LVL5_2->setEnabled(true);
    }
    else
    {
        ui->LVL5_2->setEnabled(false); ui->LVL5_2->setValue(0);
        ui->LVL6_2->setEnabled(false); ui->LVL6_2->setValue(0);
        ui->LVL7_2->setEnabled(false); ui->LVL7_2->setValue(0);
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL5 = 0;
        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL5_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL5 = arg1;

    if (arg1 > 0)
    {
        ui->LVL6_2->setEnabled(true);
    }
    else
    {
        ui->LVL6_2->setEnabled(false); ui->LVL6_2->setValue(0);
        ui->LVL7_2->setEnabled(false); ui->LVL7_2->setValue(0);
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL6 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL6_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL6 = arg1;

    if (arg1 > 0)
    {
        ui->LVL7_2->setEnabled(true);
    }
    else
    {
        ui->LVL7_2->setEnabled(false); ui->LVL7_2->setValue(0);
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL7 = 0;
        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL7_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL7 = arg1;

    if (arg1 > 0)
    {
        ui->LVL8_2->setEnabled(true);
    }
    else
    {
        ui->LVL8_2->setEnabled(false); ui->LVL8_2->setValue(0);
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_0.Field.LVL8 = 0;

        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL8_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_0.Field.LVL8 = arg1;

    if (arg1 > 0)
    {
        ui->LVL9_2->setEnabled(true);
    }
    else
    {
        ui->LVL9_2->setEnabled(false); ui->LVL9_2->setValue(0);

        new_mask.Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void PLC_RF_NetSettings_Form::on_LVL9_2_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_Mask_Destination();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL9 = arg1;

    Set_Mask_Destination(*(uint*)&(new_mask));

    //ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}
