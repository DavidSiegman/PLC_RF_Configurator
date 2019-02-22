#include "rs_settings_form.h"
#include "ui_rs_settings_form.h"

RS_Settings_Form::RS_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RS_Settings_Form)
{
    ui->setupUi(this);
}

RS_Settings_Form::~RS_Settings_Form()
{
    //emit Get_Console(NULL);
    delete ui;
}
