#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H

#include <QWidget>
#include "ui_settings_form.h"
#include "myformabstractclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

#define CONNECTION_SETTINGS_REPEATE   "Connection_Settings/REPEATE"
#define CONNECTION_SETTINGS_PERIODE   "Connection_Settings/PERIODE"

//namespace Ui {
//class Settings_Form;
//}

class Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Settings_Form(QWidget *parent = 0);
    ~Settings_Form();
    void resizeEvent(QResizeEvent *event);
signals:
    void GetRepeatNumber(uint value);
    void GetRepeatTimeout(uint value);

public slots:

private slots:
    void on_Back_clicked();
    void on_Apply_clicked();
    void on_RepeatSlider_valueChanged(int value);
    void on_PeriodeSlider_valueChanged(int value);
    void on_Repeat_valueChanged(int arg1);
    void on_Periode_valueChanged(int arg1);

private:
    Ui::Settings_Form *ui;

    QSysInfo          *SysInfo;
    QRegExp            RegSystemName;
    ResizeCalculating  resize_calculating;
};

#endif // SETTINGS_FORM_H
