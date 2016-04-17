// RFM69.h
// Author: Phil Crump (phildcrump@gmail.com)
// Copyright (C) 2014 Phil Crump
// Based on RF22.h
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2011 Mike McCauley

#ifndef RFM69_h
#define RFM69_h

#define boolean bool

#define RFM69_SPI_WRITE_MASK 0x80

// This is the maximum message length that can be supported by this library. Limited by
// the single message length octet in the header. 
// Yes, 255 is correct even though the FIFO size in the RF22 is only
// 64 octets. We use interrupts to refill the Tx FIFO during transmission and to empty the
// Rx FIFO during reception
// Can be pre-defined to a smaller size (to save SRAM) prior to including this header
#define RFM69_MAX_MESSAGE_LEN 64

// Max number of octets the RFM69 FIFO can hold
#define RFM69_FIFO_SIZE 64

#define RFM69_MODE_SLEEP    0x00 // 0.1uA
#define RFM69_MODE_STDBY    0x04 // 1.25mA
#define RFM69_MODE_RX       0x10 // 16mA
#define RFM69_MODE_TX       0x0c // >33mA


// These values we set for FIFO thresholds are actually the same as the POR values
#define RF22_TXFFAEM_THRESHOLD 4
#define RF22_RXFFAFULL_THRESHOLD 55


// Register names

#define RFM69_REG_00_FIFO           0x00
#define RFM69_REG_01_OPMODE         0x01
#define RFM69_REG_02_DATA_MODUL     0x02
#define RFM69_REG_03_BITRATE_MSB    0x03
#define RFM69_REG_04_BITRATE_LSB    0x04
#define RFM69_REG_05_FDEV_MSB       0x05
#define RFM69_REG_06_FDEV_LSB       0x06
#define RFM69_REG_07_FRF_MSB        0x07
#define RFM69_REG_08_FRF_MID        0x08
#define RFM69_REG_09_FRF_LSB        0x09
#define RFM69_REG_0A_OSC1           0x0A
#define RFM69_REG_0B_AFC_CTRL       0x0B
#define RFM69_REG_0D_LISTEN1        0x0D
#define RFM69_REG_0E_LISTEN2        0x0E
#define RFM69_REG_0F_LISTEN3        0x0F
#define RFM69_REG_10_VERSION        0x10 //Version and serial number
#define RFM69_REG_11_PA_LEVEL       0x11
#define RFM69_REG_12_PA_RAMP        0x12
#define RFM69_REG_13_OCP            0x13
#define RFM69_REG_18_LNA            0x18
#define RFM69_REG_19_RX_BW          0x19
#define RFM69_REG_1A_AFC_BW         0x1A
#define RFM69_REG_1B_OOK_PEAK       0x1B
#define RFM69_REG_1C_OOK_AVG        0x1C
#define RFM69_REG_1D_OOF_FIX        0x1D
#define RFM69_REG_1E_AFC_FEI        0x1E
#define RFM69_REG_1F_AFC_MSB        0x1F
#define RFM69_REG_20_AFC_LSB        0x20
#define RFM69_REG_21_FEI_MSB        0x21
#define RFM69_REG_22_FEI_LSB        0x22
#define RFM69_REG_23_RSSI_CONFIG    0x23
#define RFM69_REG_24_RSSI_VALUE     0x24
#define RFM69_REG_25_DIO_MAPPING1   0x25
#define RFM69_REG_26_DIO_MAPPING2   0x26
#define RFM69_REG_27_IRQ_FLAGS1     0x27
#define RFM69_REG_28_IRQ_FLAGS2     0x28
#define RFM69_REG_29_RSSI_THRESHOLD 0x29
#define RFM69_REG_2A_RX_TIMEOUT1    0x2A
#define RFM69_REG_2B_RX_TIMEOUT2    0x2B
#define RFM69_REG_2C_PREAMBLE_MSB   0x2C
#define RFM69_REG_2D_PREAMBLE_LSB   0x2D
#define RFM69_REG_2E_SYNC_CONFIG    0x2E
#define RFM69_REG_2F_SYNCVALUE1     0x2F
#define RFM69_REG_30_SYNCVALUE2     0x30
// Sync values 1-8 go here
#define RFM69_REG_37_PACKET_CONFIG1 0x37
#define RFM69_REG_38_PAYLOAD_LENGTH 0x38
// Node address, broadcast address go here
#define RFM69_REG_3B_AUTOMODES      0x3B
#define RFM69_REG_3C_FIFO_THRESHOLD 0x3C
#define RFM69_REG_3D_PACKET_CONFIG2 0x3D
// AES Key 1-16 go here
#define RFM69_REG_4E_TEMP1          0x4E
#define RFM69_REG_4F_TEMP2          0x4F
#define RFM69_REG_58_TEST_LNA       0x58
#define RFM69_REG_5A_TEST_PA1       0x5A
#define RFM69_REG_5C_TEST_PA2       0x5C
#define RFM69_REG_6F_TEST_DAGC      0x6F
#define RFM69_REG_71_TEST_AFC       0x71

//******************************************************
// RF69/SX1231 bit control definition
//******************************************************
// RegOpMode
#define RF_OPMODE_SEQUENCER_OFF             0x80
#define RF_OPMODE_SEQUENCER_ON              0x00  // Default

#define RF_OPMODE_LISTEN_ON                     0x40
#define RF_OPMODE_LISTEN_OFF                    0x00  // Default

#define RF_OPMODE_LISTENABORT                   0x20

#define RF_OPMODE_SLEEP                           0x00
#define RF_OPMODE_STANDBY                         0x04  // Default
#define RF_OPMODE_SYNTHESIZER                   0x08
#define RF_OPMODE_TRANSMITTER                   0x0C
#define RF_OPMODE_RECEIVER                      0x10

// RegDataModul
#define RF_DATAMODUL_DATAMODE_PACKET                  0x00  // Default
#define RF_DATAMODUL_DATAMODE_CONTINUOUS            0x40
#define RF_DATAMODUL_DATAMODE_CONTINUOUSNOBSYNC 0x60

#define RF_DATAMODUL_MODULATIONTYPE_FSK             0x00  // Default
#define RF_DATAMODUL_MODULATIONTYPE_OOK             0x08

#define RF_DATAMODUL_MODULATIONSHAPING_00           0x00  // Default
#define RF_DATAMODUL_MODULATIONSHAPING_01           0x01
#define RF_DATAMODUL_MODULATIONSHAPING_10           0x02
#define RF_DATAMODUL_MODULATIONSHAPING_11           0x03

// RegOsc1
#define RF_OSC1_RCCAL_START             0x80
#define RF_OSC1_RCCAL_DONE              0x40

// RegAfcCtrl
#define RF_AFCLOWBETA_ON                    0x20
#define RF_AFCLOWBETA_OFF                   0x00    // Default

// RegLowBat
#define RF_LOWBAT_MONITOR                   0x10
#define RF_LOWBAT_ON                            0x08
#define RF_LOWBAT_OFF                           0x00  // Default

#define RF_LOWBAT_TRIM_1695             0x00
#define RF_LOWBAT_TRIM_1764             0x01
#define RF_LOWBAT_TRIM_1835             0x02  // Default
#define RF_LOWBAT_TRIM_1905             0x03
#define RF_LOWBAT_TRIM_1976             0x04
#define RF_LOWBAT_TRIM_2045             0x05
#define RF_LOWBAT_TRIM_2116             0x06
#define RF_LOWBAT_TRIM_2185             0x07


// RegListen1
#define RF_LISTEN1_RESOL_64             0x50
#define RF_LISTEN1_RESOL_4100           0xA0  // Default
#define RF_LISTEN1_RESOL_262000     0xF0

#define RF_LISTEN1_CRITERIA_RSSI                  0x00  // Default
#define RF_LISTEN1_CRITERIA_RSSIANDSYNC   0x08

#define RF_LISTEN1_END_00                             0x00
#define RF_LISTEN1_END_01                             0x02  // Default
#define RF_LISTEN1_END_10                             0x04


// RegListen2
#define RF_LISTEN2_COEFIDLE_VALUE               0xF5 // Default

// RegListen3
#define RF_LISTEN3_COEFRX_VALUE                 0x20 // Default

// RegPaLevel
#define RF_PALEVEL_PA0_ON         0x80  // Default
#define RF_PALEVEL_PA0_OFF      0x00
#define RF_PALEVEL_PA1_ON           0x40
#define RF_PALEVEL_PA1_OFF      0x00  // Default
#define RF_PALEVEL_PA2_ON           0x20
#define RF_PALEVEL_PA2_OFF      0x00  // Default


// RegPaRamp
#define RF_PARAMP_3400                      0x00
#define RF_PARAMP_2000                      0x01
#define RF_PARAMP_1000                      0x02
#define RF_PARAMP_500                           0x03
#define RF_PARAMP_250                           0x04
#define RF_PARAMP_125                           0x05
#define RF_PARAMP_100                           0x06
#define RF_PARAMP_62                            0x07
#define RF_PARAMP_50                            0x08
#define RF_PARAMP_40                            0x09  // Default
#define RF_PARAMP_31                            0x0A
#define RF_PARAMP_25                            0x0B
#define RF_PARAMP_20                            0x0C
#define RF_PARAMP_15                            0x0D
#define RF_PARAMP_12                            0x0E
#define RF_PARAMP_10                            0x0F


// RegOcp
#define RF_OCP_OFF                              0x0F
#define RF_OCP_ON                                 0x1A  // Default

#define RF_OCP_TRIM_45                      0x00
#define RF_OCP_TRIM_50                      0x01
#define RF_OCP_TRIM_55                      0x02
#define RF_OCP_TRIM_60                      0x03
#define RF_OCP_TRIM_65                      0x04
#define RF_OCP_TRIM_70                      0x05
#define RF_OCP_TRIM_75                      0x06
#define RF_OCP_TRIM_80                      0x07
#define RF_OCP_TRIM_85                      0x08
#define RF_OCP_TRIM_90                      0x09
#define RF_OCP_TRIM_95                      0x0A
#define RF_OCP_TRIM_100                     0x0B  // Default
#define RF_OCP_TRIM_105                     0x0C
#define RF_OCP_TRIM_110                     0x0D
#define RF_OCP_TRIM_115                     0x0E
#define RF_OCP_TRIM_120                     0x0F


// RegAgcRef
#define RF_AGCREF_AUTO_ON                   0x40  // Default
#define RF_AGCREF_AUTO_OFF              0x00

#define RF_AGCREF_LEVEL_MINUS80     0x00  // Default
#define RF_AGCREF_LEVEL_MINUS81     0x01
#define RF_AGCREF_LEVEL_MINUS82     0x02
#define RF_AGCREF_LEVEL_MINUS83     0x03
#define RF_AGCREF_LEVEL_MINUS84     0x04
#define RF_AGCREF_LEVEL_MINUS85     0x05
#define RF_AGCREF_LEVEL_MINUS86     0x06
#define RF_AGCREF_LEVEL_MINUS87     0x07
#define RF_AGCREF_LEVEL_MINUS88     0x08
#define RF_AGCREF_LEVEL_MINUS89     0x09
#define RF_AGCREF_LEVEL_MINUS90     0x0A
#define RF_AGCREF_LEVEL_MINUS91     0x0B
#define RF_AGCREF_LEVEL_MINUS92     0x0C
#define RF_AGCREF_LEVEL_MINUS93     0x0D
#define RF_AGCREF_LEVEL_MINUS94     0x0E
#define RF_AGCREF_LEVEL_MINUS95     0x0F
#define RF_AGCREF_LEVEL_MINUS96     0x10
#define RF_AGCREF_LEVEL_MINUS97     0x11
#define RF_AGCREF_LEVEL_MINUS98     0x12
#define RF_AGCREF_LEVEL_MINUS99     0x13
#define RF_AGCREF_LEVEL_MINUS100    0x14
#define RF_AGCREF_LEVEL_MINUS101    0x15
#define RF_AGCREF_LEVEL_MINUS102    0x16
#define RF_AGCREF_LEVEL_MINUS103    0x17
#define RF_AGCREF_LEVEL_MINUS104    0x18
#define RF_AGCREF_LEVEL_MINUS105    0x19
#define RF_AGCREF_LEVEL_MINUS106    0x1A
#define RF_AGCREF_LEVEL_MINUS107    0x1B
#define RF_AGCREF_LEVEL_MINUS108    0x1C
#define RF_AGCREF_LEVEL_MINUS109    0x1D
#define RF_AGCREF_LEVEL_MINUS110    0x1E
#define RF_AGCREF_LEVEL_MINUS111    0x1F
#define RF_AGCREF_LEVEL_MINUS112    0x20
#define RF_AGCREF_LEVEL_MINUS113    0x21
#define RF_AGCREF_LEVEL_MINUS114    0x22
#define RF_AGCREF_LEVEL_MINUS115    0x23
#define RF_AGCREF_LEVEL_MINUS116    0x24
#define RF_AGCREF_LEVEL_MINUS117    0x25
#define RF_AGCREF_LEVEL_MINUS118    0x26
#define RF_AGCREF_LEVEL_MINUS119    0x27
#define RF_AGCREF_LEVEL_MINUS120    0x28
#define RF_AGCREF_LEVEL_MINUS121    0x29
#define RF_AGCREF_LEVEL_MINUS122    0x2A
#define RF_AGCREF_LEVEL_MINUS123    0x2B
#define RF_AGCREF_LEVEL_MINUS124    0x2C
#define RF_AGCREF_LEVEL_MINUS125    0x2D
#define RF_AGCREF_LEVEL_MINUS126    0x2E
#define RF_AGCREF_LEVEL_MINUS127    0x2F
#define RF_AGCREF_LEVEL_MINUS128    0x30
#define RF_AGCREF_LEVEL_MINUS129    0x31
#define RF_AGCREF_LEVEL_MINUS130    0x32
#define RF_AGCREF_LEVEL_MINUS131    0x33
#define RF_AGCREF_LEVEL_MINUS132    0x34
#define RF_AGCREF_LEVEL_MINUS133    0x35
#define RF_AGCREF_LEVEL_MINUS134    0x36
#define RF_AGCREF_LEVEL_MINUS135    0x37
#define RF_AGCREF_LEVEL_MINUS136    0x38
#define RF_AGCREF_LEVEL_MINUS137    0x39
#define RF_AGCREF_LEVEL_MINUS138    0x3A
#define RF_AGCREF_LEVEL_MINUS139    0x3B
#define RF_AGCREF_LEVEL_MINUS140    0x3C
#define RF_AGCREF_LEVEL_MINUS141    0x3D
#define RF_AGCREF_LEVEL_MINUS142    0x3E
#define RF_AGCREF_LEVEL_MINUS143    0x3F


// RegAgcThresh1
#define RF_AGCTHRESH1_SNRMARGIN_000     0x00
#define RF_AGCTHRESH1_SNRMARGIN_001     0x20
#define RF_AGCTHRESH1_SNRMARGIN_010     0x40
#define RF_AGCTHRESH1_SNRMARGIN_011     0x60
#define RF_AGCTHRESH1_SNRMARGIN_100     0x80
#define RF_AGCTHRESH1_SNRMARGIN_101     0xA0  // Default
#define RF_AGCTHRESH1_SNRMARGIN_110     0xC0
#define RF_AGCTHRESH1_SNRMARGIN_111     0xE0

#define RF_AGCTHRESH1_STEP1_0                   0x00
#define RF_AGCTHRESH1_STEP1_1                   0x01
#define RF_AGCTHRESH1_STEP1_2                   0x02
#define RF_AGCTHRESH1_STEP1_3                   0x03
#define RF_AGCTHRESH1_STEP1_4                   0x04
#define RF_AGCTHRESH1_STEP1_5                   0x05
#define RF_AGCTHRESH1_STEP1_6                   0x06
#define RF_AGCTHRESH1_STEP1_7                   0x07
#define RF_AGCTHRESH1_STEP1_8                   0x08
#define RF_AGCTHRESH1_STEP1_9                   0x09
#define RF_AGCTHRESH1_STEP1_10              0x0A
#define RF_AGCTHRESH1_STEP1_11              0x0B
#define RF_AGCTHRESH1_STEP1_12              0x0C
#define RF_AGCTHRESH1_STEP1_13              0x0D
#define RF_AGCTHRESH1_STEP1_14              0x0E
#define RF_AGCTHRESH1_STEP1_15              0x0F
#define RF_AGCTHRESH1_STEP1_16              0x10  // Default
#define RF_AGCTHRESH1_STEP1_17              0x11
#define RF_AGCTHRESH1_STEP1_18              0x12
#define RF_AGCTHRESH1_STEP1_19              0x13
#define RF_AGCTHRESH1_STEP1_20              0x14
#define RF_AGCTHRESH1_STEP1_21              0x15
#define RF_AGCTHRESH1_STEP1_22              0x16
#define RF_AGCTHRESH1_STEP1_23              0x17
#define RF_AGCTHRESH1_STEP1_24              0x18
#define RF_AGCTHRESH1_STEP1_25              0x19
#define RF_AGCTHRESH1_STEP1_26              0x1A
#define RF_AGCTHRESH1_STEP1_27              0x1B
#define RF_AGCTHRESH1_STEP1_28              0x1C
#define RF_AGCTHRESH1_STEP1_29              0x1D
#define RF_AGCTHRESH1_STEP1_30              0x1E
#define RF_AGCTHRESH1_STEP1_31              0x1F


// RegAgcThresh2
#define RF_AGCTHRESH2_STEP2_0                   0x00
#define RF_AGCTHRESH2_STEP2_1                   0x10
#define RF_AGCTHRESH2_STEP2_2                   0x20
#define RF_AGCTHRESH2_STEP2_3                   0x30  // XXX wrong -- Default
#define RF_AGCTHRESH2_STEP2_4                   0x40
#define RF_AGCTHRESH2_STEP2_5                   0x50
#define RF_AGCTHRESH2_STEP2_6                   0x60
#define RF_AGCTHRESH2_STEP2_7                   0x70    // default
#define RF_AGCTHRESH2_STEP2_8                   0x80
#define RF_AGCTHRESH2_STEP2_9                   0x90
#define RF_AGCTHRESH2_STEP2_10              0xA0
#define RF_AGCTHRESH2_STEP2_11              0xB0
#define RF_AGCTHRESH2_STEP2_12              0xC0
#define RF_AGCTHRESH2_STEP2_13              0xD0
#define RF_AGCTHRESH2_STEP2_14              0xE0
#define RF_AGCTHRESH2_STEP2_15              0xF0

#define RF_AGCTHRESH2_STEP3_0                   0x00
#define RF_AGCTHRESH2_STEP3_1                   0x01
#define RF_AGCTHRESH2_STEP3_2                   0x02
#define RF_AGCTHRESH2_STEP3_3                   0x03
#define RF_AGCTHRESH2_STEP3_4                   0x04
#define RF_AGCTHRESH2_STEP3_5                   0x05
#define RF_AGCTHRESH2_STEP3_6                   0x06
#define RF_AGCTHRESH2_STEP3_7                   0x07
#define RF_AGCTHRESH2_STEP3_8                   0x08
#define RF_AGCTHRESH2_STEP3_9                   0x09
#define RF_AGCTHRESH2_STEP3_10              0x0A
#define RF_AGCTHRESH2_STEP3_11              0x0B  // Default
#define RF_AGCTHRESH2_STEP3_12              0x0C
#define RF_AGCTHRESH2_STEP3_13              0x0D
#define RF_AGCTHRESH2_STEP3_14              0x0E
#define RF_AGCTHRESH2_STEP3_15              0x0F


// RegAgcThresh3
#define RF_AGCTHRESH3_STEP4_0                   0x00
#define RF_AGCTHRESH3_STEP4_1                   0x10
#define RF_AGCTHRESH3_STEP4_2                   0x20
#define RF_AGCTHRESH3_STEP4_3                   0x30
#define RF_AGCTHRESH3_STEP4_4                   0x40
#define RF_AGCTHRESH3_STEP4_5                   0x50
#define RF_AGCTHRESH3_STEP4_6                   0x60
#define RF_AGCTHRESH3_STEP4_7                   0x70
#define RF_AGCTHRESH3_STEP4_8                   0x80
#define RF_AGCTHRESH3_STEP4_9                   0x90  // Default
#define RF_AGCTHRESH3_STEP4_10              0xA0
#define RF_AGCTHRESH3_STEP4_11              0xB0
#define RF_AGCTHRESH3_STEP4_12              0xC0
#define RF_AGCTHRESH3_STEP4_13              0xD0
#define RF_AGCTHRESH3_STEP4_14              0xE0
#define RF_AGCTHRESH3_STEP4_15              0xF0

#define RF_AGCTHRESH3_STEP5_0                   0x00
#define RF_AGCTHRESH3_STEP5_1                   0x01
#define RF_AGCTHRESH3_STEP5_2                   0x02
#define RF_AGCTHRESH3_STEP5_3                   0x03
#define RF_AGCTHRESH3_STEP5_4                   0x04
#define RF_AGCTHRESH3_STEP5_5                   0x05
#define RF_AGCTHRESH3_STEP5_6                   0x06
#define RF_AGCTHRESH3_STEP5_7                   0x07
#define RF_AGCTHRES33_STEP5_8                   0x08
#define RF_AGCTHRESH3_STEP5_9                   0x09
#define RF_AGCTHRESH3_STEP5_10              0x0A
#define RF_AGCTHRESH3_STEP5_11              0x0B  // Default
#define RF_AGCTHRESH3_STEP5_12              0x0C
#define RF_AGCTHRESH3_STEP5_13              0x0D
#define RF_AGCTHRESH3_STEP5_14              0x0E
#define RF_AGCTHRESH3_STEP5_15              0x0F


// RegLna
#define RF_LNA_ZIN_50                               0x00
#define RF_LNA_ZIN_200                            0x80  // Default

#define RF_LNA_LOWPOWER_OFF                     0x00  // Default
#define RF_LNA_LOWPOWER_ON                      0x40

#define RF_LNA_CURRENTGAIN                      0x38

#define RF_LNA_GAINSELECT_AUTO              0x00  // Default
#define RF_LNA_GAINSELECT_MAX                   0x01
#define RF_LNA_GAINSELECT_MAXMINUS6     0x02
#define RF_LNA_GAINSELECT_MAXMINUS12    0x03
#define RF_LNA_GAINSELECT_MAXMINUS24    0x04
#define RF_LNA_GAINSELECT_MAXMINUS36    0x05
#define RF_LNA_GAINSELECT_MAXMINUS48    0x06


// RegRxBw
#define RF_RXBW_DCCFREQ_000                     0x00
#define RF_RXBW_DCCFREQ_001                     0x20
#define RF_RXBW_DCCFREQ_010                     0x40  // Default
#define RF_RXBW_DCCFREQ_011                     0x60
#define RF_RXBW_DCCFREQ_100                     0x80
#define RF_RXBW_DCCFREQ_101                     0xA0
#define RF_RXBW_DCCFREQ_110                     0xC0
#define RF_RXBW_DCCFREQ_111                     0xE0

#define RF_RXBW_MANT_16                           0x00
#define RF_RXBW_MANT_20                           0x08
#define RF_RXBW_MANT_24                           0x10  // Default

#define RF_RXBW_EXP_0                               0x00
#define RF_RXBW_EXP_1                           0x01
#define RF_RXBW_EXP_2                           0x02
#define RF_RXBW_EXP_3                               0x03
#define RF_RXBW_EXP_4                           0x04
#define RF_RXBW_EXP_5                           0x05  // Default
#define RF_RXBW_EXP_6                             0x06
#define RF_RXBW_EXP_7                             0x07


// RegAfcBw
#define RF_AFCBW_DCCFREQAFC_000             0x00
#define RF_AFCBW_DCCFREQAFC_001             0x20
#define RF_AFCBW_DCCFREQAFC_010             0x40
#define RF_AFCBW_DCCFREQAFC_011             0x60
#define RF_AFCBW_DCCFREQAFC_100             0x80  // Default
#define RF_AFCBW_DCCFREQAFC_101             0xA0
#define RF_AFCBW_DCCFREQAFC_110             0xC0
#define RF_AFCBW_DCCFREQAFC_111             0xE0

#define RF_AFCBW_MANTAFC_16                     0x00
#define RF_AFCBW_MANTAFC_20                     0x08  // Default
#define RF_AFCBW_MANTAFC_24                     0x10

#define RF_AFCBW_EXPAFC_0                         0x00
#define RF_AFCBW_EXPAFC_1                       0x01
#define RF_AFCBW_EXPAFC_2                       0x02
#define RF_AFCBW_EXPAFC_3                       0x03  // Default
#define RF_AFCBW_EXPAFC_4                       0x04
#define RF_AFCBW_EXPAFC_5                       0x05
#define RF_AFCBW_EXPAFC_6                         0x06
#define RF_AFCBW_EXPAFC_7                       0x07


// RegOokPeak
#define RF_OOKPEAK_THRESHTYPE_FIXED             0x00
#define RF_OOKPEAK_THRESHTYPE_PEAK              0x40  // Default
#define RF_OOKPEAK_THRESHTYPE_AVERAGE           0x80

#define RF_OOKPEAK_PEAKTHRESHSTEP_000           0x00  // Default
#define RF_OOKPEAK_PEAKTHRESHSTEP_001           0x08
#define RF_OOKPEAK_PEAKTHRESHSTEP_010           0x10
#define RF_OOKPEAK_PEAKTHRESHSTEP_011           0x18
#define RF_OOKPEAK_PEAKTHRESHSTEP_100           0x20
#define RF_OOKPEAK_PEAKTHRESHSTEP_101           0x28
#define RF_OOKPEAK_PEAKTHRESHSTEP_110           0x30
#define RF_OOKPEAK_PEAKTHRESHSTEP_111           0x38

#define RF_OOKPEAK_PEAKTHRESHDEC_000            0x00  // Default
#define RF_OOKPEAK_PEAKTHRESHDEC_001            0x01
#define RF_OOKPEAK_PEAKTHRESHDEC_010            0x02
#define RF_OOKPEAK_PEAKTHRESHDEC_011            0x03
#define RF_OOKPEAK_PEAKTHRESHDEC_100            0x04
#define RF_OOKPEAK_PEAKTHRESHDEC_101            0x05
#define RF_OOKPEAK_PEAKTHRESHDEC_110            0x06
#define RF_OOKPEAK_PEAKTHRESHDEC_111            0x07


// RegOokAvg
#define RF_OOKAVG_AVERAGETHRESHFILT_00      0x00
#define RF_OOKAVG_AVERAGETHRESHFILT_01      0x40
#define RF_OOKAVG_AVERAGETHRESHFILT_10      0x80  // Default
#define RF_OOKAVG_AVERAGETHRESHFILT_11      0xC0


// RegOokFix
#define RF_OOKFIX_FIXEDTHRESH_VALUE             0x06  // Default


// RegAfcFei
#define RF_AFCFEI_FEI_DONE                          0x40
#define RF_AFCFEI_FEI_START                         0x20
#define RF_AFCFEI_AFC_DONE                          0x10
#define RF_AFCFEI_AFCAUTOCLEAR_ON               0x08
#define RF_AFCFEI_AFCAUTOCLEAR_OFF              0x00  // Default

#define RF_AFCFEI_AFCAUTO_ON                        0x04
#define RF_AFCFEI_AFCAUTO_OFF                       0x00  // Default

#define RF_AFCFEI_AFC_CLEAR                         0x02
#define RF_AFCFEI_AFC_START                         0x01

// RegRssiConfig
#define RF_RSSI_FASTRX_ON                             0x08
#define RF_RSSI_FASTRX_OFF                          0x00  // Default
#define RF_RSSI_DONE                                    0x02
#define RF_RSSI_START                                   0x01


// RegDioMapping1
#define RF_DIOMAPPING1_DIO0_00                  0x00  // Default
#define RF_DIOMAPPING1_DIO0_01                  0x40
#define RF_DIOMAPPING1_DIO0_10                  0x80
#define RF_DIOMAPPING1_DIO0_11                  0xC0

#define RF_DIOMAPPING1_DIO1_00                      0x00  // Default
#define RF_DIOMAPPING1_DIO1_01                  0x10
#define RF_DIOMAPPING1_DIO1_10                  0x20
#define RF_DIOMAPPING1_DIO1_11                  0x30

#define RF_DIOMAPPING1_DIO2_00                  0x00  // Default
#define RF_DIOMAPPING1_DIO2_01                  0x04
#define RF_DIOMAPPING1_DIO2_10                  0x08
#define RF_DIOMAPPING1_DIO2_11                  0x0C

#define RF_DIOMAPPING1_DIO3_00                  0x00  // Default
#define RF_DIOMAPPING1_DIO3_01                  0x01
#define RF_DIOMAPPING1_DIO3_10                  0x02
#define RF_DIOMAPPING1_DIO3_11                  0x03


// RegDioMapping2
#define RF_DIOMAPPING2_DIO4_00                  0x00  // Default
#define RF_DIOMAPPING2_DIO4_01                  0x40
#define RF_DIOMAPPING2_DIO4_10                  0x80
#define RF_DIOMAPPING2_DIO4_11                  0xC0

#define RF_DIOMAPPING2_DIO5_00                  0x00  // Default
#define RF_DIOMAPPING2_DIO5_01                  0x10
#define RF_DIOMAPPING2_DIO5_10                  0x20
#define RF_DIOMAPPING2_DIO5_11                  0x30

#define RF_DIOMAPPING2_CLKOUT_32                0x00
#define RF_DIOMAPPING2_CLKOUT_16                0x01
#define RF_DIOMAPPING2_CLKOUT_8                 0x02
#define RF_DIOMAPPING2_CLKOUT_4                   0x03
#define RF_DIOMAPPING2_CLKOUT_2                 0x04
#define RF_DIOMAPPING2_CLKOUT_1                 0x05
#define RF_DIOMAPPING2_CLKOUT_RC                0x06
#define RF_DIOMAPPING2_CLKOUT_OFF                 0x07  // Default


// RegIrqFlags1
#define RF_IRQFLAGS1_MODEREADY                    0x80
#define RF_IRQFLAGS1_RXREADY                        0x40
#define RF_IRQFLAGS1_TXREADY                        0x20
#define RF_IRQFLAGS1_PLLLOCK                        0x10
#define RF_IRQFLAGS1_RSSI                             0x08
#define RF_IRQFLAGS1_TIMEOUT                        0x04
#define RF_IRQFLAGS1_AUTOMODE                       0x02
#define RF_IRQFLAGS1_SYNCADDRESSMATCH           0x01

// RegIrqFlags2
#define RF_IRQFLAGS2_FIFOFULL                       0x80
#define RF_IRQFLAGS2_FIFONOTEMPTY                 0x40
#define RF_IRQFLAGS2_FIFOLEVEL                    0x20
#define RF_IRQFLAGS2_FIFOOVERRUN                  0x10
#define RF_IRQFLAGS2_PACKETSENT                   0x08
#define RF_IRQFLAGS2_PAYLOADREADY                 0x04
#define RF_IRQFLAGS2_CRCOK                          0x02
#define RF_IRQFLAGS2_LOWBAT                         0x01

// RegRssiThresh
#define RF_RSSITHRESH_VALUE                         0xE4  // Default

// RegRxTimeout1
#define RF_RXTIMEOUT1_RXSTART_VALUE             0x00  // Default

// RegRxTimeout2
#define RF_RXTIMEOUT2_RSSITHRESH_VALUE      0x00  // Default

// RegPreamble
#define RF_PREAMBLESIZE_MSB_VALUE                 0x00  // Default
#define RF_PREAMBLESIZE_LSB_VALUE                 0x03  // Default


// RegSyncConfig
#define RF_SYNC_ON                              0x80  // Default
#define RF_SYNC_OFF                             0x00

#define RF_SYNC_FIFOFILL_AUTO           0x00  // Default -- when sync interrupt occurs
#define RF_SYNC_FIFOFILL_MANUAL     0x40

#define RF_SYNC_SIZE_1                      0x00
#define RF_SYNC_SIZE_2                      0x08
#define RF_SYNC_SIZE_3                      0x10
#define RF_SYNC_SIZE_4                      0x18  // Default
#define RF_SYNC_SIZE_5                      0x20
#define RF_SYNC_SIZE_6                      0x28
#define RF_SYNC_SIZE_7                      0x30
#define RF_SYNC_SIZE_8                      0x38

#define RF_SYNC_TOL_0                           0x00  // Default
#define RF_SYNC_TOL_1                           0x01
#define RF_SYNC_TOL_2                           0x02
#define RF_SYNC_TOL_3                           0x03
#define RF_SYNC_TOL_4                           0x04
#define RF_SYNC_TOL_5                           0x05
#define RF_SYNC_TOL_6                           0x06
#define RF_SYNC_TOL_7                           0x07


// RegSyncValue1-8
#define RF_SYNC_BYTE1_VALUE             0x00  // Default
#define RF_SYNC_BYTE2_VALUE             0x00  // Default
#define RF_SYNC_BYTE3_VALUE             0x00  // Default
#define RF_SYNC_BYTE4_VALUE             0x00  // Default
#define RF_SYNC_BYTE5_VALUE             0x00  // Default
#define RF_SYNC_BYTE6_VALUE             0x00  // Default
#define RF_SYNC_BYTE7_VALUE             0x00  // Default
#define RF_SYNC_BYTE8_VALUE             0x00  // Default


// RegPacketConfig1
#define RF_PACKET1_FORMAT_FIXED             0x00  // Default
#define RF_PACKET1_FORMAT_VARIABLE      0x80

#define RF_PACKET1_DCFREE_OFF                   0x00  // Default
#define RF_PACKET1_DCFREE_MANCHESTER    0x20
#define RF_PACKET1_DCFREE_WHITENING     0x40

#define RF_PACKET1_CRC_ON                         0x10  // Default
#define RF_PACKET1_CRC_OFF                      0x00

#define RF_PACKET1_CRCAUTOCLEAR_ON      0x00  // Default
#define RF_PACKET1_CRCAUTOCLEAR_OFF     0x08

#define RF_PACKET1_ADRSFILTERING_OFF                  0x00  // Default
#define RF_PACKET1_ADRSFILTERING_NODE                 0x02
#define RF_PACKET1_ADRSFILTERING_NODEBROADCAST  0x04


// RegPayloadLength
#define RF_PAYLOADLENGTH_VALUE                  0x40  // Default

// RegBroadcastAdrs
#define RF_BROADCASTADDRESS_VALUE               0x00


// RegAutoModes
#define RF_AUTOMODES_ENTER_OFF                        0x00  // Default
#define RF_AUTOMODES_ENTER_FIFONOTEMPTY           0x20
#define RF_AUTOMODES_ENTER_FIFOLEVEL                0x40
#define RF_AUTOMODES_ENTER_CRCOK                      0x60
#define RF_AUTOMODES_ENTER_PAYLOADREADY           0x80
#define RF_AUTOMODES_ENTER_SYNCADRSMATCH          0xA0
#define RF_AUTOMODES_ENTER_PACKETSENT               0xC0
#define RF_AUTOMODES_ENTER_FIFOEMPTY                0xE0

#define RF_AUTOMODES_EXIT_OFF                           0x00  // Default
#define RF_AUTOMODES_EXIT_FIFOEMPTY               0x04
#define RF_AUTOMODES_EXIT_FIFOLEVEL               0x08
#define RF_AUTOMODES_EXIT_CRCOK                       0x0C
#define RF_AUTOMODES_EXIT_PAYLOADREADY          0x10
#define RF_AUTOMODES_EXIT_SYNCADRSMATCH           0x14
#define RF_AUTOMODES_EXIT_PACKETSENT              0x18
#define RF_AUTOMODES_EXIT_RXTIMEOUT                 0x1C

#define RF_AUTOMODES_INTERMEDIATE_SLEEP           0x00  // Default
#define RF_AUTOMODES_INTERMEDIATE_STANDBY         0x01
#define RF_AUTOMODES_INTERMEDIATE_RECEIVER      0x02
#define RF_AUTOMODES_INTERMEDIATE_TRANSMITTER   0x03


// RegFifoThresh
#define RF_FIFOTHRESH_TXSTART_FIFOTHRESH          0x00
#define RF_FIFOTHRESH_TXSTART_FIFONOTEMPTY      0x80  // Default

#define RF_FIFOTHRESH_VALUE                             0x0F  // Default


// RegPacketConfig2
#define RF_PACKET2_RXRESTARTDELAY_1BIT            0x00  // Default
#define RF_PACKET2_RXRESTARTDELAY_2BITS           0x10
#define RF_PACKET2_RXRESTARTDELAY_4BITS         0x20
#define RF_PACKET2_RXRESTARTDELAY_8BITS         0x30
#define RF_PACKET2_RXRESTARTDELAY_16BITS          0x40
#define RF_PACKET2_RXRESTARTDELAY_32BITS        0x50
#define RF_PACKET2_RXRESTARTDELAY_64BITS        0x60
#define RF_PACKET2_RXRESTARTDELAY_128BITS         0x70
#define RF_PACKET2_RXRESTARTDELAY_256BITS       0x80
#define RF_PACKET2_RXRESTARTDELAY_512BITS       0x90
#define RF_PACKET2_RXRESTARTDELAY_1024BITS      0xA0
#define RF_PACKET2_RXRESTARTDELAY_2048BITS      0xB0
#define RF_PACKET2_RXRESTARTDELAY_NONE            0xC0
#define RF_PACKET2_RXRESTART                            0x04

#define RF_PACKET2_AUTORXRESTART_ON                 0x02  // Default
#define RF_PACKET2_AUTORXRESTART_OFF                0x00

#define RF_PACKET2_AES_ON                                 0x01
#define RF_PACKET2_AES_OFF                              0x00  // Default


// RegAesKey1-16
#define RF_AESKEY1_VALUE                        0x00  // Default
#define RF_AESKEY2_VALUE                        0x00  // Default
#define RF_AESKEY3_VALUE                        0x00  // Default
#define RF_AESKEY4_VALUE                        0x00  // Default
#define RF_AESKEY5_VALUE                        0x00  // Default
#define RF_AESKEY6_VALUE                        0x00  // Default
#define RF_AESKEY7_VALUE                        0x00  // Default
#define RF_AESKEY8_VALUE                        0x00  // Default
#define RF_AESKEY9_VALUE                        0x00  // Default
#define RF_AESKEY10_VALUE                       0x00  // Default
#define RF_AESKEY11_VALUE                       0x00  // Default
#define RF_AESKEY12_VALUE                       0x00  // Default
#define RF_AESKEY13_VALUE                       0x00  // Default
#define RF_AESKEY14_VALUE                       0x00  // Default
#define RF_AESKEY15_VALUE                       0x00  // Default
#define RF_AESKEY16_VALUE                       0x00  // Default


// RegTemp1
#define RF_TEMP1_MEAS_START                 0x08
#define RF_TEMP1_MEAS_RUNNING               0x04
#define RF_TEMP1_ADCLOWPOWER_ON         0x01  // Default
#define RF_TEMP1_ADCLOWPOWER_OFF        0x00

// RegTestDagc
#define RF_DAGC_NORMAL              0x00  // Reset value
#define RF_DAGC_IMPROVED_LOWBETA1   0x20  //
#define RF_DAGC_IMPROVED_LOWBETA0   0x30  // Recommended default

// RegTestLna
#define RF_TESTLNA_NORMAL           0x1B  // Default
#define RF_TESTLNA_SENSITIVE        0x2D  //


class RFM69
{
public:

    /// Constructor.
    RFM69();
  
    boolean        init();

    uint8_t        spiRead(uint8_t reg);

    void           spiWrite(uint8_t reg, uint8_t val);
    
    void           spiBurstRead(uint8_t reg, uint8_t* dest, uint8_t len);

    void           spiBurstWrite(uint8_t reg, const uint8_t* src, uint8_t len);
    
    void           spiFifoWrite(const uint8_t* src, uint8_t len);

    void           setMode(uint8_t mode);

    uint8_t        mode();

    boolean        checkRx();

    void        recv(uint8_t* buf, uint8_t* len);
    
    void        send(const uint8_t* data, uint8_t len, uint8_t power);
    
    float          readTemp();
    
    int16_t             lastRssi();
    
    int16_t             sampleRssi();
    
    void            SetLnaMode(uint8_t lnaMode);
    
    void            clearFifo();

protected:
    

private:
    uint8_t             _mode;

    uint8_t		_slaveSelectPin;

    uint8_t             _bufLen;
    uint8_t             _buf[RFM69_MAX_MESSAGE_LEN];

    int16_t                 _lastRssi;
};


#endif 


