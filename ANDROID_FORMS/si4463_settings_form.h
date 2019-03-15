#ifndef SI4463_SETTINGS_FORM_H
#define SI4463_SETTINGS_FORM_H

#include <QWidget>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QStandardItemModel>
#include "SI4463/si4463class.h"
#include "myformabstractclass.h"
#include "ui_si4463_settings_form.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

#define SI4463_BATCH_PATH      "SI4463_BATCH/Path"

//namespace Ui {
//class SI4463_Settings_Form;
//}

class SI4463_Settings_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit SI4463_Settings_Form(QWidget *parent = 0);
    ~SI4463_Settings_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    void Start_Parcer(QString);
    void Write_SI4463_Parameters(void);
    void Open_RegistersWindow(QWidget*);

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

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
    void on_Registers_clicked();
    void on_ClearConsole_clicked();

    void DeviceVersionHandling(void);

private:
    Ui::SI4463_Settings_Form *ui;

    ResizeCalculating          resize_calculating;
};

#endif // SI4463_SETTINGS_FORM_H
