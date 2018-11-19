#include "si4463_settings_form.h"
#include "ui_si4463_settings_form.h"

SI4463_Settings_Form::SI4463_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI4463_Settings_Form)
{
    ui->setupUi(this);

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

SI4463_Settings_Form::~SI4463_Settings_Form()
{
    delete ui;
}

void SI4463_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();
}

void SI4463_Settings_Form::on_Back_clicked()
{
    emit Cancel(this->geometry());
}

void SI4463_Settings_Form::on_Next_clicked()
{
    emit Next(this->geometry());
}

void SI4463_Settings_Form::on_btnSettings_clicked()
{
    emit Settings(this);
}

void SI4463_Settings_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}

void SI4463_Settings_Form::Set_Geometry(QRect new_value)
{
    this->setGeometry(new_value);
}

void SI4463_Settings_Form::on_Stop_clicked()
{
    emit Stop_Send_Data();
}

void SI4463_Settings_Form::isStopped()
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

void SI4463_Settings_Form::on_Reset_clicked()
{
    emit Get_Console(ui->console);

    ui->Stop->setEnabled(true);
    ui->SettingsWidget->setEnabled(false);
    ui->Reset->setEnabled(false);
    ui->Back->setEnabled(false);
    ui->btnSettings->setEnabled(false);
    ui->Next->setEnabled(false);

    emit Send_RF_Reset();
}

void SI4463_Settings_Form::isRF_Reset()
{
    ui->Stop->setEnabled(false);
    ui->SettingsWidget->setEnabled(true);
    ui->Reset->setEnabled(true);
    ui->Back->setEnabled(true);
    ui->btnSettings->setEnabled(true);
    ui->Next->setEnabled(true);
}

