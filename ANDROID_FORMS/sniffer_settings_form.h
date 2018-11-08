#ifndef SNIFFER_SETTINGS_FORM_H
#define SNIFFER_SETTINGS_FORM_H

#include <QWidget>

namespace Ui {
class Sniffer_Settings_Form;
}

class Sniffer_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Sniffer_Settings_Form(QWidget *parent = 0);
    ~Sniffer_Settings_Form();

private:
    Ui::Sniffer_Settings_Form *ui;
};

#endif // SNIFFER_SETTINGS_FORM_H
