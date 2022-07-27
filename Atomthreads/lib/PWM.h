/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

void PWM_init();
//adjust the PWM by val (val can be smaller than zero)
void PWM_adjust(int16_t val);