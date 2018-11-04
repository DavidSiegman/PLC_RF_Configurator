#include "open_connection_form.h"
#include "ui_open_connection_form.h"

Open_Connection_Form::Open_Connection_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Open_Connection_Form)
{
    ui->setupUi(this);
}

Open_Connection_Form::~Open_Connection_Form()
{
    delete ui;
}
