#ifndef __ADC_H__
#define __ADC_H__

#include "ioCC2541.h"
#include "ioCC2541_bitdef.h"

typedef enum {
  Resolution_7,
  Resolution_9,
  Resolution_10,
  Resolution_12,
}ADCResolution_t;

typedef enum {
  CH0,
  CH1,
  CH2,
  CH3,
  CH4,
  CH5,
  CH6,
  CH7,
  CH0_1,
  CH2_3,
  CH4_5,
  CH6_7,
  CHGND,
  CHTEMPR,
  CHVDD_3,
}ADCChannel_t;



void Init_ADC(ADCChannel_t channel ,ADCResolution_t resolution);
uint16 ADC_Convert(ADCResolution_t resolution);

#endif //__ADC_H__