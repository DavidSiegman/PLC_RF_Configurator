#include "plc_settings_form.h"
#include "ui_plc_settings_form.h"

PLC_Settings_Form::PLC_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLC_Settings_Form)
{
    ui->setupUi(this);
}

PLC_Settings_Form::~PLC_Settings_Form()
{
    delete ui;
}
