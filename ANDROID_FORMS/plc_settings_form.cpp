#include "plc_settings_form.h"
#include "ui_plc_settings_form.h"

PLC_Settings_Form::PLC_Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLC_Settings_Form)
{
    ui->setupUi(this);

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

PLC_Settings_Form::~PLC_Settings_Form()
{
    delete ui;
}

void PLC_Settings_Form::resizeEvent(QResizeEvent *event)
{
    emit isCreated();
}

void PLC_Settings_Form::on_Back_clicked()
{
    emit Get_Console(NULL);
    emit Cancel();
}

void PLC_Settings_Form::on_Next_clicked()
{
    emit Get_Console(NULL);
    emit Next();
}

void PLC_Settings_Form::SetProgress(uint progress)
{
    ui->progress->setValue(progress);
}
