#ifndef HANDS_ENTER_FORM_H
#define HANDS_ENTER_FORM_H

#include <QWidget>
#include <QScreen>
#include <QSettings>
#include <QPlainTextEdit>
#include "myformabstractclass.h"
#include "ui_hands_enter_form.h"
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"
#include "CRC/crc16_class.h"

#define  MANUAL_SETTINGS_SN_ENABLE          "Manual_Settings/SN_ENABLE"
#define  MANUAL_SETTINGS_SN                 "Manual_Settings/SN"
#define  MANUAL_SETTINGS_MESSAGE            "Manual_Settings/MESSAGE"

//namespace Ui {
//class Hands_Enter_Form;
//}

class Hands_Enter_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Hands_Enter_Form(QWidget *parent = 0);
    ~Hands_Enter_Form();
    void resizeEvent(QResizeEvent *event);

signals:
    void Send_Data(QByteArray,uint);

public slots:
    void ForceClose(void);

private slots:
    void on_Back_clicked();
    void on_cBtnSend_clicked();
    void on_SN_ENABLE_stateChanged(int arg1);
    void on_btnSettings_clicked();

private:
    Ui::Hands_Enter_Form *ui;
    QSysInfo             *SysInfo;
    QRegExp               RegSystemName;

    CRC16_Class          *oCRC16;
    ResizeCalculating     resize_calculating;
};

#endif // HANDS_ENTER_FORM_H
