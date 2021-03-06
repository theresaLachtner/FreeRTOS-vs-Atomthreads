/*
 * FreeRTOSConfigATmega328P.h
 *
 *  Created on: 27/01/2013
 *      Author: extracbd
 */

#ifndef FREERTOSCONFIGATMEGA328P_H_
#define FREERTOSCONFIGATMEGA328P_H_

	#define configMINIMAL_STACK_SIZE	( ( unsigned portSHORT ) 85 )
	#define configTOTAL_HEAP_SIZE		( (size_t ) ( 1200 ) )
	#define configMAX_PRIORITIES		( 4 )
	#define configMAX_TASK_NAME_LEN		( 8 )
	#define configUSE_PREEMPTION		0
	#define configUSE_IDLE_HOOK			1
	#define configUSE_TICK_HOOK			0
	// timer specific defines
	#define configUSE_TIMERS			1
	#define configTIMER_TASK_PRIORITY	4
	#define configTIMER_QUEUE_LENGTH	10
	#define configTIMER_TASK_STACK_DEPTH	configMINIMAL_STACK_SIZE
	#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1

	#define configCPU_CLOCK_HZ			16000000
	#define configTICK_RATE_HZ			1000
	//#define configMAX_TASK_NAME_LEN		( 16 )
	#define configUSE_TRACE_FACILITY	0
	#define configUSE_16_BIT_TICKS		1
	#define configIDLE_SHOULD_YIELD		0
	#define configQUEUE_REGISTRY_SIZE	0
	#define configUSE_MUTEXES			1
	#define configSUPPORT_DYNAMIC_ALLOCATION 1

	/* Co-routine definitions. */
	//##2009.10.20: defined as "0":
	#define configUSE_CO_ROUTINES 		0
	#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

	/* setup() and loop() parameters */
	#define configSETUP_STACK_SIZE          (configMINIMAL_STACK_SIZE * 2)
	#define configLOOP_STACK_SIZE           (configMINIMAL_STACK_SIZE)
	#define configSETUP_PRIORITY			HIGH_PRIORITY
	#define configLOOP_PRIORITY				LOW_PRIORITY

	/* Set the following definitions to 1 to include the API function, or zero
	to exclude the API function. */
	#define INCLUDE_vTaskPrioritySet		0
	#define INCLUDE_uxTaskPriorityGet		0
	#define INCLUDE_vTaskDelete				0
	#define INCLUDE_vTaskCleanUpResources	0
	#define INCLUDE_vTaskSuspend			1
	#define INCLUDE_vTaskDelayUntil			1
	#define INCLUDE_vTaskDelay				1
	#define INCLUDE_xTaskGetSchedulerState  0

#endif /* FREERTOSCONFIGATMEGA328P_H_ */
