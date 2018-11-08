#ifndef NET_SETTINGS_FORM_H
#define NET_SETTINGS_FORM_H

#include <QWidget>
#include <QScreen>
#include <QPlainTextEdit>
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "CRC/crc16_class.h"
#include "MODEM/modemclass.h"

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
    void Cancel(void);
    void isCreated(void);
    void Send_Data(QByteArray data, uint n);
    void Get_Console(QPlainTextEdit* console);

public slots:
    void SetSwitchModeToUI(uchar);
    void SetSwitchLevelToUI(uint);
    void SetSwitchTimeoutToUI(uint);

private slots:
    void on_Back_clicked();

private:
    Ui::Net_Settings_Form *ui;
};

#endif // NET_SETTINGS_FORM_H
