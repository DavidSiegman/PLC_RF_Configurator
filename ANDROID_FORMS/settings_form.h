#ifndef SETTINGS_FORM_H
#define SETTINGS_FORM_H

#include <QWidget>

namespace Ui {
class Settings_Form;
}

class Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Settings_Form(QWidget *parent = 0);
    ~Settings_Form();
signals:
    void Cancel();
    void Get_Geometry(QRect);
    void GetRepeatNumber(uint value);
    void GetRepeatTimeout(uint value);

private slots:

    void on_Cancel_clicked();

    void on_Apply_clicked();

private:
    Ui::Settings_Form *ui;

    QSysInfo          *SysInfo;
    QRegExp           RegSystemName;
};

#endif // SETTINGS_FORM_H
