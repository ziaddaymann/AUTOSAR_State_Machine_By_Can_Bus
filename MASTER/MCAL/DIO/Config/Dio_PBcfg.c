 /******************************************************************************
 *
 * [FILE NAME]: <Dio_PBcfg.c>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <03/11/2022>
 *
 * [DESCRIPTION]: <Source file for Post Build Configuration>
 *
 *******************************************************************************/

#include "Dio.h"


/* PB structure used with Dio_Init API */
const Dio_ConfigType Dio_Configuration = {
                                             
				             DioConf_SW1_PORT_NUM,DioConf_SW1_CHANNEL_NUM,    // Portf , Pin 4
				             DioConf_SW2_PORT_NUM,DioConf_SW2_CHANNEL_NUM     // Portf , Pin 0
};