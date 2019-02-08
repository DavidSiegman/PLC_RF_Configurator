#include "net_settings_form.h"
#include "connections_form.h"
#include "STYLE/style.h"

Net_Settings_Form::Net_Settings_Form(QWidget *parent) :
    myFormAbstractClass(parent)

{
    ui = new Ui::Net_Settings_Form;
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->SetMask->setStyleSheet(Basic_Buttons_Style);
    ui->SetLevel->setStyleSheet(Basic_Buttons_Style);
    ui->SetTimeout->setStyleSheet(Basic_Buttons_Style);
    ui->Write->setStyleSheet(Basic_Buttons_Style);
    ui->Stop->setStyleSheet(Basic_Buttons_Style);
    ui->Reset->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->NetTable->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);

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

    ui->SwitchLVL->setStyleSheet(Background_White);
    ui->SwitchTM->setStyleSheet(Background_White);

    ui->SwitchLVL->setVisible(false);

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

Net_Settings_Form::~Net_Settings_Form()
{
    delete ui;
}

void Net_Settings_Form::on_Back_clicked(){
    this->Back_ClickHandler();
}
void Net_Settings_Form::on_Next_clicked(){
    this->Next_ClickHandler();
}
void Net_Settings_Form::ForceClose(void){
    this->ForceCloseHandler();
}
void Net_Settings_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void Net_Settings_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void Net_Settings_Form::on_Stop_clicked(){
    emit Stop_Send_Data();
}
void Net_Settings_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);
    this->Reset_ClickHandler();
}
void Net_Settings_Form::isStopped(void){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Net_Settings_Form::isRF_Reset(void){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Net_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();

    resize_calculating.set_form_geometry(this->geometry());

    int text_size_1 = resize_calculating.get_text_size_1();
    int text_size_2 = resize_calculating.get_text_size_2();
    int text_size_3 = resize_calculating.get_text_size_3();
    int text_size_4 = resize_calculating.get_text_size_4();
    int text_size_5 = resize_calculating.get_text_size_5();

    QSize icons_size;
    icons_size.setWidth(resize_calculating.get_icons_size());
    icons_size.setHeight(resize_calculating.get_icons_size());

    QFont font_1 = ui->label_1->font();     font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->Switch->font();     font_2.setPixelSize(text_size_4);
    QFont font_3 = ui->Write->font();       font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->SetMask->font();     font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();     font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->Switch->setFont(font_2);

    ui->SetMask->setFont(font_3);
    ui->SetLevel->setFont(font_3);
    ui->SetTimeout->setFont(font_3);
    ui->Write->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);
    ui->NetTable->setFont(font_3);

    ui->LVL0->setFont(font_4);
    ui->LVL1->setFont(font_4);
    ui->LVL2->setFont(font_4);
    ui->LVL3->setFont(font_4);
    ui->LVL4->setFont(font_4);
    ui->LVL5->setFont(font_4);
    ui->LVL6->setFont(font_4);
    ui->LVL7->setFont(font_4);
    ui->LVL8->setFont(font_4);
    ui->LVL9->setFont(font_4);

    ui->SwitchLVL->setFont(font_4);
    ui->SwitchTM->setFont(font_4);

    ui->console->setFont(font_5);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}
void Net_Settings_Form::on_Switch_stateChanged(int arg1){
    if ((arg1 == 0)&&(Get_SwitchMode() != 0)){
        emit Get_Console(ui->console);
        Set_SwitchMode(0);
        ui->Stop->setEnabled(true);
        ui->SettingsWidget->setEnabled(false);
        ui->NetTable->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_SWITCH_MODE);
    }
    else if ((arg1 == 2)&&(Get_SwitchMode() != 1)){
        emit Get_Console(ui->console);
        Set_SwitchMode(1);
        ui->Stop->setEnabled(true);
        ui->SettingsWidget->setEnabled(false);
        ui->NetTable->setEnabled(false);
        ui->Reset->setEnabled(false);
        ui->Back->setEnabled(false);
        ui->btnSettings->setEnabled(false);
        ui->Next->setEnabled(false);
        emit StartSendingProcess(SEND_WRITE_SWITCH_MODE);
    }
}
void Net_Settings_Form::isSwitchMode(){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->NetTable->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Net_Settings_Form::on_SetMask_clicked(){
    emit Get_Console(ui->console);
    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->NetTable->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_SWITCH_LEVEL);
}
void Net_Settings_Form::on_SetLevel_clicked(){
    emit Get_Console(ui->console);
    Set_SwitchLevel(ui->SwitchLVL->text().toInt());
    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->NetTable->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_SWITCH_LEVEL);
}
void Net_Settings_Form::isSwitchLevel(){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->NetTable->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Net_Settings_Form::on_SetTimeout_clicked(){
    emit Get_Console(ui->console);
    Set_SwitchTimeout(ui->SwitchTM->text().toInt());
    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->NetTable->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_SWITCH_TIMEOUT);
}
void Net_Settings_Form::isSwitchTimeout(){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->NetTable->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void Net_Settings_Form::on_NetTable_clicked(){
    emit Retranslation_Table(this);
}
void Net_Settings_Form::Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data)
{
    Out_Retranslator_Properties = new_data;
}
void Net_Settings_Form::Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data)
{
    In_Retranslator_Properties = new_data;

    Out_Retranslator_Properties->setRetranslator_Level(In_Retranslator_Properties->getRetranslator_Level());
    Out_Retranslator_Properties->setRetranslator_Mode(In_Retranslator_Properties->getRetranslator_Mode());
    Out_Retranslator_Properties->setRetranslator_Timeout(In_Retranslator_Properties->getRetranslator_Timeout());

    SetSwitchModeToUI(Out_Retranslator_Properties->getRetranslator_Mode());
    //SetSwitchLevelToUI(Out_Retranslator_Properties->getRetranslator_Level());
    SetSwitchTimeoutToUI(Out_Retranslator_Properties->getRetranslator_Timeout());
    SetSwitchMaskToUI(Out_Retranslator_Properties->getRetranslator_Level());
}

void Net_Settings_Form::SetSwitchModeToUI(uchar new_value)
{
    if (new_value == 0)
    {
        ui->Switch->setChecked(false);
    }
    else if (new_value == 1)
    {
        ui->Switch->setChecked(true);
    }
}
void Net_Settings_Form::SetSwitchLevelToUI(uint new_value)
{
    ui->SwitchLVL->setValue(new_value);
}
void Net_Settings_Form::SetSwitchTimeoutToUI(uint new_value)
{
    ui->SwitchTM->setValue(new_value);
}
void Net_Settings_Form::SetSwitchMaskToUI(uint new_value)
{
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

void Net_Settings_Form::Set_SwitchMode(uchar  new_value)
{
    Out_Retranslator_Properties->setRetranslator_Mode(new_value);
}
uchar Net_Settings_Form::Get_SwitchMode(void)
{
    return Out_Retranslator_Properties->getRetranslator_Mode();
}
void Net_Settings_Form::Set_SwitchLevel(uint  new_value)
{
    Out_Retranslator_Properties->setRetranslator_Level(new_value);
}
void Net_Settings_Form::Set_SwitchTimeout(uint  new_value)
{
    Out_Retranslator_Properties->setRetranslator_Timeout(new_value);
}
void Net_Settings_Form::Set_SwitchMask(uint  new_value)
{
    Out_Retranslator_Properties->setRetranslator_Level(new_value);
}
uint  Net_Settings_Form::Get_SwitchMask(void)
{
    return Out_Retranslator_Properties->getRetranslator_Level();
}

void Net_Settings_Form::on_LVL0_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL1_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL2_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL3_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL4_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL5_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL6_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL7_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL8_valueChanged(int arg1)
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

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}

void Net_Settings_Form::on_LVL9_valueChanged(int arg1)
{
    uint Sniffer_Level = Get_SwitchMask();
    RF_Switch_Mask new_mask;
    (*(uint*)&(new_mask)) = Sniffer_Level;
    new_mask.Field.Retranslation_MASK_1.Field.LVL9 = arg1;

    Set_SwitchMask(*(uint*)&(new_mask));

    ui->SwitchLVL->setValue(*(uint*)&(new_mask));
}
