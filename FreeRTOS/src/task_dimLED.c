#include "../lib/common.h"
#include "../lib/task_dimLED.h"

#include "../lib/ADC.h"
#include "../lib/PWM.h"

int16_t get_pwmVal(uint16_t pot_value, uint16_t ldr_value);

void task_dimLED(void *pvParameters)
{
    // initialize all variables
    int16_t pwm_val = 0;
    uint16_t pot_value = 0;
    uint16_t ldr_value = 0;
    while (1 == 1)
    {
        // read current potentiometer value
        pot_value = ADC_read(POT1_CHANNEL);
        char myChar[20];
        sprintf(myChar, "%d", pot_value);
        UART_sendstring(myChar);
        UART_sendstring("\n\n");
        // read current LDR value
        ldr_value = ADC_read(LDR_CHANNEL);
        UART_sendstring("\n\n");
        // calculate PWM adjustment value from potentiometer and LDR values
        pwm_val = get_pwmVal(pot_value, ldr_value);
        // adjust PWM to calculated value
        PWM_adjust(pwm_val);

        taskYIELD();

    }
}

// calculates the correct value for PWM adjustment
int16_t get_pwmVal(uint16_t pot_value, uint16_t ldr_value)
{
    ldr_value -= LDR_LOWER_LIMIT;
    ldr_value = (int16_t)(((float)ldr_value / (float)(LDR_UPPER_LIMIT - LDR_LOWER_LIMIT)) * 1023.0);
    int16_t ret_val = pot_value - ldr_value;
    ret_val = (int16_t)(((float)ret_val / 1023.0) * 255.0);
    return ret_val;
}