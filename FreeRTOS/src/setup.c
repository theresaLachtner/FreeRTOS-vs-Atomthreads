#include "../lib/setup.h"
#include "../lib/common.h"
#include "../lib/GPIO.h"
#include "../lib/ADC.h"
#include "../lib/PWM.h"

void setup()
{
#ifdef DEBUG
	UART_init(115200);
#endif
	// set GPIO ports D6 and D5 to output for LED_1 and LED_2
	GPIO_setOutput(&DDRD, PWM_CHANNEL);
	GPIO_setOutput(&DDRD, DO_CHANNEL);
	// set GPOO port D4 to input for LDR-module
	GPIO_setInput(&DDRD, &PORTD, DI_CHANNEL);
	// initialize ADC
	ADC_init();
	// initialize PWM
	PWM_init();
}
