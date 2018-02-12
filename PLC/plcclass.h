#ifndef PLCCLASS_H
#define PLCCLASS_H

#include <QObject>
#include "ui_mainwindow.h"

struct PLC_Config_struct
{
    volatile uint LOWF;
    volatile uint HIGHF;
};

class PLCClass : public QObject
{
    Q_OBJECT
public:
    explicit PLCClass(Ui::MainWindow *ui,QObject *parent = 0);

    PLC_Config_struct* aSI4432_PLC_Config_struct(void);
private:
    Ui::MainWindow     *ui;
    PLC_Config_struct  *PLC_Parameters;

signals:

public slots:
    void           PLC_SET_LOWF  (unsigned int LOWF);
    unsigned int   PLC_GET_LOWF  (void);
    void           PLC_SET_HIGHF (unsigned int HIGHF);
    unsigned int   PLC_SET_HIGHF (void);
};

#endif // PLCCLASS_H
