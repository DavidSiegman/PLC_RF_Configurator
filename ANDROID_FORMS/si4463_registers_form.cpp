#include "si4463_registers_form.h"
#include "ui_si4463_registers_form.h"

SI4463_Registers_Form::SI4463_Registers_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SI4463_Registers_Form)
{
    ui->setupUi(this);
}

SI4463_Registers_Form::~SI4463_Registers_Form()
{
    delete ui;
}
