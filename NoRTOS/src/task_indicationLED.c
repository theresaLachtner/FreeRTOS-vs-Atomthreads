#include "../lib/common.h"
#include "../lib/task_indicationLED.h"

// function responsible for turning on/off indicator LED
void task_indicationLED()
{
    // if digital input is low, turn off LED 1
    if ((PIND & (1 << DI_CHANNEL)) == 0)
    {
        PORTD &= ~(1 << LED1_CHANNEL);
    }
    // if digital input is hight, turn on LED 1
    else
    {
        PORTD |= (1 << LED1_CHANNEL);
    }
}