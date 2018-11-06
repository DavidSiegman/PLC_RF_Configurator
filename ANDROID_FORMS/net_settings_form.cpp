#include "net_settings_form.h"
#include "ui_net_settings_form.h"

Net_Settings_Form::Net_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Net_Settings_Form)
{
    ui->setupUi(this);
}

Net_Settings_Form::~Net_Settings_Form()
{
    delete ui;
}
