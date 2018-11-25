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

    myGraphScene * scene;

    myPoligon *pRSSICurrent, *pAFC ,*pRSSI;
    QPolygonF pfRSSICurrent, pfAFC, pfRSSI;

    char Class_init_state;

    double x_coord;

signals:
    void AOPEN();
    void SET_SWITCH_MODE();
    void SET_SWITCH_PROP();
    void START_MONITOR();
    void STOP_MONITOR();
    void READ_CURRENT_RSSI();
    void READ_LRSSI_AFC();
    void WRITE_RF_PARAMS();
    void WRITE_RFSI4432_PARAMS();
    void SEND_RF_RESET();
    void SEND_SNIFER_MODE();
    void SEND_UPLINC_MODE();
    void SEND_CRC_DISABLE_MODE();
    void SEND_BROADCAST_MODE();
    void WRITE_SWITCH_TABLE();
    void SEND_SWITCH_TABLE_DELETE();
    void READ_SWITCH_TABLE();
    void WRITE_MASK_DESTINATION();
    void START_UPDATE();
    void START_DELETE();

    void ADD_NET_TABLE_ITEM(QString value);
    void DEL_NET_TABLE_ITEM();
    void SET_CURR_INDEX(uchar index);

private slots:
    void ShowConnectionPanel(void);
    void HideConnectionPanel(void);
    void Print(QByteArray data, uint n);
    void Print_Log(QString data, uint n);
    void ParceFinishHandler();

    void on_PortNameBox_currentIndexChanged(const QString &arg1);
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
    void on_LogShow_clicked();
    void on_readCurrentRSSI_clicked();
    void on_readLatchRSSI_clicked();
    void on_RFParamWrite_clicked();
    void on_pushButton_3_clicked();
    void on_actionConn_triggered();
    void on_OpenBin_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_5_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_SetNetLevel_clicked();
    void on_SetDeviceMonitorSN_clicked();
    void on_DIV_DR_stateChanged(int arg1);
    void on_FX2_stateChanged(int arg1);
    void on_FCAR_currentIndexChanged(int index);
    void on_MT_currentIndexChanged(int index);
    void on_PA_currentIndexChanged(int index);
    void on_DR_valueChanged(int arg1);
    void on_FOFF_valueChanged(int arg1);
    void on_DV_valueChanged(int arg1);
    void on_BW_currentIndexChanged(int index);
    void on_SNW_N_currentIndexChanged(int index);
    void on_HEAD_N_currentIndexChanged(int index);
    void on_RFSI4432_Write_clicked();
    void on_RF_RESET_clicked();
    void on_FNOM_valueChanged(double arg1);
    void on_TCPConnect_clicked();
    void on_NetTable_clicked(const QModelIndex &index);
    void on_Add_NetItem_clicked();
    void on_Del_NetItem_clicked();
    void on_RF_Reset_clicked();
    void on_Del_NetTable_clicked();
    void on_Read_NetTable_clicked();
    void on_Write_NetTable_clicked();

    void on_LVL0_DIS_valueChanged(int arg1);

    void on_LVL1_DIS_valueChanged(int arg1);

    void on_LVL2_DIS_valueChanged(int arg1);

    void on_LVL3_DIS_valueChanged(int arg1);

    void on_LVL4_DIS_valueChanged(int arg1);

    void on_LVL5_DIS_valueChanged(int arg1);

    void on_LVL6_DIS_valueChanged(int arg1);

    void on_LVL7_DIS_valueChanged(int arg1);

    void on_LVL8_DIS_valueChanged(int arg1);

    void on_LVL9_DIS_valueChanged(int arg1);

    void on_SetDestinationMASK_clicked();

    void on_LVL0_valueChanged(int arg1);

    void on_LVL1_valueChanged(int arg1);

    void on_LVL2_valueChanged(int arg1);

    void on_LVL3_valueChanged(int arg1);

    void on_LVL4_valueChanged(int arg1);

    void on_LVL5_valueChanged(int arg1);

    void on_LVL6_valueChanged(int arg1);

    void on_LVL7_valueChanged(int arg1);

    void on_LVL8_valueChanged(int arg1);

    void on_LVL9_valueChanged(int arg1);

    void on_SWITCH_clicked();

    void on_UPDATE_START_clicked();

    void on_CLEAR_clicked();

    void on_TCPDisconnect_clicked();

    void on_SN_ENABLE_stateChanged(int arg1);

protected:
    //virtual void mousePressEvent(QMouseEvent *);
    virtual bool eventFilter(QObject *target, QEvent *event);
    void showEvent ( QShowEvent * event );
    void resizeEvent ( QResizeEvent * event );

};
#endif // MAINWINDOW_H
