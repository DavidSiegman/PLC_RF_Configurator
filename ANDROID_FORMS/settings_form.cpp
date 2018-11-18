#include "settings_form.h"
#include "ui_settings_form.h"

Settings_Form::Settings_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings_Form)
{
    ui->setupUi(this);

    SysInfo              = new QSysInfo;
    QString product_name = SysInfo->prettyProductName();

    RegSystemName        = QRegExp("[A-Za-z]+");
    RegSystemName.indexIn(product_name,0);
    if (RegSystemName.cap(0).compare("Android") == 0)
    {
        setWindowState(Qt::WindowMaximized);
    }
    else if (RegSystemName.cap(0).compare("Windows") == 0)
    {
        this->setWindowModality(Qt::WindowModal);
        this->setFixedSize (340,560);
    }
}

Settings_Form::~Settings_Form()
{
    delete ui;
}

void Settings_Form::on_Cancel_clicked()
{
    emit Get_Geometry(this->geometry());
    emit Cancel();
    this->deleteLater();
}

void Settings_Form::on_Apply_clicked()
{
    emit GetRepeatNumber(ui->Repeat->text().toInt());
    emit GetRepeatTimeout(ui->Periode->text().toInt());
    emit Cancel();
    this->deleteLater();
}
