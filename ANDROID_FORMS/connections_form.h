#ifndef CONNECTIONS_FORM_H
#define CONNECTIONS_FORM_H

#include <QSysInfo>
#include <QWidget>
#include <QScreen>
#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextCodec>
#include <QScrollBar>
#include <QSettings>
#include <QTimer>
#include "TCP/tcp.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsLinearLayout>

#include "CONNECT_HANDLER/connecthandlerclass.h"
#include "SI4463/si4463_propertys_tablemodel.h"
#include "SI4432/si4432class.h"
#include "FILE/parceclass.h"
#include "COM/port.h"
#include "PLC/plcclass.h"
#include "MODEM/modemclass.h"
#include "CRC/crc16_class.h"
#include "GRAPH/mygraphscene.h"
#include "GRAPH/mypoligon.h"
#include "FILTER/filter.h"
#include "UPDATE/update.h"
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

#include "settings_form.h"
#include "hands_enter_form.h"
#include "open_connection_form.h"
#include "net_settings_form.h"
#include "sniffer_settings_form.h"
#include "si4432_settings_form.h"
#include "si4463_settings_form.h"
#include "firmware_updating_form.h"
#include "retranslation_table_form.h"
#include "si4463_registers_form.h"

/* Defining */
#define ORGANIZATION_NAME "MILANDR"
#define ORGANIZATION_DOMAIN "www.milandr.ru"
#define APPLICATION_NAME "RF-PLC Configurator"

#define TCP_SETTINGS_IP                 "TCP_Settings/IP"
#define TCP_SETTINGS_PORT               "TCP_Settings/PORT"

namespace Ui {
class Connections_Form;
}

class Connections_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Connections_Form(QWidget *parent = 0);
    ~Connections_Form();
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *target, QEvent *event);

    SI4463Class         *SI4463Config;                                     //
    SI4432Class         *SI4432Config;                                     //
    PLCClass            *PLCConfig;                                        //
    QTimer              *timer_COMBufferClear, *timer_ConnectionsPanel;    //
    Port                *newPort;                                          //
    DataLogic_Class     *DataLogic;                                        //
    CRC16_Class         *oCRC16;                                           //
    ConnectHandlerClass *ConnectHandler;
    MODEMClass          *MODEM;
    TCP                 *newTCP;
    ParceClass          *newParcer;
    Filter              *newFilter;
    UPDATE              *newUPDATE;

private slots:
    void Print    (QByteArray data, uint n);
    void Print_Log(QString    data, uint n);
    void start_COM_Init();
    void TCP_IsConnected(void);
    void COM_IsOpend(void);
    void TCP_IsDisconnected(void);
    void COM_IsClosed(void);
    void COM_Error(void);
    void TCP_Error(void);
    void Set_Geometry(QRect);
    void Set_ActiveConsole(QPlainTextEdit*);
    void Start_Parcer(QString);
    void Define_Next_Form(QRect);
    void Define_Pre_Form(QRect);
    void RF_Reset_Handler(void);

    void Create_And_Show_Settings_Form(QWidget*);
    void Create_And_Show_Hands_Enter_Form(QWidget*);
    void Create_And_Show_Open_Connection_Form(void);
    void Create_And_Show_Net_Settings_Form(QRect);
    void Create_And_Show_Sniffer_Settings_Form(QRect);
    void Create_And_Show_SI4432_Settings_Form(QRect);
    void Create_And_Show_SI4463_Settings_Form(QRect);
    void Create_And_Show_Firmware_Updating_Form(QWidget*);
    void Create_And_Show_Retranslation_Table_Form(QWidget*);
    void Create_And_Show_SI4463_Registers_Form(QWidget*);
    void on_TCPConnect_clicked();
    void on_PortNameBox_currentIndexChanged(const QString &arg1);
    void on_COMConnect_clicked();
    void on_btnSettings_clicked();
    void on_btnHandsEnter_clicked();
private:
    Ui::Connections_Form     *ui;

    QPlainTextEdit           *ActiveConsole;

    Settings_Form            *settings_form;
    Hands_Enter_Form         *hands_enter_form;
    Open_Connection_Form     *open_connection_form;
    Net_Settings_Form        *net_settings_form;
    Sniffer_Settings_Form    *sniffer_settings_form;
    SI4432_Settings_Form     *si4432_settings_form;
    SI4463_Settings_Form     *si4463_settings_form;
    SI4463_Registers_Form    *si4463_registers_form;
    Firmware_Updating_Form   *firmware_updating_form;
    Retranslation_Table_Form *retranslation_table_form;

    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;

    ResizeCalculating         resize_calculating;
};

#endif // CONNECTIONS_FORM_H
