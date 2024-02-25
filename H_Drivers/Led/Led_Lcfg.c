/********************************************************************************
 * @file           : CortexM4_Core_NVIC.c										*
 * @author         : Salem Elfaidy												*
 * @brief          : Contains the needed data to initialize the Led.			*
 *******************************************************************************/

#include "Led_Init.h"

const Led_Cfg_t Led1_Cfg =
{
	GPIOC,
	GPIO_PIN_13
};

const Led_Cfg_t Led2_Cfg =
{
	GPIOA,
	GPIO_PIN_7
};

const Led_Cfg_t Led3_Cfg =
{
	GPIOB,
	GPIO_PIN_0
};

const Led_Cfg_t Led4_Cfg =
{
	GPIOB,
	GPIO_PIN_1
};

const Led_Cfg_t Led5_Cfg =
{
	GPIOB,
	GPIO_PIN_2
};
