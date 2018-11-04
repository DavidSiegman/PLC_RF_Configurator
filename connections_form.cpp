#include "connections_form.h"
#include "ui_connections_form.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QTouchEvent>
#include "barr_to_string.h"

Connections_Form::Connections_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connections_Form)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    timer_COMBufferClear      = new QTimer();
    timer_ConnectionsPanel    = new QTimer();
    //MODEM                     = new MODEMClass(ui);
    newPort                   = new Port();                                                                   // Создаем Поток обработки портов
    newTCP                    = new TCP();
    oCRC16                    = new CRC16_Class();                                                            // Создаём Объект расчёта CRC
    newParcer                 = new ParceClass();
    SI4463Config              = new SI4463Class();
    //SI4432Config              = new SI4432Class(ui);
    //PLCConfig                 = new PLCClass(ui);
    //newUPDATE                 = new UPDATE(ui);

    DataLogic                 = new DataLogic_Class(oCRC16,timer_COMBufferClear,SI4463Config,SI4432Config,
                                                    PLCConfig,MODEM,newPort,newTCP,newUPDATE,this);           // Создаём Объект обработки сообщений
    //ConnectHandler            = new ConnectHandlerClass(ui, DataLogic, MODEM, newUPDATE);

    connect(newPort,  SIGNAL(COM_Started()),                  this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(newPort,  SIGNAL(COM_Error(QString,uint)),        this, SLOT(Print_Log(QString,uint)));   //Лог ошибок

    connect(newTCP,   SIGNAL(TCP_Error(QString,uint)),        this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    connect(DataLogic,SIGNAL(SendLog(QString,uint)),          this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,SIGNAL(LogForPrint(QString,uint)),      this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,SIGNAL(DataForPrint(QByteArray,uint)),  this, SLOT(Print(QByteArray,uint)));

}

Connections_Form::~Connections_Form()
{
    delete ui;
}

void Connections_Form::on_TCPConnect_clicked()
{
    Set_ActiveConsole(ui->consol);

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

void Connections_Form::on_btnSettings_clicked()
{
    settings_form = new Settings_Form;
    connect(settings_form,SIGNAL(Cancel()),this,SLOT(show()));

    this->hide();
    settings_form->show();
}

void Connections_Form::on_btnHandsEnter_clicked()
{
    hands_enter_form = new Hands_Enter_Form;
    connect(hands_enter_form,SIGNAL(Cancel()),this,SLOT(show()));
    connect(hands_enter_form,SIGNAL(Send_Data(QByteArray,uint)),DataLogic,SLOT(SEND_DATA(QByteArray,uint)));
    connect(hands_enter_form,SIGNAL(Get_Console(QPlainTextEdit*)),this,SLOT(Set_ActiveConsole(QPlainTextEdit*)));

    this->hide();
    hands_enter_form->show();
}

//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void Connections_Form::Print(QByteArray data, uint n)
{
    QString s = "Print data";
    qDebug() << s;

    QByteArray d;
    d.append(data);

    switch (n)
    {
        case COM_TX:
        {
            ActiveConsole->textCursor().insertText("TX >> " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
            break;
        }
        case COM_RX:
        {
            ActiveConsole->textCursor().insertText("RX << " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
            break;
        }
    }
    QString str;str += '\r';
    ActiveConsole->textCursor().insertText(str); // Вывод текста в консоль
    ActiveConsole->moveCursor(QTextCursor::End);//Scroll
}

//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void Connections_Form::Print_Log(QString data, uint n)
{
    ActiveConsole->textCursor().insertText(data); // Вывод текста в консоль
    ActiveConsole->moveCursor(QTextCursor::End);  //Scroll
}

void Connections_Form::Set_ActiveConsole(QPlainTextEdit * new_active_console)
{
    ActiveConsole = new_active_console;
}
