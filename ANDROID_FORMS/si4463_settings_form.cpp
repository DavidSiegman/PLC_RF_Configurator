#include "si4463_settings_form.h"
#include "connections_form.h"

SI4463_Settings_Form::SI4463_Settings_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::SI4463_Settings_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style + ToolTip_Style);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->FileOpen->setStyleSheet(Basic_PushButtons_Style);
    ui->Write->setStyleSheet(Basic_PushButtons_Style);
    ui->Stop->setStyleSheet(Basic_PushButtons_Style);
    ui->Reset->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);
    ui->Registers->setStyleSheet(Basic_PushButtons_Style);

    ui->Back->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->Next->setStyleSheet(PushButtons_Style+ToolTip_Style);
}
void SI4463_Settings_Form::on_ClearConsole_clicked(){
    WriteLogToFile(ui->console);
    ui->console->clear();
}
SI4463_Settings_Form::~SI4463_Settings_Form(){
    emit Get_Console(NULL);
    delete ui;
}
void SI4463_Settings_Form::on_Back_clicked(){
    WriteLogToFile(ui->console);
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
}
void SI4463_Settings_Form::on_Next_clicked(){
    WriteLogToFile(ui->console);
    this->Next_ClickHandler();
}
void SI4463_Settings_Form::ForceClose(void){
    WriteLogToFile(ui->console);
    this->ForceCloseHandler();
}
void SI4463_Settings_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void SI4463_Settings_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}

void SI4463_Settings_Form::on_Stop_clicked(){
    this->Stop_ClickHandler();
}
void SI4463_Settings_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    this->Reset_ClickHandler();
}
void SI4463_Settings_Form::isStopped(){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void SI4463_Settings_Form::isRF_Reset(){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);

    this->Back_ClickHandler();
}
void SI4463_Settings_Form::resizeEvent(QResizeEvent *event)
{
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

    QFont font_1 = ui->label_1->font();     font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->label_2->font();     font_2.setPixelSize(text_size_2);
    QFont font_3 = ui->Write->font();       font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->label_3->font();     font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();     font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);  ui->label_11->setFont(font_4);  ui->Freq->setFont(font_4);
    ui->label_2->setFont(font_2);  ui->label_12->setFont(font_4);  ui->RXBW->setFont(font_4);
    ui->label_3->setFont(font_4);  ui->label_13->setFont(font_4);  ui->WB_BW->setFont(font_4);
    ui->label_4->setFont(font_4);  ui->label_14->setFont(font_4);  ui->NB_BW->setFont(font_4);
    ui->label_5->setFont(font_4);  ui->DataRate->setFont(font_4);  ui->ANT_DIV->setFont(font_4);
    ui->label_6->setFont(font_4);  ui->Fdev->setFont(font_4);      ui->MOD_INDEX->setFont(font_4);
    ui->label_7->setFont(font_4);  ui->WB_Filter->setFont(font_4);
    ui->label_8->setFont(font_4);  ui->NB_Filter->setFont(font_4);
    ui->label_9->setFont(font_4);  ui->AFC_State->setFont(font_4);
    ui->label_10->setFont(font_4); ui->MODULATION->setFont(font_4);

    ui->FileOpen->setFont(font_3);
    ui->Write->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);
    ui->Registers->setFont(font_3);

    ui->console->setFont(font_5);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->label_1->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    DeviceVersionHandling();
    emit Get_Console(ui->console);
    this->Set_resizing_going(0);
}

void SI4463_Settings_Form::DeviceVersionHandling(void){
    FirmwareInformationClass* In_Firmware_Information = myFormAbstractClass::Get_In_Firmware_Information();
    Interfaces_Control_Type In_Interfaces_Control = myFormAbstractClass::Get_In_Interfaces_Control();

    if (In_Firmware_Information->getDevice_Name() == RF_PLC_MODEM){
        if ((In_Interfaces_Control.Field.RS_EN == INTERFACE_ENABLE) &&
            (In_Interfaces_Control.Field.RS_INIT_OK == INTERFACE_OK_INIT)){
            ui->Next_Widget->setEnabled(true);
            ui->Next->setEnabled(true);
        }else{
            ui->Next_Widget->setEnabled(false);
        }
    }else if (In_Firmware_Information->getDevice_Name() == RF_PLC_SNIFFER){
        if ((In_Interfaces_Control.Field.RS_EN == INTERFACE_ENABLE) &&
            (In_Interfaces_Control.Field.RS_INIT_OK == INTERFACE_OK_INIT)){
            ui->Next_Widget->setEnabled(true);
            ui->Next->setEnabled(true);
        }else{
            ui->Next_Widget->setEnabled(false);
        }
    }
}

void SI4463_Settings_Form::on_Write_clicked()
{
    emit Get_Console(ui->console);
    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);
    emit StartSendingProcess(SEND_WRITE_RFSI4463_PARAMETERS,CONFIG_SEND_CONTROL);
}
void SI4463_Settings_Form::isSI4463_Parameters(){
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}
void SI4463_Settings_Form::Set_Model(QStandardItemModel *model)
{
    //ui->SI4436_PROPSView      ->setModel(model);
    //ui->SI4436_PROPSView      ->resizeRowsToContents();
    //ui->SI4436_PROPSView      ->resizeColumnsToContents();
}

void SI4463_Settings_Form::Set_Prameters(QList<Params> *params)
{
    ui->DataRate->setText("-");  ui->Freq->setText("-");
    ui->MODULATION->setText("-");ui->Fdev->setText("-");
    ui->RXBW->setText("-");      ui->AFC_State->setText("-");
    ui->WB_Filter->setText("-"); ui->NB_Filter->setText("-");
    ui->WB_BW->setText("-");     ui->NB_BW->setText("-");
    ui->MOD_INDEX->setText("-"); ui->ANT_DIV->setText("-");
    int index = 0;
    for(int i = 0; i < params->length();i++)
    {
        if(params->at(i).name.compare("Rsymb(sps):") == 0)
        {
            ui->DataRate->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("RF Freq.(MHz):") == 0)
        {
            ui->Freq->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("MOD_type:") == 0)
        {
            ui->MODULATION->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("Fdev(Hz):") == 0)
        {
            ui->Fdev->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("RXBW(Hz):") == 0)
        {
            ui->RXBW->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("AFC_en:") == 0)
        {
            ui->AFC_State->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("WB filter ") == 0)
        {
            ui->WB_Filter->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("NB-filter ") == 0)
        {
            index = 1;
            ui->NB_Filter->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("NB-filter ") == 0)
        {
            ui->NB_Filter->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("BW =  ") == 0)
        {
            ui->WB_BW->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("BW = ") == 0)
        {
           ui->NB_BW->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("Modulation index:") == 0)
        {
            ui->MOD_INDEX->setText(params->at(i).value);
        }
        if(params->at(i).name.compare("ANT_DIV:") == 0)
        {
            ui->ANT_DIV->setText(params->at(i).value);
        }

    }
    ui->Write->setEnabled(true);
}
void SI4463_Settings_Form::on_FileOpen_clicked(){

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    QString new_path;
    QString old_path = settings.value(SI4463_BATCH_PATH).toString();

    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", old_path, "*.txt");

    QString s = "";
    for(uint i = (str.length()); i > 0; i--){
        if (str.at(i-1) != '/'){
            s.push_front(str.at(i-1));
        }
        else{
            new_path = str;
            new_path.remove(i, str.length()-i);
            settings.setValue(SI4463_BATCH_PATH, new_path);
            settings.sync();
            break;
        }
    }
    ui->FileName->setText(s);
    emit Start_Parcer(str);
}
void SI4463_Settings_Form::on_Registers_clicked(){
    emit Open_RegistersWindow(this);
}
