  /******************************************************************************
 *
 * [FILE NAME]: <os.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <02/01/2023>
 *
 * [DESCRIPTION]: <Header file for OS Scheduler>
 *
 *******************************************************************************/

#ifndef OS_H_
#define OS_H_

#include "StandardTypes.h"

/* Timer counting time in ms */
#define TIMER_BASE 10
#define EVERY_10   10
#define EVERY_100 100

/************************************************************************************
* Service Name: Os_start
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Task executes once to initialize the os
************************************************************************************/
void Os_start(void);
/************************************************************************************
* Service Name: Os_Scheduler
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: The Engine of the Os Scheduler used for switch between different tasks
************************************************************************************/
void Os_Scheduler(void);
/************************************************************************************
* Service Name: Os_NewTimerTick
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Function called by the Timer Driver in the MCAL layer using the call back pointer
************************************************************************************/
void Os_NewTimerTick(void);
/************************************************************************************
* Service Name: OS_Can_Refresh
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Function called by the Can Driver in the MCAL layer using the call back pointer
************************************************************************************/
void OS_Can_Refresh(void);

#endif /* OS_H_ */