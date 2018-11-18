#ifndef SI4463_SETTINGS_FORM_H
#define SI4463_SETTINGS_FORM_H

#include <QWidget>

namespace Ui {
class SI4463_Settings_Form;
}

class SI4463_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit SI4463_Settings_Form(QWidget *parent = 0);
    ~SI4463_Settings_Form();

private:
    Ui::SI4463_Settings_Form *ui;
};

#endif // SI4463_SETTINGS_FORM_H
