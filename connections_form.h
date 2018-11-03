#ifndef CONNECTIONS_FORM_H
#define CONNECTIONS_FORM_H

#include <QWidget>
#include "TCP/tcp.h"

namespace Ui {
class Connections_Form;
}

class Connections_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Connections_Form(QWidget *parent = 0);
    ~Connections_Form();

    TCP                 *newTCP;


private slots:
    void on_TCPConnect_clicked();

private:
    Ui::Connections_Form *ui;

    QRect               screen_size;
};

#endif // CONNECTIONS_FORM_H
