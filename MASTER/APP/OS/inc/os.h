  /******************************************************************************
 *
 * [FILE NAME]: <os.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <01/01/2023>
 *
 * [DESCRIPTION]: <Header file for OS Scheduler>
 *
 *******************************************************************************/
#ifndef OS_H_
#define OS_H_

/* Standard AUTOSAR types */
#include "StandardTypes.h"

/* Timer counting time in ms */
#define TIMER_BASE 20
#define EVERY_20 20
#define EVERY_60 60
#define EVERY_500 500



/*************************************************
*           API  Functions Prototype
**************************************************/

/************************************************************************************
* Service Name: Os_start
* Reentrancy: Non-Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Intialize the System .
************************************************************************************/
void Os_start(void);

/************************************************************************************
* Service Name: Os_Scheduler
* Reentrancy: Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Scheduler Task.
************************************************************************************/
void Os_Scheduler(void);

/************************************************************************************
* Service Name: OS_Timer_Reschedule
* Reentrancy: Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: This function is a timer tick handler for a software timer in an operating system.
************************************************************************************/
void OS_Timer_Reschedule(void);

/************************************************************************************
* Service Name: OS_Can_Refresh
* Reentrancy: Reentrant 
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Can Callback Function.
************************************************************************************/
void OS_Can_Refresh(void);
/******************************************************************************/
#endif /* OS_H_ */