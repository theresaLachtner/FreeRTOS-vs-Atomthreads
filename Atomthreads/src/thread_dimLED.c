/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/thread_dimLED.h"
#include "../lib/ADC.h"
#include "../lib/PWM.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// mutex for ADC read
extern ATOM_MUTEX _mutex_ADCread;

//------------------------------------------------------------------------
// FORWARD DECLARATIONS
//------------------------------------------------------------------------

// helper function for calculating PWM value
int16_t get_pwmVal(uint16_t pot_value, uint16_t ldr_value);

//------------------------------------------------------------------------
// DIM LED THREAD FUNCTION
// calculates the correct value for PWM adjustment
//------------------------------------------------------------------------
void thread_dimLED(uint32_t param)
{
    // declare and initialize local variables
    uint16_t pot_value = 0;
    uint16_t ldr_value = 0;
    uint16_t pwm_value = 0;
    while (1 == 1)
    {
        // GET VALUES FROM ADC
        while (atomMutexGet(&_mutex_ADCread, 10) != ATOM_OK)
        {
            // wait to get ADC read mutex
        }
        // read potentiometer value
        pot_value = ADC_read(POT1_CHANNEL);
        // put back mutex, in case time slice is up and mutex is needed
        atomMutexPut(&_mutex_ADCread);
        while (atomMutexGet(&_mutex_ADCread, 10) != ATOM_OK)
        {
            // wait to get ADCread mutex
        }
        // read LDR value
        ldr_value = ADC_read(LDR_CHANNEL);
        // put back mutex
        atomMutexPut(&_mutex_ADCread);

        // CALCULATE PWM VALUE
        pwm_value = get_pwmVal(pot_value, ldr_value);

        // SET PWM VALUE
        PWM_adjust(pwm_value);
    }
}

//------------------------------------------------------------------------
// GET PWM VAL FUNCTION
// calculates the correct value for PWM adjustment
//------------------------------------------------------------------------
int16_t get_pwmVal(uint16_t pot_value, uint16_t ldr_value)
{
    ldr_value -= LDR_LOWER_LIMIT;
    ldr_value = (int16_t)(((float)ldr_value / (float)(LDR_UPPER_LIMIT - LDR_LOWER_LIMIT)) * 1023.0);
    int16_t ret_val = pot_value - ldr_value;
    ret_val = (int16_t)(((float)ret_val / 1023.0) * 255.0);
    return ret_val;
}