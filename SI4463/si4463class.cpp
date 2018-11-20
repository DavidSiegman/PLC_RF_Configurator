#include "SI4463/si4463class.h"

SI4463Class::SI4463Class(QObject *parent) : QObject(parent)
{
    this->Color1 = new QColor(255,224,231,180);
    this->Color2 = new QColor(240,215,225,200);

    this->SI4463_PROPERTYS_BytesNumber = (uint)&(SI4463_PROPERTYS.Field.GROUP_50.Bytes[66]) - (uint)&(SI4463_PROPERTYS.Field.GROUP_00.Bytes[0]);

    this->GROUP_00_BytesNumber         = 10;
    this->GROUP_01_BytesNumber         = 4;
    this->GROUP_02_BytesNumber         = 4;
    this->GROUP_10_BytesNumber         = 14;
    this->GROUP_11_BytesNumber         = 5;
    this->GROUP_12_BytesNumber         = 53;
    this->GROUP_20_BytesNumber         = 82;
    this->GROUP_21_BytesNumber         = 36;
    this->GROUP_22_BytesNumber         = 6;
    this->GROUP_23_BytesNumber         = 8;
    this->GROUP_30_BytesNumber         = 12;
    this->GROUP_40_BytesNumber         = 8;
    this->GROUP_50_BytesNumber         = 66;

    this->SI4463_PROPERTYS_NAME.append("GLOBAL_XO_TUNE");                   // 0
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_CLK_CFG");                   // 1
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_LOW_BATT_THRESH");           // 2
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_CONFIG");                    // 3
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_WUT_CONFIG");                // 4
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_WUT_M_2");                   // 5
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_WUT_M_1");                   // 6
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_WUT_R");                     // 7
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_WUT_LDC");                   // 8
    this->SI4463_PROPERTYS_NAME.append("GLOBAL_WUT_CAL");                   // 9
    this->SI4463_PROPERTYS_NAME.append("INT_CTL_ENABLE");                   // 10
    this->SI4463_PROPERTYS_NAME.append("INT_CTL_PH_ENABLE");                // 11
    this->SI4463_PROPERTYS_NAME.append("INT_CTL_MODEM_ENABLE");             // 12
    this->SI4463_PROPERTYS_NAME.append("INT_CTL_CHIP_ENABLE");              // 13
    this->SI4463_PROPERTYS_NAME.append("FRR_CTL_A_MODE");                   // 14
    this->SI4463_PROPERTYS_NAME.append("FRR_CTL_B_MODE");                   // 15
    this->SI4463_PROPERTYS_NAME.append("FRR_CTL_C_MODE");                   // 16
    this->SI4463_PROPERTYS_NAME.append("FRR_CTL_D_MODE");                   // 17
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_TX_LENGTH");               // 18
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_CONFIG_STD_1");            // 19
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_CONFIG_NSTD");             // 20
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_CONFIG_STD_2");            // 21
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_CONFIG");                  // 22
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_PATTERN_31_24");           // 23
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_PATTERN_23_16");           // 24
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_PATTERN_15_8");            // 25
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_PATTERN_7_0");             // 26
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_POSTAMBLE_CONFIG  ");      // 27
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_POSTAMBLE_PATTERN_3");     // 28
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_POSTAMBLE_PATTERN_2");     // 29
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_POSTAMBLE_PATTERN_1");     // 30
    this->SI4463_PROPERTYS_NAME.append("PREAMBLE_POSTAMBLE_PATTERN_0");     // 31
    this->SI4463_PROPERTYS_NAME.append("SYNC_CONFIG");                      // 32
    this->SI4463_PROPERTYS_NAME.append("SYNC_BITS_31_24");                  // 33
    this->SI4463_PROPERTYS_NAME.append("SYNC_BITS_23_16");                  // 34
    this->SI4463_PROPERTYS_NAME.append("SYNC_BITS_15_8");                   // 35
    this->SI4463_PROPERTYS_NAME.append("SYNC_BITS_7_0");                    // 36
    this->SI4463_PROPERTYS_NAME.append("PKT_CRC_CONFIG");                   // 37
    this->SI4463_PROPERTYS_NAME.append("PKT_WHT_POLY_15_8");                // 38
    this->SI4463_PROPERTYS_NAME.append("PKT_WHT_POLY_7_0");                 // 39
    this->SI4463_PROPERTYS_NAME.append("PKT_WHT_SEED_15_8");                // 40
    this->SI4463_PROPERTYS_NAME.append("PKT_WHT_SEED_7_0");                 // 41
    this->SI4463_PROPERTYS_NAME.append("PKT_WHT_BIT_NUM");                  // 42
    this->SI4463_PROPERTYS_NAME.append("PKT_CONFIG1");                      // 43
    this->SI4463_PROPERTYS_NAME.append("SI4463_NONE_1");                    // 44
    this->SI4463_PROPERTYS_NAME.append("PKT_LEN");                          // 45
    this->SI4463_PROPERTYS_NAME.append("PKT_LEN_FIELD_SOURCE");             // 46
    this->SI4463_PROPERTYS_NAME.append("PKT_LEN_ADJUST");                   // 47
    this->SI4463_PROPERTYS_NAME.append("PKT_TX_THRESHOLD");                 // 48
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_THRESHOLD");                 // 49
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_1_LENGTH_12_8");          // 50
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_1_LENGTH_7_0");           // 51
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_1_CONFIG");               // 52
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_1_CRC_CONFIG");           // 53
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_2_LENGTH_12_8");          // 54
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_2_LENGTH_7_0");           // 55
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_2_CONFIG");               // 56
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_2_CRC_CONFIG");           // 57
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_3_LENGTH_12_8");          // 58
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_3_LENGTH_7_0");           // 59
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_3_CONFIG");               // 60
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_3_CRC_CONFIG");           // 61
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_4_LENGTH_12_8");          // 62
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_4_LENGTH_7_0");           // 63
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_4_CONFIG");               // 64
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_4_CRC_CONFIG");           // 65
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_5_LENGTH_12_8");          // 66
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_5_LENGTH_7_0");           // 67
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_5_CONFIG");               // 68
    this->SI4463_PROPERTYS_NAME.append("PKT_FIELD_5_CRC_CONFIG");           // 69
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_1_LENGTH_12_8");       // 70
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_1_LENGTH_7_0");        // 71
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_1_CONFIG");            // 72
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_1_CRC_CONFIG");        // 73
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_2_LENGTH_12_8");       // 74
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_2_LENGTH_7_0");        // 75
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_2_CONFIG");            // 76
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_2_CRC_CONFIG");        // 77
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_3_LENGTH_12_8");       // 78
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_3_LENGTH_7_0");        // 79
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_3_CONFIG");            // 80
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_3_CRC_CONFIG");        // 81
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_4_LENGTH_12_8");       // 82
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_4_LENGTH_7_0");        // 83
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_4_CONFIG");            // 84
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_4_CRC_CONFIG");        // 85
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_5_LENGTH_12_8");       // 86
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_5_LENGTH_7_0");        // 87
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_5_CONFIG");            // 88
    this->SI4463_PROPERTYS_NAME.append("PKT_RX_FIELD_5_CRC_CONFIG");        // 89
    this->SI4463_PROPERTYS_NAME.append("MODEM_MOD_TYPE");                   // 90
    this->SI4463_PROPERTYS_NAME.append("MODEM_MAP_CONTROL");                // 91
    this->SI4463_PROPERTYS_NAME.append("MODEM_DSM_CTRL");                   // 92
    this->SI4463_PROPERTYS_NAME.append("MODEM_DATA_RATE_2");                // 93
    this->SI4463_PROPERTYS_NAME.append("MODEM_DATA_RATE_1");                // 94
    this->SI4463_PROPERTYS_NAME.append("MODEM_DATA_RATE_0");                // 95
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_NCO_MODE_3");              // 96
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_NCO_MODE_2");              // 97
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_NCO_MODE_1");              // 98
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_NCO_MODE_0");              // 99
    this->SI4463_PROPERTYS_NAME.append("MODEM_FREQ_DEV_2");                 // 100
    this->SI4463_PROPERTYS_NAME.append("MODEM_FREQ_DEV_1");                 // 101
    this->SI4463_PROPERTYS_NAME.append("MODEM_FREQ_DEV_0");                 // 102
    this->SI4463_PROPERTYS_NAME.append("MODEM_FREQ_OFFSET_1");              // 103
    this->SI4463_PROPERTYS_NAME.append("MODEM_FREQ_OFFSET_0");              // 104
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_8");          // 105
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_7");          // 106
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_6");          // 107
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_5");          // 108
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_4");          // 109
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_3");          // 110
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_2");          // 111
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_1");          // 112
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_FILTER_COEFF_0");          // 113
    this->SI4463_PROPERTYS_NAME.append("MODEM_TX_RAMP_DELAY");              // 114
    this->SI4463_PROPERTYS_NAME.append("MODEM_MDM_CTRL");                   // 115
    this->SI4463_PROPERTYS_NAME.append("MODEM_IF_CONTROL");                 // 116
    this->SI4463_PROPERTYS_NAME.append("MODEM_IF_FREQ_2");                  // 117
    this->SI4463_PROPERTYS_NAME.append("MODEM_IF_FREQ_1");                  // 118
    this->SI4463_PROPERTYS_NAME.append("MODEM_IF_FREQ_0");                  // 119
    this->SI4463_PROPERTYS_NAME.append("MODEM_DECIMATION_CFG1");            // 120
    this->SI4463_PROPERTYS_NAME.append("MODEM_DECIMATION_CFG0");            // 121
    this->SI4463_PROPERTYS_NAME.append("SI4463_NONE_2");                    // 122
    this->SI4463_PROPERTYS_NAME.append("SI4463_NONE_3");                    // 123
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_OSR_1");                  // 124
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_OSR_0");                  // 125
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_NCO_OFFSET_2");           // 126
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_NCO_OFFSET_1");           // 127
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_NCO_OFFSET_0");           // 128
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_GAIN_1");                 // 129
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_GAIN_0");                 // 130
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_GEAR");                   // 131
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_MISC1");                  // 132
    this->SI4463_PROPERTYS_NAME.append("MODEM_BCR_MISC0");                  // 133
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_GEAR");                   // 134
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_WAIT");                   // 135
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_GAIN_1");                 // 136
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_GAIN_0");                 // 137
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_LIMITER_1");              // 138
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_LIMITER_0");              // 139
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_MISC");                   // 140
    this->SI4463_PROPERTYS_NAME.append("MODEM_AFC_ZIFOFF");                 // 141
    this->SI4463_PROPERTYS_NAME.append("MODEM_ADC_CTRL");                   // 142
    this->SI4463_PROPERTYS_NAME.append("MODEM_AGC_CONTROL");                // 143
    this->SI4463_PROPERTYS_NAME.append("SI4463_NONE_4");                    // 144
    this->SI4463_PROPERTYS_NAME.append("SI4463_NONE_5");                    // 145
    this->SI4463_PROPERTYS_NAME.append("MODEM_AGC_WINDOW_SIZE");            // 146
    this->SI4463_PROPERTYS_NAME.append("MODEM_AGC_RFPD_DECAY");             // 147
    this->SI4463_PROPERTYS_NAME.append("MODEM_AGC_IFPD_DECAY");             // 148
    this->SI4463_PROPERTYS_NAME.append("MODEM_FSK4_GAIN1");                 // 149
    this->SI4463_PROPERTYS_NAME.append("MODEM_FSK4_GAIN0");                 // 150
    this->SI4463_PROPERTYS_NAME.append("MODEM_FSK4_TH1");                   // 151
    this->SI4463_PROPERTYS_NAME.append("MODEM_FSK4_TH0");                   // 152
    this->SI4463_PROPERTYS_NAME.append("MODEM_FSK4_MAP");                   // 153
    this->SI4463_PROPERTYS_NAME.append("MODEM_OOK_PDTC");                   // 154
    this->SI4463_PROPERTYS_NAME.append("MODEM_OOK_BLOPK");                  // 155
    this->SI4463_PROPERTYS_NAME.append("MODEM_OOK_CNT1");                   // 156
    this->SI4463_PROPERTYS_NAME.append("MODEM_OOK_MISC");                   // 157
    this->SI4463_PROPERTYS_NAME.append("MODEM_RAW_SEARCH");                 // 158
    this->SI4463_PROPERTYS_NAME.append("MODEM_RAW_CONTROL");                // 159
    this->SI4463_PROPERTYS_NAME.append("MODEM_RAW_EYE_1");                  // 160
    this->SI4463_PROPERTYS_NAME.append("MODEM_RAW_EYE_0");                  // 161
    this->SI4463_PROPERTYS_NAME.append("MODEM_ANT_DIV_MODE");               // 162
    this->SI4463_PROPERTYS_NAME.append("MODEM_ANT_DIV_CONTROL");            // 163
    this->SI4463_PROPERTYS_NAME.append("MODEM_RSSI_THRESH");                // 164
    this->SI4463_PROPERTYS_NAME.append("MODEM_RSSI_JUMP_THRESH");           // 165
    this->SI4463_PROPERTYS_NAME.append("MODEM_RSSI_CONTROL");               // 166
    this->SI4463_PROPERTYS_NAME.append("MODEM_RSSI_CONTROL2");              // 167
    this->SI4463_PROPERTYS_NAME.append("MODEM_RSSI_COMP");                  // 168
    this->SI4463_PROPERTYS_NAME.append("SI4463_NONE_6");                    // 169
    this->SI4463_PROPERTYS_NAME.append("SI4463_NONE_7");                    // 170
    this->SI4463_PROPERTYS_NAME.append("MODEM_CLKGEN_BAND");                // 171
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE13_7_0");  // 172
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE12_7_0");  // 173
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE11_7_0");  // 174
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE10_7_0");  // 175
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE9_7_0");   // 176
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE8_7_0");   // 177
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE7_7_0");   // 178
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE6_7_0");   // 179
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE5_7_0");   // 180
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE4_7_0");   // 181
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE3_7_0");   // 182
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE2_7_0");   // 183
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE1_7_0");   // 184
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COE0_7_0");   // 185
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COEM0");      // 186
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COEM1");      // 187
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COEM2");      // 188
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX1_CHFLT_COEM3");      // 189
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE13_7_0");  // 190
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE12_7_0");  // 191
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE11_7_0");  // 192
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE10_7_0");  // 193
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE9_7_0");   // 194
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE8_7_0");   // 195
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE7_7_0");   // 196
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE6_7_0");   // 197
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE5_7_0");   // 198
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE4_7_0");   // 199
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE3_7_0");   // 200
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE2_7_0");   // 201
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE1_7_0");   // 202
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COE0_7_0");   // 203
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COEM0");      // 204
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COEM1");      // 205
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COEM2");      // 206
    this->SI4463_PROPERTYS_NAME.append("MODEM_CHFLT_RX2_CHFLT_COEM3");      // 207
    this->SI4463_PROPERTYS_NAME.append("PA_MODE");                          // 208
    this->SI4463_PROPERTYS_NAME.append("PA_PWR_LVL");                       // 209
    this->SI4463_PROPERTYS_NAME.append("PA_BIAS_CLKDUTY");                  // 210
    this->SI4463_PROPERTYS_NAME.append("PA_TC");                            // 211
    this->SI4463_PROPERTYS_NAME.append("PA_RAMP_EX");                       // 212
    this->SI4463_PROPERTYS_NAME.append("PA_RAMP_DOWN_DELAY");               // 213
    this->SI4463_PROPERTYS_NAME.append("SYNTH_PFDCP_CPFF");                 // 214
    this->SI4463_PROPERTYS_NAME.append("SYNTH_PFDCP_CPINT");                // 215
    this->SI4463_PROPERTYS_NAME.append("SYNTH_VCO_KV");                     // 216
    this->SI4463_PROPERTYS_NAME.append("SYNTH_LPFILT3");                    // 217
    this->SI4463_PROPERTYS_NAME.append("SYNTH_LPFILT2");                    // 218
    this->SI4463_PROPERTYS_NAME.append("SYNTH_LPFILT1");                    // 219
    this->SI4463_PROPERTYS_NAME.append("SYNTH_LPFILT0");                    // 220
    this->SI4463_PROPERTYS_NAME.append("SYNTH_VCO_KVCAL");                  // 221
    this->SI4463_PROPERTYS_NAME.append("MATCH_VALUE_1");                    // 222
    this->SI4463_PROPERTYS_NAME.append("MATCH_MASK_1");                     // 223
    this->SI4463_PROPERTYS_NAME.append("MATCH_CTRL_1");                     // 224
    this->SI4463_PROPERTYS_NAME.append("MATCH_VALUE_2");                    // 225
    this->SI4463_PROPERTYS_NAME.append("MATCH_MASK_2");                     // 226
    this->SI4463_PROPERTYS_NAME.append("MATCH_CTRL_2");                     // 227
    this->SI4463_PROPERTYS_NAME.append("MATCH_VALUE_3");                    // 228
    this->SI4463_PROPERTYS_NAME.append("MATCH_MASK_3");                     // 229
    this->SI4463_PROPERTYS_NAME.append("MATCH_CTRL_3");                     // 230
    this->SI4463_PROPERTYS_NAME.append("MATCH_VALUE_4");                    // 231
    this->SI4463_PROPERTYS_NAME.append("MATCH_MASK_4");                     // 232
    this->SI4463_PROPERTYS_NAME.append("MATCH_CTRL_4");                     // 233
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_INTE");                // 234
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_FRAC_2");              // 235
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_FRAC_1");              // 236
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_FRAC_0");              // 237
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_CHANNEL_STEP_SIZE_1"); // 238
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_CHANNEL_STEP_SIZE_0"); // 239
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_W_SIZE");              // 240
    this->SI4463_PROPERTYS_NAME.append("FREQ_CONTROL_VCOCNT_RX_ADJ");       // 241
    this->SI4463_PROPERTYS_NAME.append("RX_HOP_CONTROL");                   // 242
    this->SI4463_PROPERTYS_NAME.append("RX_HOP_TABLE_SIZE");                // 243
    this->SI4463_PROPERTYS_NAME.append("RX_HOP_TABLE_ENTRY");               // 244-307

    model = new QStandardItemModel;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Параметр");
    horizontalHeader.append("Свойства текущие");
    horizontalHeader.append("Свойства новые");
    horizontalHeader.append("Калибровка текущие");
    horizontalHeader.append("Калибровка новые");

    model->setHorizontalHeaderLabels(horizontalHeader);
    //QStringList verticalHeader;

    QStandardItem *item;
    QStandardItem *item1;
    QStandardItem *item2;
    QStandardItem *item3;
    QStandardItem *item4;
    for(int i = 0; i < SI4463_PROPERTYS_BytesNumber; i++)
    {
        item  = new QStandardItem("");
        item1 = new QStandardItem("");
        item2 = new QStandardItem("");
        item3 = new QStandardItem("");
        item4 = new QStandardItem("");

        item->setEditable(false);item->setCheckable(false);
        item1->setTextAlignment(Qt::AlignCenter);
        item1->setEditable(false);item1->setCheckable(false);
        item2->setTextAlignment(Qt::AlignCenter);
        item2->setEditable(false);item2->setCheckable(false);
        item3->setTextAlignment(Qt::AlignCenter);
        item3->setEditable(false);item3->setCheckable(false);
        item4->setTextAlignment(Qt::AlignCenter);
        item4->setEditable(false);item3->setCheckable(false);

        if(i < 244)
        {
            item->setText(this->SI4463_PROPERTYS_NAME.at(i));

        }
        else
        {
            item->setText(this->SI4463_PROPERTYS_NAME.at(244) + "_" + QString::number(i-244));

        }
        model->setItem(i, 0, item);
        model->setItem(i, 1, item1);
        model->setItem(i, 2, item2);
        model->setItem(i, 3, item3);
        model->setItem(i, 4, item4);
    }
}
void SI4463Class::aSI4463_SET_PROPERTYS(uchar GROUP, uchar START_PROP, uint PROP_COUNTER, uchar PROP_DATA, SI4463_PROPERTYS_structur* struc)
{
    QString S;
    QByteArray hex_item;
    uchar *group_adress = this->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP, struc);
    *(uchar*)(group_adress + PROP_COUNTER) = PROP_DATA;
    uint index = (uint)(group_adress + PROP_COUNTER) - (uint)&(struc->Field.GROUP_00.Bytes[0]);
    if (struc == aSI4463_PROPERTYS())
    {
        uchar *FFile_adress  = this->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP, aSI4463_PROPERTYS_FROM_FILE());
        *(uchar*)(FFile_adress + PROP_COUNTER) = PROP_DATA;
        hex_item.append(PROP_DATA);
        S = "0x" + hex_item.toHex().toUpper();
        model->item(index,1)->setText(S);
        model->item(index,2)->setText(S);
    }
    else if (struc == aSI4463_PROPERTYS_FROM_FILE())
    {
        uchar *SI4463_adress = this->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP, aSI4463_PROPERTYS());
        uchar *Calib_adress  = this->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP, aSI4463_PROPERTYS_CALIB());
        hex_item.append(PROP_DATA);
        S = "0x" + hex_item.toHex().toUpper();
        model->item(index,2)->setText(S);

        if (*(uchar*)(group_adress + PROP_COUNTER) != *(uchar*)(SI4463_adress + PROP_COUNTER))
        {
            QBrush b(*this->Color1);
            model->item(index,2)->setBackground(b);
        }
        else
        {
            QColor c(255,255,255,255); QBrush b(c);
            model->item(index,2)->setBackground(b);
        }
    }
    else if (struc == aSI4463_PROPERTYS_CALIB())
    {
        uchar *FFileCalib_adress  = this->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP, aSI4463_PROPERTYS_CALIB_FROM_FILE());
        *(uchar*)(FFileCalib_adress + PROP_COUNTER) = PROP_DATA;
        hex_item.append(PROP_DATA);
        S = "0x" + hex_item.toHex().toUpper();
        model->item(index,3)->setText(S);
        model->item(index,4)->setText(S);
    }
    else if (struc == aSI4463_PROPERTYS_CALIB_FROM_FILE())
    {
        uchar *SI4463Calib_adress = this->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP, aSI4463_PROPERTYS_CALIB());
        hex_item.append(PROP_DATA);
        S = "0x" + hex_item.toHex().toUpper();
        model->item(index,4)->setText(S);
        if (*(uchar*)(group_adress + PROP_COUNTER) != *(uchar*)(SI4463Calib_adress + PROP_COUNTER))
        {
            QBrush b(*this->Color1);
            model->item(index,4)->setBackground(b);
        }
        else
        {
            QColor c(255,255,255,255); QBrush b(c);
            model->item(index,4)->setBackground(b);
        }
    }
}

uchar SI4463Class::aSI4463_GET_PROPERTYS(uchar GROUP, uchar START_PROP, uint PROP_COUNTER, SI4463_PROPERTYS_structur* struc)
{
    uchar *group_adress = this->SI4463_Get_Group_Adress_From_RAM(GROUP, START_PROP, struc);
    return *(uchar*)(group_adress + PROP_COUNTER);
}

void SI4463Class::request_Model_handling()
{
    emit get_Model(model);
}

void SI4463Class::request_Prameters_handling()
{
    emit get_Prameters(&Parameters);
}

SI4463_PROPERTYS_structur*        SI4463Class::aSI4463_PROPERTYS(void)
{
    return &SI4463_PROPERTYS;
}
SI4463_PROPERTYS_structur*        SI4463Class::aSI4463_PROPERTYS_FROM_FILE(void)
{
    return &SI4463_PROPERTYS_FROM_FILE;
}
SI4463_PROPERTYS_structur*        SI4463Class::aSI4463_PROPERTYS_CALIB(void)
{
    return &SI4463_PROPERTYS_CALIB;
}
SI4463_PROPERTYS_structur*        SI4463Class::aSI4463_PROPERTYS_CALIB_FROM_FILE(void)
{
    return &SI4463_PROPERTYS_CALIB_FROM_FILE;
}
SI4463_PART_INFO_structur*        SI4463Class::aSI4463_PART_INFO(void)
{
    return &SI4463_PART_INFO;
}
SI4463_INTERUPTS_structur*        SI4463Class::aSI4463_INTERUPTS(void)
{
    return &SI4463_INTERUPTS;
}
SI4463_GPIO_PIN_CFG_structur*     SI4463Class::aSI4463_GPIO_PIN_CFG(void)
{
    return &SI4463_GPIO_PIN_CFG;
}


uchar* SI4463Class::SI4463_Get_Group_Adress_From_RAM(uchar GROUP, uchar START_PROP, SI4463_PROPERTYS_structur* struc)
{
    uchar *group_adress = 0;
    switch (GROUP)
    {
        case 0x00: // GLOBAL (0x00)
        {
            group_adress = (this->SI4463_PROPS_GROUP_00(struc) + START_PROP);
            break;
        }
        case 0x01: // INT_CTL (0x01)
        {
            group_adress = (this->SI4463_PROPS_GROUP_01(struc) + START_PROP);
            break;
        }
        case 0x02: // FRR_CTL (0x02)
        {
            group_adress = (this->SI4463_PROPS_GROUP_02(struc) + START_PROP);
            break;
        }
        case 0x10: // PREAMBLE (0x10)
        {
            group_adress = (this->SI4463_PROPS_GROUP_10(struc) + START_PROP);
            break;
        }
        case 0x11: // SYNC (0x11)
        {
            group_adress = (this->SI4463_PROPS_GROUP_11(struc) + START_PROP);
            break;
        }
        case 0x12: // PKT (0x12)
        {
            group_adress = (this->SI4463_PROPS_GROUP_12(struc) + START_PROP);
            break;
        }
        case 0x20: // MODEM (0x20)
        {
            group_adress = (this->SI4463_PROPS_GROUP_20(struc) + START_PROP);
            break;
        }
        case 0x21: // MODEM_CHFLT (0x21)
        {
            group_adress = (this->SI4463_PROPS_GROUP_21(struc) + START_PROP);
            break;
        }
        case 0x22: // PA (0x22)
        {
            group_adress = (this->SI4463_PROPS_GROUP_22(struc) + START_PROP);
            break;
        }
        case 0x23: // SYNTH (0x23)
        {
            group_adress = (this->SI4463_PROPS_GROUP_23(struc) + START_PROP);
            break;
        }
        case 0x30: // MATCH (0x30)
        {
            group_adress = (this->SI4463_PROPS_GROUP_30(struc) + START_PROP);
            break;
        }
        case 0x40: // FREQ_CONTROL (0x40)
        {
            group_adress = (this->SI4463_PROPS_GROUP_40(struc) + START_PROP);
            break;
        }
        case 0x50: // RX_HOP (0x50)
        {
            group_adress = (this->SI4463_PROPS_GROUP_50(struc) + START_PROP);
            break;
        }
    }
    return (uchar *)(group_adress);
}

uchar* SI4463Class::SI4463_PROPS_GROUP_00(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_00.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_01(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_01.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_02(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_02.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_10(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_10.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_11(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_11.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_12(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_12.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_20(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_20.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_21(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_21.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_22(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_22.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_23(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_23.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_30(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_30.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_40(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_40.Bytes);
}
uchar* SI4463Class::SI4463_PROPS_GROUP_50(SI4463_PROPERTYS_structur* struc)
{
    return (uchar *)(struc->Field.GROUP_50.Bytes);
}

