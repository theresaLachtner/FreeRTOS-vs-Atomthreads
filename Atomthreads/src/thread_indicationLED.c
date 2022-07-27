/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/thread_indicationLED.h"


//------------------------------------------------------------------------
// INDICATION LED THREAD FUNCTION
// calculates the correct value for PWM adjustment
//------------------------------------------------------------------------
void thread_indicationLED(uint32_t param)
{
    while(1 == 1)
    {
        // if digital input is low, turn off LED 1
        if ((PIND & (1 << DI_CHANNEL)) == 0)
        {
            PORTD &= ~(1 << LED1_CHANNEL);
        }
        // if digital input is high, turn on LED 1
        else
        {
            PORTD |= (1 << LED1_CHANNEL);
        }
    }
}