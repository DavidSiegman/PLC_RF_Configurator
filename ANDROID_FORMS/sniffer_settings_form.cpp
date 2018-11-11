#include "sniffer_settings_form.h"
#include "ui_sniffer_settings_form.h"

Sniffer_Settings_Form::Sniffer_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sniffer_Settings_Form)
{
    ui->setupUi(this);
}

Sniffer_Settings_Form::~Sniffer_Settings_Form()
{
    delete ui;
}

void Sniffer_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();
}

void Sniffer_Settings_Form::on_Back_clicked()
{
    emit Cancel();
}

void Sniffer_Settings_Form::on_Next_clicked()
{
    emit Next();
}

void Sniffer_Settings_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}
