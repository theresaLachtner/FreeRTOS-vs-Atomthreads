#include "../lib/common.h"
#include "../lib/GPIO.h"

void GPIO_setOutput(volatile uint8_t *DDRx, uint8_t pos)
{
	*DDRx |= (1 << pos);
}

void GPIO_setInput(volatile uint8_t *DDRx, volatile uint8_t *PORTx, uint8_t pos)
{
	*DDRx &= ~(1 << pos);
	*PORTx |= (1 << pos);	
}
