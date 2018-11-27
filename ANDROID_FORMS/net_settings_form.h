#ifndef NET_SETTINGS_FORM_H
#define NET_SETTINGS_FORM_H

#include <QWidget>
#include <QScreen>
#include <QPlainTextEdit>
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "CRC/crc16_class.h"
#include "MODEM/modemclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"

namespace Ui {
class Net_Settings_Form;
}

class Net_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Net_Settings_Form(QWidget *parent = 0);
    ~Net_Settings_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    void Cancel(QRect);
    void Next(QRect);
    void isCreated(void);
    void Get_Console(QPlainTextEdit* console);
    void Send_Data(QByteArray data, uint n);

public slots:
    void SetProgress(uint progress);
    void SetSwitchModeToUI(uchar);
    void SetSwitchLevelToUI(uint);
    void SetSwitchTimeoutToUI(uint);

private slots:
    void on_Back_clicked();

    void on_Next_clicked();

private:
    Ui::Net_Settings_Form     *ui;

    ResizeCalculating          resize_calculating;
};

#endif // NET_SETTINGS_FORM_H
