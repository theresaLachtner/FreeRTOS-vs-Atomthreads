/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

#include "lib/common.h"
#include "lib/setup.h"
#include "lib/thread_dimLED.h"
#include "lib/thread_indicationLED.h"
#include "lib/thread_periodicLED.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// mutex for ADC read function
extern ATOM_MUTEX _mutex_ADCread;
// queue for sending data ready message to ADC read funciton
extern ATOM_QUEUE _queue_ADCread;
// queue for signalling timer thread from timer callback
extern ATOM_QUEUE _queue_timerCallback;
// periodic LED timer
extern ATOM_TIMER _timer_periodicLED;

//------------------------------------------------------------------------
// STATIC VARIABLES
//------------------------------------------------------------------------

// storage for ADC read queue
static uint8_t queueStorage_ADCread[1];
// storage for timer callback
static uint8_t queueStorage_timerCallback[1];

// tcb storage for dim LED thread
static ATOM_TCB tcb_dimLED;
// stack of the dim LED thread
static uint8_t stack_dimLED[128];

// tcb storage for indication LED thread
static ATOM_TCB tcb_indicationLED;
// stack of the indication LED thread
static uint8_t stack_indicationLED[128];

// tcb storage for periodic LED thread
static ATOM_TCB tcb_periodicLED;
// stack of the periodic LED thread
static uint8_t stack_periodicLED[128];

// idle stac for atomOSInit function
static uint8_t stack_idleThread[128];

//------------------------------------------------------------------------
// INTERRUPT SERVICE ROUTINE
// interrupts when ADC conversion is done
//------------------------------------------------------------------------
ISR(ADC_vect)
{
	// mandatory atomthreads function when entering an ISR
	atomIntEnter();
	UART_sendstring("2\n");

	// data ready message
	uint8_t msg = 1;
	// send data ready message to queue
	if(atomQueuePut(&_queue_ADCread, 10, &msg) != ATOM_OK)
	{
		UART_sendstring("send error\n");
	}

	// mandatory atomthreads function when exiting an ISR
	atomIntExit(TRUE);
}

//------------------------------------------------------------------------
// ENTRY POINT
// starts setup, creates mutex, queues, timer and threads and starts
// scheduling process
//------------------------------------------------------------------------
int main()
{
	// setup GPIO, UART, ADC and PWM
	setup();

	// init atom OS
	atomOSInit(&stack_idleThread[0], 128, FALSE);
	// initialize the system tick timer - uses timer1
	avrInitSystemTickTimer();

	// create dim LED thread
	atomThreadCreate(&tcb_dimLED, 10, thread_dimLED, 0, &stack_dimLED[0], 128, TRUE);
	// create indication LED thread
	atomThreadCreate(&tcb_indicationLED, 10, thread_indicationLED, 0, &stack_indicationLED[0], 128, TRUE);
	// create periodic LED thread
	atomThreadCreate(&tcb_periodicLED, 10, thread_periodicLED, 0, &stack_periodicLED[0], 128, TRUE);

	_timer_periodicLED.cb_func = timer_periodicLED;
	_timer_periodicLED.cb_ticks = 1000;
	//atomTimerRegister(&_timer_periodicLED);
	
	// create mutex for ADC read
	atomMutexCreate(&_mutex_ADCread);
	// create queue for ADC read
	atomQueueCreate(&_queue_ADCread, &queueStorage_ADCread[0], sizeof(uint8_t), 1);
	// create queue for timer callback
	atomQueueCreate(&_queue_timerCallback, &queueStorage_timerCallback[0], sizeof(uint8_t), 1);


	// start scheduling
	atomOSStart();
}
