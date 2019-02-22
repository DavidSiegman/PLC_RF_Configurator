#include "interfaces_control_form.h"
#include "connections_form.h"

Interfaces_Control_Form::Interfaces_Control_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::Interfaces_Control_Form;
    ui->setupUi(this);
    this->setWindowTitle((QString)(APPLICATION_NAME) + " " + BUILDING_VERSION);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->btnPLCEnable->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnRFEnable->setStyleSheet(Basic_ToolButtons_Style);
    ui->btnRSEnable->setStyleSheet(Basic_ToolButtons_Style);
    ui->Read->setStyleSheet(Basic_PushButtons_Style);
    ui->Stop->setStyleSheet(Basic_PushButtons_Style);
    ui->Reset->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);

    ui->LastAOPEN->setStyleSheet(Work_Area_Style + Text_Green_Disabled);

    ui->Back->setStyleSheet(PushButtons_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style);
    ui->Next->setStyleSheet(PushButtons_Style);
    ui->Next->setEnabled(true);

    ui->PLCStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);
    ui->RFStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);
    ui->RSStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);
    ui->EEPROMStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);

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
Interfaces_Control_Form::~Interfaces_Control_Form(){
    emit Get_Console(NULL);
    delete ui;
}
void Interfaces_Control_Form::on_Back_clicked(){
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
}
void Interfaces_Control_Form::on_Next_clicked(){
    this->Next_ClickHandler();
}
void Interfaces_Control_Form::ForceClose(void){
    this->ForceCloseHandler();
}
void Interfaces_Control_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void Interfaces_Control_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void Interfaces_Control_Form::on_Stop_clicked(){
    this->Stop_ClickHandler();
}
void Interfaces_Control_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->Iterfaces_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    this->Reset_ClickHandler();
}
void Interfaces_Control_Form::isStopped(void){
    ui->Stop->setEnabled(false);
    ui->Iterfaces_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Interfaces_Control_Form::isRF_Reset(void){
    ui->Stop->setEnabled(false);
    ui->Iterfaces_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void Interfaces_Control_Form::resizeEvent(QResizeEvent *event){
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
    QFont font_4_1 = ui->label_3->font();  font_4_1.setPixelSize(text_size_4);
    QFont font_4_2 = ui->label_3->font();  font_4_2.setPixelSize(text_size_5);
    QFont font_5   = ui->console->font();  font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2_1);
    ui->label_3->setFont(font_4_1);
    ui->label_4->setFont(font_4_1);
    ui->label_5->setFont(font_4_1);
    ui->label_6->setFont(font_2_1);
    ui->label_7->setFont(font_4_1);
    ui->label_8->setFont(font_4_1);
    ui->label_9->setFont(font_4_1);
    ui->label_10->setFont(font_4_1);
    ui->label_11->setFont(font_2_1);

    ui->btnPLCEnable->setFont(font_4_1);
    ui->btnRFEnable->setFont(font_4_1);
    ui->btnRSEnable->setFont(font_4_1);
    ui->Read->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->LastAOPEN->setFont(font_4_1);

    ui->console->setFont(font_5);
    ui->PLCStatus->setFont(font_4_1);
    ui->RFStatus->setFont(font_4_1);
    ui->RSStatus->setFont(font_4_1);
    ui->EEPROMStatus->setFont(font_4_1);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    emit Get_Console(ui->console);
    this->Set_resizing_going(0);
}
void Interfaces_Control_Form::Set_Out_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass* new_value){
    Out_PLC_RF433_Modem_Properties = new_value;
}
void Interfaces_Control_Form::Set_In_PLC_RF433_Modem_Properties(PlcRfModemPropertiesClass* new_value){
    In_PLC_RF433_Modem_Properties = new_value;

    setInterfaces_ControlToUI(In_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control());

    //Out_PLC_RF433_Modem_Properties->setPLC_RF433_DEBUG_Control(In_PLC_RF433_Modem_Properties->getPLC_RF433_DEBUG_Control());
    Out_PLC_RF433_Modem_Properties->setPLC_RF433_Interfaces_Control(In_PLC_RF433_Modem_Properties->getPLC_RF433_Interfaces_Control());
}
void Interfaces_Control_Form::setInterfaces_ControlToUI(Interfaces_Control_Type Interfaces_Control){
    if(Interfaces_Control.Field.PLC_INIT_OK == 1){
        ui->PLCStatus->setText(INIT_OK_STRING);
        ui->PLCStatus->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    }
    if(Interfaces_Control.Field.PLC_EN != 0){
        ui->btnPLCEnable->setChecked(true);
        if (Interfaces_Control.Field.PLC_INIT_OK == 0){
            ui->PLCStatus->setText(ERROR_STRING);
            ui->PLCStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);
        }
        ui->btnRFEnable->setEnabled(true);
    }else{
        ui->btnPLCEnable->setChecked(false);
        if (Interfaces_Control.Field.PLC_INIT_OK == 0){
            ui->PLCStatus->setText(DISABLED_STRING);
            ui->PLCStatus->setStyleSheet(Work_Area_Style + Text_Red);
        }
        ui->btnRFEnable->setEnabled(false);
    }
    if(Interfaces_Control.Field.RF_INIT_OK == 1){
        ui->RFStatus->setText(INIT_OK_STRING);
        ui->RFStatus->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    }
    if(Interfaces_Control.Field.RF_EN != 0){
        ui->btnRFEnable->setChecked(true);
        if (Interfaces_Control.Field.RF_INIT_OK == 0){
            ui->RFStatus->setText(ERROR_STRING);
            ui->RFStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);
        }
        ui->btnPLCEnable->setEnabled(true);
    }else{
        ui->btnRFEnable->setChecked(false);
        if (Interfaces_Control.Field.RF_INIT_OK == 0){
            ui->RFStatus->setText(DISABLED_STRING);
            ui->RFStatus->setStyleSheet(Work_Area_Style + Text_Red);
        }
        ui->btnPLCEnable->setEnabled(false);
    }
    if(Interfaces_Control.Field.RS_INIT_OK == 1){
        ui->RSStatus->setText(INIT_OK_STRING);
        ui->RSStatus->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    }
    if(Interfaces_Control.Field.RS_EN != 0){
        ui->btnRSEnable->setChecked(true);
        if (Interfaces_Control.Field.RS_INIT_OK == 0){
            ui->RSStatus->setText(ERROR_STRING);
            ui->RSStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);
        }
    }else{
        ui->btnRSEnable->setChecked(false);
        if (Interfaces_Control.Field.RS_INIT_OK == 0){
            ui->RSStatus->setText(DISABLED_STRING);
            ui->RSStatus->setStyleSheet(Work_Area_Style + Text_Red);
        }
    }
    if(Interfaces_Control.Field.EEPROM_INIT_OK == 1){
        ui->EEPROMStatus->setText(INIT_OK_STRING);
        ui->EEPROMStatus->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    }else{
        ui->EEPROMStatus->setText(ERROR_STRING);
        ui->EEPROMStatus->setStyleSheet(Work_Area_Style + Text_Red_Disabled);
    }
}
void Interfaces_Control_Form::on_btnPLCEnable_toggled(bool checked){
    if (checked == true){
        ui->btnPLCEnable->setText("Включен");
    }else{
        ui->btnPLCEnable->setText("Выключен");
    }
}

void Interfaces_Control_Form::on_btnRFEnable_toggled(bool checked){
    if (checked == true){
        ui->btnRFEnable->setText("Включен");
    }else{
        ui->btnRFEnable->setText("Выключен");
    }
}

void Interfaces_Control_Form::on_btnRSEnable_toggled(bool checked)
{
    if (checked == true){
        ui->btnRSEnable->setText("Включен");
    }else{
        ui->btnRSEnable->setText("Выключен");
    }
}

void Interfaces_Control_Form::on_btnPLCEnable_released()
{
    emit Get_Console(ui->console);
    if (ui->btnPLCEnable->isChecked() == true){
        Out_PLC_RF433_Modem_Properties->setPLC_EN(3);
    }else{
        Out_PLC_RF433_Modem_Properties->setPLC_EN(0);
    }
    ui->Stop->setEnabled(true);
    ui->Iterfaces_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
}

void Interfaces_Control_Form::on_btnRFEnable_released()
{
    emit Get_Console(ui->console);
    if (ui->btnRFEnable->isChecked() == true){
        Out_PLC_RF433_Modem_Properties->setRF_EN(3);
    }else{
        Out_PLC_RF433_Modem_Properties->setRF_EN(0);
    }
    ui->Stop->setEnabled(true);
    ui->Iterfaces_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
}

void Interfaces_Control_Form::on_btnRSEnable_released()
{
    emit Get_Console(ui->console);
    if (ui->btnRSEnable->isChecked() == true){
        Out_PLC_RF433_Modem_Properties->setRS_EN(3);
    }else{
        Out_PLC_RF433_Modem_Properties->setRS_EN(0);
    }
    ui->Stop->setEnabled(true);
    ui->Iterfaces_Widget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_INTERFACES_CONTROL,CONFIG_SEND_CONTROL);
}

void Interfaces_Control_Form::isInterfaces_Control(){
    ui->Stop->setEnabled(false);
    ui->Iterfaces_Widget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
