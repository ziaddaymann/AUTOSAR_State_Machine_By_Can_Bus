  /******************************************************************************
 *
 * [FILE NAME]: <AppTask.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <02/01/2022>
 *
 * [DESCRIPTION]: <Header file for Tasks>
 *
 *******************************************************************************/


#ifndef APP_H_
#define APP_H_

#include "StandardTypes.h"
/************************************************************************************
* Service Name: Init_Task
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Task executes once to initialize all the Modules
************************************************************************************/
void Init_Task(void);
/************************************************************************************
* Service Name: Button_Task
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Task executes every 20 Mili-seconds to check the button state 
************************************************************************************/
void Button_Task(void);

/************************************************************************************
* Service Name: App_Task
* Reentrancy: reentrant
* Parameters (in):  Recieved_Value
* Return value: None
* Description: Task executes every 1000 Mili-seconds to get the button status and toggle the led
************************************************************************************/
void App_Task(uint8 Recieved_Value);

#endif /* APP_H_ */