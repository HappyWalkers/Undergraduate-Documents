#include "Adc.h"



void Init_ADC(ADCChannel_t channel ,ADCResolution_t mbits)
{
  
    /***************************************************************************
    * I/O-Port configuration
    * PIN0_7 is configured to an ADC input pin.
    */
    /***************************************************************************
    * ADC configuration:
    *  - [ADCCON1.ST] triggered
    *  - 12 bit resolution
    *  - Single-ended
    *  - Single-channel, due to only 1 pin is selected in the APCFG register
    *  - Reference voltage is VDD on AVDD pin
    ***************************************************************************/
    
    // Set [ADCCON1.STSEL] according to ADC configuration.
    ADCCON1 = (ADCCON1 & ~ADCCON1_STSEL) | ADCCON1_STSEL_ST;

    // Set [ADCCON2.SREF/SDIV/SCH] according to ADC configuration.
    ADCCON2 = ADCCON2_SREF_AVDD;
    
    // Set [APCFG.APCFG0 = 1].
    switch(channel)
    {
      case CH0:     APCFG |= APCFG_APCFG0;  ADCCON2 |= ADCCON2_SCH_AIN0;  break;
      case CH1:     APCFG |= APCFG_APCFG1;  ADCCON2 |= ADCCON2_SCH_AIN1;  break;
      case CH2:     APCFG |= APCFG_APCFG2;  ADCCON2 |= ADCCON2_SCH_AIN2;  break;
      case CH3:     APCFG |= APCFG_APCFG3;  ADCCON2 |= ADCCON2_SCH_AIN3;  break;
      case CH4:     APCFG |= APCFG_APCFG4;  ADCCON2 |= ADCCON2_SCH_AIN4;  break;
      case CH5:     APCFG |= APCFG_APCFG5;  ADCCON2 |= ADCCON2_SCH_AIN5;  break;
      case CH6:     APCFG |= APCFG_APCFG6;  ADCCON2 |= ADCCON2_SCH_AIN6;  break;
      case CH7:     APCFG |= APCFG_APCFG7;  ADCCON2 |= ADCCON2_SCH_AIN7;  break;
      case CH0_1:     ADCCON2 |= ADCCON2_SCH_AIN0_1;   break;
      case CH2_3:     ADCCON2 |= ADCCON2_SCH_AIN2_3;   break;
      case CH4_5:     ADCCON2 |= ADCCON2_SCH_AIN4_5;   break;
      case CH6_7:     ADCCON2 |= ADCCON2_SCH_AIN6_7;   break;
      case CHGND:     ADCCON2 |= ADCCON2_SCH_GND;      break;
      case CHTEMPR:   ADCCON2 |= ADCCON2_SCH_TEMPR;    break;
      case CHVDD_3:   ADCCON2 |= ADCCON2_SCH_VDD_3;    break;
    }
    switch(mbits)
    {
      case Resolution_7:   ADCCON2 |= ADCCON2_SDIV_64;   break;
      case Resolution_9:   ADCCON2 |= ADCCON2_SDIV_128;  break;
      case Resolution_10:  ADCCON2 |= ADCCON2_SDIV_256;  break;
      case Resolution_12:  ADCCON2 |= ADCCON2_SDIV_512;  break;
    }
    /****************************************************************************
    * ADC conversion :
    * The ADC conversion is triggered by setting [ADCCON1.ST = 1].
    * The CPU will then poll [ADCCON1.EOC] until the conversion is completed.
    */
}

uint16 ADC_Convert(ADCResolution_t resolution)
{
    
    static uint16 adc_result;
    uint8 RstAdj;
    // Set [ADCCON1.ST] and await completion (ADCCON1.EOC = 1). 
    ADCCON1 |= ADCCON1_ST;
    while( !(ADCCON1 & ADCCON1_EOC));

    /* Store the ADC result from the ADCH/L register to the adc_result variable.
    * The conversion result resides in the MSB section of the combined ADCH and
    * ADCL registers.
    */  
    adc_result = ADCL;
    adc_result |= (ADCH << 8);
    switch(resolution)
    {
      case Resolution_12:   RstAdj = 4;     break;
      case Resolution_10:   RstAdj = 6;     break;
      case Resolution_9 :   RstAdj = 7;     break;
      case Resolution_7 :   RstAdj = 9;     break;
      default :             RstAdj = 4;     break;
    }
    adc_result >>= RstAdj;
    return adc_result;
}