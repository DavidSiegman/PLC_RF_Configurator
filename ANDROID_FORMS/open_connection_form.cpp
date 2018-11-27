#include "open_connection_form.h"
#include "connections_form.h"
#include "ui_open_connection_form.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

Open_Connection_Form::Open_Connection_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Open_Connection_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    ui->SN->setText(settings.value(CONNECTION_SETTINGS_SN).toString());

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->Update->setStyleSheet(Basic_Buttons_Style);
    ui->Connect->setStyleSheet(Basic_Buttons_Style);
    ui->Stop->setStyleSheet(Basic_Buttons_Style);
    ui->Reset->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);

    ui->Interface->setStyleSheet(Background_White);
    ui->SN->setStyleSheet(Background_White);

    ui->DeviceType->setStyleSheet(Work_Area_Style + Text_Green);

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

void Open_Connection_Form::resizeEvent(QResizeEvent *event)
{
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
    QFont font_3   = ui->Connect->font();  font_3.setPixelSize(text_size_3);
    QFont font_4_1 = ui->label_2->font();  font_4_1.setPixelSize(text_size_4);
    QFont font_4_2 = ui->label_6->font();  font_4_2.setPixelSize(text_size_4);
    QFont font_5   = ui->console->font();  font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_4_1);
    ui->label_3->setFont(font_4_1);
    ui->label_4->setFont(font_4_1);
    ui->label_5->setFont(font_4_1);
    ui->label_6->setFont(font_4_2);
    ui->label_7->setFont(font_4_2);

    ui->Interface->setFont(font_4_2);
    ui->Interface->clear();
    ui->Interface->addItem("COM/УСО (Оптопорт)");
    ui->Interface->addItem("PLC/RF");
    ui->Interface->setCurrentIndex(settings.value(CONNECTION_SETTINGS_INTERFACE).toInt());

    ui->SN->setFont(font_4_2);
    ui->DeviceType->setFont(font_2_1);

    ui->Update->setFont(font_3);
    ui->Connect->setFont(font_3);
    ui->Stop->setFont(font_3);
    ui->Reset->setFont(font_3);
    ui->ClearConsole->setFont(font_3);

    ui->console->setFont(font_5);
    ui->boot_v->setFont(font_5);
    ui->boot_Size->setFont(font_5);
    ui->boot_CRC->setFont(font_5);
    ui->fw_v->setFont(font_5);
    ui->fw_Size->setFont(font_5);
    ui->fw_CRC->setFont(font_5);

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

Open_Connection_Form::~Open_Connection_Form()
{
    delete ui;
}

void Open_Connection_Form::Set_In_Firmware_Information(FirmwareInformationClass *FirmwareInformation)
{
    In_Firmware_Information = FirmwareInformation;

    SetDeviceNameToUI(In_Firmware_Information->getDevice_Name());
    SetCurrentFitmwareToUI(In_Firmware_Information->getCurrent_Firmware_Version());
    SetBootloaderVersionToUI(In_Firmware_Information->getString_Bootloader_Version());
    SetBootloaderSizeToUI(In_Firmware_Information->getBootloader_Size());
    SetBootloaderCRCToUI(In_Firmware_Information->getBootloader_CRC32());
    SetUpgradableVersionToUI(In_Firmware_Information->getString_Upgradable_Version());
    SetUpgradableSizeToUI(In_Firmware_Information->getUpgradable_Size());
    SetUpgradableCRCToUI(In_Firmware_Information->getUpgradable_CRC32());

}

void Open_Connection_Form::on_Back_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.sync();
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void Open_Connection_Form::on_Next_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.sync();
    emit Next(this->geometry());
}

void Open_Connection_Form::on_Connect_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.sync();

    Clear_Form();
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->Update->setEnabled(false);
    ui->Connect->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->InterfaceWidget->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->Next->setEnabled(false);
    ui->btnSettings->setEnabled(false);

    if (ui->Interface->currentIndex() == 0)
    {
        emit SendSerialNumber(ui->SN->text(), false);
    }
    else if (ui->Interface->currentIndex() == 1)
    {
        emit SendSerialNumber(ui->SN->text(), true);
    }

    emit AOPEN();
    emit STOP_MONITOR();
}

void Open_Connection_Form::on_btnSettings_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.sync();
    emit Settings(this);
}

void Open_Connection_Form::on_Update_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(CONNECTION_SETTINGS_SN, ui->SN->text());
    settings.setValue(CONNECTION_SETTINGS_INTERFACE, ui->Interface->currentIndex());
    settings.sync();
    emit Updating(this);
}

void Open_Connection_Form::on_Stop_clicked()
{
    emit STOP_MONITOR();
    emit STOP_SEND_DATA();
}

void Open_Connection_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void Open_Connection_Form::isOPEND()
{
    ui->Stop->setEnabled(false);
    ui->Connect->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Update->setEnabled(true);
    ui->InterfaceWidget->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(true);
    ui->btnSettings->setEnabled(true);
}

void Open_Connection_Form::isRESET()
{
    ui->Stop->setEnabled(false);
    ui->Connect->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Update->setEnabled(true);
    ui->InterfaceWidget->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(true);
    ui->btnSettings->setEnabled(true);
}

void Open_Connection_Form::isSTOPPED(void)
{
    SetProgress(0);
    ui->Stop->setEnabled(false);
    ui->Connect->setEnabled(true);
    ui->Reset->setEnabled(false);
    ui->Update->setEnabled(false);
    ui->InterfaceWidget->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(false);
    ui->btnSettings->setEnabled(true);
}

void Open_Connection_Form::Set_Geometry(QRect new_value)
{
    this->setGeometry(new_value);
}

void Open_Connection_Form::SetCurrentFitmwareToUI(uchar new_value)
{
    // Бутлоадер
    if (new_value == 0)
    {
        this->ui->boot_v->setStyleSheet(Background_Green);
        this->ui->fw_v->setStyleSheet(Background_Grey);
    }
    // Обновляемая
    else if (new_value == 1)
    {
        this->ui->boot_v->setStyleSheet(Background_Grey);
        this->ui->fw_v->setStyleSheet(Background_Green);
    }
    else if (new_value == 2)
    {
        this->ui->boot_v->setStyleSheet(Background_Grey);
        this->ui->fw_v->setStyleSheet(Background_Grey);
    }

}
void Open_Connection_Form::SetBootloaderVersionToUI(QString new_value)
{
    this->ui->boot_v->setText("NAN");
    if ((new_value.compare("0.00") != 0)&&(new_value.length() > 0))
    {
        this->ui->boot_v->setText(new_value);
    }
}
void Open_Connection_Form::SetBootloaderSizeToUI(uint new_value)
{
    this->ui->boot_Size->setText("NAN");
    if (new_value > 0)
    {
        this->ui->boot_Size->setText(QString::number(new_value));
    }
}
void Open_Connection_Form::SetBootloaderCRCToUI(QByteArray new_value)
{
    this->ui->boot_CRC->setText("NAN");
    if (new_value.length() == 4)
    {
        if ((new_value.at(0) == 0) && (new_value.at(1) == 0) &&
            (new_value.at(2) == 0) && (new_value.at(3) == 0))
        {
            this->ui->boot_CRC->setText("NAN");
        }
        else
        {
            this->ui->boot_CRC->setText(QByteAray_To_QString(new_value).toUpper());
        }
    }
}
void Open_Connection_Form::SetUpgradableVersionToUI(QString new_value)
{
    this->ui->fw_v->setText("NAN");
    if ((new_value.compare("0.00") != 0)&&(new_value.length() > 0))
    {
        this->ui->fw_v->setText(new_value);
    }
}
void Open_Connection_Form::SetUpgradableSizeToUI(uint new_value)
{
    this->ui->fw_Size->setText("NAN");
    if (new_value > 0)
    {
        this->ui->fw_Size->setText(QString::number(new_value));
    }
}
void Open_Connection_Form::SetUpgradableCRCToUI(QByteArray new_value)
{
    this->ui->fw_CRC->setText("NAN");
    if (new_value.length() == 4)
    {
        if ((new_value.at(0) == 0) && (new_value.at(1) == 0) &&
            (new_value.at(2) == 0) && (new_value.at(3) == 0))
        {
            this->ui->fw_CRC->setText("NAN");
        }
        else
        {
            this->ui->fw_CRC->setText(QByteAray_To_QString(new_value).toUpper());
        }

    }
}

void Open_Connection_Form::SetDeviceNameToUI(QString new_value)
{
   this->ui->DeviceType->setText(new_value);
}

void Open_Connection_Form::on_Interface_currentIndexChanged(int index)
{
    Clear_Form();

    switch (index)
    {
        case 0:
        {
            ui->SN->setEnabled(false);
            emit SendSerialNumber(ui->SN->text(), false);
            break;
        }
        case 1:
        {
            ui->SN->setEnabled(true);
            emit SendSerialNumber(ui->SN->text(), true);
            break;

        }
    }


}

void Open_Connection_Form::Clear_Form(void)
{
    ui->Next->setEnabled(false);
    ui->Reset->setEnabled(false);
    SetProgress(0);

    SetCurrentFitmwareToUI(2);
    SetBootloaderVersionToUI("");
    SetBootloaderSizeToUI(0);
    SetBootloaderCRCToUI(0);
    SetUpgradableVersionToUI("");
    SetUpgradableSizeToUI(0);
    SetUpgradableCRCToUI(0);
    SetDeviceNameToUI("");
}


void Open_Connection_Form::on_Reset_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->Connect->setEnabled(false);
    ui->Update->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Next->setEnabled(false);
    ui->InterfaceWidget->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);

    emit SEND_RF_RESET();
}
