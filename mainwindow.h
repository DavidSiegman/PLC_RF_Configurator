#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QTextCodec>
#include <QTimer>
#include "TCP/tcp.h"

#include <QGraphicsLinearLayout>

#include "BUTTONS_HANDLERS/connecthandlerclass.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "SI4463/si4463_propertys_tablemodel.h"
#include "COM/port.h"
#include "MODEM/modemclass.h"
#include "CRC/crc16_class.h"
#include "GRAPH/mygraphscene.h"
#include "GRAPH/mypoligon.h"
#include <mess_enum.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    SI4463Class         *SI4463Config;                             //
    QTimer              *timer_COMBufferClear;       //
    Port                *PortNew;                                  //
    DataLogic_Class     *DataLogic;                                //
    CRC16_Class         *oCRC16;                                   //
    ConnectHandlerClass *ConnectHandler;
    MODEMClass          *MODEM;
    TCP                 *TCPNew;
    QString QByteAray_To_QString(QByteArray arr);
    QByteArray QString_To_QByteAray(QString str, bool crc);

    myGraphScene * scene;

    myPoligon *pRSSICurrent, *pAFC ,*pRSSI;
    QPolygonF pfRSSICurrent, pfAFC, pfRSSI;

    double x;

signals:
    void AOPEN();
    void SET_SWITCH_MODE();
    void SET_SWITCH_PROP();
    void START_MONITOR();
    void STOP_MONITOR();
    void READ_CURRENT_RSSI();
    void READ_LRSSI_AFC();

private slots:
    void Print(QByteArray data, uint n);
    void Print_Log(QString data, uint n);

    void on_PortNameBox_currentIndexChanged(const QString &arg1);

    // COM Настройки
    void on_action9600_toggled(bool arg1);
    void on_action19200_toggled(bool arg1);
    void on_action38400_toggled(bool arg1);
    void on_action115200_toggled(bool arg1);
    void on_actionCustom_triggered();
    void on_action5_bits_toggled(bool arg1);
    void on_action6_bits_toggled(bool arg1);
    void on_action7_bits_toggled(bool arg1);
    void on_action8_bits_toggled(bool arg1);
    void on_actionNone_toggled(bool arg1);
    void on_actionEven_toggled(bool arg1);
    void on_actionOdd_toggled(bool arg1);
    void on_actionMark_toggled(bool arg1);
    void on_actionSpace_toggled(bool arg1);
    void on_action1_bit_toggled(bool arg1);
    void on_action1_5_bits_toggled(bool arg1);
    void on_action2_bits_toggled(bool arg1);
    void on_actionNone_2_toggled(bool arg1);
    void on_actionRTS_CTS_toggled(bool arg1);
    void on_actionXON_XOFF_toggled(bool arg1);
    void on_action10000_toggled(bool arg1);
    void on_action8000_toggled(bool arg1);
    void on_action6000_toggled(bool arg1);
    void on_action4000_toggled(bool arg1);
    void on_action2000_toggled(bool arg1);
    void on_action1000_toggled(bool arg1);
    void on_action_Pm_triggered();

    void on_FileOpen_clicked();
    void start_COM_Init(void);
    void on_CRC_OUT_toggled(bool checked);
    void out_Current_RSSI(signed short RSSI);
    void out_LRSSI_AFC(signed short RSSI,signed short ANT1_RSSI,signed short ANT2_RSSI,double AFC);
    void on_SN_ENABLE_toggled(bool checked);
    void on_Connect_clicked();
    void on_cBtnSend_clicked();
    void on_Interface_currentIndexChanged(int index);

    void on_action10_toggled(bool arg1);

    void on_action8_toggled(bool arg1);

    void on_action6_toggled(bool arg1);

    void on_action4_toggled(bool arg1);

    void on_action2_toggled(bool arg1);

    void on_action1_toggled(bool arg1);

    void on_action_Nm_triggered();

    void on_SWITCH_stateChanged(int arg1);

    void on_SWITCH_PROPS_clicked();

    void on_MonitorStart_clicked();

    void on_MonitorStop_clicked();

    void on_MonitorTimeout_clicked();

    void on_pushButton_clicked();

    void on_logHidden_clicked();

    void on_LogShow_clicked();

    void on_readCurrentRSSI_clicked();

    void on_readLatchRSSI_clicked();

    void on_TCPConnect_clicked();

protected:
    //virtual void mousePressEvent(QMouseEvent *);
    virtual bool eventFilter(QObject *target, QEvent *event);
    void showEvent ( QShowEvent * event );
    void resizeEvent ( QResizeEvent * event );

};
#endif // MAINWINDOW_H
