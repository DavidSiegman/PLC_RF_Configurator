#ifndef PLCCLASS_H
#define PLCCLASS_H

#include <QObject>
#include "st750configurationclass.h"
#include "ui_mainwindow.h"

class PLCClass : public QObject
{
    Q_OBJECT
public:
    explicit PLCClass(Ui::MainWindow *ui,QObject *parent = 0);
    explicit PLCClass(QObject *parent = 0);

private:
    ST750ConfigurationClass*   In_ST750_Parameters;
    ST750ConfigurationClass*   Out_ST750_Parameters;

signals:
    void                       sIn_ST750_Parameters  (ST750ConfigurationClass*);
    void                       sOut_ST750_Parameters (ST750ConfigurationClass*);

public slots:
    ST750ConfigurationClass*   getIn_ST750_PLC_Config(void);
    void                       ChangedIn_ST750_PLC_Config(void);
    ST750ConfigurationClass*   getOut_ST750_PLC_Config(void);
    void                       ChangedOut_ST750_PLC_Config(void);

};

#endif // PLCCLASS_H
