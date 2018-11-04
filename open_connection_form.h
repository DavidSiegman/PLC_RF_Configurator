#ifndef OPEN_CONNECTION_FORM_H
#define OPEN_CONNECTION_FORM_H

#include <QWidget>

namespace Ui {
class Open_Connection_Form;
}

class Open_Connection_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Open_Connection_Form(QWidget *parent = 0);
    ~Open_Connection_Form();

private:
    Ui::Open_Connection_Form *ui;
};

#endif // OPEN_CONNECTION_FORM_H
