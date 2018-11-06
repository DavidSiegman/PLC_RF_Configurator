#include "connections_form.h"
#include "ui_connections_form.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QTouchEvent>
#include "OTHER_FUNCTIONS/barr_to_string.h"

Connections_Form::Connections_Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connections_Form)
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
        //this->setFixedSize (340,560);
    }

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
    ConnectHandler            = new ConnectHandlerClass(DataLogic, MODEM, newUPDATE);

    connect(newPort,  SIGNAL(COM_Started()),                  this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(newPort,  SIGNAL(COM_Error(QString,uint)),        this, SLOT(Print_Log(QString,uint)));   //Лог ошибок

    connect(newTCP,   SIGNAL(TCP_Error(QString,uint)),        this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    connect(DataLogic,SIGNAL(SendLog(QString,uint)),          this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,SIGNAL(LogForPrint(QString,uint)),      this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,SIGNAL(DataForPrint(QByteArray,uint)),  this, SLOT(Print(QByteArray,uint)));

    DataLogic->setRepeatNumber(3);
    DataLogic->setRepeatTimeout(3000);
}
void Connections_Form::resizeEvent(QResizeEvent *event)
{
    QScreen *Screen = QApplication::primaryScreen();

    int DotsPerInch = Screen->logicalDotsPerInch();

    QSize this_size      = this->size();

    float w_to_dpi_index = float(this_size.width())/DotsPerInch;

    float size_1         = w_to_dpi_index*6;  if (size_1     > 38) {size_1     = 38;}
    float size_2         = w_to_dpi_index*4;  if (size_2     > 24) {size_2     = 24;}
    float size_3         = w_to_dpi_index*3;  if (size_3     > 16) {size_3     = 16;}

    float btn_size       = w_to_dpi_index*10; if (btn_size   > 40) {btn_size   = 40;}
    float label_size     = w_to_dpi_index*6;  if (label_size > 38) {label_size = 38;}

    QSize icon_size;     icon_size.setHeight(btn_size); icon_size.setWidth(btn_size);

    QFont font_1, font_2, font_3;
    font_1.setPointSize(size_1);
    font_2.setPointSize(size_2);
    font_3.setPointSize(size_3);

    ui->label_1->setFont(font_1);
    ui->label_2->setFont(font_2);
    ui->label_3->setFont(font_2);
    ui->label_4->setFont(font_3);
    ui->label_5->setFont(font_3);
    ui->label_6->setFont(font_3);

    ui->IPInput->setFont(font_3);
    ui->PORTInput->setFont(font_3);
    ui->PortNameBox->setFont(font_3);
    ui->COMConnect->setFont(font_3);
    ui->COMConnect->setMinimumHeight(btn_size);
    ui->TCPConnect->setFont(font_3);
    ui->TCPConnect->setMinimumHeight(btn_size);
    ui->btnHandsEnter->setFont(font_3);
    ui->btnHandsEnter->setMinimumHeight(btn_size);
    ui->btnNext->setFont(font_3);
    ui->btnNext->setMinimumHeight(btn_size);
    ui->btnNext->setIconSize(icon_size);
    ui->btnSettings->setFont(font_3);
    ui->btnSettings->setMinimumHeight(btn_size);
    ui->btnSettings->setIconSize(icon_size);
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
    connect(settings_form,SIGNAL(GetRepeatNumber(uint)),DataLogic,SLOT(setRepeatNumber(uint)));
    connect(settings_form,SIGNAL(GetRepeatTimeout(uint)),DataLogic,SLOT(setRepeatTimeout(uint)));

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


void Connections_Form::on_btnNext_clicked()
{
    open_connection_form = new Open_Connection_Form;

    connect(open_connection_form,SIGNAL(Cancel()),this,SLOT(show()));
    connect(open_connection_form,SIGNAL(Get_Console(QPlainTextEdit*)),   this,                  SLOT(Set_ActiveConsole(QPlainTextEdit*)));
    connect(open_connection_form,SIGNAL(SendSerialNumber(QString,bool)), DataLogic,             SLOT(setSerialNumberMode(QString,bool)));
    connect(open_connection_form,SIGNAL(AOPEN()),                        ConnectHandler,        SLOT(aOPEN()));
    connect(ConnectHandler,      SIGNAL(isAOPEN()),                      open_connection_form,  SLOT(isOPEND()));
    connect(ConnectHandler,      SIGNAL(Progress(uint)),                 open_connection_form,  SLOT(SetProgress(uint)));

    this->hide();
    open_connection_form->show();
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
