#ifndef OPEN_CONNECTION_FORM_H
#define OPEN_CONNECTION_FORM_H

#include "ui_open_connection_form.h"
#include "myformabstractclass.h"

#define CONNECTION_SETTINGS_INTERFACE   "Connection_Settings/INTERFACE"
#define CONNECTION_SETTINGS_SN          "Connection_Settings/SN"
#define CONNECTION_SETTINGS_MODULE_TYPE "Connection_Settings/MODULE_TYPE"

//namespace Ui {
//class Open_Connection_Form;
//}

class Open_Connection_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Open_Connection_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~Open_Connection_Form();

signals:
    void Updating(QWidget*);
    void SendSerialNumber(QString, bool);
    void SendModuleType(uchar);
    void SendInterface(uchar);
    void ClearAllData(void);

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

    void isOPEND(void);
    void isStopped(void);
    void isRF_Reset(void);

    void Set_In_Firmware_Information(FirmwareInformationClass *FirmwareInformation);

private slots:
    void on_Back_clicked();
    void on_Interface_currentIndexChanged(int index);
    void on_Connect_clicked();
    void on_Next_clicked();
    void on_Stop_clicked();
    void on_btnSettings_clicked();
    void on_Reset_clicked();
    void on_Update_clicked();
    void on_ClearConsole_clicked();

    void SetCurrentFitmwareToUI(uchar);
    void SetBootloaderVersionToUI(QString);
    void SetBootloaderSizeToUI(uint);
    void SetBootloaderCRCToUI(QByteArray);
    void SetUpgradableVersionToUI(QString);
    void SetUpgradableSizeToUI(uint);
    void SetUpgradableCRCToUI(QByteArray);
    void SetDeviceNameToUI(QString);

    void Clear_Form(void);

    void on_ModuleType_currentIndexChanged(int index);

    void on_SN_editTextChanged(const QString &arg1);

private:
    Ui::Open_Connection_Form *ui;
    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;
    ResizeCalculating         resize_calculating;

};

#endif // OPEN_CONNECTION_FORM_H
