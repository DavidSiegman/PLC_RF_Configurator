#ifndef ST750CONFIGURATIONCLASS_H
#define ST750CONFIGURATIONCLASS_H

typedef union{
    struct {
        unsigned  Freq_Custom_Or_MIB_Select: 1; // (set to "0") byte 0 bit 0 =0: TX frequency is the high or low frequency as in PHY_Config (Table 54) MIB object; =1: TX frequency is specified in bytes [1..3] (TX frequency)
        unsigned             Freq_Overwrite: 1; // (set to "0") byte 0 bit 1 =0: TX frequency expressed in the following bytes (1 ֠3) won't overwrite the frequency in PHY_Config (Table 54) MIB object; =1: TX frequency expressed in the following bytes (1 ֠3) overwrites frequency in PHY_Config (Table 54) MIB object
        unsigned                   Freq_Set: 1; // (set to "1") byte 0 bit 2 =0: TX frequency is the LowFrequency in PHY_Config MIB object; =1: TX frequency is the HighFrequency in PHY_Config MIB object
        unsigned  Gain_Custom_Or_MIB_Select: 1; // byte 0 bit 3 =0: TX gain set as in PHY Config MIB object (TX Gain parameter (Table 54)); =1: TX gain is specified in the following TX gain byte (2 or 4)
        unsigned           Frame_Modulation: 3; // byte 0 bit 4,5,6	 =0: B-PSK, =1: Q-PSK, =2: 8-PSK, =3: B-FSK, =4: B-PSK coded, =5: Q-PSK coded, =6: Reserved, =7: B-PSK coded with Peak Noise Avoidance
        unsigned Zero_Cross_Synchronization: 1; // (set to "0") byte 0 bit 7 =0: Transmission frame starts on any instant; =1: Transmission frame start after ZC delay value defined in PHY Config MIB object (Table 54)
        unsigned                    TX_Gain: 5; // byte 1 bit 0-4 =0: TX gain MAX=32 (2^5)
        unsigned 		   unused_in_byte_1: 3; // byte 1 bit 5-7
    } Feld;
    unsigned short HalbWord;
} TX_Conditions_Type;

struct PLC_Config_struct {
    unsigned int LOWF;
    unsigned int HIGHF;
    TX_Conditions_Type Transmit_Conditions;
};

class ST750ConfigurationClass
{
public:
    ST750ConfigurationClass();

    void                setPLC_Config_struct(PLC_Config_struct);
    PLC_Config_struct   getPLC_Config_struct(void);

    void                setST750_LOWF  (unsigned int);
    unsigned int        getST750_LOWF  ();
    void                setST750_HIGHF (unsigned int);
    unsigned int        getST750_HIGHF ();
    void                setST750_Transmit_Conditions(TX_Conditions_Type);
    TX_Conditions_Type  getST750_Transmit_Conditions();
private:
    PLC_Config_struct  ST750_Configuration_Data;
};

#endif // ST750CONFIGURATIONCLASS_H
