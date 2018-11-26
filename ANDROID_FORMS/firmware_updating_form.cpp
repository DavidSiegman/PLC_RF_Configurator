#include "firmware_updating_form.h"
#include "connections_form.h"
#include "ui_firmware_updating_form.h"

Firmware_Updating_Form::Firmware_Updating_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Firmware_Updating_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

    ui->OpenBin->setStyleSheet(Basic_Buttons_Style);
    ui->UpdateStart->setStyleSheet(Basic_Buttons_Style);
    ui->Stop->setStyleSheet(Basic_Buttons_Style);
    ui->Clear->setStyleSheet(Basic_Buttons_Style);
    ui->ClearConsole->setStyleSheet(Basic_Buttons_Style);

    ui->Back->setStyleSheet(Buttons_Style);
    ui->btnSettings->setStyleSheet(Buttons_Style);
    ui->Next->setStyleSheet(Buttons_Style);

    ui->PatchBin->setStyleSheet(Work_Area_Style + Text_Green);

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


void Firmware_Updating_Form::resizeEvent(QResizeEvent *event)
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

    QFont font_1 = ui->label_1->font();    font_1.setPixelSize(text_size_1);
    QFont font_2 = ui->label_2->font();    font_2.setPixelSize(text_size_2);
    QFont font_3 = ui->OpenBin->font();    font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->label_3->font();    font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();    font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);
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

    QScrollBar *VerticalScrollBar = new QScrollBar(); VerticalScrollBar->setStyleSheet(ScrollBar_Style);

    ui->scrollArea->setVerticalScrollBar(VerticalScrollBar);

    ui->Back->setIconSize(icons_size); ui->Back->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->Next->setIconSize(icons_size); ui->Next->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
    ui->btnSettings->setIconSize(icons_size); ui->btnSettings->setMinimumHeight(icons_size.height() + icons_size.height()*30/100);
}

Firmware_Updating_Form::~Firmware_Updating_Form()
{
    delete ui;
}

void Firmware_Updating_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void Firmware_Updating_Form::Set_Geometry(QRect new_value)
{
    this->setGeometry(new_value);
}


void Firmware_Updating_Form::isSTOPPED(void)
{
    SetProgress(0);
    ui->Stop->setEnabled(false);
    ui->OpenBin->setEnabled(true);
    ui->UpdateStart->setEnabled(true);
    ui->Clear->setEnabled(false);
    ui->Back->setEnabled(true);
    ui->Next->setEnabled(false);
    ui->btnSettings->setEnabled(true);
}

void Firmware_Updating_Form::on_Back_clicked()
{
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void Firmware_Updating_Form::on_btnSettings_clicked()
{
    emit Settings(this);
}

void Firmware_Updating_Form::on_Stop_clicked()
{
    emit STOP_MONITOR();
    emit STOP_SEND_DATA();
}

void Firmware_Updating_Form::on_OpenBin_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open File", "", "*.bin");

    QString s = "";
    for(uint i = (str.length()); i > 0; i--)
    {
        if (str.at(i-1) != '/')
        {
            s.push_front(str.at(i-1));
        }
        else
        {
            break;
        }
    }

    ui->PatchBin->setText(s);
    //newUPDATE->setPATCH(str);
}
