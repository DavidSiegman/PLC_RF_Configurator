#ifndef PLC_SETTINGS_FORM_H
#define PLC_SETTINGS_FORM_H

#include <QWidget>
#include <QPlainTextEdit>

namespace Ui {
class PLC_Settings_Form;
}

class PLC_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit PLC_Settings_Form(QWidget *parent = 0);
    ~PLC_Settings_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    void Cancel(void);
    void Next(void);
    void isCreated(void);
    void Get_Console(QPlainTextEdit* console);

public slots:
    void SetProgress(uint progress);

private slots:
    void on_Back_clicked();

    void on_Next_clicked();

private:
    Ui::PLC_Settings_Form *ui;
};

#endif // PLC_SETTINGS_FORM_H
