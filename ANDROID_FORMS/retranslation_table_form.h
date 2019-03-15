#ifndef RETRANSLATION_TABLE_FORM_H
#define RETRANSLATION_TABLE_FORM_H

#include <QWidget>
#include <QScreen>
#include <QPlainTextEdit>
#include "ui_retranslation_table_form.h"
#include "myformabstractclass.h"
#include "MODEM/modemclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"

//namespace Ui {
//class Retranslation_Table_Form;
//}

class Retranslation_Table_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit Retranslation_Table_Form(QWidget *parent = 0);
    ~Retranslation_Table_Form();

    void resizeEvent(QResizeEvent *event);
signals:

public slots:
    void SetProgress(uint progress);
    void ForceClose(void);

    void Set_Out_Retranslator_Properties (RetranslatorPropertiesClass* new_data);
    void Set_In_Retranslator_Properties (RetranslatorPropertiesClass* new_data);

    void isSwitch_Table(void);
    void isDelet_Switch_Table(void);
    void isStopped(void);
    void isRF_Reset(void);

    void ModelItemChanged(QStandardItem*);

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
    void on_Reset_clicked();
    void on_ClearConsole_clicked();

private:
    Ui::Retranslation_Table_Form *ui;

    RetranslatorPropertiesClass  *In_Retranslator_Properties;
    RetranslatorPropertiesClass  *Out_Retranslator_Properties;

    ResizeCalculating             resize_calculating;

    QStandardItemModel           *model;
    uchar                         modelChanging;
};

#endif // RETRANSLATION_TABLE_FORM_H
