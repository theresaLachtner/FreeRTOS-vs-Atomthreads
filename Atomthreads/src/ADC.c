#include "../lib/common.h"
#include "../lib/ADC.h"

//set voltage reference, prescaler and activate ADC
void ADC_init()
{
	//activate ADC + interrupt
	ADCSRA = (1 << ADEN) | (1 << ADIE); 
	//set AVCC as voltage reference
	ADMUX = (1 << REFS0);
	//set the prescaler to 128 
	ADCSRA |= (1 << ADPS0)|(1 << ADPS1)|(1 << ADPS2);
}

//read single value from ADC-channel
uint16_t ADC_read(uint16_t channel)
{
	//clear channel register
	ADMUX &= ~(0x1F);
	//write channel to register
	ADMUX |= (channel & 0x1F);
	//start conversion
	ADCSRA |= (1 << ADSC);
	//return the raw converted value
	return ADCW;
}
