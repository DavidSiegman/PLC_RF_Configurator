#ifndef SI4463_PROPERTYS_TYPE
#define SI4463_PROPERTYS_TYPE

typedef union SI4463_PROPERTYS_Type
{
    struct
    {
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char TUNE_VALUE: 7;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                } GLOBAL_XO_TUNE;                                // 1

                union
                {
                    struct
                    {
                        volatile unsigned char CLK_32K_SEL: 2;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char DIVIDED_CLK_SEL: 3;
                        volatile unsigned char DIVIDED_CLK_EN: 1;
                        volatile unsigned char NONE_2: 1;
                    }Field;
                } GLOBAL_CLK_CFG;                                // 2

                union
                {
                    struct
                    {
                        volatile unsigned char THRESHOLD: 5;
                        volatile unsigned char NONE_1: 3;
                    }Field;
                } GLOBAL_LOW_BATT_THRESH;                        // 3

                union
                {
                    struct
                    {
                        volatile unsigned char POWER_MODE: 1;
                        volatile unsigned char PROTOCOL: 3;
                        volatile unsigned char FIFO_MODE: 1;
                        volatile unsigned char SEQUENCER_MODE: 1;
                        volatile unsigned char RESERVED: 1;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                } GLOBAL_CONFIG;                                 // 4

                union
                {
                    struct
                    {
                        volatile unsigned char CAL_EN: 1;
                        volatile unsigned char WUT_EN: 1;
                        volatile unsigned char WUT_LBD_EN: 1;
                        volatile unsigned char WUT_CAL_PERIOD: 3;
                        volatile unsigned char WUT_LDC_EN: 2;
                    }Field;
                } GLOBAL_WUT_CONFIG;                              // 5

                union
                {
                    struct
                    {
                        volatile unsigned char GLOBAL_WUT_M_1: 8;
                        volatile unsigned char GLOBAL_WUT_M_0: 8;
                    }Field;
                } GLOBAL_WUT_M;                                  // 6-7

                union
                {
                    struct
                    {
                        volatile unsigned char WUT_R: 5;
                        volatile unsigned char WUT_SLEEP: 1;
                        volatile unsigned char RESERVED_WRITE_ONE: 2;
                    }Field;
                } GLOBAL_WUT_R;                                  // 8

                union
                {
                    struct
                    {
                        volatile unsigned char WUT_LDC: 8;
                    }Field;
                } GLOBAL_WUT_LDC;                                // 9
                union
                {
                    struct
                    {
                        volatile unsigned char WUT_CAL: 8;
                    }Field;
                }GLOBAL_WUT_CAL;                                 // 10
            }Field;
            unsigned char Bytes[10];
      }GROUP_00;

        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char PH_INT_STATUS_EN: 1;
                        volatile unsigned char MODEM_INT_STATUS_EN: 1;
                        volatile unsigned char CHIP_INT_STATUS_EN: 1;
                        volatile unsigned char NONE_1: 5;
                    }Field;
                } INT_CTL_ENABLE;                                // 11

                union
                {
                    struct
                    {
                        volatile unsigned char RX_FIFO_ALMOST_FULL_EN: 1;
                        volatile unsigned char TX_FIFO_ALMOST_EMPTY_EN: 1;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ERROR_EN: 1;
                        volatile unsigned char PACKET_RX_EN: 1;
                        volatile unsigned char PACKET_SENT_EN: 1;
                        volatile unsigned char FILTER_MISS_EN: 1;
                        volatile unsigned char FILTER_MATCH_EN: 1;
                    }Field;
                } INT_CTL_PH_ENABLE;                             // 12

                union
                {
                    struct
                    {
                        volatile unsigned char SYNC_DETECT_EN: 1;
                        volatile unsigned char PREAMBLE_DETECT_EN: 1;
                        volatile unsigned char INVALID_PREAMBLE_EN: 1;
                        volatile unsigned char RSSI_EN: 1;
                        volatile unsigned char RSSI_JUMP_EN: 1;
                        volatile unsigned char INVALID_SYNC_EN: 1;
                        volatile unsigned char POSTAMBLE_DETECT_EN: 1;
                        volatile unsigned char RSSI_LATCH_EN: 1;
                    }Field;
                } INT_CTL_MODEM_ENABLE;                          // 13

                union
                {
                    struct
                    {
                        volatile unsigned char WUT_EN: 1;
                        volatile unsigned char LOW_BATT_EN: 1;
                        volatile unsigned char CHIP_READY_EN: 1;
                        volatile unsigned char CMD_ERROR_EN: 1;
                        volatile unsigned char STATE_CHANGE_EN: 1;
                        volatile unsigned char FIFO_UNDERFLOW_OVERFLOW_ERROR_EN: 1;
                        volatile unsigned char CAL_EN: 1;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                } INT_CTL_CHIP_ENABLE;                           // 14
            }Field;
            unsigned char Bytes[4];
      }GROUP_01;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char FRR_A_MODE: 8;
                    }Field;
                } FRR_CTL_A_MODE;                                // 15

                union
                {
                    struct
                    {
                        volatile unsigned char FRR_B_MODE: 8;
                    }Field;
                } FRR_CTL_B_MODE;                                // 16

                union
                {
                    struct
                    {
                        volatile unsigned char FRR_C_MODE: 8;
                    }Field;
                } FRR_CTL_C_MODE;                                // 17

                union
                {
                    struct
                    {
                        volatile unsigned char FRR_D_MODE: 8;
                    }Field;
                } FRR_CTL_D_MODE;                                // 18
            }Field;
            unsigned char Bytes[4];
      }GROUP_02;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char TX_LENGTH: 8;
                    }Field;
                } PREAMBLE_TX_LENGTH;                            // 19

                union
                {
                    struct
                    {
                        volatile unsigned char RX_THRESH: 7;
                        volatile unsigned char SKIP_SYNC_TIMEOUT: 1;
                    }Field;
                } PREAMBLE_CONFIG_STD_1;                         // 20

                union
                {
                    struct
                    {
                        volatile unsigned char PATTERN_LENGTH: 5;
                        volatile unsigned char RX_ERRORS: 3;
                    }Field;
                } PREAMBLE_CONFIG_NSTD;                          // 21

                union
                {
                    struct
                    {
                        volatile unsigned char RX_PREAMBLE_TIMEOUT: 4;
                        volatile unsigned char RX_PREAMBLE_TIMEOUT_EXTEND: 4;
                    }Field;
                } PREAMBLE_CONFIG_STD_2;                         // 22

                union
                {
                    struct
                    {
                        volatile unsigned char STANDARD_PREAM: 2;
                        volatile unsigned char MAN_ENABLE: 1;
                        volatile unsigned char MAN_CONST: 1;
                        volatile unsigned char LENGTH_CONFIG: 1;
                        volatile unsigned char PREAM_FIRST_1_OR_0: 1;
                        volatile unsigned char NONE_1: 2;
                    }Field;
                } PREAMBLE_CONFIG;                               // 23

                union
                {
                    struct
                    {
                        volatile unsigned char PATTERN_3: 8;
                        volatile unsigned char PATTERN_2: 8;
                        volatile unsigned char PATTERN_1: 8;
                        volatile unsigned char PATTERN_0: 8;
                    }Field;
                } PREAMBLE_PATTERN;                              // 24-27

                union
                {
                    struct
                    {
                        volatile unsigned char POSTAMBLE_SIZE: 2;
                        volatile unsigned char NONE_1: 4;
                        volatile unsigned char PKT_VALID_ON_POSTAMBLE: 1;
                        volatile unsigned char POSTAMBLE_ENABLE: 1;
                    }Field;
                } PREAMBLE_POSTAMBLE_CONFIG;                     // 28

                union
                {
                    struct
                    {
                        volatile unsigned char POSTAMBLE_PATTERN_3: 8;
                        volatile unsigned char POSTAMBLE_PATTERN_2: 8;
                        volatile unsigned char POSTAMBLE_PATTERN_1: 8;
                        volatile unsigned char POSTAMBLE_PATTERN_0: 8;
                    }Field;
                } PREAMBLE_POSTAMBLE_PATTERN;                    // 29-32
            }Field;
            unsigned char Bytes[14];
      }GROUP_10;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char LENGTH: 2;
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char RX_ERRORS: 3;
                        volatile unsigned char SKIP_TX: 1;
                    }Field;
                } SYNC_CONFIG;                                   // 33

                union
                {
                    struct
                    {
                        volatile unsigned char BITS_3: 8;
                        volatile unsigned char BITS_2: 8;
                        volatile unsigned char BITS_1: 8;
                        volatile unsigned char BITS_0: 8;
                    }Field;
                } SYNC_BITS;                                     // 34-37
            }Field;
            unsigned char Bytes[5];
      }GROUP_11;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char CRC_POLYNOMIAL: 4;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char CRC_SEED: 1;
                    }Field;
                } PKT_CRC_CONFIG;                                // 38

                union
                {
                    struct
                    {
                        volatile unsigned char WHT_POLY_1: 8;
                        volatile unsigned char WHT_POLY_0: 8;
                    }Field;
                } PKT_WHT_POLY;                                  // 39-40
                union
                {
                    struct
                    {
                        volatile unsigned char WHT_SEED_1: 8;
                        volatile unsigned char WHT_SEED_0: 8;
                    }Field;
                } PKT_WHT_SEED;                                  // 41-42

                union
                {
                    struct
                    {
                        volatile unsigned char WHT_BIT_NUM: 4;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char SW_CRC_CTRL: 1;
                        volatile unsigned char SW_WHT_CTRL: 1;
                    }Field;
                } PKT_WHT_BIT_NUM;                               // 43

                union
                {
                    struct
                    {
                        volatile unsigned char BIT_ORDER: 1;
                        volatile unsigned char CRC_ENDIAN: 1;
                        volatile unsigned char CRC_INVERT: 1;
                        volatile unsigned char MANCH_POL: 1;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char _4FSK_EN: 1;
                        volatile unsigned char PH_RX_DISABLE: 1;
                        volatile unsigned char PH_FIELD_SPLIT: 1;
                    }Field;
                } PKT_CONFIG1;                                   // 44
                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 8;
                    }Field;
                } NONE_1;                                        // 45

                union
                {
                    struct
                    {
                        volatile unsigned char DST_FIELD: 3;
                        volatile unsigned char IN_FIFO: 1;
                        volatile unsigned char SIZE: 1;
                        volatile unsigned char ENDIAN: 1;
                        volatile unsigned char NONE_1: 2;
                    }Field;
                } PKT_LEN;                                       // 46

                union
                {
                    struct
                    {
                        volatile unsigned char SRC_FIELD: 3;
                        volatile unsigned char NONE_1: 5;
                    }Field;
                } PKT_LEN_FIELD_SOURCE;                          // 47

                union
                {
                    struct
                    {
                        volatile unsigned char LEN_ADJUST: 8;
                    }Field;
                } PKT_LEN_ADJUST;                                // 48

                union
                {
                    struct
                    {
                        volatile unsigned char TX_THRESHOLD: 8;
                    }Field;
                } PKT_TX_THRESHOLD;                              // 49

                union
                {
                    struct
                    {
                        volatile unsigned char RX_THRESHOLD: 8;
                    }Field;
                } PKT_RX_THRESHOLD;                              // 50

                union
                {
                    struct
                    {
                        volatile unsigned char FIELD_1_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char FIELD_1_LENGTH_0: 8;
                    }Field;
                } PKT_FIELD_1_LENGTH;                            // 51-52

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char PN_START: 1;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_FIELD_1_CONFIG;                            // 53

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 1;
                        volatile unsigned char SEND_CRC: 1;
                        volatile unsigned char NONE_4: 1;
                        volatile unsigned char CRC_START: 1;
                    }Field;
                } PKT_FIELD_1_CRC_CONFIG;                        // 54

                union
                {
                    struct
                    {
                        volatile unsigned char FIELD_2_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char FIELD_2_LENGTH_0: 8;
                    }Field;
                } PKT_FIELD_2_LENGTH;                            // 55-56

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_FIELD_2_CONFIG;                            // 57

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 1;
                        volatile unsigned char SEND_CRC: 1;
                        volatile unsigned char NONE_4: 2;
                    }Field;
                } PKT_FIELD_2_CRC_CONFIG;                        // 58

                union
                {
                    struct
                    {
                        volatile unsigned char FIELD_3_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char FIELD_3_LENGTH_0: 8;
                    }Field;
                }PKT_FIELD_3_LENGTH;                             // 59-60

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_FIELD_3_CONFIG;                            // 61

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 1;
                        volatile unsigned char SEND_CRC: 1;
                        volatile unsigned char NONE_4: 2;
                    }Field;
                } PKT_FIELD_3_CRC_CONFIG;                        // 62

                union
                {
                    struct
                    {
                        volatile unsigned char FIELD_4_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char FIELD_4_LENGTH_0: 8;
                    }Field;
                }PKT_FIELD_4_LENGTH;                             // 63-64

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_FIELD_4_CONFIG;                            // 65

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 1;
                        volatile unsigned char SEND_CRC: 1;
                        volatile unsigned char NONE_4: 2;
                    }Field;
                } PKT_FIELD_4_CRC_CONFIG;                        // 66

                union
                {
                    struct
                    {
                        volatile unsigned char FIELD_5_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char FIELD_5_LENGTH_0: 8;
                    }Field;
                }PKT_FIELD_5_LENGTH;                             // 67-68

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_FIELD_5_CONFIG;                            // 69

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 1;
                        volatile unsigned char SEND_CRC: 1;
                        volatile unsigned char NONE_4: 2;
                    }Field;
                } PKT_FIELD_5_CRC_CONFIG;                        // 70

                union
                {
                    struct
                    {
                        volatile unsigned char RX_FIELD_1_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char RX_FIELD_1_LENGTH_0: 8;
                    }Field;
                }PKT_RX_FIELD_1_LENGTH;                          // 71-72

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char PN_START: 1;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_RX_FIELD_1_CONFIG;                         // 73

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 3;
                        volatile unsigned char CRC_START: 1;
                    }Field;
                } PKT_RX_FIELD_1_CRC_CONFIG;                     // 74

                union
                {
                    struct
                    {
                        volatile unsigned char RX_FIELD_2_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char RX_FIELD_2_LENGTH_0: 8;
                    }Field;
                }PKT_RX_FIELD_2_LENGTH;                          // 75-76

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_RX_FIELD_2_CONFIG;                         // 77

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 4;
                    }Field;
                } PKT_RX_FIELD_2_CRC_CONFIG;                     // 78

                union
                {
                    struct
                    {
                        volatile unsigned char RX_FIELD_3_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char RX_FIELD_3_LENGTH_0: 8;
                    }Field;
                }PKT_RX_FIELD_3_LENGTH;                          // 79-80

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_RX_FIELD_3_CONFIG;                         // 81

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 4;
                    }Field;
                } PKT_RX_FIELD_3_CRC_CONFIG;                     // 82

                union
                {
                    struct
                    {
                        volatile unsigned char RX_FIELD_4_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char RX_FIELD_4_LENGTH_0: 8;
                    }Field;
                }PKT_RX_FIELD_4_LENGTH;                          // 83-84

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_RX_FIELD_4_CONFIG;                         // 85

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 4;
                    }Field;
                } PKT_RX_FIELD_4_CRC_CONFIG;                     // 86

                union
                {
                    struct
                    {
                        volatile unsigned char RX_FIELD_5_LENGTH_1: 5;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char RX_FIELD_5_LENGTH_0: 8;
                    }Field;
                }PKT_RX_FIELD_5_LENGTH;                          // 87-88

                union
                {
                    struct
                    {
                        volatile unsigned char MANCH: 1;
                        volatile unsigned char WHITEN: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char _4FSK: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                } PKT_RX_FIELD_5_CONFIG;                         // 89

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char CRC_ENABLE: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char CHECK_CRC: 1;
                        volatile unsigned char NONE_3: 4;
                    }Field;
                } PKT_RX_FIELD_5_CRC_CONFIG;                     // 90
            }Field;
            unsigned char Bytes[53];
      }GROUP_12;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char MOD_TYPE: 3;
                        volatile unsigned char MOD_SOURCE: 2;
                        volatile unsigned char TX_DIRECT_MODE_GPIO: 2;
                        volatile unsigned char TX_DIRECT_MODE_TYPE: 1;
                    }Field;
                } MODEM_MOD_TYPE;                                // 91

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 4;
                        volatile unsigned char ENINV_FD: 1;
                        volatile unsigned char ENINV_TXBIT: 1;
                        volatile unsigned char ENINV_RXBIT: 1;
                        volatile unsigned char ENMANCH: 1;
                    }Field;
                }MODEM_MAP_CONTROL;                              // 92

                union
                {
                    struct
                    {
                        volatile unsigned char DSM_ORDER: 2;
                        volatile unsigned char DSM_LSB: 1;
                        volatile unsigned char DSM_RST: 1;
                        volatile unsigned char DSMDTTP: 1;
                        volatile unsigned char DSMDT_EN: 1;
                        volatile unsigned char DSM_MODE: 1;
                        volatile unsigned char DSMCLK_SEL: 1;
                    }Field;
                }MODEM_DSM_CTRL;                                 // 93

                union
                {
                    struct
                    {
                        volatile unsigned char DATA_RATE_2: 8;
                        volatile unsigned char DATA_RATE_1: 8;
                        volatile unsigned char DATA_RATE_0: 8;
                    }Field;
                }MODEM_DATA_RATE;                                // 94-96

                union
                {
                    struct
                    {
                        volatile unsigned char NCOMOD_3: 2;
                        volatile unsigned char TXOSR: 2;
                        volatile unsigned char NONE_1: 4;
                        volatile unsigned char NCOMOD_2: 8;
                        volatile unsigned char NCOMOD_1: 8;
                        volatile unsigned char NCOMOD_0: 8;
                    }Field;
                }MODEM_TX_NCO_MODE;                              // 97-100

                union
                {
                    struct
                    {
                        volatile unsigned char FREQDEV_2: 1;
                        volatile unsigned char NONE_1: 7;
                        volatile unsigned char FREQDEV_1: 8;
                        volatile unsigned char FREQDEV_0: 8;
                    }Field;
                }MODEM_FREQ_DEV;                                 // 101-103

                union
                {
                    struct
                    {
                        volatile unsigned char FREQOFFSET_1: 8;
                        volatile unsigned char FREQOFFSET_0: 8;
                    }Field;
                }MODEM_FREQ_OFFSET;                              // 104-105

                volatile char  MODEM_TX_FILTER_COEFF_8;          // 106
                volatile char  MODEM_TX_FILTER_COEFF_7;          // 107
                volatile char  MODEM_TX_FILTER_COEFF_6;          // 108
                volatile char  MODEM_TX_FILTER_COEFF_5;          // 109
                volatile char  MODEM_TX_FILTER_COEFF_4;          // 110
                volatile char  MODEM_TX_FILTER_COEFF_3;          // 111
                volatile char  MODEM_TX_FILTER_COEFF_2;          // 112
                volatile char  MODEM_TX_FILTER_COEFF_1;          // 113
                volatile char  MODEM_TX_FILTER_COEFF_0;          // 114

                union
                {
                    struct
                    {
                        volatile unsigned char RAMP_DLY: 3;
                        volatile unsigned char NONE_1: 5;
                    }Field;
                }MODEM_TX_RAMP_DELAY;                            // 115

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 7;
                        volatile unsigned char PH_SRC_SEL: 1;
                    }Field;
                }MODEM_MDM_CTRL;                                 // 116

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char FIXIF: 1;
                        volatile unsigned char ZEROIF: 1;
                        volatile unsigned char NONE_2: 3;
                    }Field;
                }MODEM_IF_CONTROL;                               // 117

                union
                {
                    struct
                    {
                        volatile unsigned char IF_FREQ_2: 2;
                        volatile unsigned char NONE_1: 6;
                        volatile unsigned char IF_FREQ_1: 8;
                        volatile unsigned char IF_FREQ_0: 8;
                    }Field;
                }MODEM_IF_FREQ;                                  // 118-120

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char NDEC0: 3;
                        volatile unsigned char NDEC1: 2;
                        volatile unsigned char NDEC2: 2;
                    }Field;
                }MODEM_DECIMATION_CFG1;                          // 121

                union
                {
                    struct
                    {
                        volatile unsigned char RXGAINX2: 1;
                        volatile unsigned char NONE_1: 3;
                        volatile unsigned char DWN2BYP: 1;
                        volatile unsigned char DWN3BYP: 1;
                        volatile unsigned char DROOPFLTBYP: 1;
                        volatile unsigned char CHFLT_LOPW: 1;
                    }Field;
                }MODEM_DECIMATION_CFG0;                          // 122
                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 8;
                    }Field;
                }NONE_1;                                         // 123
                union
                {
                    struct
                    {
                        volatile unsigned char NONE_2: 8;
                    }Field;
                }NONE_2;                                         // 124
                union
                {
                    struct
                    {
                        volatile unsigned char RXOSR_1: 4;
                        volatile unsigned char NONE_1: 4;
                        volatile unsigned char RXOSR_0: 8;
                    }Field;
                }MODEM_BCR_OSR;                                  // 125-126

                union
                {
                    struct
                    {
                        volatile unsigned char NCOFF_2: 6;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char NCOFF_1: 8;
                        volatile unsigned char NCOFF_0: 8;
                    }Field;
                }MODEM_BCR_NCO_OFFSET;                           // 127-129

                union
                {
                    struct
                    {
                        volatile unsigned char CRGAIN_1: 3;
                        volatile unsigned char NONE_1: 5;
                        volatile unsigned char CRGAIN_0: 8;
                    }Field;
                }MODEM_BCR_GAIN;                                 // 130-131

                union
                {
                    struct
                    {
                        volatile unsigned char CRSLOW: 3;
                        volatile unsigned char CRFAST: 3;
                        volatile unsigned char NONE_1: 2;
                    }Field;
                }MODEM_BCR_GEAR;                                 // 132

                union
                {
                    struct
                    {
                        volatile unsigned char ESC_MIDPT: 1;
                        volatile unsigned char DIS_MIDPT: 1;
                        volatile unsigned char CRGAINX2: 1;
                        volatile unsigned char RXCOMP_LAT: 1;
                        volatile unsigned char RXNCOCOMP: 1;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char SLICEFBBYP: 1;
                        volatile unsigned char BCRFBBYP: 1;
                    }Field;
                }MODEM_BCR_MISC1;                                // 133

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 4;
                        volatile unsigned char PH0SIZE: 1;
                        volatile unsigned char DISTOGG: 1;
                        volatile unsigned char ADCRST: 1;
                        volatile unsigned char ADCWATCH: 1;
                    }Field;
                }MODEM_BCR_MISC0;                                // 134

                union
                {
                    struct
                    {
                        volatile unsigned char AFC_SLOW: 3;
                        volatile unsigned char AFC_FAST: 3;
                        volatile unsigned char GEAR_SW: 2;
                    }Field;
                }MODEM_AFC_GEAR;                                 // 135

                union
                {
                    struct
                    {
                        volatile unsigned char LGWAIT: 4;
                        volatile unsigned char SHWAIT: 4;
                    }Field;
                }MODEM_AFC_WAIT;                                 // 136

                union
                {
                    struct
                    {
                        volatile unsigned char AFCGAIN_1: 5;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char AFCBD: 1;
                        volatile unsigned char ENAFC: 1;
                        volatile unsigned char AFCGAIN_0: 8;
                    }Field;
                }MODEM_AFC_GAIN;                                 // 137-138

                union
                {
                    struct
                    {
                        volatile unsigned char AFCLIM_1: 7;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char AFCLIM_0: 8;
                    }Field;
                }MODEM_AFC_LIMITER;                              // 139-140

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char NON_FRZEN: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char ENAFC_CLKSW: 1;
                        volatile unsigned char ENFZPMEND: 1;
                        volatile unsigned char EN2TB_EST: 1;
                        volatile unsigned char ENFBPLL: 1;
                        volatile unsigned char ENAFCFRZ: 1;
                    }Field;
                }MODEM_AFC_MISC;                                 // 141

                union
                {
                    struct
                    {
                        volatile unsigned char ZEROFF: 8;
                    }Field;
                }MODEM_AFC_ZIFOFF;                               // 142

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char REALADC: 1;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char EN_DRST: 1;
                        volatile unsigned char HGAIN: 1;
                        volatile unsigned char NONE_3: 3;
                    }Field;
                }MODEM_ADC_CTRL;                                 // 143

                union
                {
                    struct
                    {
                        volatile unsigned char RST_PKDT_PERIOD: 1;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char AGC_SLOW: 1;
                        volatile unsigned char SGI_N: 1;
                        volatile unsigned char RFPDSLOW: 1;
                        volatile unsigned char IFPDSLOW: 1;
                        volatile unsigned char AGCOVPKT: 1;
                    }Field;
                }MODEM_AGC_CONTROL;                              // 144
                union
                {
                    struct
                    {
                        volatile unsigned char NONE_3: 8;
                    }Field;
                }NONE_3;                                         // 145
                union
                {
                    struct
                    {
                        volatile unsigned char NONE_4: 8;
                    }Field;
                }NONE_4;                                         // 146
                union
                {
                    struct
                    {
                        volatile unsigned char SETTLEWIN: 4;
                        volatile unsigned char MEASWIN: 4;
                    }Field;
                }MODEM_AGC_WINDOW_SIZE;                          // 147

                union
                {
                    struct
                    {
                        volatile unsigned char RFPD_DECAY: 8;
                    }Field;
                }MODEM_AGC_RFPD_DECAY;                           // 148

                union
                {
                    struct
                    {
                        volatile unsigned char IFPD_DECAY: 8;
                    }Field;
                }MODEM_AGC_IFPD_DECAY;                           // 149

                union
                {
                    struct
                    {
                        volatile unsigned char _4FSK_GAIN1: 7;
                        volatile unsigned char _4FSK_ISIS_DISABLE: 1;
                    }Field;
                }MODEM_FSK4_GAIN1;                               // 150

                union
                {
                    struct
                    {
                        volatile unsigned char _4FSK_GAIN0: 7;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }MODEM_FSK4_GAIN0;                               // 151

                union
                {
                    struct
                    {
                        volatile unsigned char _4FSKTH_1: 8;
                        volatile unsigned char _4FSKTH_0: 8;
                    }Field;
                }MODEM_FSK4_TH;                                  // 152-153

                union
                {
                    struct
                    {
                        volatile unsigned char _4FSKMAP: 8;
                    }Field;
                }MODEM_FSK4_MAP;                                 // 154

                union
                {
                    struct
                    {
                        volatile unsigned char DECAY: 4;
                        volatile unsigned char ATTACK: 3;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }MODEM_OOK_PDTC;                                 // 155

                union
                {
                    struct
                    {
                        volatile unsigned char BW_PK: 8;
                    }Field;
                }MODEM_OOK_BLOPK;                                // 156

                union
                {
                    struct
                    {
                        volatile unsigned char SQUELCH: 2;
                        volatile unsigned char SLICER_FAST: 1;
                        volatile unsigned char RAW_SYN: 1;
                        volatile unsigned char MA_FREQDWN: 1;
                        volatile unsigned char OOKFRZEN: 1;
                        volatile unsigned char S2P_MAP: 2;
                    }Field;
                }MODEM_OOK_CNT1;                                 // 157

                union
                {
                    struct
                    {
                        volatile unsigned char DETECTOR: 2;
                        volatile unsigned char NONE_1: 5;
                        volatile unsigned char OOKFASTMA: 1;
                    }Field;
                }MODEM_OOK_MISC;                                 // 158

                union
                {
                    struct
                    {
                        volatile unsigned char SCHPRD_LOW: 2;
                        volatile unsigned char SCHPRD_HI: 2;
                        volatile unsigned char SCH_FRZTH: 3;
                        volatile unsigned char SCH_FRZEN: 1;
                    }Field;
                }MODEM_RAW_SEARCH;                               // 159

                union
                {
                    struct
                    {
                        volatile unsigned char RAWGAIN: 2;
                        volatile unsigned char PM_PATTERN: 2;
                        volatile unsigned char NONE_1: 2;
                        volatile unsigned char CONSCHK_BYP: 1;
                        volatile unsigned char UNSTDPK: 1;
                    }Field;
                }MODEM_RAW_CONTROL;                              // 160

                union
                {
                    struct
                    {
                        volatile unsigned char RAWEYE_1: 3;
                        volatile unsigned char NONE_1: 5;
                        volatile unsigned char RAWEYE_0: 8;
                    }Field;
                }MODEM_RAW_EYE;                                  // 161-162

                union
                {
                    struct
                    {
                        volatile unsigned char ANWAIT: 3;
                        volatile unsigned char SKIP2PHTH: 1;
                        volatile unsigned char SKIP2PH: 1;
                        volatile unsigned char BYP1P5: 1;
                        volatile unsigned char SWANT_TIMER: 2;
                    }Field;
                }MODEM_ANT_DIV_MODE;                             // 163

                union
                {
                    struct
                    {
                        volatile unsigned char RESERVED: 1;
                        volatile unsigned char ANTDIV: 2;
                        volatile unsigned char MATAP: 1;
                        volatile unsigned char ANT2PM_THD: 4;
                    }Field;
                }MODEM_ANT_DIV_CONTROL;                          // 164

                union
                {
                    struct
                    {
                        volatile unsigned char RSSI_THRESH: 8;
                    }Field;
                }MODEM_RSSI_THRESH;                              // 165

                union
                {
                    struct
                    {
                        volatile unsigned char RSSIJMPTHD: 7;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }MODEM_RSSI_JUMP_THRESH;                         // 166

                union
                {
                    struct
                    {
                        volatile unsigned char LATCH: 3;
                        volatile unsigned char AVERAGE: 2;
                        volatile unsigned char CHECK_THRESH_AT_LATCH: 1;
                        volatile unsigned char NONE_1: 2;
                    }Field;
                }MODEM_RSSI_CONTROL;                             // 167

                union
                {
                    struct
                    {
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char ENJMPRX: 1;
                        volatile unsigned char JMPDLYLEN: 1;
                        volatile unsigned char ENRSSIJMP: 1;
                        volatile unsigned char RSSIJMP_UP: 1;
                        volatile unsigned char RSSIJMP_DWN: 1;
                        volatile unsigned char NONE_2: 2;
                    }Field;
                }MODEM_RSSI_CONTROL2;                            // 168

                union
                {
                    struct
                    {
                        volatile unsigned char RSSI_COMP: 7;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }MODEM_RSSI_COMP;                                // 169
                union
                {
                    struct
                    {
                        volatile unsigned char NONE_5: 8;
                    }Field;
                }NONE_5;                                         // 170
                union
                {
                    struct
                    {
                        volatile unsigned char NONE_6: 8;
                    }Field;
                }NONE_6;                                         // 171
                union
                {
                    struct
                    {
                        volatile unsigned char BAND: 3;
                        volatile unsigned char SY_SEL: 1;
                        volatile unsigned char NONE_1: 4;
                    }Field;
                }MODEM_CLKGEN_BAND;                              // 172
            }Field;
            unsigned char Bytes[82];
      }GROUP_20;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char RX1_CHFLT_COE_13: 8;
                        volatile unsigned char RX1_CHFLT_COE_12: 8;
                        volatile unsigned char RX1_CHFLT_COE_11: 8;
                        volatile unsigned char RX1_CHFLT_COE_10: 8;
                        volatile unsigned char RX1_CHFLT_COE_09: 8;
                        volatile unsigned char RX1_CHFLT_COE_08: 8;
                        volatile unsigned char RX1_CHFLT_COE_07: 8;
                        volatile unsigned char RX1_CHFLT_COE_06: 8;
                        volatile unsigned char RX1_CHFLT_COE_05: 8;
                        volatile unsigned char RX1_CHFLT_COE_04: 8;
                        volatile unsigned char RX1_CHFLT_COE_03: 8;
                        volatile unsigned char RX1_CHFLT_COE_02: 8;
                        volatile unsigned char RX1_CHFLT_COE_01: 8;
                        volatile unsigned char RX1_CHFLT_COE_00: 8;
                        volatile unsigned char RX1_CHFLT_COE13:  2;
                        volatile unsigned char RX1_CHFLT_COE12:  2;
                        volatile unsigned char RX1_CHFLT_COE11:  2;
                        volatile unsigned char RX1_CHFLT_COE10:  2;
                        volatile unsigned char RX1_CHFLT_COE09:  2;
                        volatile unsigned char RX1_CHFLT_COE08:  2;
                        volatile unsigned char RX1_CHFLT_COE07:  2;
                        volatile unsigned char RX1_CHFLT_COE06:  2;
                        volatile unsigned char RX1_CHFLT_COE05:  2;
                        volatile unsigned char RX1_CHFLT_COE04:  2;
                        volatile unsigned char RX1_CHFLT_COE03:  2;
                        volatile unsigned char RX1_CHFLT_COE02:  2;
                        volatile unsigned char RX1_CHFLT_COE01:  2;
                        volatile unsigned char RX1_CHFLT_COE00:  2;
                        volatile unsigned char NONE_1:           4;
                    }Field;
                }MODEM_CHFLT_RX1_CHFLT_COE;                      // 173-190

                union
                {
                    struct
                    {
                        volatile unsigned char RX2_CHFLT_COE_13: 8;
                        volatile unsigned char RX2_CHFLT_COE_12: 8;
                        volatile unsigned char RX2_CHFLT_COE_11: 8;
                        volatile unsigned char RX2_CHFLT_COE_10: 8;
                        volatile unsigned char RX2_CHFLT_COE_09: 8;
                        volatile unsigned char RX2_CHFLT_COE_08: 8;
                        volatile unsigned char RX2_CHFLT_COE_07: 8;
                        volatile unsigned char RX2_CHFLT_COE_06: 8;
                        volatile unsigned char RX2_CHFLT_COE_05: 8;
                        volatile unsigned char RX2_CHFLT_COE_04: 8;
                        volatile unsigned char RX2_CHFLT_COE_03: 8;
                        volatile unsigned char RX2_CHFLT_COE_02: 8;
                        volatile unsigned char RX2_CHFLT_COE_01: 8;
                        volatile unsigned char RX2_CHFLT_COE_00: 8;
                        volatile unsigned char RX2_CHFLT_COE13:  2;
                        volatile unsigned char RX2_CHFLT_COE12:  2;
                        volatile unsigned char RX2_CHFLT_COE11:  2;
                        volatile unsigned char RX2_CHFLT_COE10:  2;
                        volatile unsigned char RX2_CHFLT_COE09:  2;
                        volatile unsigned char RX2_CHFLT_COE08:  2;
                        volatile unsigned char RX2_CHFLT_COE07:  2;
                        volatile unsigned char RX2_CHFLT_COE06:  2;
                        volatile unsigned char RX2_CHFLT_COE05:  2;
                        volatile unsigned char RX2_CHFLT_COE04:  2;
                        volatile unsigned char RX2_CHFLT_COE03:  2;
                        volatile unsigned char RX2_CHFLT_COE02:  2;
                        volatile unsigned char RX2_CHFLT_COE01:  2;
                        volatile unsigned char RX2_CHFLT_COE00:  2;
                        volatile unsigned char NONE_1:           4;
                    }Field;
                }MODEM_CHFLT_RX2_CHFLT_COE;                      // 191-208
            }Field;
            unsigned char Bytes[36];
      }GROUP_21;
      union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char PA_MODE: 1;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char PA_SEL: 4;
                        volatile unsigned char NONE_2: 1;
                        volatile unsigned char EXT_PA_RAMP: 1;
                    }Field;
                }PA_MODE;                                        // 208

                union
                {
                    struct
                    {
                        volatile unsigned char DDAC: 7;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }PA_PWR_LVL;                                     // 210

                union
                {
                    struct
                    {
                        volatile unsigned char _OB: 6;
                        volatile unsigned char CLK_DUTY: 2;
                    }Field;
                }PA_BIAS_CLKDUTY;                                // 211

                union
                {
                    struct
                    {
                        volatile unsigned char TC: 5;
                        volatile unsigned char FSK_MOD_DLY: 3;
                    }Field;
                }PA_TC;                                          // 212

                union
                {
                    struct
                    {
                        volatile unsigned char TC: 4;
                        volatile unsigned char NONE_1: 4;
                    }Field;
                }PA_RAMP_EX;                                     // 213

                union
                {
                    struct
                    {
                        volatile unsigned char RAMP_DOWN_DELAY: 8;
                    }Field;
                }PA_RAMP_DOWN_DELAY;                             // 214
            }Field;
            unsigned char Bytes[6];
      }GROUP_22;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char CP_FF_CUR: 6;
                        volatile unsigned char CP_FF_CUR_TEST: 1;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }SYNTH_PFDCP_CPFF;                               // 215

                union
                {
                    struct
                    {
                        volatile unsigned char CP_INT_CUR: 4;
                        volatile unsigned char NONE_1: 4;
                    }Field;
                }SYNTH_PFDCP_CPINT;                              // 216

                union
                {
                    struct
                    {
                        volatile unsigned char KV_INT: 2;
                        volatile unsigned char KV_DIR: 2;
                        volatile unsigned char RESERVED: 1;
                        volatile unsigned char NONE_1: 3;
                    }Field;
                }SYNTH_VCO_KV;                                   // 217

                union
                {
                    struct
                    {
                        volatile unsigned char LPF_FF_R2: 3;
                        volatile unsigned char NONE_1: 5;
                    }Field;
                }SYNTH_LPFILT3;                                  // 218

                union
                {
                    struct
                    {
                        volatile unsigned char LPF_FF_C2: 5;
                        volatile unsigned char NONE_1: 3;
                    }Field;
                }SYNTH_LPFILT2;                                  // 219

                union
                {
                    struct
                    {
                        volatile unsigned char LPF_FF_C3: 2;
                        volatile unsigned char LPF_FF_C1_CODE: 2;
                        volatile unsigned char LPF_FF_C1: 3;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }SYNTH_LPFILT1;                                  // 220

                union
                {
                    struct
                    {
                        volatile unsigned char LPF_FF_BIAS: 2;
                        volatile unsigned char NONE_1: 6;
                    }Field;
                }SYNTH_LPFILT0;                                  // 221

                union
                {
                    struct
                    {
                        volatile unsigned char KVCAL: 4;
                        volatile unsigned char LADR_SELECT: 1;
                        volatile unsigned char NONE_1: 3;
                    }Field;
                }SYNTH_VCO_KVCAL;                                // 222
            }Field;
            unsigned char Bytes[8];
      }GROUP_23;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char VALUE_1: 8;
                    }Field;
                }MATCH_VALUE_1;                                  // 223

                union
                {
                    struct
                    {
                        volatile unsigned char MASK_1: 8;
                    }Field;
                }MATCH_MASK_1;                                   // 224

                union
                {
                    struct
                    {
                        volatile unsigned char OFFSET: 5;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char MATCH_EN: 1;
                        volatile unsigned char POLARITY: 1;
                    }Field;
                }MATCH_CTRL_1;                                   // 225

                union
                {
                    struct
                    {
                        volatile unsigned char VALUE_2: 8;
                    }Field;
                }MATCH_VALUE_2;                                  // 226

                union
                {
                    struct
                    {
                        volatile unsigned char MASK_2: 8;
                    }Field;
                }MATCH_MASK_2;                                   // 227

                union
                {
                    struct
                    {
                        volatile unsigned char OFFSET: 5;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char LOGIC: 1;
                        volatile unsigned char POLARITY: 1;
                    }Field;
                }MATCH_CTRL_2;                                   // 228

                union
                {
                    struct
                    {
                        volatile unsigned char VALUE_3: 8;
                    }Field;
                }MATCH_VALUE_3;                                  // 229

                union
                {
                    struct
                    {
                        volatile unsigned char MASK_3: 8;
                    }Field;
                }MATCH_MASK_3;                                   // 230

                union
                {
                    struct
                    {
                        volatile unsigned char OFFSET: 5;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char LOGIC: 1;
                        volatile unsigned char POLARITY: 1;
                    }Field;
                }MATCH_CTRL_3;                                   // 231

                union
                {
                    struct
                    {
                        volatile unsigned char VALUE_4: 8;
                    }Field;
                }MATCH_VALUE_4;                                  // 232

                union
                {
                    struct
                    {
                        volatile unsigned char MASK_4: 8;
                    }Field;
                }MATCH_MASK_4;                                   // 233

                union
                {
                    struct
                    {
                        volatile unsigned char OFFSET: 5;
                        volatile unsigned char NONE_1: 1;
                        volatile unsigned char LOGIC: 1;
                        volatile unsigned char POLARITY: 1;
                    }Field;
                }MATCH_CTRL_4;                                   // 234
            }Field;
            unsigned char Bytes[12];
      }GROUP_30;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char INTE: 7;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }FREQ_CONTROL_INTE;                              // 235

                union
                {
                    struct
                    {
                        volatile unsigned char FRAC_2: 4;
                        volatile unsigned char NONE_1: 4;
                        volatile unsigned char FRAC_1: 8;
                        volatile unsigned char FRAC_0: 8;
                    }Field;
                }FREQ_CONTROL_FRAC;                              // 236-238

                union
                {
                    struct
                    {
                        volatile unsigned char CHANNEL_STEP_SIZE_1: 8;
                        volatile unsigned char CHANNEL_STEP_SIZE_0: 8;
                    }Field;
                }FREQ_CONTROL_CHANNEL_STEP_SIZE;                 // 239-240

                union
                {
                    struct
                    {
                        volatile unsigned char W_SIZE: 8;
                    }Field;
                }FREQ_CONTROL_W_SIZE;                            // 241

                union
                {
                    struct
                    {
                        volatile unsigned char VCOCNT_RX_ADJ: 8;
                    }Field;
                }FREQ_CONTROL_VCOCNT_RX_ADJ;                     // 242
            }Field;
            unsigned char Bytes[8];
      }GROUP_40;
        union
        {
            struct
            {
                union
                {
                    struct
                    {
                        volatile unsigned char RSSI_TIMEOUT: 4;
                        volatile unsigned char HOP_EN: 3;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }RX_HOP_CONTROL;                                 // 243

                union
                {
                    struct
                    {
                        volatile unsigned char RX_HOP_TABLE_SIZE: 7;
                        volatile unsigned char NONE_1: 1;
                    }Field;
                }RX_HOP_TABLE_SIZE;                              // 244

                volatile char  RX_HOP_TABLE_ENTRY[64];           // 245-308
            }Field;
            unsigned char Bytes[66];
        }GROUP_50;
    }Field;
} SI4463_PROPERTYS_structur;

typedef union GPIO_PIN_CFG_Type
{
    struct
    {
        union
        {
            struct
            {
              volatile unsigned char GPIO_MODE:  6;
                volatile unsigned char NONE_1:     1;
              volatile unsigned char GPIO_STATE: 1;
            }Field;
        } GPIO_0;
        union
        {
            struct
            {
              volatile unsigned char GPIO_MODE:  6;
                volatile unsigned char NONE_1:     1;
              volatile unsigned char GPIO_STATE: 1;
            }Field;
        } GPIO_1;
        union
        {
            struct
            {
              volatile unsigned char GPIO_MODE:  6;
                volatile unsigned char NONE_1:     1;
              volatile unsigned char GPIO_STATE: 1;
            }Field;
        } GPIO_2;
        union
        {
            struct
            {
              volatile unsigned char GPIO_MODE:  6;
                volatile unsigned char NONE_1:     1;
              volatile unsigned char GPIO_STATE: 1;
            }Field;
        } GPIO_3;
        union
        {
            struct
            {
              volatile unsigned char NIRQ_MODE:  6;
                volatile unsigned char NONE_1:     1;
              volatile unsigned char NIRQ_STATE: 1;
            }Field;
        } NIRQ;
        union
        {
            struct
            {
              volatile unsigned char SDO_MODE:  6;
                volatile unsigned char NONE_1:    1;
              volatile unsigned char SDO_STATE: 1;
            }Field;
        } SDO;
        union
        {
            struct
            {
              volatile unsigned char NONE_1:       5;
                volatile unsigned char DRV_STRENGTH: 2;
              volatile unsigned char NONE_2:       1;
            }Field;
        } GEN_CONFIG;
    }Field;
} SI4463_GPIO_PIN_CFG_structur;

typedef union PART_INFO_Type
{
    struct
    {
        volatile unsigned char  CHIPREV:    8;
        union
        {
            struct
            {
              volatile unsigned char PART_1:  8;
              volatile unsigned char PART_0:  8;
            }Field;
        } PART;
        volatile unsigned char  PBUILD:     8;
        union
        {
            struct
            {
              volatile unsigned char ID_1:    8;
              volatile unsigned char ID_0:    8;
            }Field;
        } ID;
        volatile unsigned char  CUSTOMER:   8;
        volatile unsigned char  ROMID:      8;

        volatile unsigned char  REVEXT:     8;
        volatile unsigned char  REVBRANCH:  8;
        volatile unsigned char  REVINT:     8;
        union
        {
            struct
            {
              volatile unsigned char PATCH_1: 8;
              volatile unsigned char PATCH_0: 8;
            }Field;
        } PATCH;
        volatile unsigned char  FUNC:       8;

        union
        {
            struct
            {
              volatile unsigned char MAIN_STATE: 4;
              volatile unsigned char NONE_1:     4;
            }Field;
        } CURR_STATE;

        volatile unsigned char  CURRENT_CHANNEL: 8;
    }Field;
} SI4463_PART_INFO_structur;

typedef union SI4463_INTERUPTS_Type
{
    struct
    {
        union
        {
            struct
            {
              volatile unsigned char PH_INT_PEND: 1;
              volatile unsigned char MODEM_INT_PEND: 1;
                volatile unsigned char CHIP_INT_PEND: 1;
                volatile unsigned char NONE_1: 5;
            }Field;
        }GLOBAL_INT_PEND;

        union
        {
            struct
            {
              volatile unsigned char WUT: 1;
              volatile unsigned char LOW_BATT: 1;
                volatile unsigned char CHIP_READY: 1;
                volatile unsigned char CMD_ERROR: 1;
                volatile unsigned char STATE_CHANGE: 1;
                volatile unsigned char FIFO_UNDERFLOW_OVERFLOW_ERROR: 1;
                volatile unsigned char CAL: 1;
                volatile unsigned char NONE_1: 1;
            }Field;
        }CHIP_PEND;
        union
        {
            struct
            {
              volatile unsigned char WUT: 1;
              volatile unsigned char LOW_BATT: 1;
                volatile unsigned char CHIP_READY: 1;
                volatile unsigned char CMD_ERROR: 1;
                volatile unsigned char STATE_CHANGE: 1;
                volatile unsigned char FIFO_UNDERFLOW_OVERFLOW_ERROR: 1;
                volatile unsigned char CAL: 1;
                volatile unsigned char NONE_1: 1;
            }Field;
        }INT_CHIP_STATUS;
        union
        {
            struct
            {
              volatile unsigned char CMD_ERR_STATUS: 8;
            }Field;
        }CMD_ERR_STATUS;
        union
        {
            struct
            {
              volatile unsigned char CMD_ERR_CMD_ID: 8;
            }Field;
        }CMD_ERR_CMD_ID;
        union
        {
            struct
            {
              volatile unsigned char RX_FIFO_ALMOST_FULL: 1;
              volatile unsigned char TX_FIFO_ALMOST_EMPTY: 1;
                volatile unsigned char NONE_1: 1;
                volatile unsigned char CRC_ERROR: 1;
                volatile unsigned char PACKET_RX: 1;
                volatile unsigned char PACKET_SENT: 1;
                volatile unsigned char FILTER_MISS: 1;
                volatile unsigned char FILTER_MATCH: 1;
            }Field;
        }PH_PEND;
        union
        {
            struct
            {
              volatile unsigned char RX_FIFO_ALMOST_FULL: 1;
              volatile unsigned char TX_FIFO_ALMOST_EMPTY: 1;
                volatile unsigned char NONE_1: 1;
                volatile unsigned char CRC_ERROR: 1;
                volatile unsigned char PACKET_RX: 1;
                volatile unsigned char PACKET_SENT: 1;
                volatile unsigned char FILTER_MISS: 1;
                volatile unsigned char FILTER_MATCH: 1;
            }Field;
        }INT_PH_STATUS;
        union
        {
            struct
            {
              volatile unsigned char SYNC_DETECT: 1;
              volatile unsigned char PREAMBLE_DETECT: 1;
                volatile unsigned char INVALID_PREAMBLE: 1;
                volatile unsigned char RSSI: 1;
                volatile unsigned char RSSI_JUMP: 1;
                volatile unsigned char INVALID_SYNC: 1;
                volatile unsigned char POSTAMBLE_DETECT: 1;
                volatile unsigned char NONE_1: 1;
            }Field;
        }MODEM_PEND;
        union
        {
            struct
            {
              volatile unsigned char SYNC_DETECT: 1;
              volatile unsigned char PREAMBLE_DETECT: 1;
                volatile unsigned char INVALID_PREAMBLE: 1;
                volatile unsigned char RSSI: 1;
                volatile unsigned char RSSI_JUMP: 1;
                volatile unsigned char INVALID_SYNC: 1;
                volatile unsigned char POSTAMBLE_DETECT: 1;
                volatile unsigned char NONE_1: 1;
            }Field;
        }INT_MODEM_STATUS;
        union
        {
            struct
            {
              volatile unsigned char CURR_RSSI_1: 8;
              volatile unsigned char CURR_RSSI_0: 8;
            }Field;
        }CURR_RSSI;
        union
        {
            struct
            {
                volatile unsigned char LATCH_RSSI_1: 8;
                volatile unsigned char LATCH_RSSI_0: 8;
            }Field;
        }LATCH_RSSI;
        union
        {
            struct
            {
              volatile unsigned char ANT1_RSSI_1: 8;
              volatile unsigned char ANT1_RSSI_0: 8;
            }Field;
        }ANT1_RSSI;
        union
        {
            struct
            {
              volatile unsigned char ANT2_RSSI_1: 8;
              volatile unsigned char ANT2_RSSI_0: 8;
            }Field;
        }ANT2_RSSI;
        union
        {
            struct
            {
                volatile unsigned char AFC_FREQ_OFFSET_3: 8;
                volatile unsigned char AFC_FREQ_OFFSET_2: 8;
                volatile unsigned char AFC_FREQ_OFFSET_1: 8;
                volatile unsigned char AFC_FREQ_OFFSET_0: 8;
            }Field;
        }AFC_FREQ_OFFSET;
    }Field;
} SI4463_INTERUPTS_structur;

#endif // SI4463_PROPERTYS_TYPE

