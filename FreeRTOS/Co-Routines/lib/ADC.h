/*------------------------------------------------------------------------
Project:    FreeRTOS vs. Atomthreads
Submodule:  FreeRTOS
Author:     Theresa Lachtner
Date:       24.07.2022
------------------------------------------------------------------------*/

// set voltage reference, prescaler and activate ADC
void ADC_init();

// read single value from ADC-channel
void ADC_read(uint16_t channel);