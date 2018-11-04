#include "settings_form.h"
#include "ui_settings_form.h"

Settings_Form::Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_Form)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
}

Settings_Form::~Settings_Form()
{
    delete ui;
}

void Settings_Form::on_Cancel_clicked()
{
    emit Cancel();
    this->deleteLater();
}
