#include "open_connection_form.h"
#include "ui_open_connection_form.h"
#include "OTHER_FUNCTIONS/barr_to_string.h"

Open_Connection_Form::Open_Connection_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Open_Connection_Form)
{
    ui->setupUi(this);

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

void Open_Connection_Form::resizeEvent(QResizeEvent *event)
{
    QScreen *Screen = QApplication::primaryScreen();

    int DotsPerInch = Screen->logicalDotsPerInch();

    QSize this_size      = this->size();

    float w_to_dpi_index = float(this_size.width())/DotsPerInch;

    float size_1         = w_to_dpi_index*6;  if (size_1     > 38) {size_1     = 38;}
    float size_2         = w_to_dpi_index*4;  if (size_2     > 24) {size_2     = 24;}
    float size_3         = w_to_dpi_index*3;  if (size_3     > 16) {size_3     = 16;}

    float btn_size       = w_to_dpi_index*10; if (btn_size   > 40) {btn_size   = 40;}
    float label_size     = w_to_dpi_index*6;  if (label_size > 38) {label_size = 38;}

    QSize icon_size;     icon_size.setHeight(btn_size); icon_size.setWidth(btn_size);

    QFont font_1, font_2, font_3;
    font_1.setPointSize(size_1);
    font_2.setPointSize(size_2);
    font_3.setPointSize(size_3);

    ui->boot_CRC->setFont(font_3);
    ui->boot_CRC->setMinimumHeight(label_size);
    ui->boot_Size->setFont(font_3);
    ui->boot_Size->setMinimumHeight(label_size);
    ui->boot_v->setFont(font_3);
    ui->boot_v->setMinimumHeight(label_size);
    ui->DeviceType->setFont(font_3);
    ui->DeviceType->setMinimumHeight(label_size);
    ui->fw_CRC->setFont(font_3);
    ui->fw_CRC->setMinimumHeight(label_size);
    ui->fw_Size->setFont(font_3);
    ui->fw_Size->setMinimumHeight(label_size);
    ui->fw_v->setFont(font_3);
    ui->fw_v->setMinimumHeight(label_size);
    ui->Interface->setFont(font_3);
    ui->Interface->setMinimumHeight(label_size);
    ui->SN->setFont(font_3);
    ui->SN->setMinimumHeight(label_size);

    ui->Back->setFont(font_3);
    ui->Back->setMinimumHeight(btn_size);
    ui->Back->setIconSize(icon_size);
    ui->ClearConsole->setFont(font_3);
    ui->ClearConsole->setMinimumHeight(btn_size);
    ui->Connect->setFont(font_3);
    ui->Connect->setMinimumHeight(btn_size);
    ui->Next->setFont(font_3);
    ui->Next->setMinimumHeight(btn_size);
    ui->Next->setIconSize(icon_size);

    ui->label_9->setFont(font_3);
    ui->label_9->setMinimumHeight(label_size);

    float label_9_width = ui->label_9->geometry().width();

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_3);
    ui->label_2->setMinimumHeight(label_size);
    ui->label_3->setFont(font_3);
    ui->label_3->setMinimumHeight(label_size);
    ui->label_4->setFont(font_3);
    ui->label_4->setMinimumHeight(label_size);
    ui->label_5->setFont(font_3);
    ui->label_5->setMinimumHeight(label_size);
    ui->label_6->setFont(font_3);
    ui->label_6->setMinimumHeight(label_size);
    ui->label_6->setMinimumWidth(label_9_width);
    ui->label_6->setMaximumWidth(label_9_width);
    ui->label_7->setFont(font_3);
    ui->label_7->setMinimumHeight(label_size);
    ui->label_7->setMinimumWidth(label_9_width);
    ui->label_7->setMaximumWidth(label_9_width);
    ui->label_8->setFont(font_3);
    ui->label_8->setMinimumHeight(label_size);
    ui->label_8->setMinimumWidth(label_9_width);
    ui->label_8->setMaximumWidth(label_9_width);
    ui->label_10->setFont(font_3);
    ui->label_10->setMinimumHeight(label_size);
    ui->label_10->setMinimumWidth(label_9_width);
    ui->label_10->setMaximumWidth(label_9_width);
    ui->label_11->setFont(font_3);
    ui->label_11->setMinimumHeight(label_size);
    ui->label_11->setMinimumWidth(label_9_width);
    ui->label_11->setMaximumWidth(label_9_width);
}

Open_Connection_Form::~Open_Connection_Form()
{
    delete ui;
}

void Open_Connection_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void Open_Connection_Form::isOPEND()
{

}

void Open_Connection_Form::SetCurrentFitmwareToUI(uchar new_value)
{
    QString String2_2(
                         "QWidget{"
                         "background-color: rgb(186, 229, 202);"
                         "}"
                     );
    QString String2_3(
                         "QWidget{"
                         "background: rgba(100,50,00,0);"
                         "}"
                     );

    // Бутлоадер
    if (new_value == 0)
    {
        this->ui->boot_v->setStyleSheet(String2_2);
        this->ui->fw_v->setStyleSheet(String2_3);
    }
    // Обновляемая
    else if (new_value == 1)
    {
        this->ui->boot_v->setStyleSheet(String2_3);
        this->ui->fw_v->setStyleSheet(String2_2);
    }

}
void Open_Connection_Form::SetBootloaderVersionToUI(QString new_value)
{
    this->ui->boot_v->setText(new_value);
}
void Open_Connection_Form::SetBootloaderSizeToUI(uint new_value)
{
    this->ui->boot_Size->setText(QString::number(new_value));
}
void Open_Connection_Form::SetBootloaderCRCToUI(QByteArray new_value)
{
    this->ui->boot_CRC->setText(QByteAray_To_QString(new_value).toUpper());
}
void Open_Connection_Form::SetUpgradableVersionToUI(QString new_value)
{
    this->ui->fw_v->setText(new_value);
}
void Open_Connection_Form::SetUpgradableSizeToUI(uint new_value)
{
    this->ui->fw_Size->setText(QString::number(new_value));
}
void Open_Connection_Form::SetUpgradableCRCToUI(QByteArray new_value)
{
    this->ui->fw_CRC->setText(QByteAray_To_QString(new_value).toUpper());
}



void Open_Connection_Form::on_Back_clicked()
{
    emit Cancel();
    this->deleteLater();
}

void Open_Connection_Form::on_Interface_currentIndexChanged(int index)
{
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

void Open_Connection_Form::on_Connect_clicked()
{
    emit Get_Console(ui->console);

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
