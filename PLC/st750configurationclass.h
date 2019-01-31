#ifndef ST750CONFIGURATIONCLASS_H
#define ST750CONFIGURATIONCLASS_H

struct PLC_Config_struct
{
    unsigned int LOWF;
    unsigned int HIGHF;
};

class ST750ConfigurationClass
{
public:
    ST750ConfigurationClass();

    void              setPLC_Config_struct(PLC_Config_struct);
    PLC_Config_struct getPLC_Config_struct(void);

    void              setST750_LOWF  (unsigned int LOWF);
    unsigned int      getST750_LOWF  ();
    void              setST750_HIGHF (unsigned int TXDR);
    unsigned int      getST750_HIGHF ();
private:
    PLC_Config_struct  ST750_Configuration_Data;
};

#endif // ST750CONFIGURATIONCLASS_H
