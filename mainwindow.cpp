#include "mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include "ui_mainwindow.h"
#include "STYLE/style.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QString s = Style::ToolTip_StyleSheet + Style::Widget1_StyleSheet;

    ui->setupUi(this);
    ui->centralWidget         ->setLayout(ui->CentralLayout);
    ui->tab                   ->setLayout(ui->tab_1_Layout);
    ui->NetTab                ->setLayout(ui->NetTab_Layout);
    ui->RFTab                 ->setLayout(ui->RFTab_Layout);
    ui->MonitorTab            ->setLayout(ui->MonitorTab_Layout);
    ui->COMWidget             ->setLayout(ui->COMLayout);
    ui->TCPWidget             ->setLayout(ui->TCPLayout);
    ui->MANUAL_ENTER          ->setLayout(ui->MANUAL_ENTER_Layout);
    ui->RSSIWidget            ->setLayout(ui->RSSILayout);
    ui->SwitchPropWidget      ->setLayout(ui->SwitchPropLayout);
    ui->SwTableWidget         ->setLayout(ui->SwTableLayout);

    ui->RSSIWidget            ->setEnabled(false);
    ui->tabWidget             ->setEnabled(false);
    ui->MANUAL_ENTER          ->setEnabled(false);

    ui->PortNameBox           ->installEventFilter(this);

    #ifdef Q_OS_WIN
    ui->action1_5_bits        ->setEnabled(true);
    #endif

    timer_COMBufferClear      = new QTimer();
    MODEM                     = new MODEMClass;
    PortNew                   = new Port();                                                                   // Создаем Поток обработки портов
    TCPNew                    = new TCP();
    oCRC16                    = new CRC16_Class();                                                            // Создаём Объект расчёта CRC
    newParcer                 = new ParceClass();
    SI4463Config              = new SI4463Class();
    DataLogic                 = new DataLogic_Class(oCRC16,timer_COMBufferClear,SI4463Config,MODEM,PortNew,TCPNew);   // Создаём Объект обработки сообщений
    ConnectHandler            = new ConnectHandlerClass(ui, DataLogic,MODEM);
    scene                     = new myGraphScene(this);

    ui->SI4436_PROPSView      ->setModel(SI4463Config->model);
    ui->SI4436_PROPSView      ->resizeRowsToContents();
    ui->SI4436_PROPSView      ->resizeColumnsToContents();

    scene                     ->setGeometry(640,290);

    x                         = -6;
    pRSSICurrent              = new myPoligon(QString::fromUtf8("RSSI Current"),0,scene);
    pRSSICurrent->BrushColor  = QColor::fromRgbF(0.9,0.9,0.3,1);
    pRSSICurrent->CurveColor  = QColor::fromRgbF(0.5,0.0,0.3,1);
    pAFC                      = new myPoligon(QString::fromUtf8("AFC"),1,scene);
    pAFC->BrushColor          = QColor::fromRgbF(0.3,0.9,0.9,1);
    pAFC->CurveColor          = QColor::fromRgbF(0.0,0.0,0.5,1);

    pRSSI                     = new myPoligon(QString::fromUtf8("RSSI"),2,scene);
    pRSSI->PointsVisible      = true;
    pRSSI->BrushColor         = QColor::fromRgbF(1,0.6,1,1);
    pRSSI->CurveColor         = QColor::fromRgbF(0.1,0.0,0.3,1);

    DataLogic->Repeat_Number  = 2;
    DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    DataLogic->Delay_Time     = 2000;

    connect(PortNew, SIGNAL(COM_Started()),               this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(PortNew, SIGNAL(COM_Error(QString,uint)),     this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    //connect(TCPNew, SIGNAL(TCP_Started()),              this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(TCPNew, SIGNAL(TCP_Error(QString,uint)),      this, SLOT(Print_Log(QString,uint)));   //Лог ошибок

    connect(ConnectHandler, SIGNAL(SendLog(QString,uint)),this, SLOT(Print_Log(QString,uint)));

    connect(ui->COMConnect,    SIGNAL(clicked()),PortNew,SLOT(COM_Connect()));
    connect(ui->TCPConnect,    SIGNAL(clicked()),TCPNew,SLOT(TCP_Connect()));

    connect(ui->COMDisconnect, SIGNAL(clicked()),PortNew,SLOT(COM_Disconnect()));
    connect(ui->COMDisconnect, SIGNAL(clicked()),ConnectHandler,SLOT(StopMonitor()));

    connect(this,SIGNAL(AOPEN()),            ConnectHandler,SLOT(aOPEN()));
    connect(this,SIGNAL(SET_SWITCH_MODE()),  ConnectHandler,SLOT(SetSWITCH_MODE()));
    connect(this,SIGNAL(SET_SWITCH_PROP()),  ConnectHandler,SLOT(SetSWITCH_PROP()));
    connect(this,SIGNAL(READ_CURRENT_RSSI()),ConnectHandler,SLOT(ReadCURRENT_RSSI()));
    connect(this,SIGNAL(READ_LRSSI_AFC()),   ConnectHandler,SLOT(ReadLRSSI_AFC()));
    connect(this,SIGNAL(START_MONITOR()),    ConnectHandler,SLOT(StartMonitor()));
    connect(this,SIGNAL(STOP_MONITOR()),     ConnectHandler,SLOT(StopMonitor()));

    connect(DataLogic,SIGNAL(noANSWER()),    ConnectHandler,SLOT(aOPEN()));
    connect(DataLogic,SIGNAL(noANSWER()),    ConnectHandler,SLOT(StopMonitor()));

    connect(DataLogic,SIGNAL(DataForPrint(QByteArray,uint)),this,SLOT(Print(QByteArray,uint)));
    connect(DataLogic,SIGNAL(outCurrentRSSI(signed short)),this,SLOT(out_Current_RSSI(signed short)));
    connect(DataLogic,SIGNAL(outLRSSI_AFC(signed short,signed short,signed short,double)),this,SLOT(out_LRSSI_AFC(signed short,signed short,signed short,double)));

    connect(timer_COMBufferClear,SIGNAL(timeout()), DataLogic, SLOT(ClearIn_DataBuffer()));

    PortNew->start();
    TCPNew ->start();
}

//++++++++[Процедура закрытия приложения]++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::~MainWindow()
{
    delete ui; //Удаление формы
}

void MainWindow::showEvent ( QShowEvent * event )
{

}

void MainWindow::resizeEvent ( QResizeEvent * event )
{
    scene->setGeometry(ui->graphicsView->geometry().width(),ui->graphicsView->geometry().height());
}

void MainWindow::on_Connect_clicked()
{
    emit AOPEN();
    emit STOP_MONITOR();
}

void MainWindow::on_SWITCH_stateChanged(int arg1)
{
    emit SET_SWITCH_MODE();
}

void MainWindow::on_SWITCH_PROPS_clicked()
{
    emit SET_SWITCH_PROP();
}

void MainWindow::on_readCurrentRSSI_clicked()
{
    emit READ_CURRENT_RSSI();
}

void MainWindow::on_readLatchRSSI_clicked()
{
    emit READ_LRSSI_AFC();
}
void MainWindow::on_MonitorStart_clicked()
{

    pRSSICurrent->removePolygon(scene);
    pAFC->removePolygon(scene);
    pRSSI->removePolygon(scene);
    pfRSSICurrent.clear();pfAFC.clear();pfRSSI.clear();
    scene->setGeometry(ui->graphicsView->geometry().width(),ui->graphicsView->geometry().height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();

    emit START_MONITOR();
}

void MainWindow::on_MonitorStop_clicked()
{
    x = -6;
    emit STOP_MONITOR();

}

void MainWindow::on_MonitorTimeout_clicked()
{
    bool ok;
    if(ui->Interface->currentIndex() == 0)
    {
        int i = QInputDialog::getInt(this, QString::fromUtf8("Введите таймаут от 100 - 10000 [мс]"), QString::fromUtf8("[мс]"), 500, 100, 10000, 1, &ok);
        if (ok){
            ui->MonitorTimeout->setText(QString::number(i));
        }
    }
    else if (ui->Interface->currentIndex() == 1)
    {
        int i = QInputDialog::getInt(this, QString::fromUtf8("Введите таймаут от 1000 - 30000 [мс]"), QString::fromUtf8("[мс]"), 2000, 1000, 10000, 1, &ok);
        if (ok){
            ui->MonitorTimeout->setText(QString::number(i));
        }
    }

}
//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void MainWindow::Print(QByteArray data, uint n)
{
    ui->SI4436_PROPSView      ->setModel(SI4463Config->model);
    QString s = "Print data";
    qDebug() << s;

    QByteArray d;
    d.append(data);


    switch (n)
    {
        case COM_TX:
        {
            ui->consol->textCursor().insertText("TX >> " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
            break;
        }
        case COM_RX:
        {
            ui->consol->textCursor().insertText("RX << " + QByteAray_To_QString(d).toUpper()); // Вывод текста в консоль
            break;
        }
    }
    QString str;str += '\r';
    ui->consol->textCursor().insertText(str); // Вывод текста в консоль
    ui->consol->moveCursor(QTextCursor::End);//Scroll
}

//+++++++++++++[Процедура вывода данных в консоль]++++++++++++++++++++++++++++++++++++++++
void MainWindow::Print_Log(QString data, uint n)
{
    ui->consol->textCursor().insertText(data); // Вывод текста в консоль
    ui->consol->moveCursor(QTextCursor::End);  //Scroll

    switch (n)
    {
        case COM_OPEN:
        {

            ui->COMConnect->setEnabled(false);
            ui->PortNameBox->setEnabled(false);
            ui->TCPWidget->setEnabled(false);

            ui->COMDisconnect->setEnabled(true);
            ui->MANUAL_ENTER->setEnabled(true);
            ui->tabWidget->setEnabled(true);
            ui->RSSIWidget->setEnabled(true);

            break;
        }
        case COM_CLOSE:
        {

            ui->PortNameBox->setEnabled(false);
            ui->COMDisconnect->setEnabled(false);
            ui->TCPDisconnect->setEnabled(false);
            ui->MANUAL_ENTER->setEnabled(false);
            ui->tabWidget->setEnabled(false);
            ui->RSSIWidget->setEnabled(false);

            ui->PortNameBox->setEnabled(true);
            ui->COMConnect->setEnabled(true);
            ui->TCPWidget->setEnabled(true);



            QString s = ui->Connect->text();
            if (s.compare("Отключение") == 0)
            {
                emit AOPEN();
            }
            break;
        }
    }
}

void MainWindow::out_Current_RSSI(signed short RSSI)
{
    double r = (double)(RSSI);
    r/=10;
    ui->Current_RSSI->setText(QString("%1").arg(r));

    if (ui->MonitorStart->isEnabled() == false)
    {
        if (x >= 6)
        {
            pRSSICurrent->removePolygon(scene);
            pAFC->removePolygon(scene);
            pRSSI->removePolygon(scene);
            pfRSSICurrent.clear();pfAFC.clear();pfRSSI.clear();
            x = -6;
        }
        pfRSSICurrent <<  QPointF(x, r);

        x += ui->MonitorTimeout->text().toDouble()/1000;
        pRSSICurrent->drawPolygon(&pfRSSICurrent, scene);
    }
}
void MainWindow::out_LRSSI_AFC(signed short RSSI,signed short ANT1_RSSI,signed short ANT2_RSSI,double AFC)
{
    double r = (double)(RSSI);
    r/=10;
    ui->Latch_RSSI->setText(QString("%1").arg(r));

    r = (double)(ANT1_RSSI);
    r/=10;
    ui->RSSI_ANT1->setText(QString("%1").arg(r));

    r = (double)(ANT2_RSSI);
    r/=10;
    ui->RSSI_ANT2->setText(QString("%1").arg(r));

    ui->AFC->setText(QString("%1").arg(AFC));
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->PortNameBox && event->type() == QEvent::MouseButtonPress)
    {
       if (ui->PortNameBox->isEnabled())
       {
           ui->PortNameBox->clear();
           foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
           {
              ui->PortNameBox->addItem(info.portName());
              ui->COMConnect->setEnabled(true);
           }
       }
    }
    return false;
}

void MainWindow::on_PortNameBox_currentIndexChanged(const QString &arg1)
{
    PortNew->COM_SetPortName(arg1);
}

void MainWindow::on_FileOpen_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.txt");

    ui->FileName->setText(str);

    newParcer->PARCE_Start(ui->FileName->text(), SI4463Config);
}

void MainWindow::start_COM_Init(void)
{
    if (ui->action9600->isChecked())
    {
        PortNew->COM_SetBaudRate(QSerialPort::Baud9600);
    }
    else if (ui->action19200->isChecked())
    {
        PortNew->COM_SetBaudRate(QSerialPort::Baud19200);
    }
    else if (ui->action38400->isChecked())
    {
        PortNew->COM_SetBaudRate(QSerialPort::Baud38400);
    }
    else if (ui->action115200->isChecked())
    {
        PortNew->COM_SetBaudRate(QSerialPort::Baud38400);
    }
    else if (ui->actionCustom->isChecked())
    {
        ui->actionCustom->setChecked(false);
        ui->action9600->setChecked(true);
        PortNew->COM_SetBaudRate(QSerialPort::Baud9600);
    }
    if (ui->action5_bits->isChecked())
    {
        PortNew->COM_SetDataBits(QSerialPort::Data5);
    }
    else if (ui->action6_bits->isChecked())
    {
        PortNew->COM_SetDataBits(QSerialPort::Data6);
    }
    else if (ui->action7_bits->isChecked())
    {
        PortNew->COM_SetDataBits(QSerialPort::Data7);
    }
    else if (ui->action8_bits->isChecked())
    {
        PortNew->COM_SetDataBits(QSerialPort::Data8);
    }
    if (ui->actionNone->isChecked())
    {
        PortNew->COM_SetParity(QSerialPort::NoParity);
    }
    else if (ui->actionEven->isChecked())
    {
        PortNew->COM_SetParity(QSerialPort::EvenParity);
    }
    else if (ui->actionOdd->isChecked())
    {
        PortNew->COM_SetParity(QSerialPort::OddParity);
    }
    else if (ui->actionMark->isChecked())
    {
        PortNew->COM_SetParity(QSerialPort::MarkParity);
    }
    else if (ui->actionSpace->isChecked())
    {
        PortNew->COM_SetParity(QSerialPort::SpaceParity);
    }
    if (ui->action1_bit->isChecked())
    {
        PortNew->COM_SetStopBits(QSerialPort::OneStop);
    }
    else if (ui->action1_5_bits->isChecked())
    {
        PortNew->COM_SetStopBits(QSerialPort::OneAndHalfStop);
    }
    else if (ui->action2_bits->isChecked())
    {
        PortNew->COM_SetStopBits(QSerialPort::TwoStop);
    }
    if (ui->actionNone_2->isChecked())
    {
        PortNew->COM_SetFlowControl(QSerialPort::NoFlowControl);
    }
    else if (ui->actionRTS_CTS->isChecked())
    {
        PortNew->COM_SetFlowControl(QSerialPort::HardwareControl);
    }
    else if (ui->actionXON_XOFF->isChecked())
    {
        PortNew->COM_SetFlowControl(QSerialPort::SoftwareControl);
    }
}

void MainWindow::on_SN_ENABLE_toggled(bool checked)
{
    if (checked == true)
    {
        ui->SN_TEXT->setEnabled(true);
    }
    else
    {
        ui->SN_TEXT->setEnabled(false);
    }
}

void MainWindow::on_CRC_OUT_toggled(bool checked)
{
    if (checked == true)
    {
        QByteArray data_to_out, data_to_write; // Текстовая переменная
        data_to_out = ui->cEnterText->text().toUtf8(); // Присвоение "data" значения из EnterText

        data_to_write = QString_To_QByteAray(ui->cEnterText->text(),false);

        ushort CRC_Calculated = oCRC16->CRC16_Generate(&data_to_write);
        QByteArray CRC_Calc;
        CRC_Calc.append((uchar)(CRC_Calculated >> 0));
        CRC_Calc.append((uchar)(CRC_Calculated >> 8));

        ui->CRC_OUT->setText(QByteAray_To_QString(CRC_Calc).toUpper());
        data_to_write.append(CRC_Calc);
    }
    else
    {
        ui->CRC_OUT->setText("CRC16");
    }
}

void MainWindow::on_cBtnSend_clicked()
{
    QByteArray data_to_write; // Текстовая переменная
    int sn = 0;

    QString str2;
    str2.clear();

    if (ui->SN_ENABLE->isChecked())
    {
        sn = ui->SN_TEXT->text().toInt();
        data_to_write.append((char)(sn >> 0));
        data_to_write.append((char)(sn >> 8));
        data_to_write.append((char)(sn >> 16));
        data_to_write.append((char)(sn >> 24));
    }

    data_to_write.append(QString_To_QByteAray(ui->cEnterText->text(), ui->CRC_OUT->isChecked()));

    if (ui->CRC_OUT->isChecked())
    {
        QByteArray CRC_Calc;
        CRC_Calc.append(data_to_write.at(data_to_write.length()-2));
        CRC_Calc.append(data_to_write.at(data_to_write.length()-1));
        ui->CRC_OUT->setText(QByteAray_To_QString(CRC_Calc).toUpper());
    }
    else
    {
        ui->CRC_OUT->setText("CRC16");
    }

    if (ui->SN_ENABLE->isChecked())
    {
        ushort CRC_Calculated = oCRC16->CRC16_Generate(&data_to_write);
        QByteArray CRC_Calc_2;
        CRC_Calc_2.append((uchar)(CRC_Calculated >> 0));
        CRC_Calc_2.append((uchar)(CRC_Calculated >> 8));

        ui->CRC16_2->setText(QByteAray_To_QString(CRC_Calc_2).toUpper());

        data_to_write.append(CRC_Calc_2);
    }
    else
    {
        ui->CRC16_2->setText("CRC16");
    }
    if (data_to_write.length() > 0)
    {
        DataLogic->SEND_DATA(data_to_write,MANUAL_SEND_CONTROL);
    }
}

void MainWindow::on_Interface_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
        {
            ui->SN->setEnabled(false);
            DataLogic->setSerialNumberMode(ui->SN->text(), false);
            ui->MonitorTimeout->setText("500");
            break;
        }
        case 1:
        {
            ui->SN->setEnabled(true);
            DataLogic->setSerialNumberMode(ui->SN->text(), true);
            ui->MonitorTimeout->setText("2000");
            break;

        }
    }
}

QString MainWindow::QByteAray_To_QString(QByteArray arr)
{
    int index = 0;
    QString str1; str1.clear();
    QByteArray hex_item; hex_item.clear();
    while (index < arr.length())
    {
        hex_item.clear();
        hex_item.append(arr[index]);
        str1.append(hex_item.toHex());
        str1 += ' ';
        index++;
    }
    return str1;
}

QByteArray MainWindow::QString_To_QByteAray(QString str, bool crc)
{
    QByteArray data_to_out, data_to_write; // Текстовая переменная
    data_to_out = str.toUtf8(); // Присвоение "data" значения из EnterText

    QString str2; str2.clear();


    int index = 0, index_2 = 0;


    ushort CalcCRC16;
    uint cnt2 = 0;
    CalcCRC16 = 0xFFFF;
    while (index < data_to_out.size())
    {

        str2[index] = data_to_out[index];
        index++;
        index_2++;
        if (index_2 == 2)
        {
            bool b = false;
            uint nHex = str2.toUInt(&b,16);
            data_to_write.append((char)(nHex));
            if (crc)
            {
                CalcCRC16 = oCRC16->GetCRC16(CalcCRC16, data_to_write.at(cnt2++));
            }
            str2.clear();
            index_2 = 0;
            if (data_to_out[index] == ' ')
            {
                index++;
            }
        }
    }
    if (crc)
    {
        //ushort CRC_Calculated = oCRC16->CRC16_Generate(&data_to_write);
        QByteArray CRC_Calc;
        CRC_Calc.append((uchar)(CalcCRC16 >> 0));
        CRC_Calc.append((uchar)(CalcCRC16 >> 8));

        int index = 0;
        QString str1; str1.clear();
        QByteArray hex_item; hex_item.clear();
        QString s = "Print CRC";
        qDebug() << s;
        while (index < CRC_Calc.length())
        {
            hex_item.clear();
            hex_item.append(CRC_Calc[index]);
            str1.append(hex_item.toHex());
            str1 += ' ';
            index++;
        }
        data_to_write.append(CRC_Calc);
    }

    return data_to_write;
}

// ===========================================================================================================================================================
// ============ MENU =========================================================================================================================================
// ===========================================================================================================================================================

void MainWindow::on_action9600_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action9600->setChecked(true);
        ui->action19200->setChecked(false);
        ui->action38400->setChecked(false);
        ui->action115200->setChecked(false);
        ui->actionCustom->setChecked(false);
        PortNew->COM_SetBaudRate(QSerialPort::Baud9600);
    }
}

void MainWindow::on_action19200_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action9600->setChecked(false);
        ui->action19200->setChecked(true);
        ui->action38400->setChecked(false);
        ui->action115200->setChecked(false);
        ui->actionCustom->setChecked(false);
        PortNew->COM_SetBaudRate(QSerialPort::Baud19200);
    }
}

void MainWindow::on_action38400_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action9600->setChecked(false);
        ui->action19200->setChecked(false);
        ui->action38400->setChecked(true);
        ui->action115200->setChecked(false);
        ui->actionCustom->setChecked(false);
        PortNew->COM_SetBaudRate(QSerialPort::Baud38400);
    }
}

void MainWindow::on_action115200_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action9600->setChecked(false);
        ui->action19200->setChecked(false);
        ui->action38400->setChecked(false);
        ui->action115200->setChecked(true);
        ui->actionCustom->setChecked(false);
        PortNew->COM_SetBaudRate(QSerialPort::Baud115200);
    }
}

void MainWindow::on_actionCustom_triggered()
{
        bool ok;
        int i = QInputDialog::getInt(this, QString::fromUtf8("Введите скорость в пределах 300 - 115200[BPS]"), QString::fromUtf8("[BPS]"), 9600, 300, 115200, 1, &ok);
        if (ok){
            ui->action9600->setChecked(false);
            ui->action19200->setChecked(false);
            ui->action38400->setChecked(false);
            ui->action115200->setChecked(false);
            ui->actionCustom->setChecked(true);
            PortNew->COM_SetBaudRate(i);
        }
}

void MainWindow::on_action5_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action5_bits->setChecked(true);
        ui->action6_bits->setChecked(false);
        ui->action7_bits->setChecked(false);
        ui->action8_bits->setChecked(false);
        PortNew->COM_SetDataBits(QSerialPort::Data5);
    }
}

void MainWindow::on_action6_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action5_bits->setChecked(false);
        ui->action6_bits->setChecked(true);
        ui->action7_bits->setChecked(false);
        ui->action8_bits->setChecked(false);
        PortNew->COM_SetDataBits(QSerialPort::Data6);
    }
}

void MainWindow::on_action7_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action5_bits->setChecked(false);
        ui->action6_bits->setChecked(false);
        ui->action7_bits->setChecked(true);
        ui->action8_bits->setChecked(false);
        PortNew->COM_SetDataBits(QSerialPort::Data7);
    }
}

void MainWindow::on_action8_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action5_bits->setChecked(false);
        ui->action6_bits->setChecked(false);
        ui->action7_bits->setChecked(false);
        ui->action8_bits->setChecked(true);
        PortNew->COM_SetDataBits(QSerialPort::Data8);
    }
}

void MainWindow::on_actionNone_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone->setChecked(true);
        ui->actionEven->setChecked(false);
        ui->actionOdd->setChecked(false);
        ui->actionMark->setChecked(false);
        ui->actionSpace->setChecked(false);
        PortNew->COM_SetParity(QSerialPort::NoParity);
    }
}

void MainWindow::on_actionEven_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone->setChecked(false);
        ui->actionEven->setChecked(true);
        ui->actionOdd->setChecked(false);
        ui->actionMark->setChecked(false);
        ui->actionSpace->setChecked(false);
        PortNew->COM_SetParity(QSerialPort::EvenParity);
    }
}

void MainWindow::on_actionOdd_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone->setChecked(false);
        ui->actionEven->setChecked(false);
        ui->actionOdd->setChecked(true);
        ui->actionMark->setChecked(false);
        ui->actionSpace->setChecked(false);
        PortNew->COM_SetParity(QSerialPort::OddParity);
    }
}

void MainWindow::on_actionMark_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone->setChecked(false);
        ui->actionEven->setChecked(false);
        ui->actionOdd->setChecked(false);
        ui->actionMark->setChecked(true);
        ui->actionSpace->setChecked(false);
        PortNew->COM_SetParity(QSerialPort::MarkParity);
    }
}

void MainWindow::on_actionSpace_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone->setChecked(false);
        ui->actionEven->setChecked(false);
        ui->actionOdd->setChecked(false);
        ui->actionMark->setChecked(false);
        ui->actionSpace->setChecked(true);
        PortNew->COM_SetParity(QSerialPort::SpaceParity);
    }
}

void MainWindow::on_action1_bit_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action1_bit->setChecked(true);
        ui->action1_5_bits->setChecked(false);
        ui->action2_bits->setChecked(false);
        PortNew->COM_SetStopBits(QSerialPort::OneStop);
    }
}

void MainWindow::on_action1_5_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action1_bit->setChecked(false);
        ui->action1_5_bits->setChecked(true);
        ui->action2_bits->setChecked(false);
        PortNew->COM_SetStopBits(QSerialPort::OneAndHalfStop);
    }
}

void MainWindow::on_action2_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action1_bit->setChecked(false);
        ui->action1_5_bits->setChecked(false);
        ui->action2_bits->setChecked(true);
        PortNew->COM_SetStopBits(QSerialPort::TwoStop);
    }
}

void MainWindow::on_actionNone_2_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone_2->setChecked(true);
        ui->actionRTS_CTS->setChecked(false);
        ui->actionXON_XOFF->setChecked(false);
        PortNew->COM_SetFlowControl(QSerialPort::NoFlowControl);
    }
}

void MainWindow::on_actionRTS_CTS_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone_2->setChecked(false);
        ui->actionRTS_CTS->setChecked(true);
        ui->actionXON_XOFF->setChecked(false);
        PortNew->COM_SetFlowControl(QSerialPort::HardwareControl);
    }
}

void MainWindow::on_actionXON_XOFF_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone_2->setChecked(false);
        ui->actionRTS_CTS->setChecked(false);
        ui->actionXON_XOFF->setChecked(true);
        PortNew->COM_SetFlowControl(QSerialPort::SoftwareControl);
    }
}

void MainWindow::on_action10000_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10000->setChecked(true);
        ui->action8000->setChecked(false);
        ui->action6000->setChecked(false);
        ui->action4000->setChecked(false);
        ui->action2000->setChecked(false);
        ui->action1000->setChecked(false);
        ui->action_Pm->setChecked(false);

        DataLogic->Delay_Time = 10000;
    }
}

void MainWindow::on_action8000_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10000->setChecked(false);
        ui->action8000->setChecked(true);
        ui->action6000->setChecked(false);
        ui->action4000->setChecked(false);
        ui->action2000->setChecked(false);
        ui->action1000->setChecked(false);
        ui->action_Pm->setChecked(false);

        DataLogic->Delay_Time = 8000;
    }
}

void MainWindow::on_action6000_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10000->setChecked(false);
        ui->action8000->setChecked(false);
        ui->action6000->setChecked(true);
        ui->action4000->setChecked(false);
        ui->action2000->setChecked(false);
        ui->action1000->setChecked(false);
        ui->action_Pm->setChecked(false);

        DataLogic->Delay_Time = 6000;
    }
}

void MainWindow::on_action4000_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10000->setChecked(false);
        ui->action8000->setChecked(false);
        ui->action6000->setChecked(false);
        ui->action4000->setChecked(true);
        ui->action2000->setChecked(false);
        ui->action1000->setChecked(false);
        ui->action_Pm->setChecked(false);

        DataLogic->Delay_Time = 4000;
    }
}

void MainWindow::on_action2000_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10000->setChecked(false);
        ui->action8000->setChecked(false);
        ui->action6000->setChecked(false);
        ui->action4000->setChecked(false);
        ui->action2000->setChecked(true);
        ui->action1000->setChecked(false);
        ui->action_Pm->setChecked(false);

        DataLogic->Delay_Time = 2000;
    }
}

void MainWindow::on_action1000_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10000->setChecked(false);
        ui->action8000->setChecked(false);
        ui->action6000->setChecked(false);
        ui->action4000->setChecked(false);
        ui->action2000->setChecked(false);
        ui->action1000->setChecked(true);
        ui->action_Pm->setChecked(false);

        DataLogic->Delay_Time = 1000;
    }
}

void MainWindow::on_action_Pm_triggered()
{

        bool ok;
        int i = QInputDialog::getInt(this, QString::fromUtf8("Введите период повторений от 100 - 60000[мс]"), QString::fromUtf8("[мс]"), 3000, 100, 60000, 1, &ok);
        if (ok){
            ui->action10000->setChecked(false);
            ui->action8000->setChecked(false);
            ui->action6000->setChecked(false);
            ui->action4000->setChecked(false);
            ui->action2000->setChecked(false);
            ui->action1000->setChecked(false);
            ui->action_Pm->setChecked(true);
            DataLogic->Delay_Time = i;
        }
}

void MainWindow::on_action10_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10->setChecked(true);
        ui->action8->setChecked(false);
        ui->action6->setChecked(false);
        ui->action4->setChecked(false);
        ui->action2->setChecked(false);
        ui->action1->setChecked(false);
        ui->action_Nm->setChecked(false);

        DataLogic->Repeat_Number = 10;
        DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    }
}

void MainWindow::on_action8_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10->setChecked(false);
        ui->action8->setChecked(true);
        ui->action6->setChecked(false);
        ui->action4->setChecked(false);
        ui->action2->setChecked(false);
        ui->action1->setChecked(false);
        ui->action_Nm->setChecked(false);

        DataLogic->Repeat_Number = 8;
        DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    }
}

void MainWindow::on_action6_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10->setChecked(false);
        ui->action8->setChecked(false);
        ui->action6->setChecked(true);
        ui->action4->setChecked(false);
        ui->action2->setChecked(false);
        ui->action1->setChecked(false);
        ui->action_Nm->setChecked(false);

        DataLogic->Repeat_Number = 6;
        DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    }
}

void MainWindow::on_action4_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10->setChecked(false);
        ui->action8->setChecked(false);
        ui->action6->setChecked(false);
        ui->action4->setChecked(true);
        ui->action2->setChecked(false);
        ui->action1->setChecked(false);
        ui->action_Nm->setChecked(false);

        DataLogic->Repeat_Number = 4;
        DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    }
}

void MainWindow::on_action2_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10->setChecked(false);
        ui->action8->setChecked(false);
        ui->action6->setChecked(false);
        ui->action4->setChecked(false);
        ui->action2->setChecked(true);
        ui->action1->setChecked(false);
        ui->action_Nm->setChecked(false);

        DataLogic->Repeat_Number = 2;
        DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    }
}

void MainWindow::on_action1_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action10->setChecked(false);
        ui->action8->setChecked(false);
        ui->action6->setChecked(false);
        ui->action4->setChecked(false);
        ui->action2->setChecked(false);
        ui->action1->setChecked(true);
        ui->action_Nm->setChecked(false);

        DataLogic->Repeat_Number = 1;
        DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    }
}

void MainWindow::on_action_Nm_triggered()
{
    bool ok;
    int i = QInputDialog::getInt(this, QString::fromUtf8("Введите кол-во повторений от 1 - 100 [раз]"), QString::fromUtf8("[раз]"), 3, 1, 100, 1, &ok);
    if (ok){
        ui->action1->setChecked(false);
        ui->action8->setChecked(false);
        ui->action6->setChecked(false);
        ui->action4->setChecked(false);
        ui->action2->setChecked(false);
        ui->action1->setChecked(false);
        ui->action_Pm->setChecked(true);
        DataLogic->Repeat_Number = i;
        DataLogic->Repeat_Counter = DataLogic->Repeat_Number;
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->consol->clear();
}

void MainWindow::on_logHidden_clicked()
{
    if (ui->consol->maximumHeight() == 200)
    {ui->consol->setMaximumHeight(0);}
    if (ui->consol->maximumHeight() == 400)
    {ui->consol->setMaximumHeight(200);}

}

void MainWindow::on_LogShow_clicked()
{
    if (ui->consol->maximumHeight() == 200)
    {ui->consol->setMaximumHeight(400);}
    if (ui->consol->maximumHeight() == 0)
    {ui->consol->setMaximumHeight(200);}

}
