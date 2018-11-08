#ifndef HANDS_ENTER_FORM_H
#define HANDS_ENTER_FORM_H

#include <QWidget>
#include <QScreen>
#include <QPlainTextEdit>
#include <OTHER_FUNCTIONS/mess_enum.h>
#include "CRC/crc16_class.h"

namespace Ui {
class Hands_Enter_Form;
}

class Hands_Enter_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Hands_Enter_Form(QWidget *parent = 0);
    ~Hands_Enter_Form();
    void resizeEvent(QResizeEvent *event);

signals:
    void Cancel();
    void Next();
    void Send_Data(QByteArray data, uint n);
    void Get_Console(QPlainTextEdit* console);

private slots:
    void on_Back_clicked();

    void on_cBtnSend_clicked();

    void on_pushButton_clicked();

private:
    Ui::Hands_Enter_Form *ui;
    QSysInfo             *SysInfo;
    QRegExp               RegSystemName;

    CRC16_Class          *oCRC16;
};

#endif // HANDS_ENTER_FORM_H
