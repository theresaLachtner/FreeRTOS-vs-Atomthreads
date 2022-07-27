/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/ADC.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// queue for sending data ready message to ADC read funciton
extern ATOM_QUEUE _queue_ADCread;

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
uint16_t ADC_read(uint16_t channel)
{
	// clear channel register
	ADMUX &= ~(0x1F);
	// write channel to register
	ADMUX |= (channel & 0x1F);
	// start conversion
	ADCSRA |= (1 << ADSC);

	// message variable
	uint8_t msg = 0;
	// get message from ADC conversion ready ISR
	atomQueueGet(&_queue_ADCread, 10000, &msg);

	// return the raw converted value
	return ADCW;
}
