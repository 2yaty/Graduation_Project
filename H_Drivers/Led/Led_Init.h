/********************************************************************************
 * @file           : CortexM4_Core_NVIC.h										*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains  APIs to control Led.								*
 *******************************************************************************/

#ifndef LED_LED_INIT_H
#define LED_LED_INIT_H


/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/


/** @defgroup GPIO_port_define GPIO ports define
  * @{
  */
#define GPIO_PORT_A                      	GPIOA
#define GPIO_PORT_B	                  	 	GPIOB
#define GPIO_PORT_C       		         	GPIOC
#define GPIO_PORT_D                      	GPIOD
#define GPIO_PORT_E                      	GPIOE
#define GPIO_PORT_H                      	GPIOH

/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/
typedef struct
{
	GPIO_TypeDef *Led_Port;        		/*!< Specifies the GPIO port that connected to the led.
                           	   	   	   	   This parameter can be any value of @ref GPIO_port_define */

	uint16_t LedPin;       				/*!< Specifies the GPIO pins that connected to the led.
                           	   	   	   	   This parameter can be any value of GPIO_PIN_0 to GPIO_PIN_15 */

}Led_Cfg_t;

/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/

/**
 * @Function Name: LED_voidTurnOn
 *
 * @Description: Apply 3.3V (logical 1) on the pin that led connected to turn it on.
 *
 * @Arguments:
 * 			1.Led_Cfg_t *Copy_strLedCfg[in]:
 * 					This a pointer to stuct that contains the led configurations
 * 					( Port and Pin Number).
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus LED_voidTurnOn(const Led_Cfg_t *Copy_strLedCfg);


/**
 * @Function Name: LED_voidTurnOff
 *
 * @Description: Apply 0V (logical 0) on the pin that led connected to turn it off.
 *
 * @Arguments:
 * 			1.Led_Cfg_t *Copy_strLedCfg[in]:
 * 					This a pointer to stuct that contains the led configurations
 * 					( Port and Pin Number).
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus LED_voidTurnOff(const Led_Cfg_t *Copy_strLedCfg);


/**
 * @Function Name: LED_voidToggle
 *
 * @Description: toggle the led connected.
 *
 * @Arguments:
 * 			1.Led_Cfg_t *Copy_strLedCfg[in]:
 * 					This a pointer to stuct that contains the led configurations
 * 					( Port and Pin Number).
 *
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus LED_voidToggle(const Led_Cfg_t *Copy_strLedCfg);
/*------------------------- Software Interfaces Declarations End ----------------------------*/



#endif /* LED_LED_INIT_H_ */
