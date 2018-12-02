#ifndef OPEN_CONNECTION_FORM_H
#define OPEN_CONNECTION_FORM_H

#include <QWidget>
#include <QScreen>
#include <QScrollBar>
#include <QSettings>
#include <QPlainTextEdit>
#include "MODEM/firmwareinformationclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

#define CONNECTION_SETTINGS_INTERFACE   "Connection_Settings/INTERFACE"
#define CONNECTION_SETTINGS_SN          "Connection_Settings/SN"

namespace Ui {
class Open_Connection_Form;
}

class Open_Connection_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Open_Connection_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~Open_Connection_Form();

public slots:
    void SetProgress(uint progress);
    void isOPEND(void);
    void isRESET(void);
    void isSTOPPED(void);
    void Set_Geometry(QRect);
    void Set_In_Firmware_Information(FirmwareInformationClass*);

signals:
    void Cancel(void);
    void Next(QRect);
    void Settings(QWidget*);
    void Updating(QWidget*);
    void Get_Geometry(QRect);
    void Get_Console(QPlainTextEdit* console);
    void SendSerialNumber(QString, bool);
    void ClearAllData(void);
    void AOPEN(void);
    void SEND_RF_RESET(void);

    void STOP_MONITOR(void);
    void STOP_SEND_DATA(void);

private slots:
    void on_Back_clicked();

    void on_Interface_currentIndexChanged(int index);

    void on_Connect_clicked();

    void on_Next_clicked();

    void Clear_Form(void);

    void on_Stop_clicked();

    void on_btnSettings_clicked();

    void on_Reset_clicked();

    void on_Update_clicked();

    void SetCurrentFitmwareToUI(uchar);
    void SetBootloaderVersionToUI(QString);
    void SetBootloaderSizeToUI(uint);
    void SetBootloaderCRCToUI(QByteArray);
    void SetUpgradableVersionToUI(QString);
    void SetUpgradableSizeToUI(uint);
    void SetUpgradableCRCToUI(QByteArray);
    void SetDeviceNameToUI(QString);

private:
    Ui::Open_Connection_Form *ui;
    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;

    FirmwareInformationClass *In_Firmware_Information;
    ResizeCalculating         resize_calculating;
};

#endif // OPEN_CONNECTION_FORM_H
