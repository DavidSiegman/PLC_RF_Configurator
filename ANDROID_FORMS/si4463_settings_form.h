#ifndef SI4463_SETTINGS_FORM_H
#define SI4463_SETTINGS_FORM_H

#include <QWidget>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QStandardItemModel>

#include "SI4463/si4463class.h"

namespace Ui {
class SI4463_Settings_Form;
}

class SI4463_Settings_Form : public QWidget
{
    Q_OBJECT

public:
    explicit SI4463_Settings_Form(QWidget *parent = 0);
    ~SI4463_Settings_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    void Cancel(QRect);
    void Next(QRect);
    void Settings(QWidget*);
    void isCreated(void);
    void Stop_Send_Data(void);
    void Get_Console(QPlainTextEdit* console);
    void Start_Parcer(QString);
    void Send_RF_Reset(void);
    void Write_SI4463_Parameters(void);

public slots:
    void SetProgress(uint progress);
    void Set_Geometry(QRect);
    void Set_Model(QStandardItemModel *model);
    void Set_Prameters(QList<Params> *params);

    void isStopped(void);
    void isRF_Reset(void);
    void isSI4463_Parameters(void);

private slots:
    void on_Back_clicked();

    void on_btnSettings_clicked();

    void on_Next_clicked();

    void on_Stop_clicked();

    void on_Reset_clicked();

    void on_FileOpen_clicked();

    void on_Write_clicked();

private:
    Ui::SI4463_Settings_Form *ui;
};

#endif // SI4463_SETTINGS_FORM_H
