#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H

#include <QWidget>
#include "RESIZE_CALCULATING/resizecalculating.h"

#define CONNECTION_SETTINGS_REPEATE   "Connection_Settings/REPEATE"
#define CONNECTION_SETTINGS_PERIODE   "Connection_Settings/PERIODE"

namespace Ui {
class Settings_Form;
}

class Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Settings_Form(QWidget *parent = 0);
    ~Settings_Form();
    void resizeEvent(QResizeEvent *event);
signals:
    void Cancel();
    void Get_Geometry(QRect);
    void GetRepeatNumber(uint value);
    void GetRepeatTimeout(uint value);

private slots:

    void on_Back_clicked();

    void on_Apply_clicked();

private:
    Ui::Settings_Form *ui;

    QSysInfo          *SysInfo;
    QRegExp            RegSystemName;
    ResizeCalculating  resize_calculating;
};

#endif // SETTINGS_FORM_H
