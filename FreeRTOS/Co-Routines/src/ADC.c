/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/ADC.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// semaphore hanlde for ADC read function
extern SemaphoreHandle_t sh_ADCread;
// queue hanlde for ADC interrupt queue
extern QueueHandle_t qh_ADCinterrupt;

//------------------------------------------------------------------------
// FORWARD DECLARATIONS
//------------------------------------------------------------------------

// local helper function that waits for interrupt from ADC
void ISR_wait();

//------------------------------------------------------------------------
// ADC INIT FUNCTION
// initializes ADC on arduino
//------------------------------------------------------------------------
void ADC_init()
{
	// activate ADC + interrupt
	ADCSRA = (1 << ADEN) | (1 << ADIE);
	// set AVCC as voltage reference
	ADMUX = (1 << REFS0);
	// set the prescaler to 128
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

//------------------------------------------------------------------------
// ADC READ FUNCTION
// read single value from ADC-channel
//------------------------------------------------------------------------
void ADC_read(uint16_t channel)
{
	// clear channel register
	ADMUX &= ~(0x1F);
	// write channel to register
	ADMUX |= (channel & 0x1F);
	// start conversion
	ADCSRA |= (1 << ADSC);
}
