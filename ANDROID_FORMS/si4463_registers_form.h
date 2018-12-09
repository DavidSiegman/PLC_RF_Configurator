#ifndef SI4463_REGISTERS_FORM_H
#define SI4463_REGISTERS_FORM_H

#include <QWidget>
#include <QStandardItemModel>

#include "RESIZE_CALCULATING/resizecalculating.h"

namespace Ui {
class SI4463_Registers_Form;
}

class SI4463_Registers_Form : public QWidget
{
    Q_OBJECT

public:
    explicit SI4463_Registers_Form(QWidget *parent = 0);
    ~SI4463_Registers_Form();
    void resizeEvent(QResizeEvent *event);

signals:
    void Cancel();
    void Next(QRect);
    void Settings(QWidget*);
    void isCreated(void);
    void Get_Geometry(QRect);

public slots:
    void Set_Model(QStandardItemModel *model);

private slots:
    void on_Back_clicked();
    void on_Next_clicked();
    void on_btnSettings_clicked();

private:
    Ui::SI4463_Registers_Form *ui;

    ResizeCalculating          resize_calculating;
};

#endif // SI4463_REGISTERS_FORM_H
