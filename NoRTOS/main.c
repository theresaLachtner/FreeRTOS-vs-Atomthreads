#include "lib/common.h"
#include "lib/setup.h"
#include "lib/task_dimLED.h"
#include "lib/task_periodicLED.h"
#include "lib/task_indicationLED.h"


int main()
{
	setup();
	while (1)
	{
		task_dimLED();
		task_periodicLED();
		task_indicationLED();
	}
}