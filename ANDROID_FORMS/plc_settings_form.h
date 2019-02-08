#ifndef PLC_SETTINGS_FORM_H
#define PLC_SETTINGS_FORM_H

#include <QWidget>
#include <QScreen>
#include <QScrollBar>
#include <QSettings>
#include <QPlainTextEdit>
#include "myformabstractclass.h"
#include "ui_plc_settings_form.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

//namespace Ui {
//class PLC_Settings_Form;
//}

class PLC_Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit PLC_Settings_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~PLC_Settings_Form();

signals:

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

private slots:
    void on_Back_clicked();
    void on_Next_clicked();

    void on_Stop_clicked();

    void on_Reset_clicked();

    void on_btnSettings_clicked();

    void on_Write_clicked();

private:
    Ui::PLC_Settings_Form *ui;
    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;
    ResizeCalculating         resize_calculating;
};

#endif // PLC_SETTINGS_FORM_H
