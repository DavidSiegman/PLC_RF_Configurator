#ifndef PLC_SETTINGS_FORM_H
#define PLC_SETTINGS_FORM_H

#include <QWidget>

namespace Ui {
class PLC_Settings_Form;
}

class PLC_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit PLC_Settings_Form(QWidget *parent = 0);
    ~PLC_Settings_Form();

private:
    Ui::PLC_Settings_Form *ui;
};

#endif // PLC_SETTINGS_FORM_H
