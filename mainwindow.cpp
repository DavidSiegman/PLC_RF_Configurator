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
#include "barr_to_string.h"
#include "STYLE/style.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Class_init_state = 0;
    QString s = Style::ToolTip_StyleSheet + Style::Widget1_StyleSheet;

    ui->setupUi(this);
    ui->centralWidget         ->setLayout(ui->CentralLayout);
    ui->tab                   ->setLayout(ui->tab_1_Layout);
    ui->NetTab                ->setLayout(ui->NetTab_Layout);
    ui->RFTab                 ->setLayout(ui->RFTab_Layout);
    ui->PLCTab                ->setLayout(ui->PLCTab_Layout);
    ui->RFOldTab              ->setLayout(ui->RFOldLayout);
    ui->MonitorTab            ->setLayout(ui->MonitorTab_Layout);
    ui->COMWidget             ->setLayout(ui->COMLayout);
    ui->TCPWidget             ->setLayout(ui->TCPLayout);
    ui->MANUAL_ENTER          ->setLayout(ui->MANUAL_ENTER_Layout);
    ui->RSSIWidget            ->setLayout(ui->RSSILayout);
    ui->SwitchPropWidget      ->setLayout(ui->SwitchPropLayout);
    ui->SwTableWidget         ->setLayout(ui->SwTableLayout);
    ui->InfoWidget            ->setLayout(ui->InfoLayout);
    ui->ConnectionsWidget     ->setLayout(ui->ConnectionsLayout);
    ui->LogWidget             ->setLayout(ui->LogLayout);
    ui->DevConnectWidget      ->setLayout(ui->DevConnectLayout);
    ui->UpgradeWidget         ->setLayout(ui->UpgradeLayout);
    ui->SI4432_Widget         ->setLayout(ui->SI4432_Layout);

    ui->RSSIWidget            ->setEnabled(false);
    ui->tabWidget             ->setEnabled(false);
    ui->MANUAL_ENTER          ->setEnabled(false);

    ui->PortNameBox           ->installEventFilter(this);

    #ifdef Q_OS_WIN
    ui->action1_5_bits        ->setEnabled(true);
    #endif

    ui->InfoWidget            ->setMaximumHeight(0);
    ui->LogWidget             ->setMaximumHeight(0);
    //ui->ConnectionsWidget     ->setMaximumWidth(0);
    this->setGeometry(100,100,this->geometry().width(),this->geometry().height()-250);

    timer_COMBufferClear      = new QTimer();
    timer_ConnectionsPanel    = new QTimer();
    MODEM                     = new MODEMClass(ui);
    newPort                   = new Port();                                                                   // Создаем Поток обработки портов
    newTCP                    = new TCP();
    oCRC16                    = new CRC16_Class();                                                            // Создаём Объект расчёта CRC
    newParcer                 = new ParceClass();
    SI4463Config              = new SI4463Class();
    SI4432Config              = new SI4432Class(ui);
    PLCConfig                 = new PLCClass(ui);
    newUPDATE                 = new UPDATE(ui);

    DataLogic                 = new DataLogic_Class(oCRC16,timer_COMBufferClear,SI4463Config,SI4432Config,
                                                    PLCConfig,MODEM,newPort,newTCP,newUPDATE,this);   // Создаём Объект обработки сообщений
    ConnectHandler            = new ConnectHandlerClass(ui, DataLogic, MODEM, newUPDATE);
    scene                     = new myGraphScene(this);
    newFilter                 = new Filter(10);


    ui->SI4436_PROPSView      ->setModel(SI4463Config->model);
    ui->SI4436_PROPSView      ->resizeRowsToContents();
    ui->SI4436_PROPSView      ->resizeColumnsToContents();

    scene                     ->setGeometry(640,290);

    x_coord                   = -6;
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

    connect(newPort, SIGNAL(COM_Started()),               this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(newPort, SIGNAL(COM_Error(QString,uint)),     this, SLOT(Print_Log(QString,uint)));   //Лог ошибок
    //connect(TCPNew, SIGNAL(TCP_Started()),              this, SLOT(start_COM_Init()));          //Установка свойств порта при открытии
    connect(newTCP, SIGNAL(TCP_Error(QString,uint)),      this, SLOT(Print_Log(QString,uint)));   //Лог ошибок

    connect(ConnectHandler,    SIGNAL(SendLog(QString,uint)),this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,         SIGNAL(SendLog(QString,uint)),this, SLOT(Print_Log(QString,uint)));

    connect(ui->COMConnect,    SIGNAL(clicked()),newPort,SLOT(COM_Connect()));
    connect(ui->TCPConnect,    SIGNAL(clicked()),newTCP, SLOT(TCP_Connect()));

    connect(ui->COMDisconnect, SIGNAL(clicked()),newPort,       SLOT(COM_Disconnect()));
    connect(ui->COMDisconnect, SIGNAL(clicked()),ConnectHandler,SLOT(StopMonitor()));

    connect(ui->TCPDisconnect, SIGNAL(clicked()),newTCP,        SLOT(TCP_Disconnect()));
    connect(ui->TCPDisconnect, SIGNAL(clicked()),ConnectHandler,SLOT(StopMonitor()));

    connect(this,SIGNAL(AOPEN()),                       ConnectHandler,SLOT(aOPEN()));
    connect(this,SIGNAL(SET_SWITCH_MODE()),             ConnectHandler,SLOT(SetSWITCH_MODE()));
    connect(this,SIGNAL(SET_SWITCH_PROP()),             ConnectHandler,SLOT(SetSWITCH_PROP()));
    connect(this,SIGNAL(READ_CURRENT_RSSI()),           ConnectHandler,SLOT(ReadCURRENT_RSSI()));
    connect(this,SIGNAL(READ_LRSSI_AFC()),              ConnectHandler,SLOT(ReadLRSSI_AFC()));
    connect(this,SIGNAL(START_MONITOR()),               ConnectHandler,SLOT(StartMonitor()));
    connect(this,SIGNAL(STOP_MONITOR()),                ConnectHandler,SLOT(StopMonitor()));
    connect(this,SIGNAL(WRITE_RF_PARAMS()),             ConnectHandler,SLOT(WriteRF_PARAMS()));
    connect(this,SIGNAL(WRITE_RFSI4432_PARAMS()),       ConnectHandler,SLOT(WriteRFSI4432_PARAMS()));
    connect(this,SIGNAL(SEND_RF_RESET()),               ConnectHandler,SLOT(SendRF_RESET()));
    connect(this,SIGNAL(SEND_SNIFER_MODE()),            ConnectHandler,SLOT(SendSNIFER_MODE()));
    connect(this,SIGNAL(SEND_UPLINC_MODE()),            ConnectHandler,SLOT(SendUPLINC_MODE()));
    connect(this,SIGNAL(SEND_CRC_DISABLE_MODE()),       ConnectHandler,SLOT(SendCRC_DISABLE_MODE()));
    connect(this,SIGNAL(SEND_BROADCAST_MODE()),         ConnectHandler,SLOT(SendBROADCAST_MODE()));
    connect(this,SIGNAL(WRITE_SWITCH_TABLE()),          ConnectHandler,SLOT(WriteSWITCH_TABLE()));
    connect(this,SIGNAL(READ_SWITCH_TABLE()),           ConnectHandler,SLOT(ReadSWITCH_TABLE()));
    connect(this,SIGNAL(SEND_SWITCH_TABLE_DELETE()),    ConnectHandler,SLOT(SendSWITCH_TABLE_DELETE()));
    connect(this,SIGNAL(WRITE_MASK_DESTINATION()),      ConnectHandler,SLOT(WriteMASK_DESTINATION()));
    connect(this,SIGNAL(START_UPDATE()),                ConnectHandler,SLOT(StartUPDATE()));
    connect(this,SIGNAL(START_DELETE()),                ConnectHandler,SLOT(StartDELETE()));

    connect(ui->STOP, SIGNAL(clicked(bool)), DataLogic,     SLOT(STOP_SEND_DATA(bool)));
    connect(DataLogic,SIGNAL(STOP()),               ConnectHandler,SLOT(StopMonitor()));
    connect(DataLogic,SIGNAL(STOP()),               ConnectHandler,SLOT(STOP()));
    connect(DataLogic,SIGNAL(noANSWER()),           ConnectHandler,SLOT(StopMonitor()));
    connect(DataLogic,SIGNAL(noANSWER()),           ConnectHandler,SLOT(STOP()));
    connect(DataLogic,SIGNAL(outPROGRESS(uint)),    ConnectHandler,SLOT(setPROGRESS(uint)));

    connect(DataLogic,SIGNAL(DataForPrint(QByteArray,uint)),  this,SLOT(Print(QByteArray,uint)));
    connect(DataLogic,SIGNAL(LogForPrint(QString,uint)),      this, SLOT(Print_Log(QString,uint)));
    connect(DataLogic,SIGNAL(outCurrentRSSI(signed short)),this,SLOT(out_Current_RSSI(signed short)));
    connect(DataLogic,SIGNAL(outLRSSI_AFC(signed short,signed short,signed short,double)),this,SLOT(out_LRSSI_AFC(signed short,signed short,signed short,double)));

    connect(timer_COMBufferClear,  SIGNAL(timeout()), DataLogic, SLOT(ClearIn_DataBuffer()));
    //connect(timer_ConnectionsPanel,SIGNAL(timeout()), this, SLOT(HideConnectionPanel()));

    connect(this,SIGNAL(ADD_NET_TABLE_ITEM(QString)), MODEM, SLOT(addNewItem(QString)));
    connect(this,SIGNAL(DEL_NET_TABLE_ITEM()),        MODEM, SLOT(delNewItem()));
    connect(this,SIGNAL(SET_CURR_INDEX(uchar)),       MODEM, SLOT(setCurrent_Index(uchar)));

    connect(newParcer,SIGNAL(PARCE_currentLine(int)), ui->progressBar, SLOT(setValue(int)));
    connect(newParcer,SIGNAL(PARCE_End()), this, SLOT(ParceFinishHandler()));

    newPort->start();
    newTCP ->start();
    Class_init_state = 1;
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
    x_coord = -6;
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
    case TCP_OPEN:
    {

        ui->TCPConnect->setEnabled(false);
        ui->PortNameBox->setEnabled(false);
        ui->COMWidget->setEnabled(false);

        ui->TCPDisconnect->setEnabled(true);
        ui->MANUAL_ENTER->setEnabled(true);
        ui->tabWidget->setEnabled(true);
        ui->RSSIWidget->setEnabled(true);

        break;
    }
    case TCP_CLOSE:
    {

        ui->PortNameBox->setEnabled(false);
        ui->COMDisconnect->setEnabled(false);
        ui->TCPDisconnect->setEnabled(false);
        ui->MANUAL_ENTER->setEnabled(false);
        ui->tabWidget->setEnabled(false);
        ui->RSSIWidget->setEnabled(false);

        ui->PortNameBox->setEnabled(true);
        ui->TCPConnect->setEnabled(true);
        ui->COMWidget->setEnabled(true);

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
        if (x_coord >= 6)
        {
            pRSSICurrent->removePolygon(scene);
            pAFC->removePolygon(scene);
            pRSSI->removePolygon(scene);
            pfRSSICurrent.clear();pfAFC.clear();pfRSSI.clear();
            x_coord = -6;
        }
        pfRSSICurrent <<  QPointF(x_coord, r);

        x_coord += ui->MonitorTimeout->text().toDouble()/1000;
        pRSSICurrent->drawPolygon(&pfRSSICurrent, scene);
    }
}
void MainWindow::out_LRSSI_AFC(signed short RSSI,signed short ANT1_RSSI,signed short ANT2_RSSI,double AFC)
{
    double r = (double)(RSSI);
    r/=10;
    ui->Latch_RSSI->setText(QString("%1").arg(r));

    double r1 = (double)(ANT1_RSSI);
    r1/=10;
    ui->RSSI_ANT1->setText(QString("%1").arg(r1));

    double r2 = (double)(ANT2_RSSI);
    r2/=10;
    ui->RSSI_ANT2->setText(QString("%1").arg(r2));

    ui->AFC->setText(QString("%1").arg(AFC));

    if (ui->MonitorStart->isEnabled() == false)
    {
        unsigned int counter = ui->YesAnswer->text().toInt();
        counter++;
        newFilter->add_value(r);
        double average = newFilter->get_result();
        ui->AValue->setText(QString::number(average));
        ui->YesAnswer->setText(QString::number(counter));

        if (x_coord >= 6)
        {
            pRSSICurrent->removePolygon(scene);
            pAFC->removePolygon(scene);
            pRSSI->removePolygon(scene);
            pfRSSICurrent.clear();pfAFC.clear();pfRSSI.clear();
            x_coord = -6;
        }
        pfRSSI <<  QPointF(x_coord, r);

        x_coord += ui->MonitorTimeout->text().toDouble()/10000;
        pRSSI->drawPolygon(&pfRSSI, scene);
    }
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

void MainWindow::ParceFinishHandler(void)
{
    int index = 0;
    for(int i = 0; i < SI4463Config->Parameters.length();i++)
    {
        if(SI4463Config->Parameters.at(i).name.compare("Rsymb(sps):") == 0)
        {
            ui->DataRate->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("RF Freq.(MHz):") == 0)
        {
            ui->Freq->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("MOD_type:") == 0)
        {
            ui->MODULATION->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("Fdev(Hz):") == 0)
        {
            ui->Fdev->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("RXBW(Hz):") == 0)
        {
            ui->RXBW->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("AFC_en:") == 0)
        {
            ui->AFC_State->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("WB filter ") == 0)
        {
            ui->WB_Filter->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("NB-filter ") == 0)
        {
            index = 1;
            ui->NB_Filter->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("NB-filter ") == 0)
        {
            ui->NB_Filter->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("BW =  ") == 0)
        {
            ui->WB_BW->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("BW = ") == 0)
        {
           ui->NB_BW->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("Modulation index:") == 0)
        {
            ui->MOD_INDEX->setText(SI4463Config->Parameters.at(i).value);
        }
        if(SI4463Config->Parameters.at(i).name.compare("ANT_DIV:") == 0)
        {
            ui->ANT_DIV->setText(SI4463Config->Parameters.at(i).value);
        }

    }
    ui->RFParamWrite->setEnabled(true);
}

void MainWindow::on_PortNameBox_currentIndexChanged(const QString &arg1)
{
    newPort->COM_SetPortName(arg1);
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
        newPort->COM_SetBaudRate(QSerialPort::Baud9600);
    }
    else if (ui->action19200->isChecked())
    {
        newPort->COM_SetBaudRate(QSerialPort::Baud19200);
    }
    else if (ui->action38400->isChecked())
    {
        newPort->COM_SetBaudRate(QSerialPort::Baud38400);
    }
    else if (ui->action115200->isChecked())
    {
        newPort->COM_SetBaudRate(QSerialPort::Baud38400);
    }
    else if (ui->actionCustom->isChecked())
    {
        ui->actionCustom->setChecked(false);
        ui->action9600->setChecked(true);
        newPort->COM_SetBaudRate(QSerialPort::Baud9600);
    }
    if (ui->action5_bits->isChecked())
    {
        newPort->COM_SetDataBits(QSerialPort::Data5);
    }
    else if (ui->action6_bits->isChecked())
    {
        newPort->COM_SetDataBits(QSerialPort::Data6);
    }
    else if (ui->action7_bits->isChecked())
    {
        newPort->COM_SetDataBits(QSerialPort::Data7);
    }
    else if (ui->action8_bits->isChecked())
    {
        newPort->COM_SetDataBits(QSerialPort::Data8);
    }
    if (ui->actionNone->isChecked())
    {
        newPort->COM_SetParity(QSerialPort::NoParity);
    }
    else if (ui->actionEven->isChecked())
    {
        newPort->COM_SetParity(QSerialPort::EvenParity);
    }
    else if (ui->actionOdd->isChecked())
    {
        newPort->COM_SetParity(QSerialPort::OddParity);
    }
    else if (ui->actionMark->isChecked())
    {
        newPort->COM_SetParity(QSerialPort::MarkParity);
    }
    else if (ui->actionSpace->isChecked())
    {
        newPort->COM_SetParity(QSerialPort::SpaceParity);
    }
    if (ui->action1_bit->isChecked())
    {
        newPort->COM_SetStopBits(QSerialPort::OneStop);
    }
    else if (ui->action1_5_bits->isChecked())
    {
        newPort->COM_SetStopBits(QSerialPort::OneAndHalfStop);
    }
    else if (ui->action2_bits->isChecked())
    {
        newPort->COM_SetStopBits(QSerialPort::TwoStop);
    }
    if (ui->actionNone_2->isChecked())
    {
        newPort->COM_SetFlowControl(QSerialPort::NoFlowControl);
    }
    else if (ui->actionRTS_CTS->isChecked())
    {
        newPort->COM_SetFlowControl(QSerialPort::HardwareControl);
    }
    else if (ui->actionXON_XOFF->isChecked())
    {
        newPort->COM_SetFlowControl(QSerialPort::SoftwareControl);
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

        data_to_write = QString_To_QByteAray(ui->cEnterText->text(),false,NULL);

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

    data_to_write.append(QString_To_QByteAray(ui->cEnterText->text(), ui->CRC_OUT->isChecked(),oCRC16));

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
        if (ui->Cyclic->isChecked())
        {
            DataLogic->SEND_DATA(data_to_write,MANUAL_CYCLIC_SEND_CONTROL);
        }
        else
        {
            DataLogic->SEND_DATA(data_to_write,MANUAL_SEND_CONTROL);
        }
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
        newPort->COM_SetBaudRate(QSerialPort::Baud9600);
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
        newPort->COM_SetBaudRate(QSerialPort::Baud19200);
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
        newPort->COM_SetBaudRate(QSerialPort::Baud38400);
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
        newPort->COM_SetBaudRate(QSerialPort::Baud115200);
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
            newPort->COM_SetBaudRate(i);
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
        newPort->COM_SetDataBits(QSerialPort::Data5);
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
        newPort->COM_SetDataBits(QSerialPort::Data6);
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
        newPort->COM_SetDataBits(QSerialPort::Data7);
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
        newPort->COM_SetDataBits(QSerialPort::Data8);
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
        newPort->COM_SetParity(QSerialPort::NoParity);
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
        newPort->COM_SetParity(QSerialPort::EvenParity);
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
        newPort->COM_SetParity(QSerialPort::OddParity);
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
        newPort->COM_SetParity(QSerialPort::MarkParity);
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
        newPort->COM_SetParity(QSerialPort::SpaceParity);
    }
}

void MainWindow::on_action1_bit_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action1_bit->setChecked(true);
        ui->action1_5_bits->setChecked(false);
        ui->action2_bits->setChecked(false);
        newPort->COM_SetStopBits(QSerialPort::OneStop);
    }
}

void MainWindow::on_action1_5_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action1_bit->setChecked(false);
        ui->action1_5_bits->setChecked(true);
        ui->action2_bits->setChecked(false);
        newPort->COM_SetStopBits(QSerialPort::OneAndHalfStop);
    }
}

void MainWindow::on_action2_bits_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->action1_bit->setChecked(false);
        ui->action1_5_bits->setChecked(false);
        ui->action2_bits->setChecked(true);
        newPort->COM_SetStopBits(QSerialPort::TwoStop);
    }
}

void MainWindow::on_actionNone_2_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone_2->setChecked(true);
        ui->actionRTS_CTS->setChecked(false);
        ui->actionXON_XOFF->setChecked(false);
        newPort->COM_SetFlowControl(QSerialPort::NoFlowControl);
    }
}

void MainWindow::on_actionRTS_CTS_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone_2->setChecked(false);
        ui->actionRTS_CTS->setChecked(true);
        ui->actionXON_XOFF->setChecked(false);
        newPort->COM_SetFlowControl(QSerialPort::HardwareControl);
    }
}

void MainWindow::on_actionXON_XOFF_toggled(bool arg1)
{
    if (arg1 == true)
    {
        ui->actionNone_2->setChecked(false);
        ui->actionRTS_CTS->setChecked(false);
        ui->actionXON_XOFF->setChecked(true);
        newPort->COM_SetFlowControl(QSerialPort::SoftwareControl);
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

void MainWindow::on_LogShow_clicked()
{
    if (ui->LogWidget->maximumHeight() > 0)
    {
        ui->LogWidget->setMaximumHeight(0);
        this->setGeometry(this->geometry().x(),this->geometry().y(),this->geometry().width(),this->geometry().height()-200);
    }
    else
    {
        this->setGeometry(this->geometry().x(),this->geometry().y(),this->geometry().width(),this->geometry().height()+200);
        ui->LogWidget->setMaximumHeight(200);
    }
}

void MainWindow::on_RFParamWrite_clicked()
{
    emit WRITE_RF_PARAMS();
}

void MainWindow::on_RFSI4432_Write_clicked()
{
    emit WRITE_RFSI4432_PARAMS();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->ConnectionsWidget->maximumWidth() > 0)
    {
        HideConnectionPanel();
    }
    else
    {
        ShowConnectionPanel();
    }
}

void MainWindow::ShowConnectionPanel(void)
{
    ui->ConnectionsWidget->setMaximumWidth(175);
    timer_ConnectionsPanel->start(15000);
}
void MainWindow::HideConnectionPanel(void)
{
    if(timer_ConnectionsPanel->isActive())
    {
        timer_ConnectionsPanel->stop();
    }
    ui->ConnectionsWidget->setMaximumWidth(0);
}
void MainWindow::on_actionConn_triggered()
{
    if(ui->ConnectionsWidget->maximumWidth() > 0)
    {
        HideConnectionPanel();
    }
    else
    {
        ShowConnectionPanel();
    }
}

void MainWindow::on_OpenBin_clicked()
{
   QString str = QFileDialog::getOpenFileName(0, "Open File", "", "*.bin");
   ui->PatchBin->setText(str);
   newUPDATE->setPATCH(str);
}

void MainWindow::on_Add_NetItem_clicked()
{
    bool ok;
    int i = QInputDialog::getInt(this, QString::fromUtf8("Введите серийный номер"), QString::fromUtf8(""), 1, 1, 2147483647, 1, &ok);
    if (ok){
        emit ADD_NET_TABLE_ITEM(QString::number(i));
    }

}

void MainWindow::on_Del_NetItem_clicked()
{
    emit DEL_NET_TABLE_ITEM();
}

void MainWindow::on_NetTable_clicked(const QModelIndex &index)
{
    emit SET_CURR_INDEX((uchar)(index.row()+1));
}

void MainWindow::on_Del_NetTable_clicked()
{
    emit SEND_SWITCH_TABLE_DELETE();
}

void MainWindow::on_Read_NetTable_clicked()
{
    emit READ_SWITCH_TABLE();
}

void MainWindow::on_Write_NetTable_clicked()
{
    MODEM->setCurrent_Index(0);
    emit WRITE_SWITCH_TABLE();
}

void MainWindow::on_RF_Reset_clicked()
{
    emit SEND_RF_RESET();
}

void MainWindow::on_RF_RESET_clicked()
{
    emit SEND_RF_RESET();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    MODEM->SNIFER_MODE = index;
    emit SEND_SNIFER_MODE();
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        MODEM->UP_LINC = 0;
    }
    else
    {
        MODEM->UP_LINC = 1;
    }

    emit SEND_UPLINC_MODE();
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        MODEM->CRC_CHECK_DISABLE = 0;
    }
    else
    {
        MODEM->CRC_CHECK_DISABLE = 1;
    }
    emit SEND_CRC_DISABLE_MODE();
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        MODEM->BROADCAST = 0;
    }
    else
    {
        MODEM->BROADCAST = 1;
    }
    emit SEND_BROADCAST_MODE();
}

void MainWindow::on_SetNetLevel_clicked()
{
    emit SET_SWITCH_PROP();
}

void MainWindow::on_SetDeviceMonitorSN_clicked()
{
    int numb = ui->DeviceMonitorSN->text().toInt();
    if (numb > 0)
    {
        MODEM->clearNetTable();
        MODEM->addNewItem(ui->DeviceMonitorSN->text());
        emit WRITE_SWITCH_TABLE();
    }
    else
    {
        emit SEND_SWITCH_TABLE_DELETE();
    }
}

void MainWindow::on_DIV_DR_stateChanged(int arg1)
{
    if ((SI4432Config != NULL)&&(Class_init_state == 1))
    {
        if (arg1 == 0)
        {
            SI4432Config->RF22_SET_DivDR(0);
        }
        else
        {
            SI4432Config->RF22_SET_DivDR(1);
        }
    }
}

void MainWindow::on_FX2_stateChanged(int arg1)
{
    if ((SI4432Config != NULL)&&(Class_init_state == 1))
    {
        if (arg1 == 0)
        {
            unsigned int fnom    = SI4432Config->RF22_GET_NFREQ ();
            fnom /= 2;
            SI4432Config->RF22_SET_hb(0);
            SI4432Config->RF22_SET_NFREQ (fnom);
        }
        else
        {
            unsigned int fnom    = SI4432Config->RF22_GET_NFREQ ();
            fnom *= 2;
            SI4432Config->RF22_SET_hb(1);
            SI4432Config->RF22_SET_NFREQ (fnom);
        }
    }
}

void MainWindow::on_FCAR_currentIndexChanged(int index)
{
    if ((index >= 0)&&(SI4432Config != NULL)&&(Class_init_state == 1))
    {
        SI4432Config->RF22_SET_FC(index);
    }
}

void MainWindow::on_MT_currentIndexChanged(int index)
{
    if ((index >= 0)&&(SI4432Config != NULL)&&(Class_init_state == 1))
    {
        SI4432Config->RF22_SET_MT(index);
    }
}

void MainWindow::on_PA_currentIndexChanged(int index)
{
    if ((index >= 0)&&(SI4432Config != NULL)&&(Class_init_state == 1))
    {
        SI4432Config->RF22_SET_PA(index);
    }
}

void MainWindow::on_DR_valueChanged(int arg1)
{
    if ((SI4432Config != NULL)&&(Class_init_state == 1))
    {
        SI4432Config->RF22_SET_TXDR(arg1);
    }
}

void MainWindow::on_FOFF_valueChanged(int arg1)
{
    if ((SI4432Config != NULL)&&(Class_init_state == 1))
    {
       SI4432Config->RF22_SET_Fo(arg1);
    }
}

void MainWindow::on_DV_valueChanged(int arg1)
{
    if ((SI4432Config != NULL)&&(Class_init_state == 1))
    {
        SI4432Config->RF22_SET_Fd(arg1);
    }
}

void MainWindow::on_BW_currentIndexChanged(int index)
{
    if ((index >= 0)&&(SI4432Config != NULL)&&(Class_init_state == 1))
    {
        SI4432Config->RF22_SET_IFBW(index);
    }
}

void MainWindow::on_SNW_N_currentIndexChanged(int index)
{

}

void MainWindow::on_HEAD_N_currentIndexChanged(int index)
{

}


void MainWindow::on_FNOM_valueChanged(double arg1)
{
    if ((SI4432Config != NULL)&&(Class_init_state == 1))
    {
        int arg = (int)((arg1+0.0005)*1000);

        SI4432Config->RF22_SET_NFREQ (arg);
    }
}

void MainWindow::on_TCPConnect_clicked()
{
    newTCP->TCP_SetIP(ui->IPInput->text());
    newTCP->TCP_SetPORT(ui->PORTInput->text().toInt());
}

void MainWindow::on_LVL0_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL0 = arg1;

    if (arg1 > 0)
    {
        ui->LVL1_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL1_DIS->setEnabled(false); ui->LVL1_DIS->setValue(0);
        ui->LVL2_DIS->setEnabled(false); ui->LVL2_DIS->setValue(0);
        ui->LVL3_DIS->setEnabled(false); ui->LVL3_DIS->setValue(0);
        ui->LVL4_DIS->setEnabled(false); ui->LVL4_DIS->setValue(0);
        ui->LVL5_DIS->setEnabled(false); ui->LVL5_DIS->setValue(0);
        ui->LVL6_DIS->setEnabled(false); ui->LVL6_DIS->setValue(0);
        ui->LVL7_DIS->setEnabled(false); ui->LVL7_DIS->setValue(0);
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL1 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL2 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL3 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL1_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL1 = arg1;

    if (arg1 > 0)
    {
        ui->LVL2_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL2_DIS->setEnabled(false); ui->LVL2_DIS->setValue(0);
        ui->LVL3_DIS->setEnabled(false); ui->LVL3_DIS->setValue(0);
        ui->LVL4_DIS->setEnabled(false); ui->LVL4_DIS->setValue(0);
        ui->LVL5_DIS->setEnabled(false); ui->LVL5_DIS->setValue(0);
        ui->LVL6_DIS->setEnabled(false); ui->LVL6_DIS->setValue(0);
        ui->LVL7_DIS->setEnabled(false); ui->LVL7_DIS->setValue(0);
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL2 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL3 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL2_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL2 = arg1;

    if (arg1 > 0)
    {
        ui->LVL3_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL3_DIS->setEnabled(false); ui->LVL3_DIS->setValue(0);
        ui->LVL4_DIS->setEnabled(false); ui->LVL4_DIS->setValue(0);
        ui->LVL5_DIS->setEnabled(false); ui->LVL5_DIS->setValue(0);
        ui->LVL6_DIS->setEnabled(false); ui->LVL6_DIS->setValue(0);
        ui->LVL7_DIS->setEnabled(false); ui->LVL7_DIS->setValue(0);
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL3 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL3_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL3 = arg1;

    if (arg1 > 0)
    {
        ui->LVL4_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL4_DIS->setEnabled(false); ui->LVL4_DIS->setValue(0);
        ui->LVL5_DIS->setEnabled(false); ui->LVL5_DIS->setValue(0);
        ui->LVL6_DIS->setEnabled(false); ui->LVL6_DIS->setValue(0);
        ui->LVL7_DIS->setEnabled(false); ui->LVL7_DIS->setValue(0);
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL4_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL4 = arg1;

    if (arg1 > 0)
    {
        ui->LVL5_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL5_DIS->setEnabled(false); ui->LVL5_DIS->setValue(0);
        ui->LVL6_DIS->setEnabled(false); ui->LVL6_DIS->setValue(0);
        ui->LVL7_DIS->setEnabled(false); ui->LVL7_DIS->setValue(0);
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL5_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL5 = arg1;

    if (arg1 > 0)
    {
        ui->LVL6_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL6_DIS->setEnabled(false); ui->LVL6_DIS->setValue(0);
        ui->LVL7_DIS->setEnabled(false); ui->LVL7_DIS->setValue(0);
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL6_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL6 = arg1;

    if (arg1 > 0)
    {
        ui->LVL7_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL7_DIS->setEnabled(false); ui->LVL7_DIS->setValue(0);
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL7_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL7 = arg1;

    if (arg1 > 0)
    {
        ui->LVL8_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL8_DIS->setEnabled(false); ui->LVL8_DIS->setValue(0);
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL8_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_0.Field.LVL8 = arg1;

    if (arg1 > 0)
    {
        ui->LVL9_DIS->setEnabled(true);
    }
    else
    {
        ui->LVL9_DIS->setEnabled(false); ui->LVL9_DIS->setValue(0);

        MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_LVL9_DIS_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK_DESTINATION->Field.Retranslation_MASK_1.Field.LVL9 = arg1;
    ui->NetDestination->setText(QString::number(*(unsigned int*)(MODEM->SWITCH_MASK_DESTINATION)));
}

void MainWindow::on_SetDestinationMASK_clicked()
{
    emit WRITE_MASK_DESTINATION();
}

void MainWindow::on_LVL0_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL0 = arg1;
    if (arg1 > 0)
    {
        ui->LVL1->setEnabled(true);
    }
    else
    {
        ui->LVL1->setEnabled(false); ui->LVL1->setValue(0);
        ui->LVL2->setEnabled(false); ui->LVL2->setValue(0);
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL1 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL2 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL3 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL1_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL1 = arg1;
    if (arg1 > 0)
    {
        ui->LVL2->setEnabled(true);
    }
    else
    {
        ui->LVL2->setEnabled(false); ui->LVL2->setValue(0);
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL2 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL3 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL2_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL2 = arg1;
    if (arg1 > 0)
    {
        ui->LVL3->setEnabled(true);
    }
    else
    {
        ui->LVL3->setEnabled(false); ui->LVL3->setValue(0);
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL3 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL3_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL3 = arg1;
    if (arg1 > 0)
    {
        ui->LVL4->setEnabled(true);
    }
    else
    {
        ui->LVL4->setEnabled(false); ui->LVL4->setValue(0);
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL4 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL4_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL4 = arg1;
    if (arg1 > 0)
    {
        ui->LVL5->setEnabled(true);
    }
    else
    {
        ui->LVL5->setEnabled(false); ui->LVL5->setValue(0);
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL5 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL5_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL5 = arg1;
    if (arg1 > 0)
    {
        ui->LVL6->setEnabled(true);
    }
    else
    {
        ui->LVL6->setEnabled(false); ui->LVL6->setValue(0);
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL6_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL6 = arg1;
    if (arg1 > 0)
    {
        ui->LVL7->setEnabled(true);
    }
    else
    {
        ui->LVL7->setEnabled(false); ui->LVL7->setValue(0);
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = 0;
        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL7_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL7 = arg1;
    if (arg1 > 0)
    {
        ui->LVL8->setEnabled(true);
    }
    else
    {
        ui->LVL8->setEnabled(false); ui->LVL8->setValue(0);
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = 0;

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL8_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_0.Field.LVL8 = arg1;
    if (arg1 > 0)
    {
        ui->LVL9->setEnabled(true);
    }
    else
    {
        ui->LVL9->setEnabled(false); ui->LVL9->setValue(0);

        MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = 0;
    }
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_LVL9_valueChanged(int arg1)
{
    MODEM->SWITCH_MASK->Field.Retranslation_MASK_1.Field.LVL9 = arg1;
    MODEM->setSWITCH_LEVEL(*(unsigned int*)(MODEM->SWITCH_MASK));
    ui->SWITCHLVL->setText(QString::number(MODEM->getSWITCH_LEVEL()));
}

void MainWindow::on_SWITCH_clicked()
{
    emit SET_SWITCH_MODE();
}

void MainWindow::on_UPDATE_START_clicked()
{
    emit START_UPDATE();
}

void MainWindow::on_CLEAR_clicked()
{
    emit START_DELETE();
}

void MainWindow::on_TCPDisconnect_clicked()
{

}
