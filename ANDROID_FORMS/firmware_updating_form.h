#ifndef FIRMWARE_UPDATING_FORM_H
#define FIRMWARE_UPDATING_FORM_H

#include <QWidget>
#include <QScreen>
#include <QScrollBar>
#include <QSettings>
#include <QPlainTextEdit>
#include "MODEM/firmwareinformationclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

namespace Ui {
class Firmware_Updating_Form;
}

class Firmware_Updating_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Firmware_Updating_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~Firmware_Updating_Form();

public slots:
    void isStopped(void);
    void isDeleted(void);
    void isUpdated(void);
    void SetProgress(uint progress);
    void Set_Geometry(QRect);

    void Set_In_Firmware_Information(FirmwareInformationClass *FirmwareInformation);
signals:
    void Cancel(void);
    void isCreated(void);
    void Next(QRect);
    void Settings(QWidget*);
    void Get_Geometry(QRect);
    void Get_Console(QPlainTextEdit* console);
    void Get_FirmwareData(QString,QByteArray);

    void Stop_Send_Data(void);
    void Start_Delete(void);
    void Start_Update(void);

private slots:
    void SetUpgradableVersionToUI(QString);
    void SetUpgradableSizeToUI(uint);
    void SetUpgradableCRCToUI(QByteArray);

    void on_Back_clicked();

    void on_btnSettings_clicked();

    void on_Stop_clicked();

    void on_OpenBin_clicked();

    void on_Clear_clicked();

    void on_UpdateStart_clicked();

private:
    Ui::Firmware_Updating_Form *ui;
    QSysInfo                   *SysInfo;
    QRegExp                     RegSystemName;

    ResizeCalculating           resize_calculating;
    FirmwareInformationClass   *In_Firmware_Information;
};

#endif // FIRMWARE_UPDATING_FORM_H
