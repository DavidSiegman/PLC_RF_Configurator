#ifndef OPEN_CONNECTION_FORM_H
#define OPEN_CONNECTION_FORM_H

#include <QWidget>
#include <QScreen>
#include <QPlainTextEdit>

namespace Ui {
class Open_Connection_Form;
}

class Open_Connection_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Open_Connection_Form(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~Open_Connection_Form();

public slots:
    void SetProgress(uint progress);
    void isOPEND(void);
    void SetCurrentFitmwareToUI(uchar);
    void SetBootloaderVersionToUI(QString);
    void SetBootloaderSizeToUI(uint);
    void SetBootloaderCRCToUI(QByteArray);
    void SetUpgradableVersionToUI(QString);
    void SetUpgradableSizeToUI(uint);
    void SetUpgradableCRCToUI(QByteArray);
    void SetDeviceNameToUI(QString);

signals:
    void Cancel(void);
    void Next(void);
    void Get_Console(QPlainTextEdit* console);
    void SendSerialNumber(QString, bool);
    void AOPEN(void);
    void STOP_MONITOR(void);

private slots:
    void on_Back_clicked();

    void on_Interface_currentIndexChanged(int index);

    void on_Connect_clicked();

    void on_Next_clicked();

    void Clear_Form(void);

private:
    Ui::Open_Connection_Form *ui;
    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;
};

#endif // OPEN_CONNECTION_FORM_H
