#ifndef RETRANSLATION_TABLE_FORM_H
#define RETRANSLATION_TABLE_FORM_H

#include <QWidget>
#include <QScreen>
#include <QPlainTextEdit>
#include "MODEM/modemclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"

namespace Ui {
class Retranslation_Table_Form;
}

class Retranslation_Table_Form : public QWidget
{
    Q_OBJECT

public:
    explicit Retranslation_Table_Form(QWidget *parent = 0);
    ~Retranslation_Table_Form();

    void resizeEvent(QResizeEvent *event);
signals:
    void Cancel(void);
    void Next(QRect);
    void Settings(QWidget*);
    void isCreated(void);
    void Stop_Send_Data(void);
    void Get_Geometry(QRect);
    void Get_Console(QPlainTextEdit* console);

    void Send_Read_Switch_Table(void);
    void Send_Write_Switch_Table(void);
    void Send_Clear_Switch_Table(void);
    void Send_RF_Reset(void);

public slots:
    void SetProgress(uint progress);
    void Set_Geometry(QRect);

    void Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data);
    void Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data);

    void isSwitch_Table(void);
    void isSwitch_Table_Delete(void);
    void isStopped(void);
    void isRF_Reset(void);

private slots:
    void on_Back_clicked();

    void on_btnSettings_clicked();

    void on_Stop_clicked();

    void on_Next_clicked();

    void on_Add_NetItem_clicked();

    void on_Del_NetItem_clicked();

    void on_Read_NetTable_clicked();

    void on_Write_clicked();

    void on_Del_NetTable_clicked();

private:
    Ui::Retranslation_Table_Form *ui;

    RetranslatorPropertiesClass*  In_Retranslator_Properties;
    RetranslatorPropertiesClass*  Out_Retranslator_Properties;

    ResizeCalculating             resize_calculating;

    QStandardItemModel *model;
};

#endif // RETRANSLATION_TABLE_FORM_H
