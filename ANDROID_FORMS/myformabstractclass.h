#ifndef MYFORMABSTRACTCLASS_H
#define MYFORMABSTRACTCLASS_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>

class myFormAbstractClass : public QWidget
{
    Q_OBJECT
public:
    explicit myFormAbstractClass(QWidget *parent = 0);



signals:
    void isCreated(void);
    void Cancel(QRect);
    void Next(QRect);
    void Settings(QWidget*);
    void ForcedClosed(void);
    void Get_Geometry(QRect);
    void Stop_Send_Data(void);
    void Get_Console(QPlainTextEdit* console);
    void Send_RF_Reset(void);

public slots:
    void SetProgress(uint progress);
    void Set_Geometry(QRect);

    void isStopped(void);
    void isRF_Reset(void);

    void Reset_ClickHandler(void);
    void Back_ClickHandler(void);
    void Next_ClickHandler(void);
    void Setting_ClickHandler(void);
    void ForceCloseHandler(void);
    void Stop_ClickHandler(void);

    uchar Get_resizing_going(void);
    void  Set_resizing_going(uchar);

private:
    uchar resizing_going;
};

#endif // MYFORMABSTRACTCLASS_H
