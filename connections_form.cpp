#include "connections_form.h"
#include "ui_connections_form.h"
#include <QDesktopWidget>
#include <QApplication>

Connections_Form::Connections_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connections_Form)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    this->setLayout(ui->Connection_Form_Layout);

    newTCP                              = new TCP();

    connect(ui->TCPConnect,    SIGNAL(clicked()),newTCP, SLOT(TCP_Connect()));
}

Connections_Form::~Connections_Form()
{
    delete ui;
}

void Connections_Form::on_TCPConnect_clicked()
{
    if(ui->TCPConnect->text() == "Подключить")
    {
        newTCP->TCP_SetIP(ui->IPInput->text());
        newTCP->TCP_SetPORT(ui->PORTInput->text().toInt());
        newTCP->TCP_Connect();
        ui->TCPConnect->setText("Отключить");
    }
    else
    {
        newTCP->TCP_Disconnect();
        ui->TCPConnect->setText("Подключить");
    }
}
