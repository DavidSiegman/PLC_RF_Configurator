#ifndef CONNECTIONS_FORM_H
#define CONNECTIONS_FORM_H

#include <QWidget>
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
#include <mess_enum.h>
#include "settings_form.h"
#include "hands_enter_form.h"

namespace Ui {
class Connections_Form;
}

class Connections_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Connections_Form(QWidget *parent = 0);
    ~Connections_Form();

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

    void Set_ActiveConsole(QPlainTextEdit*);

    void on_TCPConnect_clicked();

    void on_btnSettings_clicked();

    void on_btnHandsEnter_clicked();

private:
    Ui::Connections_Form *ui;

    QPlainTextEdit   *ActiveConsole;

    Settings_Form    *settings_form;
    Hands_Enter_Form *hands_enter_form;
};

#endif // CONNECTIONS_FORM_H
