/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:	Atomthreads
Author:     Theresa Lachtner
Date:       26.07.2022
------------------------------------------------------------------------*/

// indication LED thread function
void thread_periodicLED(uint32_t param);
// callback function for periodic LED timer
void timer_periodicLED(void* param);