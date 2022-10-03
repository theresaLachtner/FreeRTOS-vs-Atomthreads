/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/thread_periodicLED.h"
#include "../lib/ADC.h"

// timer for periodic LED
extern ATOM_TIMER _timer_periodicLED;
// mutex for ADC read
extern ATOM_MUTEX _mutex_ADCread;
// queue for signalling timer thread from timer callback
extern ATOM_QUEUE _queue_timerCallback;

//------------------------------------------------------------------------
// PERIODIC LED THREAD FUNCTION
// waits for timer to elapse and send message to queue
// toggles LED, reads new timer period value
// sets timer parameters and starts new timer
//------------------------------------------------------------------------
void thread_periodicLED(uint32_t param)
{
    // tick count
    uint16_t tickCount;
    // time elapsed message from queue
    uint8_t msg = 0;
    // register timer
    atomTimerRegister(&_timer_periodicLED);

    // endless loop
    while (TRUE)
    {
        // wait for message from timer (max timer count value is 1024)
        atomQueueGet(&_queue_timerCallback, 3000, &msg);
        // toggle LED 2
        PIND |= (1 << LED2_CHANNEL);

        // get mutex on ADC read
        atomMutexGet(&_mutex_ADCread, 10);
        // read potentiometer 2 value
        tickCount = ADC_read(POT2_CHANNEL);
        // put back mutex on ADC read
        atomMutexPut(&_mutex_ADCread);
        // tick count must be greater than 0
        if (tickCount < 1)
        {
            tickCount = 1;
        }

        // set timer callback function
        _timer_periodicLED.cb_func = timer_periodicLED;
        // set timer ticks
        _timer_periodicLED.cb_ticks = tickCount;
        // start timer
        atomTimerRegister(&_timer_periodicLED);
    }
}

//------------------------------------------------------------------------
// CALLBACK FUNCTION FOR PERIOD TIMER
// sends time elapsed message to queue
//------------------------------------------------------------------------
void timer_periodicLED(void *param)
{
    // time elapsed signal message
    uint8_t msg = 1;
    // send time elapsed signal to queue
    atomQueuePut(&_queue_timerCallback, 10, &msg);
}