#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
// only included in debug-mode
#ifdef DEBUG
#include <stdio.h>
#include "debug.h"
#include "string.h"
#endif

//------------------------------------------------------------------------
// GLOBAL VARIABLE DECLARATION
//------------------------------------------------------------------------



//------------------------------------------------------------------------
// PRIVATE TYPEDEF
//------------------------------------------------------------------------



//------------------------------------------------------------------------
// PRIVATE MAKROS
//------------------------------------------------------------------------

// ADC channel of potentiometer
#define POT_CHANNEL 0
// ADC channel of light dependent resistor
#define LDR_CHANNEL 1
// PWM output channel of LED_1
#define PWM_CHANNEL 6
// Digital opuput channel of LED_2
#define DO_CHANNEL 5
// Digital input channel of LDR-module
#define DI_CHANNEL 4

// upper voltage limit of the LDR
#define LDR_UPPER_LIMIT 860
// lower voltage limit of the LDR
#define LDR_LOWER_LIMIT 102

#define REGISTER_SIZE 256

#endif
