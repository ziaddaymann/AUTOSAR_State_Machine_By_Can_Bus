  /******************************************************************************
 *
 * [FILE NAME]: <AppTask.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <02/01/2022>
 *
 * [DESCRIPTION]: <Source file for Tasks>
 *
 *******************************************************************************/

#include "AppTask.h"
#include "Port.h"
#include "Dio.h"
#include "Led.h"


/************************************************************************************
* Service Name: Init_Task
* Reentrancy: reentrant
* Parameters (in):  None
* Return value: None
* Description: Task executes once to initialize all the Modules
************************************************************************************/
void Init_Task(void)
{
   /* Initialize Port Driver */
  Port_Init(&Port_ConfigSet[0]);
  /* Initialize Dio Driver */
  Dio_Init(&Dio_Configuration);
}

/************************************************************************************
* Service Name: App_Task
* Reentrancy: reentrant
* Parameters (in):  Recieved_Value
* Return value: None
* Description: Task executes every 1000 Mili-seconds to get the button status and toggle the led
************************************************************************************/
void App_Task(uint8 Recieved_Value)
{    
  static uint8 state_machine;
  static uint8 PreviousState;
  static uint32 ElapsedTime;

    state_machine = Recieved_Value;
    
    if (state_machine == PreviousState) // if state has not changed
    {
        ElapsedTime += 1000; // increment elapsed time by 1000ms (since AppTask is called every 1000ms)
    }
    else // if state has changed
    {
        ElapsedTime = 0; // reset elapsed time
        PreviousState = state_machine; // update previous state
    }
    
    if (ElapsedTime >= 5000)
    {
      WHITE_On();
    }
    
    else
    {
    
  if(state_machine==1)
  {
    RED_On();
  }
  else if (state_machine==2)
  {
    BLUE_On();
  }
  else if (state_machine==3)
  {
    GREEN_On();
  }
  else {}
    }
  
}