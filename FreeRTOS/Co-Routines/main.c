/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

#include "lib/common.h"
#include "lib/setup.h"

#include "lib/coroutine_dimLED.h"
#include "lib/coroutine_indicationLED.h"
#include "lib/timer_periodicLED.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// task handle for dimLED task
extern TaskHandle_t th_dimLED;
// task handle for inicationLED task
extern TaskHandle_t th_indicationLED;
// task handle for periodicLED task
extern TaskHandle_t th_periodicLED;

// semaphore hanlde ADC read
extern SemaphoreHandle_t sh_ADCread;

// queue handle for blocking ADC read
extern QueueHandle_t qh_ADCmutex;
// queue handle for receiving from ISR
extern QueueHandle_t qh_fromISR;

// timer handle for period timer
extern TimerHandle_t tih_periodTimer;

#if (configUSE_IDLE_HOOK == 1)

void vApplicationIdleHook(void);

#endif

//------------------------------------------------------------------------
// INTERRUPT SERVICE ROUTINE
// interrupts when ADC conversion is done
//------------------------------------------------------------------------
ISR(ADC_vect)
{
	// message to queue
	uint8_t msg = 1;
	BaseType_t x = pdFALSE;
	UART_sendstring("3\n");
	// send conversion ready message to queue
	crQUEUE_SEND_FROM_ISR(qh_fromISR, &msg, x);
}

//------------------------------------------------------------------------
// ENTRY POINT
// starts setup, creates mutex, queue, timer and tasks and starts
// scheduling process
//------------------------------------------------------------------------
int main()
{
	// setup GPIO, ADC, PWM and UART
	setup();

	// create queue for blocking ADC read
	qh_ADCmutex = xQueueCreate(1, sizeof(uint8_t));
	// create queue for notifying from ISR
	qh_fromISR = xQueueCreate(1, sizeof(uint8_t));

	// create periodic LED timer
	tih_periodTimer = xTimerCreate("periodTimer", 10, pdTRUE, (void *)0, timer_callback);

	// create LED dimming task with highest priority
	if(xCoRoutineCreate(coroutine_dimLED, 2, 0) != pdPASS)
	{
		UART_sendstring("could not start dimmer\n");
	}
	// create LED indication task with medium priority
	if(xCoRoutineCreate(coroutine_indicationLED, 1, 1) != pdPASS)
	{
		UART_sendstring("could not start indicator\n");
	}
	xCoRoutineCreate(coroutine_periodicLED, 2, 2);

	// start periodic LED timer
	if (xTimerStart(tih_periodTimer, 10) != pdPASS)
	{
		UART_sendstring("could not start timer.\n");
	}

	// start the scheduling process
	vTaskStartScheduler();
}

#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook(void)
{
	while(1 == 1)
	{
		UART_sendstring("sceduled\n");
		vCoRoutineSchedule();
	}
}
#endif
