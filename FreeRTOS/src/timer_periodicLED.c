#include "../lib/common.h"
#include "../lib/task_periodicLED.h"
#include "../lib/ADC.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// timer handle for period timer
extern TimerHandle_t tih_periodTimer;

//------------------------------------------------------------------------
// LOCAL VARIABLES
//------------------------------------------------------------------------

// semaphore handle for ADC read mutex
SemaphoreHandle_t sh_ADCread;
// timer period
uint16_t timerPeriod = 1;

//------------------------------------------------------------------------
// TIMER CALLBACK FUNCTION
// for periodic LED timer - reads potentiometer value, sets timer period
// and toggles LED 2
//------------------------------------------------------------------------
void timer_callback(TimerHandle_t tih_timer)
{
    BaseType_t gotMutex = pdFALSE;
    // wait to get ADC read mutex 
    while (gotMutex == pdFALSE)
    {
        // take ADC read mutex
        if(xSemaphoreTake(sh_ADCread, (TickType_t)10) == pdTRUE)
        {
            // read timer period from potentiometer 2
            timerPeriod = ADC_read(POT2_CHANNEL);
            // give back mutex
            xSemaphoreGive(sh_ADCread);
            // timer period must not be less than 1
            if(timerPeriod < 1)
            {
                timerPeriod = 1;
            }
            // set mutex flag to true
            gotMutex = pdTRUE;
        }
        else
        {
            // if mutex is taken, yield remaining slice time
            portYIELD();
        }
    }

    // change the timer period
    xTimerChangePeriod(tih_timer, timerPeriod, 1);

    // toggle LED
    PIND |= (1 << LED2_CHANNEL);
}