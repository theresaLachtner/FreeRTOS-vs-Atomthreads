/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

// initialize UART
void UART_init (uint32_t baudrate);
// transmit single byte via UART
void UART_transmit(uint8_t byte_to_send);
// transmit string via UART
void UART_sendstring(char *p);
