/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/timer_periodicLED.h"
#include "../lib/ADC.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// timer handle for period timer
extern TimerHandle_t tih_periodTimer;
// queue handle for blocking ADC read
extern QueueHandle_t qh_ADCmutex;
// queue handle for receiving from ISR
extern QueueHandle_t qh_fromISR;
// queue handle for blocking until timer elapses
extern QueueHandle_t qh_timerElapsed;

//------------------------------------------------------------------------
// CO-ROUTINE FUNCTION
// for periodic LED co-routine reads new timer period when timer elapses
//------------------------------------------------------------------------
void coroutine_periodicLED(CoRoutineHandle_t xHandle, UBaseType_t uxIndex)
{
    // timer period
    static uint16_t timerPeriod = 1;
    // blocked queue flag
    static BaseType_t blockedQueue = pdFALSE;
    static BaseType_t success = pdFALSE;
    // message to queue
    static uint8_t msg = 1;

    // start co-routine
    crSTART(xHandle);
    // block queue for first time
    crQUEUE_SEND(xHandle, qh_timerElapsed, &msg, 1, &success);
    while (1 == 1)
    {    
        UART_sendstring("here\n");
        // wait for timer to elapse
        crQUEUE_RECEIVE(xHandle, qh_timerElapsed, &msg, 1, &success);
        // wait to get ADC read mutex 
        while (blockedQueue != pdPASS)
        {
            // block ADC mutex queue
            crQUEUE_SEND(xHandle, qh_ADCmutex, &msg, (TickType_t)10, &blockedQueue);

            // taken ADC read mutex
            if (blockedQueue == pdPASS)
            {
                // read timer period from potentiometer 2
                ADC_read(POT2_CHANNEL);
                // wait for message from ISR
                crQUEUE_RECEIVE(xHandle, qh_fromISR, &msg, (TickType_t)100, &success);
                // read converted ADC value
                timerPeriod = ADCW;
                // unblock queue
                crQUEUE_RECEIVE(xHandle, qh_ADCmutex, &msg, (TickType_t)10, &success);
                // timer period must not be less than 1
                if(timerPeriod < 1)
                {
                    timerPeriod = 1;
                }
                // set mutex flag to true
                blockedQueue = pdTRUE;

                // block timer elapsed queue
                crQUEUE_SEND(xHandle, qh_timerElapsed, &msg, 10, &success);
            }
        }

        // change the timer period
        xTimerChangePeriod(tih_periodTimer, timerPeriod, 1);
    }
    // end co-routine
    crEND();
}

//------------------------------------------------------------------------
// TIMER CALLBACK FUNCTION
// toggles LED 2
//------------------------------------------------------------------------
void timer_callback(TimerHandle_t tih_periodTimer)
{
    // toggle LED
    PIND |= (1 << LED2_CHANNEL);
}