#ifndef FIRMWARE_UPDATING_FORM_H
#define FIRMWARE_UPDATING_FORM_H

#include <QWidget>
#include <QScreen>
#include <QScrollBar>
#include <QSettings>
#include <QPlainTextEdit>
#include "myformabstractclass.h"
#include "ui_firmware_updating_form.h"
#include "MODEM/firmwareinformationclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

#define FIRMWARE_BIN_PATH      "FIRMWARE_BIN/Path"

//namespace Ui {
//class Firmware_Updating_Form;
//}

class Firmware_Updating_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Firmware_Updating_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~Firmware_Updating_Form();

signals:
    void Get_FirmwareData(QString,QByteArray);

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

    void isStopped(void);
    void isDeleted(void);
    void isUpdated(void);

    void Set_In_Firmware_Information(FirmwareInformationClass *FirmwareInformation);

private slots:
    void on_Back_clicked();
    void on_btnSettings_clicked();
    void on_Stop_clicked();
    void on_OpenBin_clicked();
    void on_Clear_clicked();
    void on_UpdateStart_clicked();
    void on_ClearConsole_clicked();

    void SetUpgradableVersionToUI(QString);
    void SetUpgradableSizeToUI(uint);
    void SetUpgradableCRCToUI(QByteArray);

private:
    Ui::Firmware_Updating_Form *ui;
    QSysInfo                   *SysInfo;
    QRegExp                     RegSystemName;

    ResizeCalculating           resize_calculating;
    FirmwareInformationClass   *In_Firmware_Information;
};

#endif // FIRMWARE_UPDATING_FORM_H
