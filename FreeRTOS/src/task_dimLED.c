/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/task_dimLED.h"

#include "../lib/ADC.h"
#include "../lib/PWM.h"

//------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------

// semaphore handle for ADC read mutex
extern SemaphoreHandle_t sh_ADCread;

//------------------------------------------------------------------------
// FUNCTION DECLARATION
//------------------------------------------------------------------------

// local helper function to calculate PWM value
int16_t get_pwmVal(uint16_t pot_value, uint16_t ldr_value);

//------------------------------------------------------------------------
// DIM LED TASK FUNCTION
// reads potentiometer and LDR values and calculates the corresponding
// PWM value for dimmable LED
//------------------------------------------------------------------------
void task_dimLED(void *pvParameters)
{
    // initialize all variables
    int16_t pwm_val = 0;
    uint16_t pot_value = 0;
    uint16_t ldr_value = 0;
    // mutex flag
    BaseType_t gotMutex;
    while (1 == 1)
    {
        // reset mutex flag
        gotMutex = pdFALSE;
        // read current potentiometer value
        while (gotMutex == pdFALSE)
        {
            // take ADC read mutex
            if (xSemaphoreTake(sh_ADCread, (TickType_t)10) == pdPASS)
            {
                UART_sendstring("1\n");
                // read value from potentiometer 1
                pot_value = ADC_read(POT1_CHANNEL);
                // give back mutex
                xSemaphoreGive(sh_ADCread);
                // set mutex flag to true
                gotMutex = pdTRUE;
            }
            else
            {
                // if mutex is taken, yield remaining slice time
                portYIELD();
            }
        }

        // reset mutex flag
        gotMutex = pdFALSE;

        // read current LDR value
        while (gotMutex == pdFALSE)
        {
            // take ADC read mutex
            if (xSemaphoreTake(sh_ADCread, (TickType_t)10) == pdPASS)
            {
                // UART_sendstring("2\n");
                //  read value from LDR
                ldr_value = ADC_read(LDR_CHANNEL);
                // give back mutex
                xSemaphoreGive(sh_ADCread);
                // set mutex flag to true
                gotMutex = pdTRUE;
            }
            else
            {
                // if mutex is taken, yield remaining slice time
                portYIELD();
            }
        }

        // calculate PWM adjustment value from potentiometer and LDR values
        pwm_val = get_pwmVal(pot_value, ldr_value);
        // adjust PWM to calculated value
        PWM_adjust(pwm_val);

        taskYIELD();
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