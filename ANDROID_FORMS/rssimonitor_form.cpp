#include "rssimonitor_form.h"
#include "ui_rssimonitor_form.h"

RSSIMonitor_Form::RSSIMonitor_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RSSIMonitor_Form)
{
    ui->setupUi(this);
}

RSSIMonitor_Form::~RSSIMonitor_Form()
{
    delete ui;
}
