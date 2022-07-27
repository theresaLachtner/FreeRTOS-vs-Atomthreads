/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG

#include <avr/io.h>
#include <util/delay.h>

#include "../kernel/atom.h"
#include "../kernel/atomport-private.h"
#include "../kernel/atomtimer.h"
#include "../kernel/atommutex.h"
#include "../kernel/atomqueue.h"

// only included in debug-mode
#ifdef DEBUG
#include <stdio.h>
#include "debug.h"
#endif


//------------------------------------------------------------------------
// GLOBAL VARIABLE DECLARATION
//------------------------------------------------------------------------

// mutex for ADC read function
ATOM_MUTEX _mutex_ADCread;

// queue for sending data ready message to ADC read funciton
ATOM_QUEUE _queue_ADCread;
// queue for signalling timer thread from timer callback
ATOM_QUEUE _queue_timerCallback;

// timer for periodic toggling LED
ATOM_TIMER _timer_periodicLED;

//------------------------------------------------------------------------
// PROJECT SPECIFIC MAKROS
//------------------------------------------------------------------------

// ADC channel of potentiometer 1
#define POT1_CHANNEL 0
// ADC channel of potentiometer 2
#define POT2_CHANNEL 2
// ADC channel of light dependent resistor
#define LDR_CHANNEL 1
// PWM output channel of dimmable LED
#define PWM_CHANNEL 6
// Digital opuput channel of LED_1
#define LED1_CHANNEL 5
// Digital input channel of LDR-module
#define DI_CHANNEL 4
// Digital output channel of LED_2
#define LED2_CHANNEL 3

// upper voltage limit of the LDR
#define LDR_UPPER_LIMIT 860
// lower voltage limit of the LDR
#define LDR_LOWER_LIMIT 102

#define REGISTER_SIZE 256

#endif
