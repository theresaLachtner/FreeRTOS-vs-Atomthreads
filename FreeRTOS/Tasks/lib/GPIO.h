/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

// set GPIO channel as output
void GPIO_setOutput(volatile uint8_t *DDRx, uint8_t channel);
// set GPIO channel as input
void GPIO_setInput(volatile uint8_t *DDRx, volatile uint8_t *PORTx, uint8_t pos);
