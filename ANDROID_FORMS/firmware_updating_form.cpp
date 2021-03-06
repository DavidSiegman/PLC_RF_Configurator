#include "firmware_updating_form.h"
#include "connections_form.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"
#include "CRC/crc32_class.h"

Firmware_Updating_Form::Firmware_Updating_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::Firmware_Updating_Form;
    ui->setupUi(this);
    this->setWindowTitle(WINDOW_TITLE);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style + ToolTip_Style);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->console->verticalScrollBar()->setStyleSheet(ScrollBar_Style);
    ui->DownPanel_Widget->setStyleSheet(DownPanel_Widget_Style);

    ui->OpenBin->setStyleSheet(Basic_PushButtons_Style);
    ui->UpdateStart->setStyleSheet(Basic_PushButtons_Style);
    ui->Stop->setStyleSheet(Basic_PushButtons_Style);
    ui->Clear->setStyleSheet(Basic_PushButtons_Style);
    ui->ClearConsole->setStyleSheet(Basic_PushButtons_Style);

    ui->Back->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->btnSettings->setStyleSheet(PushButtons_Style+ToolTip_Style);
    ui->Next->setStyleSheet(PushButtons_Style+ToolTip_Style);

    ui->PatchBin->setStyleSheet(Work_Area_Style + Text_Green);

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

    ui->new_v->setText("-");
    ui->new_Size->setText("-");
    ui->new_CRC->setText("-");
}
void Firmware_Updating_Form::on_ClearConsole_clicked(){
    WriteLogToFile(ui->console);
    ui->console->clear();
}
Firmware_Updating_Form::~Firmware_Updating_Form(){
    emit Get_Console(NULL);
    delete ui;
}
void Firmware_Updating_Form::on_Back_clicked(){
    WriteLogToFile(ui->console);
    this->Back_ClickHandler();
    emit Cancel(this->geometry());
}
void Firmware_Updating_Form::ForceClose(void){
    WriteLogToFile(ui->console);
    this->ForceCloseHandler();
}
void Firmware_Updating_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void Firmware_Updating_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void Firmware_Updating_Form::on_Stop_clicked(){
    emit Stop_Send_Data();
}
void Firmware_Updating_Form::isStopped(){
    SetProgress(0);
    ui->Stop->setEnabled(false);
    ui->OpenBin->setEnabled(true);
    if ((ui->new_v->text().compare("-") != 0)&&(ui->new_v->text().length() > 0)){
        ui->UpdateStart->setEnabled(true);
    }
    if ((ui->curr_v->text().compare("-") != 0)&&(ui->curr_v->text().length() > 0)){
        ui->Clear->setEnabled(true);
    }
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(false);
    ui->btnSettings->setEnabled(true);
}

void Firmware_Updating_Form::resizeEvent(QResizeEvent *event){
    emit isCreated();

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

    QFont font_1 = ui->label_1->font();    font_1.setPixelSize(text_size_1);
    //QFont font_2 = ui->label_2->font();    font_2.setPixelSize(text_size_4);
    QFont font_3 = ui->OpenBin->font();    font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->label_3->font();    font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();    font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    //ui->label_2->setFont(font_2);
    ui->label_3->setFont(font_4);
    ui->label_4->setFont(font_4);

    ui->PatchBin->setFont(font_3);

    ui->OpenBin->setFont(font_3);
    ui->UpdateStart->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Clear->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->console->setFont(font_5);
    ui->new_v->setFont(font_5);
    ui->new_Size->setFont(font_5);
    ui->new_CRC->setFont(font_5);
    ui->curr_v->setFont(font_5);
    ui->curr_Size->setFont(font_5);
    ui->curr_CRC->setFont(font_5);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->label_1->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);

    emit Get_Console(ui->console);
}

void Firmware_Updating_Form::Set_In_Firmware_Information(FirmwareInformationClass *FirmwareInformation){
    In_Firmware_Information = FirmwareInformation;

    SetUpgradableVersionToUI(In_Firmware_Information->getString_Upgradable_Version());
    SetUpgradableSizeToUI(In_Firmware_Information->getUpgradable_Size());
    SetUpgradableCRCToUI(In_Firmware_Information->getUpgradable_CRC32());
}
void Firmware_Updating_Form::on_OpenBin_clicked(){

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    QRegExp RegVER; RegVER      = QRegExp("ver");
    QFile *file; file = NULL;
    uint pos = 0;
    uint nSIZE = 0;
    QByteArray Data; Data.clear();
    QByteArray nCRC32; nCRC32.clear();
    QString VERSION = "";
    crc32_class CRC32;

    QString new_path;
    QString old_path = settings.value(FIRMWARE_BIN_PATH).toString();

    QString patch = QFileDialog::getOpenFileName(0, "Open File", old_path, "*.bin");

    QString s = "";
    for(uint i = (patch.length()); i > 0; i--){
        if (patch.at(i-1) != '/'){
            s.push_front(patch.at(i-1));
        }
        else{
            new_path = patch;
            new_path.remove(i, patch.length()-i);
            settings.setValue(FIRMWARE_BIN_PATH, new_path);
            settings.sync();
            break;
        }
    }

    ui->PatchBin->setText(s);

    if (RegVER.indexIn(patch,0) != -1){
        pos = RegVER.indexIn(patch,pos) + 3;
        VERSION.clear();
        VERSION.append(patch.data() + pos,4);
        ui->new_v->setText(VERSION);
        ui->UpdateStart->setEnabled(true);

        if (patch.length() != 0){
            file = new QFile(patch);
            if(file->exists()){
                if (file->open(QIODevice::ReadOnly)){
                   Data = file->readAll();
                   file->close();

                   nSIZE = Data.length();

                   uint crc = CRC32.crc32((unsigned long*)(Data.data()), Data.length());
                   nCRC32.append((char)(crc >> 24));
                   nCRC32.append((char)(crc >> 16));
                   nCRC32.append((char)(crc >> 8));
                   nCRC32.append((char)(crc >> 0));

                   ui->new_CRC->setText(QByteAray_To_QString(nCRC32).toUpper());
                   ui->new_Size->setText(QString::number(nSIZE));

                   emit Get_FirmwareData(VERSION, Data);

                }
            }
        }
    }
    else{
        ui->new_v->setText("-");
        ui->new_Size->setText("-");
        ui->new_CRC->setText("-");
        ui->UpdateStart->setEnabled(false);
    }
}
void Firmware_Updating_Form::SetUpgradableVersionToUI(QString new_value){
    this->ui->curr_v->setText("-");
    if ((new_value.compare("0.00") != 0)&&(new_value.length() > 0)){
        this->ui->curr_v->setText(new_value);
        this->ui->Clear->setEnabled(true);
    }
}
void Firmware_Updating_Form::SetUpgradableSizeToUI(uint new_value){
    this->ui->curr_Size->setText("-");
    if (new_value > 0){
        this->ui->curr_Size->setText(QString::number(new_value));
    }
}
void Firmware_Updating_Form::SetUpgradableCRCToUI(QByteArray new_value){
    this->ui->curr_CRC->setText("-");
    if (new_value.length() == 4){
        if ((new_value.at(0) == 0) && (new_value.at(1) == 0) &&
            (new_value.at(2) == 0) && (new_value.at(3) == 0)){
            this->ui->curr_CRC->setText("-");
        }
        else{
            this->ui->curr_CRC->setText(QByteAray_To_QString(new_value).toUpper());
        }

    }
}
void Firmware_Updating_Form::on_Clear_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->OpenBin->setEnabled(false);
    ui->UpdateStart->setEnabled(false);
    ui->Clear->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);

    emit StartSendingProcess(DELETE_HANDLING,CONFIG_SEND_CONTROL);
}
void Firmware_Updating_Form::isDeleted(void){
    ui->Stop->setEnabled(false);
    ui->OpenBin->setEnabled(true);
    ui->UpdateStart->setEnabled(false);
    if ((ui->new_v->text().compare("-") != 0)&&(ui->new_v->text().length() > 0)){
        ui->UpdateStart->setEnabled(true);
    }
    ui->Clear->setEnabled(false);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
}
void Firmware_Updating_Form::on_UpdateStart_clicked(){
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->OpenBin->setEnabled(false);
    ui->UpdateStart->setEnabled(false);
    ui->Clear->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);

    emit StartSendingProcess(UPDATE_HANDLING,CONFIG_SEND_CONTROL);
}
void Firmware_Updating_Form::isUpdated(void){
    ui->Stop->setEnabled(false);
    ui->OpenBin->setEnabled(true);
    ui->UpdateStart->setEnabled(true);
    ui->Clear->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
}
