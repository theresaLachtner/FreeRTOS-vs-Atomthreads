/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../FreeRTOS-Kernel/include/FreeRTOS.h"
#include "../FreeRTOS-Kernel/include/task.h"
#include "../FreeRTOS-Kernel/include/semphr.h"
#include "../FreeRTOS-Kernel/include/queue.h"
#include "../FreeRTOS-Kernel/include/timers.h"

// only included in debug-mode
#ifdef DEBUG
#include <stdio.h>
#include "debug.h"
#endif

//------------------------------------------------------------------------
// GLOBAL VARIABLE DECLARATION
//------------------------------------------------------------------------

// task handle for dimLED task
TaskHandle_t th_dimLED;
// task handle for indicationLED task
TaskHandle_t th_indicationLED;
// task handle for periodicLED task
TaskHandle_t th_periodicLED;

// semaphore handle for ADC read function
SemaphoreHandle_t sh_ADCread;

// queue handle for ADC interrupt queue
QueueHandle_t qh_ADCinterrupt;

// extern timer handle for period timer
TimerHandle_t tih_periodTimer;

//------------------------------------------------------------------------
// PROJECT SPECIFIC TYPEDEF
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// MAKROS
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
