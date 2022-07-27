/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

#include "../lib/common.h"
#include "../lib/GPIO.h"

//------------------------------------------------------------------------
// GPIO SET OUTPUT FUNCTION
// sets given pin from given register as output
//------------------------------------------------------------------------
void GPIO_setOutput(volatile uint8_t *DDRx, uint8_t pos)
{
	*DDRx |= (1 << pos);
}

//------------------------------------------------------------------------
// GPIO SET INPUT FUNCTION
// sets given pin from given register as input
//------------------------------------------------------------------------
void GPIO_setInput(volatile uint8_t *DDRx, volatile uint8_t *PORTx, uint8_t pos)
{
	*DDRx &= ~(1 << pos);
	*PORTx |= (1 << pos);	
}
