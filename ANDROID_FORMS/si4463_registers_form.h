#ifndef SI4463_REGISTERS_FORM_H
#define SI4463_REGISTERS_FORM_H

#include <QWidget>

namespace Ui {
class SI4463_Registers_Form;
}

class SI4463_Registers_Form : public QWidget
{
    Q_OBJECT

public:
    explicit SI4463_Registers_Form(QWidget *parent = 0);
    ~SI4463_Registers_Form();

private:
    Ui::SI4463_Registers_Form *ui;
};

#endif // SI4463_REGISTERS_FORM_H
