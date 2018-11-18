#include "si4463_settings_form.h"
#include "ui_si4463_settings_form.h"

SI4463_Settings_Form::SI4463_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI4463_Settings_Form)
{
    ui->setupUi(this);
}

SI4463_Settings_Form::~SI4463_Settings_Form()
{
    delete ui;
}
