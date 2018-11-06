#ifndef NET_SETTINGS_FORM_H
#define NET_SETTINGS_FORM_H

#include <QWidget>

namespace Ui {
class Net_Settings_Form;
}

class Net_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Net_Settings_Form(QWidget *parent = 0);
    ~Net_Settings_Form();

private:
    Ui::Net_Settings_Form *ui;
};

#endif // NET_SETTINGS_FORM_H
