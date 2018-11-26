#ifndef FIRMWARE_UPDATING_FORM_H
#define FIRMWARE_UPDATING_FORM_H

#include <QWidget>
#include <QScreen>
#include <QScrollBar>
#include <QSettings>
#include <QPlainTextEdit>
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
    void SetProgress(uint progress);
    void isSTOPPED(void);
    void Set_Geometry(QRect);

signals:
    void Cancel(void);
    void Next(QRect);
    void Settings(QWidget*);
    void Get_Geometry(QRect);
    void Get_Console(QPlainTextEdit* console);

    void STOP_SEND_DATA(void );
    void STOP_MONITOR(void);

private slots:
    void on_Back_clicked();

    void on_btnSettings_clicked();

    void on_Stop_clicked();

    void on_OpenBin_clicked();

private:
    Ui::Firmware_Updating_Form *ui;
    QSysInfo                   *SysInfo;
    QRegExp                     RegSystemName;

    ResizeCalculating           resize_calculating;
};

#endif // FIRMWARE_UPDATING_FORM_H
