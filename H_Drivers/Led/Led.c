/********************************************************************************
 * @file           : CortexM4_Core_NVIC.c										*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains the static code to control Led.					*
 *******************************************************************************/

#include "Led_Init.h"


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
tenuErrorStatus LED_voidTurnOn(const Led_Cfg_t *Copy_strLedCfg)
{
	tenuErrorStatus RetStatus = E_OK;
	if (Copy_strLedCfg != NULL)
	{
		HAL_GPIO_WritePin(Copy_strLedCfg->Led_Port, Copy_strLedCfg->LedPin, GPIO_PIN_SET);
	}
	else { RetStatus = E_NOK;}
	return RetStatus;

}


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
tenuErrorStatus LED_voidTurnOff(const Led_Cfg_t *Copy_strLedCfg)
{
	tenuErrorStatus RetStatus = E_OK;
	if (Copy_strLedCfg != NULL)
	{
		HAL_GPIO_WritePin(Copy_strLedCfg->Led_Port, Copy_strLedCfg->LedPin, GPIO_PIN_RESET);
	}
	else { RetStatus = E_NOK;}
	return RetStatus;
}


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
tenuErrorStatus LED_voidToggle(const Led_Cfg_t *Copy_strLedCfg)
{
	tenuErrorStatus RetStatus = E_OK;
	if (Copy_strLedCfg != NULL)
	{
		HAL_GPIO_TogglePin(Copy_strLedCfg->Led_Port, Copy_strLedCfg->LedPin);
	}
	else { RetStatus = E_NOK;}
	return RetStatus;
}
