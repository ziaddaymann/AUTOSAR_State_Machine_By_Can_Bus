  /******************************************************************************
 *
 * [FILE NAME]: <AppTask.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <01/01/2022>
 *
 * [DESCRIPTION]: <Source file for Tasks>
 *
 *******************************************************************************/

#include "AppTask.h"
#include "Port.h"
#include "Button.h"
#include "Dio.h"
#include "TransmissionState.h"

/* state machine variable linked with Sw1*/
static uint8  state_machine=0;

/*Variable to Check if both flags Pressed or No*/
static volatile uint8 Two_Switches_Flag=0;

/* Flag to indicate that there is a new command from Sw1 to be transmitted*/ 
static volatile uint8 SW1_Flag=0;

/* Flag to indicate that there is a new command from Sw1 to be transmitted*/ 
static volatile uint8 SW2_Flag=0;
/************************************************************************************
* Service Name: Init_Task
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (im): None
* Parameters (out): None
* Return value: None
* Description: Intialize Port , Dio Drivers & Can Bus
************************************************************************************/
void Init_Task(void)
{
    /* Initialize Port Driver */
    Port_Init(&Port_ConfigSet[0]); 
      
    /* Initialize DIO Driver */
    Dio_Init(&Dio_Configuration); 
    
    /* Initialize Can Bus */
    initcan();
}


/************************************************************************************
* Service Name: Button_Task
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Fuctions To check Buttons state 

************************************************************************************/
void Button_Task(void)
{
    Button1_Current_State();
    
    Button2_Current_State();
}


/************************************************************************************
* Service Name: Transmit_MSG
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task executes every 500 Mili-seconds to transmit Can Message

************************************************************************************/

void Transmit_MSG(void)
{
  if(Two_Switches_Flag==Set_Flag)
     {
       TransmissionState(Two_Switches_Flag);
     }
  else if(SW1_Flag==Set_Flag)
  {
    TransmissionState(state_machine);
    
    SW1_Flag=Clear_Flag;
  }
  else if(SW2_Flag==Set_Flag)
  {
    TransmissionState(state_machine);
    
    SW2_Flag=Clear_Flag;
  }
}

/************************************************************************************
* Service Name: App_Task
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Task Executes every 40MS function to change the Leds color according to the Switches State 
*********************************************************************************************************/
void App_Task(void)
{
  /* Variables to reade Sw1 Current & Prervious state*/
    static uint8 button1_previous_state = BUTTON_RELEASED;
     static uint8 button1_current_state  = BUTTON_RELEASED;

      /* Variables to reade Sw2 Current & Prervious state*/
     static uint8 button2_previous_state = BUTTON_RELEASED;
    static uint8 button2_current_state  = BUTTON_RELEASED;
    
    /* Read the SW1 state */
    button1_current_state = BUTTON_getState1();
    
     /* Read the SW2 state */
    button2_current_state = BUTTON_getState2(); 

   /* Checks the boths buttons current state is pressed and the previous state is not pressed*/
    if ((button2_current_state ==BUTTON_PRESSED)&&(button2_previous_state==BUTTON_RELEASED)
         &&(button1_current_state ==BUTTON_PRESSED)&&(button1_previous_state==BUTTON_RELEASED))
     {
       
      /*resets Sw1 & Sw2 state machine states variables*/
       state_machine=Reset_Value;
       
       /*Raise the Two_Switches flag */
       Two_Switches_Flag=Set_Flag;
     }
    /* Checks the button current state is pressed and the previous state is not pressed*/
   else if ((button1_current_state ==BUTTON_PRESSED)&&(button1_previous_state==BUTTON_RELEASED))
    {
       /*Resets the Two_Switches flag */
      Two_Switches_Flag=Clear_Flag;
      
      /*Raise  the Sw1 flag */
      SW1_Flag=Set_Flag;
      
      if(state_machine<= Min_Pressed )
      {
        /*Resets the Sw1 State machine flag if it exceeds Max_Pressed */
        state_machine=Reset2_Value;
      }
      else
      {
        /*Incremente State Machine 1 variable*/
        state_machine--;
      }
    } 
         
    
    /* Checks the button current state is pressed and the previous state is not pressed*/
     else if ((button2_current_state ==BUTTON_PRESSED)&&(button2_previous_state==BUTTON_RELEASED))
    {
      
      /*Resets the Two_Switches flag */
      Two_Switches_Flag=Clear_Flag;
      
     /*Raise  the Sw1 flag */
      SW2_Flag=Set_Flag;
      if(state_machine>=Max_Pressed )
      {
        /*Resets the Sw1 State machine flag if it exceeds Max_Pressed */
        state_machine=Reset_Value;
      }
      else
      {
        /*Incremente State Machine 1 variable*/
        state_machine++;
      }
    }
    
    
 /*Saves the Current buttons state in previous state variable*/   
button1_previous_state=button1_current_state;
button2_previous_state=button2_current_state;
}
