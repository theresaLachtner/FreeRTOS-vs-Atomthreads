#include "lib/common.h"
#include "lib/setup.h"
#include "lib/ADC.h"
#include "lib/task_dimLED.h"
#include "lib/task_periodicLED.h"
#include "lib/task_indicationLED.h"

int main()
{
	setup();
	int counter = 0;
	uint16_t compareValue = 0;
	while (1)
	{
		task_dimLED();
		_delay_ms(10);
		compareValue = ADC_read(POT2_CHANNEL);
		if (counter >= compareValue)
		{
			task_periodicLED();
			counter = 0;
		}
		counter++;
		task_indicationLED();
	}
}