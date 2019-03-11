#include "plc_settings_form.h"
#include "connections_form.h"

PLC_Settings_Form::PLC_Settings_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::PLC_Settings_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);
    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->Write->setStyleSheet(Basic_PushButtons_Style);
    ui->Stop->setStyleSheet(Basic_PushButtons_Style);
    ui->Reset->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);

    ui->Back->setStyleSheet(PushButtons_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style);
    ui->Next->setStyleSheet(PushButtons_Style);

    ui->PLC_PowerIndic->setStyleSheet(Background_White + Text_Green);
    ui->PLCModulation->setStyleSheet(Background_White);
    ui->PLC_HighF->setStyleSheet(Background_White);
    ui->PLC_LowF->setStyleSheet(Background_White);

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

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

PLC_Settings_Form::~PLC_Settings_Form(){
    emit Get_Console(NULL);
    delete ui;
}
void PLC_Settings_Form::on_Back_clicked(){
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
}
void PLC_Settings_Form::on_Next_clicked(){
    this->Next_ClickHandler();
}
void PLC_Settings_Form::ForceClose(void){
    this->ForceCloseHandler();
}
void PLC_Settings_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void PLC_Settings_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void PLC_Settings_Form::on_Stop_clicked(){
    this->Stop_ClickHandler();
}
void PLC_Settings_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->Write->setEnabled(false);
    ui->Freq_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    this->Reset_ClickHandler();
}
void PLC_Settings_Form::isStopped(void){
    ui->Stop->setEnabled(false);
    ui->Write->setEnabled(true);
    ui->Freq_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_Settings_Form::isRF_Reset(){
    ui->Stop->setEnabled(false);
    ui->Write->setEnabled(true);
    ui->Freq_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);

    this->Back_ClickHandler();
}
void PLC_Settings_Form::resizeEvent(QResizeEvent *event){
    emit isCreated();
    this->Set_resizing_going(1);
    //QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
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
    QFont font_3   = ui->Write->font();    font_3.setPixelSize(text_size_3);
    QFont font_4_1 = ui->label_3->font();  font_4_1.setPixelSize(text_size_4);

    QFont font_5   = ui->console->font();  font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2_1);
    ui->label_3->setFont(font_4_1);
    ui->label_4->setFont(font_4_1);
    ui->label_5->setFont(font_2_1);
    ui->label_6->setFont(font_2_1);
    ui->label_7->setFont(font_4_1);
    ui->label_8->setFont(font_5);
    ui->label_9->setFont(font_5);
    ui->label_10->setFont(font_5);
    ui->label_11->setFont(font_5);
    ui->label_12->setFont(font_5);
    ui->Freq_Custom_Or_MIB_Select->setFont(font_5);
    ui->Freq_Overwrite->setFont(font_5);
    ui->Freq_Set->setFont(font_5);
    ui->Gain_Custom_Or_MIB_Select->setFont(font_5);
    ui->Zero_Cross_Synchronization->setFont(font_5);

    ui->PLC_HighF->setFont(font_4_1);
    ui->PLC_LowF->setFont(font_4_1);
    ui->PLC_PowerIndic->setFont(font_4_1);

    ui->PLCModulation->setFont(font_4_1);
    int current_index = ui->PLCModulation->currentIndex();
    ui->PLCModulation->clear();
    ui->PLCModulation->addItem("B-PSK 9600");
    ui->PLCModulation->addItem("Q-PSK 19200");
    ui->PLCModulation->addItem("8-PSK 28800");
    ui->PLCModulation->addItem("B-PSK Coded 4800");
    ui->PLCModulation->addItem("Q-PSK Coded 9600");
    ui->PLCModulation->addItem("B-PSK Coded PNA 2400");
    ui->PLCModulation->setCurrentIndex(current_index);

    ui->Write->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->console->setFont(font_5);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    DeviceVersionHandling();
    emit Get_Console(ui->console);
    this->Set_resizing_going(0);
}
void PLC_Settings_Form::DeviceVersionHandling(void){
    FirmwareInformationClass* In_Firmware_Information = myFormAbstractClass::Get_In_Firmware_Information();
    Interfaces_Control_Type In_Interfaces_Control = myFormAbstractClass::Get_In_Interfaces_Control();

    if (In_Firmware_Information->getDevice_Name() == PLC_MODEM){
        if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version() >= 2)       &&
             (In_Firmware_Information->getBootloader_Version() < 3)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version() >= 2)       &&
             (In_Firmware_Information->getUpgradable_Version() < 3))){
            ui->Reset_Widget->setEnabled(false);
            ui->PLCSettings_Widget->setVisible(false);
        }
    }else if (In_Firmware_Information->getDevice_Name() == RF_PLC_MODEM){
        if (((In_Interfaces_Control.Field.RF_EN == INTERFACE_ENABLE) && (In_Interfaces_Control.Field.RF_INIT_OK == INTERFACE_OK_INIT)) ||
           ((In_Interfaces_Control.Field.RS_EN == INTERFACE_ENABLE) && (In_Interfaces_Control.Field.RS_INIT_OK == INTERFACE_OK_INIT)))
           {
            ui->Next_Widget->setEnabled(true);
            ui->Next->setEnabled(true);
        }else{
            ui->Next_Widget->setEnabled(false);
        }
    }else if (In_Firmware_Information->getDevice_Name() == RF_PLC_SNIFFER){
        if (((In_Interfaces_Control.Field.RF_EN == INTERFACE_ENABLE) && (In_Interfaces_Control.Field.RF_INIT_OK == INTERFACE_OK_INIT)) ||
           ((In_Interfaces_Control.Field.RS_EN == INTERFACE_ENABLE) && (In_Interfaces_Control.Field.RS_INIT_OK == INTERFACE_OK_INIT)))
        {
            ui->Next_Widget->setEnabled(true);
            ui->Next->setEnabled(true);
        }else{
            ui->Next_Widget->setEnabled(false);
        }
    }
}
void PLC_Settings_Form::setOut_ST750_Parameters(ST750ConfigurationClass *new_value){
    Out_ST750_Parameters = new_value;
}
void PLC_Settings_Form::setIn_ST750_Parameters(ST750ConfigurationClass *new_value){
    In_ST750_Parameters = new_value;

    setLOWFToUI(In_ST750_Parameters->getST750_LOWF());
    setHIGHFToUI(In_ST750_Parameters->getST750_HIGHF());
    setTransmit_ConditionsToUI(In_ST750_Parameters->getST750_Transmit_Conditions());

    Out_ST750_Parameters->setPLC_Config_struct(In_ST750_Parameters->getPLC_Config_struct());
}
void PLC_Settings_Form::isST750_Parameters(){
    ui->Stop->setEnabled(false);
    ui->Write->setEnabled(true);
    ui->Freq_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void PLC_Settings_Form::on_Write_clicked(){
    FirmwareInformationClass* In_Firmware_Information = myFormAbstractClass::Get_In_Firmware_Information();

    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->Write->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Freq_Widget->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    if (In_Firmware_Information->getDevice_Name() == PLC_MODEM){
        emit StartSendingProcess(SEND_WRITE_ST750_FREQ,CONFIG_SEND_CONTROL);
    }else if (In_Firmware_Information->getDevice_Name() == RF_PLC_MODEM){
        emit StartSendingProcess(SEND_WRITE_ST750_PARAMETERS,CONFIG_SEND_CONTROL);
    }else if (In_Firmware_Information->getDevice_Name() == RF_PLC_SNIFFER){
        emit StartSendingProcess(SEND_WRITE_ST750_PARAMETERS,CONFIG_SEND_CONTROL);
    }
}
void PLC_Settings_Form::on_PLC_LowF_valueChanged(int arg1){
    Out_ST750_Parameters->setST750_LOWF((unsigned int)(arg1));
}
void PLC_Settings_Form::setLOWFToUI(unsigned int new_value){
    ui->PLC_LowF->setValue((int)(new_value));
}
void PLC_Settings_Form::on_PLC_HighF_valueChanged(int arg1){
    Out_ST750_Parameters->setST750_HIGHF((int)(arg1));
}
void PLC_Settings_Form::setHIGHFToUI(unsigned int new_value){
    ui->PLC_HighF->setValue((int)(new_value));
}
void PLC_Settings_Form::setTransmit_ConditionsToUI(TX_Conditions_Type new_value){
    if (new_value.Feld.TX_Gain != ui->PLC_Power->value()){
        ui->PLC_Power->setValue(new_value.Feld.TX_Gain);
    }
    if (new_value.Feld.Frame_Modulation != ui->PLCModulation->currentIndex()){
        switch (new_value.Feld.Frame_Modulation){
            case 0: ui->PLCModulation->setCurrentIndex(0); break;
            case 1: ui->PLCModulation->setCurrentIndex(1); break;
            case 2: ui->PLCModulation->setCurrentIndex(2); break;
            case 4: ui->PLCModulation->setCurrentIndex(3); break;
            case 5: ui->PLCModulation->setCurrentIndex(4); break;
            case 7: ui->PLCModulation->setCurrentIndex(5); break;
        }
    }
    ui->Freq_Custom_Or_MIB_Select->setText(QString::number(new_value.Feld.Freq_Custom_Or_MIB_Select));
    ui->Freq_Overwrite->setText(QString::number(new_value.Feld.Freq_Overwrite));
    ui->Freq_Set->setText(QString::number(new_value.Feld.Freq_Set));
    ui->Gain_Custom_Or_MIB_Select->setText(QString::number(new_value.Feld.Gain_Custom_Or_MIB_Select));
    ui->Zero_Cross_Synchronization->setText(QString::number(new_value.Feld.Zero_Cross_Synchronization));
}
void PLC_Settings_Form::on_PLC_Power_valueChanged(int value){
    double k = (double)(100 - 60)/(31-3);
    double percent = k * (value - 3) + 60;
    ui->PLC_PowerIndic->setText(QString::number(percent,'f', 1) + "%");
}

void PLC_Settings_Form::on_PLC_Power_sliderReleased(){
   TX_Conditions_Type Transmit_Conditions = Out_ST750_Parameters->getST750_Transmit_Conditions();
   Transmit_Conditions.Feld.TX_Gain = ui->PLC_Power->value();
   Out_ST750_Parameters->setST750_Transmit_Conditions(Transmit_Conditions);
}

void PLC_Settings_Form::on_PLCModulation_currentIndexChanged(int index){
    if ((index >= 0)&&(index < 6)&&(this->Get_resizing_going() == 0)){
        TX_Conditions_Type Transmit_Conditions = Out_ST750_Parameters->getST750_Transmit_Conditions();
        switch(index){
            case 0: Transmit_Conditions.Feld.Frame_Modulation = 0; break;
            case 1: Transmit_Conditions.Feld.Frame_Modulation = 1; break;
            case 2: Transmit_Conditions.Feld.Frame_Modulation = 2; break;
            case 3: Transmit_Conditions.Feld.Frame_Modulation = 4; break;
            case 4: Transmit_Conditions.Feld.Frame_Modulation = 5; break;
            case 5: Transmit_Conditions.Feld.Frame_Modulation = 7; break;
        }
        Out_ST750_Parameters->setST750_Transmit_Conditions(Transmit_Conditions);
    }
}
