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

    ui->Write->setStyleSheet(Basic_Buttons_Style);
    ui->Stop->setStyleSheet(Basic_Buttons_Style);
    ui->Reset->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);
    ui->Next->setEnabled(false);

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
    QFont font_2_1 = ui->label_2->font();  font_2_1.setPixelSize(text_size_3);
    QFont font_3   = ui->Write->font();    font_3.setPixelSize(text_size_3);
    QFont font_4_1 = ui->label_3->font();  font_4_1.setPixelSize(text_size_4);

    QFont font_5   = ui->console->font();  font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2_1);
    ui->label_3->setFont(font_4_1);
    ui->label_4->setFont(font_4_1);

    ui->PLC_HighF->setFont(font_4_1);
    ui->PLC_LowF->setFont(font_4_1);


    ui->Write->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->console->setFont(font_5);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    DeviceVersionHandling();
    emit Get_Console(ui->console);
    this->Set_resizing_going(0);
}
void PLC_Settings_Form::DeviceVersionHandling(void){
    FirmwareInformationClass* In_Firmware_Information = myFormAbstractClass::Get_In_Firmware_Information();

    if (In_Firmware_Information->getDevice_Name() == PLC_MODEM){
        if (((In_Firmware_Information->getCurrent_Firmware_Version() == 0) &&
             (In_Firmware_Information->getBootloader_Version() >= 2)       &&
             (In_Firmware_Information->getBootloader_Version() < 3)) ||
            ((In_Firmware_Information->getCurrent_Firmware_Version() == 1) &&
             (In_Firmware_Information->getUpgradable_Version() >= 2)       &&
             (In_Firmware_Information->getUpgradable_Version() < 3))){
            ui->Reset_Widget->setEnabled(false);
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
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->Write->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Freq_Widget->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit StartSendingProcess(SEND_WRITE_ST750_PARAMETERS,CONFIG_SEND_CONTROL);
}
void PLC_Settings_Form::on_PLC_LowF_valueChanged(int arg1){
    if (arg1 > ui->PLC_HighF->value()){
        arg1 = ui->PLC_HighF->value();
        setLOWFToUI(arg1);
    }
    Out_ST750_Parameters->setST750_LOWF((unsigned int)(arg1));
}
void PLC_Settings_Form::setLOWFToUI(unsigned int new_value){
    ui->PLC_LowF->setValue((int)(new_value));
}
void PLC_Settings_Form::on_PLC_HighF_valueChanged(int arg1){
    if (arg1 < ui->PLC_LowF->value()){
        arg1 = ui->PLC_LowF->value();
        setHIGHFToUI(arg1);
    }
    Out_ST750_Parameters->setST750_HIGHF((int)(arg1));
}
void PLC_Settings_Form::setHIGHFToUI(unsigned int new_value){
    ui->PLC_HighF->setValue((int)(new_value));
}

