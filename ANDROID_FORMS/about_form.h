#ifndef ABOUT_FORM_H
#define ABOUT_FORM_H

#include <QWidget>
#include "ui_about_form.h"
#include "myformabstractclass.h"
#include "RESIZE_CALCULATING/resizecalculating.h"
#include "STYLE/style.h"

//namespace Ui {
//class About_Form;
//}

class About_Form : public myFormAbstractClass
{
    Q_OBJECT

public:
    explicit About_Form(QWidget *parent = 0);
    ~About_Form();
    void resizeEvent(QResizeEvent *event);
public slots:
    void ForceClose(void);

private slots:
    void on_Apply_clicked();

private:
    Ui::About_Form *ui;
    QSysInfo                 *SysInfo;
    QRegExp                   RegSystemName;
    ResizeCalculating         resize_calculating;
};

#endif // ABOUT_FORM_H
