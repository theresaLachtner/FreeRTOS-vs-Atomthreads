#include "../lib/common.h"
#include "../lib/task_periodicLED.h"

// function responsible for turning on/off LED periodically
void task_periodicLED()
{
    PIND |= (1 << LED2_CHANNEL);
}

