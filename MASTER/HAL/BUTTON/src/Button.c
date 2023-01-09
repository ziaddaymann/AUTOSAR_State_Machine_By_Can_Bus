 /******************************************************************************
 *
 * Module: Button
 *
 * File Name: Button.c
 *
 * Description: Source file to Initilaze Buttons.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/

#include "Dio.h"
#include "Button.h"

/* Global variable to hold the button state */
#define BUTTON_DEBOUNCE_THRESHOLD 3

/* Global variables to hold the button states */
static uint8 buttonStateSW1 = BUTTON_RELEASED;
static uint8 buttonStateSW2 = BUTTON_RELEASED;

/************************************************************************************
* Service Name: BUTTON_getState1
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): Switch 1 State
* Return value: None
* Description: Returns the current state of switch 1
*********************************************************************************************************/
uint8 BUTTON_getState1(void)
{
    return buttonStateSW1;
}

/************************************************************************************
* Service Name: BUTTON_getState2
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): Switch 2 State
* Return value: None
* Description: Returns the current state of switch 2
*********************************************************************************************************/
uint8 BUTTON_getState2(void)
{
    return buttonStateSW2;
}

/************************************************************************************
* Service Name: Button1_Current_State
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Updates the state of switch 1 using debouncing to ensure reliable button presses
*********************************************************************************************************/
void Button1_Current_State(void)
{
    /* Counter to track debouncing */
    static uint8 debounceCounter = 0;

    /* Get the current state of the button */
    uint8 currentState = Dio_ReadChannel(DioConf_SW1_CHANNEL_ID_INDEX);

    /* If the current state is the same as the previous state, reset the debounce counter */
    if (currentState == buttonStateSW1)
    {
        debounceCounter = 0;
    }
    /* If the current state is different from the previous state, increment the debounce counter */
    else
    {
        debounceCounter++;
        /* If the debounce counter has reached the threshold, update the button state and reset the debounce counter */
        
        if (debounceCounter >= BUTTON_DEBOUNCE_THRESHOLD)
        {
            buttonStateSW1 = currentState;
            debounceCounter = 0;
        }
    }
}

/************************************************************************************
* Service Name: Button2_Current_State
* Reentrancy: Non-reentrant
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: Updates the state of switch 2 using debouncing to ensure reliable button presses
*********************************************************************************************************/
void Button2_Current_State(void)
{
    /* Counter to track debouncing */
    static uint8 debounceCounter = 0;

    /* Get the current state of the button */
    uint8 currentState = Dio_ReadChannel(DioConf_SW2_CHANNEL_ID_INDEX);

    /* If the current state is the same as the previous state, reset the debounce counter */
    if (currentState == buttonStateSW2)
    {
        debounceCounter = 0;
    }
    /* If the current state is different from the previous state, increment the debounce counter */
    else
    {
        debounceCounter++;
        /* If the debounce counter has reached the threshold, update the button state and reset the debounce counter */
        if (debounceCounter >= BUTTON_DEBOUNCE_THRESHOLD)
        {
            buttonStateSW2 = currentState;
            debounceCounter = 0;
        }
    }
}
