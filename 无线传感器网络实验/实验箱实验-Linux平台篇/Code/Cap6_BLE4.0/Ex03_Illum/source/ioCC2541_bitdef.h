/******************************************************************************
    Filename: ioCC2541_bitdef.h

    This file contains the bit definitions of registers in CC2541.

    Note: The USB and Radio bit defintions are in seperate headers.

    Last Modify time:   2013.12.05

    Author: songwei   <wei.song@sunplusapp.com>
******************************************************************************/
#ifndef __IOCC2541_BITDEF_H__
#define __IOCC2541_BITDEF_H__

typedef unsigned char uint8 ;
typedef unsigned int uint16;

typedef char int8;
typedef int int16;

//Bit definitions
#define BIT7  0x80
#define BIT6  0x40
#define BIT5  0x20
#define BIT4  0x10
#define BIT3  0x08
#define BIT2  0x04
#define BIT1  0x02
#define BIT0  0x01





/*******************************************************************************
 * Memory Control Registers
 */

// MPAGE (0x93) - Memory Page Select

// MEMCTR (0xC7) - Memory Arbiter Control
#define MEMCTR_XMAP                      0x08   // Maps SRAM into the CODE Memory Space, enables code execution from RAM.

// DPH0 (0x83) ?Data Pointer-0 High Byte

// DPL0 (0x82) ?Data Pointer-0 Low Byte

// DPH1 (0x85) ?Data Pointer-1 High Byte

// DPL1 (0x84) ?Data Pointer-1 Low Byte

// DPS (0x92) ?Data-Pointer Select
#define DPS_DPS                           0x01    // Data pointer selection, DPTR1 when set, DPTR0 when cleared.

// PSW (0xD0) ?Program Status Word

// ACC (0xE0) ?Accumulator

// B (0xF0) ?B Register

// SP (0x81) ?Stack Pointer



/*******************************************************************************
 * Interrupt Control Registers
 */

// IEN0 (0xA8) - Interrupt Enable 0 Register - bit accessible SFR register

// IEN1 (0xB8) - Interrupt Enable 1 Register - bit accessible SFR register
#define IEN1_P0IE                         0x20        // Port 0 interrupt enable
#define IEN1_T4IE                         0x10        // Timer 4 interrupt enable
#define IEN1_T3IE                         0x08        // Timer 3 interrupt enable
#define IEN1_T2IE                         0x04        // Timer 2 interrupt enable
#define IEN1_T1IE                         0x02        // Timer 1 interrupt enable
#define IEN1_DMAIE                        0x01        // DMA transfer interrupt enable

// IEN2 (0x9A) - Interrupt Enable 2 Register
#define IEN2_WDTIE                        0x20
#define IEN2_P1IE                         0x10
#define IEN2_UTX1IE                        0x08     // USART 1 TX interrupt enable
#define IEN2_UTX0IE                       0x04
#define IEN2_P2IE                         0x02
#define IEN2_USBIE                        0x02
#define IEN2_RFIE                         0x01

// TCON (0x88) - CPU Interrupt Flag 1 - bit accessible SFR register

// S0CON (0x98) - CPU Interrupt Flag 2 - bit accessible SFR register

// S1CON (0x9B) - CPU Interrupt Flag 3
#define S1CON_RFIF_1                      0x02
#define S1CON_RFIF_0                      0x01

// IRCON (0xC0) - CPU Interrupt Flag 4 - bit accessible SFR register

// IRCON2 (0xE8) - CPU Interrupt Flag 5 - bit accessible SFR register

// IP1 (0xB9) - Interrupt Priority 1
#define IP1_IPG5                          0x20
#define IP1_IPG4                          0x10
#define IP1_IPG3                          0x08
#define IP1_IPG2                          0x04
#define IP1_IPG1                          0x02
#define IP1_IPG0                          0x01

// IP0 (0xA9) - Interrupt Priority 0
#define IP0_IPG5                          0x20
#define IP0_IPG4                          0x10
#define IP0_IPG3                          0x08
#define IP0_IPG2                          0x04
#define IP0_IPG1                          0x02
#define IP0_IPG0                          0x01


/*******************************************************************************
 * Power Management and Clocks
 */

// SRCRC (0x6262) ?Sleep Reset CRC (not available on the CC2544)
#define SRCRC_FORCE_RESET                 0x20          // Force watchdog reset
#define SRCRC_CRC_RESULT                  (0x03 << 2)   // CRC value, bit mask
  #define SRCRC_CRC_RESULT_PASS             (0x00 << 2)   // CRC of retained registers passed
  #define SRCRC_CRC_RESULT_LOW              (0x01 << 2)   // Low CRC value failed
  #define SRCRC_CRC_RESULT_HIGH             (0x02 << 2)   // High CRC value failed
  #define SRCRC_CRC_RESULT_BOTH             (0x03 << 2)   // Both CRC values failed
#define SRCRC_CRC_RESET_EN                0x01          // CRC != 00 reset enable, after wakeup from PM2/PM3.

// PCON (0x87) - Power Mode Control
#define PCON_IDLE                         0x01

// SLEEPCMD (0xBE) - Sleep Mode Control
#define OSC32K_CALDIS                     0x80
#define SLEEPCMD_MODE                     (0x03)      // Power mode bit mask
  #define SLEEPCMD_MODE_IDLE                (0x00)
  #define SLEEPCMD_MODE_PM1                 (0x01)  
  #if (chip == 2541 || chip == 2543 || chip == 2545)  // (not applicable on CC2544)
    #define SLEEPCMD_MODE_PM2                 (0x02)  
    #define SLEEPCMD_MODE_PM3                 (0x03)
  #endif

// SLEEPSTA (0x9D) ?Sleep-Mode Control Status
#define SLEEPSTA_CLK32K_CALDIS            0x80          // Calibration disable status
#define SLEEPSTA_RST                      (0x03 << 3)   // Cause of last reset, bit mask
  #define SLEEPSTA_RST_POR_BOD              (0x00 << 3)   // Power-on reset, or brownout detection
  #define SLEEPSTA_RST_EXT                  (0x01 << 3)   // External reset
  #define SLEEPSTA_RST_WDT                  (0x02 << 3)   // Watchdog Timer reset
  #define SLEEPSTA_RST_CLK_LOSS             (0x03 << 3)   // Clock loss reset
#define SLEEPSTA_CLK32K                   0x01          // 32 kHz clock signal

// STLOAD (0xAD) ?Sleep Timer Load Status
#define STLOAD_LDRDY                      0x01

// CLKCONCMD (0xC6) ?Clock Control Command
// and CLKCONSTA (0x9E) ?Clock Control Status
#define CLKCON_OSC32K                     0x80          // 32 kHz clock source select/status
#define CLKCON_OSC                        0x40          // system clock source select/status
#define CLKCON_TICKSPD                    (0x07 << 3)   // bit mask, global timer tick speed divider
  #define CLKCON_TICKSPD_32M                (0x00 << 3)
  #define CLKCON_TICKSPD_16M                (0x01 << 3)
  #define CLKCON_TICKSPD_8M                 (0x02 << 3)
  #define CLKCON_TICKSPD_4M                 (0x03 << 3)
  #define CLKCON_TICKSPD_2M                 (0x04 << 3)
  #define CLKCON_TICKSPD_1M                 (0x05 << 3)
  #define CLKCON_TICKSPD_500K               (0x06 << 3)
  #define CLKCON_TICKSPD_250K               (0x07 << 3)
#define CLKCON_CLKSPD                     (0x07)        // bit mask for the clock speed division
  #define CLKCON_CLKSPD_32M                 (0x00)
  #define CLKCON_CLKSPD_16M                 (0x01)
  #define CLKCON_CLKSPD_8M                  (0x02)
  #define CLKCON_CLKSPD_4M                  (0x03)
  #define CLKCON_CLKSPD_2M                  (0x04)
  #define CLKCON_CLKSPD_1M                  (0x05)
  #define CLKCON_CLKSPD_500K                (0x06)
  #define CLKCON_CLKSPD_250K                (0x07)

// CLD (0x6290) ?Clock-Loss Detection
#define CLD_EN                            0x01          // Clock-loss detector enable


/*******************************************************************************
 *  Flash Controller
 */

// FCTL (0x6270) - Flash Control
#define FCTL_BUSY                         0x80
#define FCTL_FULL                         0x40
#define FCTL_ABORT                        0x20
#define FCTL_CM                           (0x03 << 2)   // cache mode bit mask
  #define FCTL_CM_DIS                       (0x00 << 2)   // cache mode disabled
  #define FCTL_CM_EN                        (0x01 << 2)   // cache mode enabled
  #define FCTL_CM_PREFETCH                  (0x02 << 2)   // cache mode enabled, prefetch mode
  #define FCTL_CM_REALTIME                  (0x03 << 2)   // cache mode enabled, real-time mode
#define FCTL_WRITE                        0x02
#define FCTL_ERASE                        0x01


// FWDATA (0xAF) - Flash Write Data

// FADDRH (0xAD) - Flash Address High Byte

// FADDRL (0xAC) - Flash Address Low Byte












/*******************************************************************************
 * I/O Ports
 */
// *************************** CC2541 ********************************
  // P0 (0x80) - Port 0 - bit accessible SFR register

  // P1 (0x90) - Port 1 - bit accessible SFR register 

  // P2 (0xA0) - Port 2 - bit accessible SFR register

  //PERCFG  (0xF1) - Peripheral Control
#define PERCFG_T1CFG      0x40    //Timer 1 I/O location
#define PERCFG_T3CFG      0x20    //Timer 3 I/O location
#define PERCFG_T4CFG      0x10    //Timer 4 I/O location
#define PERCFG_U1CFG      0x02    //USART 1 I/O location
#define PERCFG_U0CFG      0x01    //USART 0 I/O location
  #define PERCFG_U0CFG_ALT1  0x00   //Alternative 1 location
  #define PERCFG_U0CFG_ALT2  0x01   //Alternative 2 location

 // APCFG (0xF2) - Analog Peripheral I/O Configuration
  #define APCFG_APCFG7                      0x80        // When set, analog I/O on P0_7 is enabled
  #define APCFG_APCFG6                      0x40
  #define APCFG_APCFG5                      0x20
  #define APCFG_APCFG4                      0x10
  #define APCFG_APCFG3                      0x08
  #define APCFG_APCFG2                      0x04
  #define APCFG_APCFG1                      0x02
  #define APCFG_APCFG0                      0x01



/*******************************************************************************
 * ADC
 */
  // ADCL (0xBA) - ADC Data Low (only bit 7-4 used)
  // ADCH (0xBB) - ADC Data High
  // ADCCON1 (0xB4) - ADC Control 1
  #define ADCCON1_EOC                       0x80
  #define ADCCON1_ST                        0x40
  #define ADCCON1_STSEL                     (0x03 << 4)   // bit mask, ADC start select
    #define ADCCON1_STSEL_P2_0                (0x00 << 4)   // External trigger on P2.0
    #define ADCCON1_STSEL_FULL_SPEED          (0x01 << 4)   // Do not wait for triggers
    #define ADCCON1_STSEL_T1C0_CMP_EVT        (0x02 << 4)   // Timer 1 ch0 compare event
    #define ADCCON1_STSEL_ST                  (0x03 << 4)   // ADCCON1.ST = 1

  // ADCCON2 (0xB5) - ADC Control 2
  #define ADCCON2_SREF                      (0x03 << 6)   // bit mask, select reference voltage
    #define ADCCON2_SREF_1_15V                (0x00 << 6)   // Internal reference 1.15 V
    #define ADCCON2_SREF_P0_7                 (0x01 << 6)   // External reference on AIN7 pin
    #define ADCCON2_SREF_AVDD                 (0x02 << 6)   // AVDD5 pin
    #define ADCCON2_SREF_P0_6_P0_7            (0x03 << 6)   // External reference on AIN6-AIN7 differential input
  #define ADCCON2_SDIV                      (0x03 << 4)   // bit mask, decimation rate
    #define ADCCON2_SDIV_64                   (0x00 << 4)   // 7 bits ENOB
    #define ADCCON2_SDIV_128                  (0x01 << 4)   // 9 bits ENOB
    #define ADCCON2_SDIV_256                  (0x02 << 4)   // 10 bits ENOB
    #define ADCCON2_SDIV_512                  (0x03 << 4)   // 12 bits ENOB
  #define ADCCON2_SCH                       (0x0F)        // bit mask, sequence channel select  
    #define ADCCON2_SCH_AIN0                  (0x00)        // selects the end of a single input sequence (starts at AIN0) 
    #define ADCCON2_SCH_AIN1                  (0x01)
    #define ADCCON2_SCH_AIN2                  (0x02)
    #define ADCCON2_SCH_AIN3                  (0x03)
    #define ADCCON2_SCH_AIN4                  (0x04)
    #define ADCCON2_SCH_AIN5                  (0x05)
    #define ADCCON2_SCH_AIN6                  (0x06)
    #define ADCCON2_SCH_AIN7                  (0x07)        
    #define ADCCON2_SCH_AIN0_1                (0x08)        // selects the end of a differential input sequence (starts at AIN0-AIN1)
    #define ADCCON2_SCH_AIN2_3                (0x09)
    #define ADCCON2_SCH_AIN4_5                (0x0A)
    #define ADCCON2_SCH_AIN6_7                (0x0B)        
    #define ADCCON2_SCH_GND                   (0x0C)        // only one conversion is performed
    #define ADCCON2_SCH_TEMPR                 (0x0E)        // only one conversion is performed
    #define ADCCON2_SCH_VDD_3                 (0x0F)        // only one conversion is performed
    
  // ADCCON3 (0xB6) - ADC Control 3
  #define ADCCON3_EREF                      0xC0
    #define ADCCON3_EREF_1_25V                (0x00 << 6)
    #define ADCCON3_EREF_P0_7                 (0x01 << 6)
    #define ADCCON3_EREF_AVDD                 (0x02 << 6)
    #define ADCCON3_EREF_P0_6_P0_7            (0x03 << 6)
  #define ADCCON3_EDIV                      0x30
    #define ADCCON3_EDIV_64                   (0x00 << 4)
    #define ADCCON3_EDIV_128                  (0x01 << 4)
    #define ADCCON3_EDIV_256                  (0x02 << 4)
    #define ADCCON3_EDIV_512                  (0x03 << 4)
  #define ADCCON3_ECH                       0x0F
    #define ADCCON3_ECH_AIN0                  (0x00)
    #define ADCCON3_ECH_AIN1                  (0x01)
    #define ADCCON3_ECH_AIN2                  (0x02)
    #define ADCCON3_ECH_AIN3                  (0x03)
    #define ADCCON3_ECH_AIN4                  (0x04)
    #define ADCCON3_ECH_AIN5                  (0x05)
    #define ADCCON3_ECH_AIN6                  (0x06)
    #define ADCCON3_ECH_AIN7                  (0x07)
    #define ADCCON3_ECH_AIN0_1                (0x08)
    #define ADCCON3_ECH_AIN2_3                (0x09)
    #define ADCCON3_ECH_AIN4_5                (0x0A)
    #define ADCCON3_ECH_AIN6_7                (0x0B)
    #define ADCCON3_ECH_GND                   (0x0C)
    #define ADCCON3_ECH_TEMPR                 (0x0E)
    #define ADCCON3_ECH_VDD_3                 (0x0F)

  // TR0 (0x624B) ?Test Register 0
  #define TR0_ADCTM                         0x01    // Enable temperatur sensor, see datasheet.


  // *********************** Analog Comparator *************************

  // CMPCTL (0x62D0) ?Analog Comparator Control and Status
  #define CMPCTL_EN                         0x02    // Comparator enable
  #define CMPCTL_OUTPUT                     0x01    // The comparator output






/*******************************************************************************
 * Watchdog Timer
 */
//WDCTL (0xC9) - Watchdog Timer Control

#define WDCTL_CLR       0xF0
  #define WDCTL_CLR0      0x10
  #define WDCTL_CLR1      0x20
  #define WDCTL_CLR2      0x40
  #define WDCTL_CLR3      0x80
#define WDCTL_MODE      (0x03<<2)//select mode,bit mask
  #define WDCTL_MODE_IDLE   (0x00<<2)
  #define WDCTL_MODE_WD     (0x02<<2)
  #define WDCTL_MODE_TIMER  (0x03<<2)
#define WDCTL_INT       (0x03)
  #define WDCTL_INT_1_SEC     (0x00)//1s
  #define WDCTL_INT_250_MSEC  (0x01)//0.25s
  #define WDCTL_INT_15_MSEC   (0x02)//15.625ms
  #define WDCTL_INT_2_MSEC    (0x03)//1.9ms

/*******************************************************************************
 * USART
 */
//U0CSR (0x86) - USART 0 Control and Status
#define U0CSR_MODE        0x80//0:SPI mode 1:UART mode
#define U0CSR_RE          0x40//0:Receiver disable 1:Receiver enable
#define U0CSR_SLAVE       0x20//0:SPI master 1:SPI slave
#define U0CSR_FE          0x10//0:No framing error detected 1:Byte received with incorrect stop-bit level
#define U0CSR_ERR         0x08//0:No parity error detected 1:Byte received with parity error
#define U0CSR_RX_BYTE     0x04//0:No byte received 1:Received byte ready
#define U0CSR_TX_BYTE     0x02//0:Byte not transmitted 1:Last byte written to data-buffer register has been transmitted
#define U0CSR_ACTIVE      0x01//0:USART idle 1:USART busy in transmit or receive mode

//U0UCR (0xC4) - USART 0 UART Control
#define U0UCR_FLUSH     0x80//Flush unit ,When set ,this event stops the current operation and returns the unit to the idle state.
#define U0UCR_FLOW      0x40//0:Flow control disable 1:Flow control enable
#define U0UCR_D9        0x20//0: Odd parity 1: Even parity
#define U0UCR_BIT9      0x10//0: 8-bit transfer 1: 9-bit transfer
#define U0UCR_PARITY    0x08//0:Parity disable 1: Parity enable
#define U0UCR_SPB       0x04//0: 1 stop bit 1: 2 stop bits
#define U0UCR_STOP      0x02//0:Low stop bit 1:High stop bit
#define U0UCR_START     0x01//0:Low start bit 1:High start bit

//U0GCR (0xC5) - USART 0 Genaric Control Register
#define U0GCR_CPOL      0x80//0:Negative clock poiarity 1:Positive clock poiarity
#define U0GCR_CPHA      0x40//SPI clock phase
#define U0GCR_ORDER     0x20//0:LSB first 1:MSB first
#define U0GCR_BAUD_E    0x1F
  #define U0GCR_BAUD_E0   0x01
  #define U0GCR_BAUD_E1   0x02
  #define U0GCR_BAUD_E2   0x04
  #define U0GCR_BAUD_E3   0x08
  #define U0GCR_BAUD_E4   0x10

// U0DBUF (0xC1) - USART 0 Receive/Transmit Data Buffer

// U0BAUD (0xC2) - USART 0 Baud Rate Control




#endif