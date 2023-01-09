  /******************************************************************************
 *
 * [FILE NAME]: <AppTask.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <01/01/2022>
 *
 * [DESCRIPTION]: <Header file for Tasks>
 *
 *******************************************************************************/



#ifndef APP_H_
#define APP_H_

/* Standard AUTOSAR types */
#include "StandardTypes.h"


#define Clear_Flag 0
#define Reset_Value 1
#define Reset2_Value 3
#define Set_Flag   1
#define Max_Pressed 3 
#define Min_Pressed 1 

/*************************************************
*           API  Functions Prototype
**************************************************/

/************************************************************************************
* Service Name: Init_Task
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (im): None
* Parameters (out): None
* Return value: None
* Description: Intialize Port , Dio Drivers & Can Bus
************************************************************************************/
void Init_Task(void);

/************************************************************************************
* Service Name: Button_Task
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Fuctions To check Buttons state 

************************************************************************************/
void Button_Task(void);

/************************************************************************************
* Service Name: Transmit_MSG
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task executes every 500 Mili-seconds to transmit Can Message

************************************************************************************/
void Transmit_MSG(void);	  

/************************************************************************************
* Service Name: App_Task
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task Executes every 60MS function to change the Leds color according to the Switches State 
*********************************************************************************************************/
void App_Task(void);

/******************************************************************************/
#endif /* APP_H_ */