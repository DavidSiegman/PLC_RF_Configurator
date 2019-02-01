#include "rssimonitor_form.h"
#include "connections_form.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

RSSIMonitor_Form::RSSIMonitor_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new (Ui::RSSIMonitor_Form);
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    ui->SN->setText(settings.value(CONNECTION_SETTINGS_SN).toString());
    ui->ModuleType->setCurrentIndex(settings.value(CONNECTION_SETTINGS_MODULE_TYPE).toInt());
    ui->Interface->setCurrentIndex(settings.value(CONNECTION_SETTINGS_INTERFACE).toInt());

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->readLatchRSSI->setStyleSheet(Basic_Buttons_Style);
    ui->MonitorStart->setStyleSheet(Basic_Buttons_Style);
    ui->Stop->setStyleSheet(Basic_Buttons_Style);
    ui->Reset->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);

    ui->Interface->setStyleSheet(Background_White);
    ui->ModuleType->setStyleSheet(Background_White);
    ui->SN->setStyleSheet(Background_White);

    ui->AFC->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    ui->RSSI_ANT1->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    ui->RSSI_ANT2->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    ui->MsgCounter->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    ui->YesAnswer->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    ui->NoAnswer->setStyleSheet(Work_Area_Style + Text_Green_Disabled);
    ui->AValue->setStyleSheet(Work_Area_Style + Text_Green_Disabled);

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

RSSIMonitor_Form::~RSSIMonitor_Form()
{
    delete ui;
}
void RSSIMonitor_Form::on_Back_clicked(){
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.setValue(CONNECTION_SETTINGS_MODULE_TYPE, ADDITIONAL_MODULE_TYPE);
    settings.sync();
    this->Back_ClickHandler();
}
void RSSIMonitor_Form::on_Next_clicked(){
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.setValue(CONNECTION_SETTINGS_MODULE_TYPE, ADDITIONAL_MODULE_TYPE);
    settings.sync();
    this->Next_ClickHandler();
}
void RSSIMonitor_Form::ForceClose(void){
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.setValue(CONNECTION_SETTINGS_MODULE_TYPE, ADDITIONAL_MODULE_TYPE);
    settings.sync();
    this->ForceCloseHandler();
}
void RSSIMonitor_Form::on_btnSettings_clicked(){
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.setValue(CONNECTION_SETTINGS_MODULE_TYPE, ADDITIONAL_MODULE_TYPE);
    settings.sync();
    emit Settings(this);
}
//void RSSIMonitor_Form::SetProgress(uint progress){
//    ui->progress->setValue(progress);
//}

void RSSIMonitor_Form::on_Stop_clicked(){
    //this->Stop_ClickHandler();
    emit StopRSSIMonitor();
}
void RSSIMonitor_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);

    ui->InterfaceWidget->setEnabled(false);
    ui->LatchRSSIWidget->setEnabled(false);
    ui->MonitorWidget->setEnabled(false);
    ui->Stop->setEnabled(true);
    ui->Reset->setEnabled(false);
    ui->Next->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);

    this->Reset_ClickHandler();
}
void RSSIMonitor_Form::isStopped(void){
    SetProgress(0);
    ui->InterfaceWidget->setEnabled(true);
    ui->LatchRSSIWidget->setEnabled(true);
    ui->MonitorWidget->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(false);
    ui->btnSettings->setEnabled(true);
}
void RSSIMonitor_Form::isRF_Reset(){

    ui->InterfaceWidget->setEnabled(true);
    ui->LatchRSSIWidget->setEnabled(true);
    ui->MonitorWidget->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(true);
    ui->btnSettings->setEnabled(true);

    SetRSSILvlToUI(0);
    ui->RSSI_ANT1->setText("NAN");
    ui->RSSI_ANT2->setText("NAN");
    ui->AFC->setText("NAN");
    SetMsgCounterToUI(0);
    SetYesAnswerToUI(0);
    SetNoAnswerToUI(0);
    SetAValueUI(0);
}
void RSSIMonitor_Form::resizeEvent(QResizeEvent *event)
{
    this->Set_resizing_going(1);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

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
    QFont font_3   = ui->readLatchRSSI->font();  font_3.setPixelSize(text_size_3);
    QFont font_4_1 = ui->label_2->font();  font_4_1.setPixelSize(text_size_4);
    QFont font_4_2 = ui->label_6->font();  font_4_2.setPixelSize(text_size_4);
    QFont font_5   = ui->console->font();  font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_4_1);
    ui->label_3->setFont(font_4_1);
    ui->label_4->setFont(font_4_1);
    ui->label_5->setFont(font_4_2);
    ui->label_6->setFont(font_4_2);
    ui->label_7->setFont(font_4_2);
    ui->label_8->setFont(font_5);
    ui->label_9->setFont(font_5);
    ui->label_10->setFont(font_5);
    ui->label_11->setFont(font_5);

    ui->Interface->setFont(font_4_2);
    ui->Interface->clear();
    ui->Interface->addItem("COM/УСО (Оптопорт)");
    ui->Interface->addItem("PLC/RF");
    ui->Interface->setCurrentIndex(settings.value(CONNECTION_SETTINGS_INTERFACE).toInt());

    ui->ModuleType->setFont(font_4_2);
    ui->ModuleType->clear();
    ui->ModuleType->addItem("Дополнительный");
    ui->ModuleType->addItem("Основной");
    ui->ModuleType->setCurrentIndex(settings.value(CONNECTION_SETTINGS_MODULE_TYPE).toInt());

    ui->SN->setFont(font_4_2);
    //ui->DeviceType->setFont(font_2_1);

    ui->readLatchRSSI->setFont(font_3);
    ui->MonitorStart->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->console->setFont(font_5);
    ui->RSSI_ANT1->setFont(font_4_2);
    ui->RSSI_ANT2->setFont(font_4_2);
    ui->AFC->setFont(font_4_2);
    ui->MsgCounter->setFont(font_5);
    ui->YesAnswer->setFont(font_5);
    ui->NoAnswer->setFont(font_5);
    ui->AValue->setFont(font_5);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    this->Set_resizing_going(0);
}

void RSSIMonitor_Form::on_MonitorStart_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);

    emit StartRSSIMonitor();
}

void RSSIMonitor_Form::isOPEND(){
    ui->Stop->setEnabled(false);
    //ui->Connect->setEnabled(true);
    ui->Reset->setEnabled(true);
    //ui->Update->setEnabled(true);
    //ui->InterfaceWidget->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(true);
    ui->btnSettings->setEnabled(true);
}

void RSSIMonitor_Form::SetRSSILvlToUI(int new_value){
    if (new_value < -1300){new_value = -1300;}
    if (new_value > 0){new_value = 0;}
    if ((new_value > -1300)&&(new_value <= 0)){
        double r = (double)(new_value);
        r/=10;
        ui->RSSI_Lvl_1->setValue(r);
        ui->RSSI_Lvl_2->setValue(r);
    }
}
void RSSIMonitor_Form::SetRSSIANT1ToUI(int new_value){
    if (new_value < -1300){new_value = -1300;}
    if (new_value > 0){ui->RSSI_ANT1->setText("NAN");}
    if ((new_value > -1300)&&(new_value <= 0)){
        double r = (double)(new_value);
        r/=10;
        ui->RSSI_ANT1->setText(QString("%1").arg(r));
        //ui->RSSI_ANT1->setText(QString::number(new_value));
    }
}
void RSSIMonitor_Form::SetRSSIANT2ToUI(int new_value){
    if (new_value < -1300){new_value = -1300;}
    if (new_value > 0){ui->RSSI_ANT2->setText("NAN");}
    if ((new_value > -1300)&&(new_value <= 0)){
        double r = (double)(new_value);
        r/=10;
        ui->RSSI_ANT2->setText(QString("%1").arg(r));
        //ui->RSSI_ANT2->setText(QString::number(new_value));
    }
}
void RSSIMonitor_Form::SetAFCToUI(int new_value){
    ui->AFC->setText(QString::number(new_value));
}
void RSSIMonitor_Form::SetMsgCounterToUI(int new_value){
    ui->MsgCounter->setText(QString::number(new_value));
}
void RSSIMonitor_Form::SetYesAnswerToUI(int new_value){
    ui->YesAnswer->setText(QString::number(new_value));
}
void RSSIMonitor_Form::SetNoAnswerToUI(int new_value){
    ui->NoAnswer->setText(QString::number(new_value));
}
void RSSIMonitor_Form::SetAValueUI(int new_value){
    ui->AValue->setText(QString::number(new_value));
}
void RSSIMonitor_Form::on_readLatchRSSI_clicked(){
    emit Get_Console(ui->console);
    ui->InterfaceWidget->setEnabled(false);
    ui->LatchRSSIWidget->setEnabled(false);
    ui->MonitorWidget->setEnabled(false);
    ui->Stop->setEnabled(true);
    ui->Reset->setEnabled(false);
    ui->Next->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);

    if (ui->Interface->currentIndex() == COM_USO_INTERFACE){
        emit SendSerialNumber(ui->SN->text(), false);
    }
    else if (ui->Interface->currentIndex() == PLC_RF_INTERFACE){
        emit SendSerialNumber(ui->SN->text(), true);
    }
    emit SendModuleType(ui->ModuleType->currentIndex());
    emit SendInterface(ui->Interface->currentIndex());
    emit SendReadLatchRSSI_AFC();
}
void RSSIMonitor_Form::isLatchRSSI_AFC(signed short RSSI,signed short ANT1_RSSI,signed short ANT2_RSSI,double AFC)
{
    ui->InterfaceWidget->setEnabled(true);
    ui->LatchRSSIWidget->setEnabled(true);
    ui->MonitorWidget->setEnabled(true);
    ui->Stop->setEnabled(false);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(true);
    ui->btnSettings->setEnabled(true);

    SetRSSILvlToUI(RSSI);
    SetRSSIANT1ToUI(ANT1_RSSI);
    SetRSSIANT2ToUI(ANT2_RSSI);
    SetAFCToUI(AFC);
}

void RSSIMonitor_Form::on_Interface_currentIndexChanged(int index){
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    if (this->Get_resizing_going() == 0){
        switch (index){
            case COM_USO_INTERFACE:{
                    Clear_Form();
                    ui->SN->setEnabled(false);
                    ui->ModuleType->setEnabled(true);
                    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
                    settings.sync();
                    emit SendInterface((uchar)(index));
                    emit SendSerialNumber(ui->SN->text(), false);
                break;
            }
            case PLC_RF_INTERFACE:{
                    Clear_Form();
                    ui->SN->setEnabled(true);
                    ui->ModuleType->setEnabled(false);
                    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
                    settings.sync();
                    emit SendInterface((uchar)(index));
                    emit SendSerialNumber(ui->SN->text(), true);
                break;
            }
        }
    }
}

void RSSIMonitor_Form::on_ModuleType_currentIndexChanged(int index)
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    if (this->Get_resizing_going() == 0){
        switch (index){
            case ADDITIONAL_MODULE_TYPE:{
                    Clear_Form();
                    settings.setValue(CONNECTION_SETTINGS_MODULE_TYPE, ui->ModuleType->currentIndex());
                    settings.sync();
                    emit SendModuleType((uchar)(index));
                break;
            }
            case MAIN_MODULE_TYPE:{
                    Clear_Form();
                    settings.setValue(CONNECTION_SETTINGS_MODULE_TYPE, ui->ModuleType->currentIndex());
                    settings.sync();
                    emit SendModuleType((uchar)(index));
                break;
            }
        }
    }
}

void RSSIMonitor_Form::Clear_Form(void){
    emit ClearAllData();
    SetRSSILvlToUI(0);
    ui->RSSI_ANT1->setText("NAN");
    ui->RSSI_ANT2->setText("NAN");
    ui->AFC->setText("NAN");
    SetMsgCounterToUI(0);
    SetYesAnswerToUI(0);
    SetNoAnswerToUI(0);
    SetAValueUI(0);
}
