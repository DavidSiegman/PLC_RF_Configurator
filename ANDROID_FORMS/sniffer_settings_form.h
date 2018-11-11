#ifndef SNIFFER_SETTINGS_FORM_H
#define SNIFFER_SETTINGS_FORM_H

#include <QWidget>
#include <QPlainTextEdit>

namespace Ui {
class Sniffer_Settings_Form;
}

class Sniffer_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Sniffer_Settings_Form(QWidget *parent = 0);
    ~Sniffer_Settings_Form();

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
    Ui::Sniffer_Settings_Form *ui;
};

#endif // SNIFFER_SETTINGS_FORM_H
