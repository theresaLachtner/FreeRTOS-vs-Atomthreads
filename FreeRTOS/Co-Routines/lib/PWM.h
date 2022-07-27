/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

// initialize PWM
void PWM_init();
// adjust the PWM by val (val can be smaller than zero)
void PWM_adjust(int16_t val);