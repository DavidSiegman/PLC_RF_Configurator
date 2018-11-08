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
