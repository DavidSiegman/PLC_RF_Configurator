#include "plc_settings_form.h"

PLC_Settings_Form::PLC_Settings_Form(QWidget *parent) :
    myFormAbstractClass(parent)
{
    ui = new Ui::PLC_Settings_Form;
    ui->setupUi(this);

    connect(ui->ClearConsole,  SIGNAL(clicked(bool)),         ui->console, SLOT(clear()));
}

PLC_Settings_Form::~PLC_Settings_Form(){
    delete ui;
}
void PLC_Settings_Form::on_Back_clicked(){
    this->Back_ClickHandler();
}
void PLC_Settings_Form::on_Next_clicked(){
    this->Next_ClickHandler();
}
void PLC_Settings_Form::ForceClose(void){
    this->ForceCloseHandler();
}
void PLC_Settings_Form::on_btnSettings_clicked(){
    emit Settings(this);
}
void PLC_Settings_Form::SetProgress(uint progress){
    ui->progress->setValue(progress);
}
void PLC_Settings_Form::resizeEvent(QResizeEvent *event){
    emit isCreated();
}
void PLC_Settings_Form::on_Stop_clicked(){
    this->Stop_ClickHandler();
}
void PLC_Settings_Form::on_Reset_clicked(){
    emit Get_Console(ui->console);

    this->Reset_ClickHandler();
}
void PLC_Settings_Form::on_Write_clicked(){

}
