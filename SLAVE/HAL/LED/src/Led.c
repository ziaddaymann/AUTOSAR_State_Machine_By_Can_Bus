 /******************************************************************************
 *
 * Module: LED
 *
 * File Name: Led.c
 *
 * Description: Source file to Initilaze Leds.
 *
 * Author: Ziad Ayman
 *
 *******************************************************************************/
#include "Dio.h"
#include "Led.h"



/************************************************************************************
* Service Name: RED_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Red on.
************************************************************************************/
void RED_On(void)
{
  Dio_WriteChannel(DioConf_RedLED1_CHANNEL_ID_INDEX,LOGIC_HIGH);
  Dio_WriteChannel(DioConf_BlueLED2_CHANNEL_ID_INDEX,LOGIC_LOW);
  Dio_WriteChannel(DioConf_GreenLED3_CHANNEL_ID_INDEX,LOGIC_LOW);
}

/************************************************************************************
* Service Name: BLUE_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to BLUE on.
************************************************************************************/
void BLUE_On(void)
{
  Dio_WriteChannel(DioConf_RedLED1_CHANNEL_ID_INDEX,LOGIC_LOW);
  Dio_WriteChannel(DioConf_BlueLED2_CHANNEL_ID_INDEX,LOGIC_HIGH);
  Dio_WriteChannel(DioConf_GreenLED3_CHANNEL_ID_INDEX,LOGIC_LOW);
}

/************************************************************************************
* Service Name: GREEN_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to GREEN on.
************************************************************************************/
void GREEN_On(void)
{
  Dio_WriteChannel(DioConf_RedLED1_CHANNEL_ID_INDEX,LOGIC_LOW);
  Dio_WriteChannel(DioConf_BlueLED2_CHANNEL_ID_INDEX,LOGIC_LOW);
  Dio_WriteChannel(DioConf_GreenLED3_CHANNEL_ID_INDEX,LOGIC_HIGH);
}

/************************************************************************************
* Service Name: WHITE_On
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to WHITE on.
************************************************************************************/
void WHITE_On(void)
{
  Dio_WriteChannel(DioConf_RedLED1_CHANNEL_ID_INDEX,LOGIC_HIGH);
  Dio_WriteChannel(DioConf_BlueLED2_CHANNEL_ID_INDEX,LOGIC_HIGH);
  Dio_WriteChannel(DioConf_GreenLED3_CHANNEL_ID_INDEX,LOGIC_HIGH);
}
