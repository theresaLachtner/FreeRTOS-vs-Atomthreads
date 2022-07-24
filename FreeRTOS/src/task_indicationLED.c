#include "../lib/common.h"
#include "../lib/task_indicationLED.h"

//------------------------------------------------------------------------
// TASK FUNCTION
// for indication LED task - reads digital input from light dependent
// resistor and sets LED 1 output high or low
//------------------------------------------------------------------------
void task_indicationLED(void *pvParameters)
{
    while (1 == 1)
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
        // yield remaining slice time
        taskYIELD();
    }
}