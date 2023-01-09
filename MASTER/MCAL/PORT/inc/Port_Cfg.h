  /******************************************************************************
 *
 * [FILE NAME]: <Port_Cfg.h>
 *
 * [AUTHOR]: <Ziad Ayman>
 *
 * [DATE CREATED]: <03/11/2022>
 *
 * [DESCRIPTION]: <Header file for Pre Compile Confg>
 *
 *******************************************************************************/
 
 
#ifndef PORT_CFG_H
#define PORT_CFG_H



   /*Pre-compile to enable / disable the use of the function 
Port_SetPinDirection()   */
#define PORT_SET_PIN_DIRECTION_API            (STD_OFF)

/* Pre-compile to enable / disable the use of the function 
Port_SetPinMode(). */
#define PORT_SET_PIN_MODE_API                 (STD_OFF)

/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES             (43U)
   
/* Number of the configured Port Modes */
#define PORT_MODES             (8U)
   
/* Channel Index in the array of structures in Port_PBcfg.c */
#define PortConf_PortA_Pin0_CHANNEL_ID_INDEX        (uint8)0x00
#define PortConf_PortA_Pin1_CHANNEL_ID_INDEX        (uint8)0x01
#define PortConf_PortA_Pin2_CHANNEL_ID_INDEX        (uint8)0x02
#define PortConf_PortA_Pin3_CHANNEL_ID_INDEX        (uint8)0x03
#define PortConf_PortA_Pin4_CHANNEL_ID_INDEX        (uint8)0x04
#define PortConf_PortA_Pin5_CHANNEL_ID_INDEX        (uint8)0x05
#define PortConf_PortA_Pin6_CHANNEL_ID_INDEX        (uint8)0x06
#define PortConf_PortA_Pin7_CHANNEL_ID_INDEX        (uint8)0x07

#define PortConf_PortB_Pin0_CHANNEL_ID_INDEX        (uint8)0x08
#define PortConf_PortB_Pin1_CHANNEL_ID_INDEX        (uint8)0x09
#define PortConf_PortB_Pin2_CHANNEL_ID_INDEX        (uint8)0x0A
#define PortConf_PortB_Pin3_CHANNEL_ID_INDEX        (uint8)0x0B
#define PortConf_PortB_Pin4_CHANNEL_ID_INDEX        (uint8)0x0C
#define PortConf_PortB_Pin5_CHANNEL_ID_INDEX        (uint8)0x0D
#define PortConf_PortB_Pin6_CHANNEL_ID_INDEX        (uint8)0x0E
#define PortConf_PortB_Pin7_CHANNEL_ID_INDEX        (uint8)0x0F

#define PortConf_PortC_Pin0_CHANNEL_ID_INDEX        (uint8)0x10
#define PortConf_PortC_Pin1_CHANNEL_ID_INDEX        (uint8)0x11
#define PortConf_PortC_Pin2_CHANNEL_ID_INDEX        (uint8)0x12
#define PortConf_PortC_Pin3_CHANNEL_ID_INDEX        (uint8)0x13
#define PortConf_PortC_Pin4_CHANNEL_ID_INDEX        (uint8)0x14
#define PortConf_PortC_Pin5_CHANNEL_ID_INDEX        (uint8)0x15
#define PortConf_PortC_Pin6_CHANNEL_ID_INDEX        (uint8)0x16
#define PortConf_PortC_Pin7_CHANNEL_ID_INDEX        (uint8)0x17

#define PortConf_PortD_Pin0_CHANNEL_ID_INDEX        (uint8)0x18
#define PortConf_PortD_Pin1_CHANNEL_ID_INDEX        (uint8)0x19
#define PortConf_PortD_Pin2_CHANNEL_ID_INDEX        (uint8)0x1A
#define PortConf_PortD_Pin3_CHANNEL_ID_INDEX        (uint8)0x1B
#define PortConf_PortD_Pin4_CHANNEL_ID_INDEX        (uint8)0x1C
#define PortConf_PortD_Pin5_CHANNEL_ID_INDEX        (uint8)0x1D
#define PortConf_PortD_Pin6_CHANNEL_ID_INDEX        (uint8)0x1E
#define PortConf_PortD_Pin7_CHANNEL_ID_INDEX        (uint8)0x1F

#define PortConf_PortE_Pin0_CHANNEL_ID_INDEX        (uint8)0x20
#define PortConf_PortE_Pin1_CHANNEL_ID_INDEX        (uint8)0x21
#define PortConf_PortE_Pin2_CHANNEL_ID_INDEX        (uint8)0x22
#define PortConf_PortE_Pin3_CHANNEL_ID_INDEX        (uint8)0x23
#define PortConf_PortE_Pin4_CHANNEL_ID_INDEX        (uint8)0x24
#define PortConf_PortE_Pin5_CHANNEL_ID_INDEX        (uint8)0x25

#define PortConf_PortF_Pin0_CHANNEL_ID_INDEX        (uint8)0x26
#define PortConf_PortF_Pin1_CHANNEL_ID_INDEX        (uint8)0X27
#define PortConf_PortF_Pin2_CHANNEL_ID_INDEX        (uint8)0x28
#define PortConf_PortF_Pin3_CHANNEL_ID_INDEX        (uint8)0x29
#define PortConf_PortF_Pin4_CHANNEL_ID_INDEX        (uint8)0x2A
   
   
/* Port Configured Port ID's  */
#define PortConf_PORTA_NUM            (Port_PinType)0U 
#define PortConf_PORTB_NUM            (Port_PinType)1U
#define PortConf_PORTC_NUM            (Port_PinType)2U
#define PortConf_PORTD_NUM            (Port_PinType)3U
#define PortConf_PORTE_NUM            (Port_PinType)4U 
#define PortConf_PORTF_NUM            (Port_PinType)5U 
   
   

/* Port Configured Channel ID's */
#define PortConf_Pin0_CHANNEL_NUM       (uint8)0U
#define PortConf_Pin1_CHANNEL_NUM       (uint8)1U
#define PortConf_Pin2_CHANNEL_NUM       (uint8)2U
#define PortConf_Pin3_CHANNEL_NUM       (uint8)3U
#define PortConf_Pin4_CHANNEL_NUM       (uint8)4U
#define PortConf_Pin5_CHANNEL_NUM       (uint8)5U
#define PortConf_Pin6_CHANNEL_NUM       (uint8)6U
#define PortConf_Pin7_CHANNEL_NUM       (uint8)7U


/* Port Configured Channel Modes */

#define PortConf_PortA_Pin0_Mode      (Port_PinModeType)1 /*UART Mode*/
#define PortConf_PortA_Pin1_Mode      (Port_PinModeType)1 /*UART Mode*/
#define PortConf_PortA_Pin2_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortA_Pin3_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortA_Pin4_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortA_Pin5_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortA_Pin6_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortA_Pin7_Mode      (Port_PinModeType)0 /*Digital Mode*/

   
#define PortConf_PortB_Pin0_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortB_Pin1_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortB_Pin2_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortB_Pin3_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortB_Pin4_Mode      (Port_PinModeType)8 /*CAN0 Mode*/
#define PortConf_PortB_Pin5_Mode      (Port_PinModeType)8 /*CAN0 Mode*/
#define PortConf_PortB_Pin6_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortB_Pin7_Mode      (Port_PinModeType)0 /*Digital Mode*/

   
#define PortConf_PortC_Pin0_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortC_Pin1_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortC_Pin2_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortC_Pin3_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortC_Pin4_Mode      (Port_PinModeType)1 /*UART4 Mode*/
#define PortConf_PortC_Pin5_Mode      (Port_PinModeType)1 /*UART4 Mode*/
#define PortConf_PortC_Pin6_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortC_Pin7_Mode      (Port_PinModeType)0 /*Digital Mode*/

   
#define PortConf_PortD_Pin0_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortD_Pin1_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortD_Pin2_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortD_Pin3_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortD_Pin4_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortD_Pin5_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortD_Pin6_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortD_Pin7_Mode      (Port_PinModeType)0 /*Digital Mode*/
  
#define PortConf_PortE_Pin0_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortE_Pin1_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortE_Pin2_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortE_Pin3_Mode      (Port_PinModeType)0 /*Digital Mode*/ 
#define PortConf_PortE_Pin4_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortE_Pin5_Mode      (Port_PinModeType)0 /*Digital Mode*/
   
#define PortConf_PortF_Pin0_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortF_Pin1_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortF_Pin2_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortF_Pin3_Mode      (Port_PinModeType)0 /*Digital Mode*/
#define PortConf_PortF_Pin4_Mode      (Port_PinModeType)0 /*Digital Mode*/




#endif /* DIO_CFG_H */