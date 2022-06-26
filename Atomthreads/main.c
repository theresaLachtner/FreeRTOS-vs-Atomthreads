#include "lib/common.h"
#include "lib/setup.h"

#if (configUSE_IDLE_HOOK == 1)

void vApplicationIdleHook(void);

#endif


int main()
{
	setup();
}

#if (configUSE_IDLE_HOOK == 1)
void vApplicationIdleHook(void)
{
	// vCoRoutineSchedule();
}
#endif
