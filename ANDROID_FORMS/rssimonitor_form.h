#ifndef RSSIMONITOR_FORM_H
#define RSSIMONITOR_FORM_H

#include <QWidget>

namespace Ui {
class RSSIMonitor_Form;
}

class RSSIMonitor_Form : public QWidget
{
    Q_OBJECT

public:
    explicit RSSIMonitor_Form(QWidget *parent = 0);
    ~RSSIMonitor_Form();

private:
    Ui::RSSIMonitor_Form *ui;
};

#endif // RSSIMONITOR_FORM_H
