#include "net_settings_form.h"
#include "ui_net_settings_form.h"

Net_Settings_Form::Net_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Net_Settings_Form)
{
    ui->setupUi(this);

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

Net_Settings_Form::~Net_Settings_Form()
{
    delete ui;
}

void Net_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();
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
        ui->SWITCH->setChecked(false);
    }
    else if (new_value == 1)
    {
        ui->SWITCH->setChecked(true);
    }
}
void Net_Settings_Form::SetSwitchLevelToUI(uint new_value)
{
    ui->SWITCHLVL->setText(QString::number(new_value));
}
void Net_Settings_Form::SetSwitchTimeoutToUI(uint new_value)
{
    ui->SWITCHTM->setText(QString::number(new_value));
}
