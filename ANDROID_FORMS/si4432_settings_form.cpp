#include "si4432_settings_form.h"
#include "ui_si4432_settings_form.h"

SI4432_Settings_Form::SI4432_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI4432_Settings_Form)
{
    ui->setupUi(this);
}

SI4432_Settings_Form::~SI4432_Settings_Form()
{
    delete ui;
}
