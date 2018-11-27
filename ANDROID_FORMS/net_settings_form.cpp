#include "net_settings_form.h"
#include "connections_form.h"
#include "ui_net_settings_form.h"
#include "STYLE/style.h"

Net_Settings_Form::Net_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Net_Settings_Form)
{
    ui->setupUi(this);
    this->setWindowTitle(APPLICATION_NAME);

    this->setStyleSheet(Main_Widget_Style);
    ui->label_1->setStyleSheet(Titel_Widget_Style);
    ui->scrollAreaWidgetContents->setStyleSheet(Work_Area_Style + Basic_Text_Style);

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

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

Net_Settings_Form::~Net_Settings_Form()
{
    delete ui;
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
    QFont font_2 = ui->label_2->font();     font_2.setPixelSize(text_size_4);
    QFont font_3 = ui->Write->font();       font_3.setPixelSize(text_size_3);
    QFont font_4 = ui->label_3->font();     font_4.setPixelSize(text_size_4);
    QFont font_5 = ui->console->font();     font_5.setPixelSize(text_size_5);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);
    ui->label_3->setFont(font_4);
    ui->label_4->setFont(font_4);

    ui->Switch->setFont(font_2);

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

void Net_Settings_Form::on_Back_clicked()
{
    emit Cancel(this->geometry());
}

void Net_Settings_Form::on_Next_clicked()
{
    emit Next(this->geometry());
}

void Net_Settings_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
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
    ui->SwitchLVL->setText(QString::number(new_value));
}
void Net_Settings_Form::SetSwitchTimeoutToUI(uint new_value)
{
    ui->SwitchTM->setText(QString::number(new_value));
}
