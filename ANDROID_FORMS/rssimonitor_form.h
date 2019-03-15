#ifndef RSSIMONITOR_FORM_H
#define RSSIMONITOR_FORM_H

#include <QWidget>
#include <QScreen>
#include <QScrollBar>
#include <QSettings>
#include <QPlainTextEdit>
#include "ui_rssimonitor_form.h"
#include "myformabstractclass.h"
#include "MODEM/firmwareinformationclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "GRAPH/mygraphscene.h"
#include "GRAPH/mypoligon.h"
#include "FILTER/filter.h"
#include "STYLE/style.h"

#define CONNECTION_SETTINGS_INTERFACE   "Connection_Settings/INTERFACE"
#define CONNECTION_SETTINGS_SN          "Connection_Settings/SN"
#define CONNECTION_SETTINGS_MODULE_TYPE "Connection_Settings/MODULE_TYPE"

enum{
    RSSI_MODE_FORM = 0,
    PGA_MODE_FORM
};

//namespace Ui {
//class RSSIMonitor_Form;
//}

class RSSIMonitor_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit RSSIMonitor_Form(uchar Mode, QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~RSSIMonitor_Form();

signals:
    //void Updating(QWidget*);
    void SendSerialNumber(QString, bool);
    void SendModuleType(uchar);
    void SendInterface(uchar);
    void ClearAllData(void);
    void SendReadLatchRSSI_AFC();
    void StartRSSIMonitor(uint Message);
    void StopRSSIMonitor();

public slots:
    void ForceClose(void);
    void isStopped(void);
    void isRF_Reset(void);
    void RSSI_RequestSended(void);
    void isLatchRSSI_AFC(signed short RSSI,signed short ANT1_RSSI,signed short ANT2_RSSI,double AFC);
    void isLatchPGA(signed short Received_Power,double PGA_Value);

    void Set_ConnectionType(uchar);

private slots:
    void on_Back_clicked();
    void on_Next_clicked();
    void on_Stop_clicked();
    void on_btnSettings_clicked();
    void on_Reset_clicked();
    void on_Interface_currentIndexChanged(int index);
    void on_ModuleType_currentIndexChanged(int index);
    void on_readLatchRSSI_clicked();
    void on_MonitorStart_clicked();
    void on_SN_editTextChanged(const QString &arg1);
    void on_ClearConsole_clicked();

    void SetRSSILvlToUI(int);
    void SetRSSIANT1ToUI(int);
    void SetRSSIANT2ToUI(int);
    void SetAFCToUI(int);
    void SetReseivedPowerToUI(int);
    void SetPGA_ValueToUI(int);
    void SetMsgCounterToUI(int);
    void SetYesAnswerToUI(int);
    void SetNoAnswerToUI(int);
    void SetAValueUI(int);
    void Clear_Form(void);


private:
    Ui::RSSIMonitor_Form     *ui;
    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;
    ResizeCalculating         resize_calculating;
    uchar                     Monitor_running;

    myGraphScene             *scene;
    Filter                   *newFilter;

    myPoligon *pRSSICurrent, *pAFC ,*pRSSI;
    QPolygonF pfRSSICurrent, pfAFC, pfRSSI;

    uchar                     RSSI_RequestAnswerDetector;
    uchar                     ConnectionType;

    uchar                     Mode_Form;
};

#endif // RSSIMONITOR_FORM_H
