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
// LOCAL VARIABLES
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
uint16_t ADC_read(uint16_t channel)
{
	// clear channel register
	ADMUX &= ~(0x1F);
	// write channel to register
	ADMUX |= (channel & 0x1F);

	// task is resumed in ISR after conversion is complete
	ISR_wait();

	// return the raw converted value
	return ADCW;
}

//------------------------------------------------------------------------
// LOCAL FUNCTIONS
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// ISR WAIT FUNCTION
// local helper function that waits for interrupt from ADC
//------------------------------------------------------------------------
void ISR_wait()
{
	// get current task handle
	TaskHandle_t th_current = xTaskGetCurrentTaskHandle();
	// send current task handle to queue
	if (xQueueSend(qh_ADCinterrupt, &th_current, 10) != pdTRUE)
	{
		UART_sendstring("ERROR!\n");
	}
	// start conversion
	ADCSRA |= (1 << ADSC);
	// wait until notification from ISR
	if (xTaskNotifyWait(0, 0, NULL, (TickType_t)1000) != pdTRUE)
	{
		UART_sendstring("ERROR!\n");
	}
}
