/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

#include "lib/common.h"
#include "lib/setup.h"

#include "lib/task_dimLED.h"
#include "lib/task_indicationLED.h"
#include "lib/task_periodicLED.h"
#include "lib/timer_measurement.h"


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

// queue handle for ADC interrupt queue
extern QueueHandle_t qh_ADCinterrupt;

// timer handle for period timer
extern TimerHandle_t tih_periodTimer;
// timer handle for measurement timer
extern TimerHandle_t tih_measurementTimer;

#if (configUSE_IDLE_HOOK == 1)

void vApplicationIdleHook(void);

#endif

//------------------------------------------------------------------------
// INTERRUPT SERVICE ROUTINE
// interrupts when ADC conversion is done
//------------------------------------------------------------------------
ISR(ADC_vect)
{
	// stores the task handle currently blocking the ADC read mutex
	TaskHandle_t th_current;
	// task woken by receive
	BaseType_t taskWokenByReceive = pdFALSE;
	// read the current task handle from queue
	xQueueReceiveFromISR(qh_ADCinterrupt, &th_current, &taskWokenByReceive);
	// resume current ADC reading task
	xTaskNotifyFromISR(th_current, 0, (eNotifyAction)eNoAction, NULL);
	portYIELD();
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

	// create mutex for ADC read
	sh_ADCread = xSemaphoreCreateMutex();

	// create queue for ADC interrupt
	qh_ADCinterrupt = xQueueCreate(5, sizeof(TaskHandle_t));

	// create periodic LED timer
	tih_periodTimer = xTimerCreate("periodTimer", 10, pdTRUE, (void *)0, timer_callback);
	// create periodic LED timer
	tih_measurementTimer = xTimerCreate("measurementTimer", 5000, pdTRUE, (void *)0, m_timer_callback);

	// create LED dimming task with highest priority
	xTaskCreate(&task_dimLED, (portCHAR *)"dimLED", configMINIMAL_STACK_SIZE, NULL, 4, &th_dimLED);
	// create LED indication task with medium priority
	xTaskCreate(&task_indicationLED, (portCHAR *)"indicationLED", configMINIMAL_STACK_SIZE, NULL, 4, &th_indicationLED);

	// start periodic LED timer
	if (xTimerStart(tih_periodTimer, 10) != pdPASS)
	{
		UART_sendstring("could not start timer.\n");
	}
	if (xTimerStart(tih_measurementTimer, 10) != pdPASS)
	{
		UART_sendstring("could not start timer.\n");
	}

	// start the scheduling process
	vTaskStartScheduler();
}

#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook(void)
{
	// vCoRoutineSchedule();
}
#endif
