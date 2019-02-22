#ifndef RS_SETTINGS_FORM_H
#define RS_SETTINGS_FORM_H

#include <QWidget>

namespace Ui {
class RS_Settings_Form;
}

class RS_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit RS_Settings_Form(QWidget *parent = 0);
    ~RS_Settings_Form();

private:
    Ui::RS_Settings_Form *ui;
};

#endif // RS_SETTINGS_FORM_H
