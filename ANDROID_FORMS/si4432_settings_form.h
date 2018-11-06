#ifndef SI4432_SETTINGS_FORM_H
#define SI4432_SETTINGS_FORM_H

#include <QWidget>

namespace Ui {
class SI4432_Settings_Form;
}

class SI4432_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit SI4432_Settings_Form(QWidget *parent = 0);
    ~SI4432_Settings_Form();

private:
    Ui::SI4432_Settings_Form *ui;
};

#endif // SI4432_SETTINGS_FORM_H
