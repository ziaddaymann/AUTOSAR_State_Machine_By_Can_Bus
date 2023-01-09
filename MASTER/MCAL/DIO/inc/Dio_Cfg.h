  /******************************************************************************
 *
 * [FILE NAME]: <Dio_Cfg.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <03/11/2022>
 *
 * [DESCRIPTION]: <Header file for Pre Compile Configurations>
 *
 *******************************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H



/* Pre-compile option for presence of Dio_FlipChannel API */
#define DIO_FLIP_CHANNEL_API                (STD_ON)

/* Number of the configured Dio Channels */
#define DIO_CONFIGURED_CHANNLES              (2U)

/* Channel Index in the array of structures in Dio_PBcfg.c */


#define DioConf_SW1_CHANNEL_ID_INDEX         (uint8)0x00
#define DioConf_SW2_CHANNEL_ID_INDEX         (uint8)0x01

/* DIO Configured Port ID's  */

#define DioConf_SW1_PORT_NUM                 (Dio_PortType)5 /* PORTF */
#define DioConf_SW2_PORT_NUM                 (Dio_PortType)5 /* PORTF */

/* DIO Configured Channel ID's */
#define DioConf_SW1_CHANNEL_NUM              (Dio_ChannelType)4 /* Pin 4 in PORTF */
#define DioConf_SW2_CHANNEL_NUM              (Dio_ChannelType)0 /* Pin 0in PORTF */

#endif /* DIO_CFG_H */
