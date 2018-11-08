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
#include <QTimer>
#include "TCP/tcp.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsLinearLayout>

#include "BUTTONS_HANDLERS/connecthandlerclass.h"
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
#include "settings_form.h"
#include "hands_enter_form.h"
#include "open_connection_form.h"
#include "net_settings_form.h"

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

    void Set_ActiveConsole(QPlainTextEdit*);

    void Create_And_Show_Net_Settings_Form(void);

    void Create_And_Show_Settings_Form(void);

    void Create_And_Show_Hands_Enter_Form(void);

    void Create_And_Show_Open_Connection_Form(void);

    void on_TCPConnect_clicked();

    void on_PortNameBox_currentIndexChanged(const QString &arg1);

    void on_COMConnect_clicked();

private:
    Ui::Connections_Form *ui;

    QPlainTextEdit         *ActiveConsole;

    Settings_Form          *settings_form;
    Hands_Enter_Form       *hands_enter_form;
    Open_Connection_Form   *open_connection_form;
    Net_Settings_Form      *net_settings_form;

    QSysInfo               *SysInfo;
    QRegExp                 RegSystemName;

};

#endif // CONNECTIONS_FORM_H
