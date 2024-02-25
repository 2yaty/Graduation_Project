/********************************************************************************
 * @file           : MOTOR_MDD10A.c												*
 * @author         : Salem Elfaidy  -- 2023/10/15												*
 * @brief          : Contains the static code to control the motor Driver.		*
 *******************************************************************************/

#include "MOTOR_MDD10A_Lcfg.h"


extern void MOTOR_cfg_Init (void);
static void Select_CCRx( MOTOR_HandleTypeDef *MOTOR_cfg, uint16_t Copy_u16CCRxValue);


/**
 * @Function Name: MOTOR_voidInitMotor
 *
 * @Description: This function initializes the timer PWM depending on configuration you provided in
 * 				 @ref MOTOR_MDD10A_Lcfg.c file.
 *
 * @Arguments:
 * 			void:
 * 					take nothing.
 *
 * @Return:
 * 			void: return nothing.
 **/
void MOTOR_voidInitMotor(void)
{
	/* Define the timer configurations */
	MOTOR_cfg_Init();
}


/**
 * @Function Name: MOTOR_voidMoveForward
 *
 * @Description: Move motor forward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidMoveForward(uint8_t Copy_u8MotorSpeed, MOTOR_HandleTypeDef *MOTOR_cfg)
{
	tenuErrorStatus RetStatus = E_OK;
	if(HAL_TIM_PMM_DutyCycle(MOTOR_cfg, Copy_u8MotorSpeed) != E_OK){RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	else
	{
		/* Set motor direction forward */
		HAL_GPIO_WritePin(MOTOR_cfg->Motor_Dir_Port, MOTOR_cfg->Motor_Dir_Pin, SET);
		/* Start motor moving */
		HAL_TIM_PWM_Start(MOTOR_cfg->htimX, MOTOR_cfg->Motor_Channel);
	}
	return RetStatus;
}



/**
 * @Function Name: MOTOR_voidMoveBackward
 *
 * @Description: Move motor backward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidMoveBackward(uint8_t Copy_u8MotorSpeed, MOTOR_HandleTypeDef *MOTOR_cfg)
{
	tenuErrorStatus RetStatus = E_OK;
	if(HAL_TIM_PMM_DutyCycle(MOTOR_cfg, Copy_u8MotorSpeed) != E_OK){RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	else
	{
		/* Set motor direction backward */
		HAL_GPIO_WritePin(MOTOR_cfg->Motor_Dir_Port, MOTOR_cfg->Motor_Dir_Pin, RESET);
		/* Start motor moving */
		HAL_TIM_PWM_Start(MOTOR_cfg->htimX, MOTOR_cfg->Motor_Channel);
	}
	return RetStatus;
}



/**
 * @Function Name: MOTOR_voidMoveBackward
 *
 * @Description: Move motor backward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidTurnLeft(uint8_t Copy_u8MotorSpeed, uint8_t Copy_u8TurnAngle, MOTOR_HandleTypeDef *MOTOR_1_cfg, MOTOR_HandleTypeDef *MOTOR_2_cfg)
{
	tenuErrorStatus RetStatus = E_OK;
	uint16_t  Loc_u8SpeeedDiff;

	if ((Copy_u8TurnAngle >= 0) && (Copy_u8TurnAngle <= 90))
	{
		Loc_u8SpeeedDiff = (Copy_u8MotorSpeed * (uint16_t)Copy_u8TurnAngle)/90;
		MOTOR_voidMoveForward(Copy_u8MotorSpeed, MOTOR_1_cfg);
		MOTOR_voidMoveForward(Copy_u8MotorSpeed - Loc_u8SpeeedDiff, MOTOR_2_cfg);
	}
	else if ((Copy_u8TurnAngle > 90) && (Copy_u8TurnAngle <= 180))
	{
		Loc_u8SpeeedDiff = (Copy_u8MotorSpeed * (uint16_t)Copy_u8TurnAngle)/180;
		MOTOR_voidMoveForward(Copy_u8MotorSpeed, MOTOR_1_cfg);
		MOTOR_voidMoveBackward(Loc_u8SpeeedDiff, MOTOR_2_cfg);
	}

	return RetStatus;
}



/**
 * @Function Name: MOTOR_voidMoveBackward
 *
 * @Description: Move motor backward with specific speed.
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8MotorSpeed[in]:
 * 					Specify the motor speed.
 * 				 	You can specify the motor speed in range 0 (as min speed) to 100 (as max speed)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that contains the motor configurations
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus MOTOR_voidTurnRight(uint8_t Copy_u8MotorSpeed, uint8_t Copy_u8TurnAngle, MOTOR_HandleTypeDef *MOTOR_1_cfg, MOTOR_HandleTypeDef *MOTOR_2_cfg)
{
	tenuErrorStatus RetStatus = E_OK;
	uint16_t  Loc_u8SpeeedDiff;

	if ((Copy_u8TurnAngle >= 0) && (Copy_u8TurnAngle <= 90))
	{
		Loc_u8SpeeedDiff = (Copy_u8MotorSpeed * (uint16_t)Copy_u8TurnAngle)/90;
		MOTOR_voidMoveForward(Copy_u8MotorSpeed, MOTOR_2_cfg);
		MOTOR_voidMoveForward(Copy_u8MotorSpeed - Loc_u8SpeeedDiff, MOTOR_1_cfg);
	}
	else if ((Copy_u8TurnAngle > 90) && (Copy_u8TurnAngle <= 180))
	{
		Loc_u8SpeeedDiff = (Copy_u8MotorSpeed * (uint16_t)Copy_u8TurnAngle)/180;
		MOTOR_voidMoveForward(Copy_u8MotorSpeed, MOTOR_2_cfg);
		MOTOR_voidMoveBackward(Loc_u8SpeeedDiff, MOTOR_1_cfg);
	}

	return RetStatus;


}

/**
 * @Function Name: MOTOR_voidStopMoving
 *
 * @Description: Stop the motor.
 *
 * @Arguments:
 * 			1.MOTOR_HandleTypeDef *MOTOR_cfg[in]:
 * 					This is a pointer to stuct that indicates to the motor u wanna stop.
 * 					((Port and Pin Number) to control motor direction -> Dir pin in "MDD10A" board,
 * 					and Timer Channel index -> PWM pin in "MDD10A" board).
 * @Return:
 * 			void: return nothing.
 **/
void MOTOR_voidStopMoving(MOTOR_HandleTypeDef *MOTOR_cfg)
{
	HAL_TIM_PWM_Stop(MOTOR_cfg->htimX, MOTOR_cfg->Motor_Channel);
}



/**
 * @Function Name: HAL_TIM_PMM_DutyCycle
 *
 * @Description: Generate PWM with desired duty cycle for (General Purpose).
 * 				 Note: this function isn't necessary to drive the motor driver "MDD10A".
 *
 * @Arguments:
 * 			1.uint8_t Copy_u8DutyPercentage[in]:
 * 					Specify the PWM duty cycle.
 * 				 	You can specify the PWM duty cycle in range 0 (as min duty cycle) to 100 (as max duty cycle)
 * 				 	Note: in case u Insert number more than 100, the function returns error state.
 * 			2.uint8_t Copy_u8OutChannel[in]:
 * 					Specify the channel u wanna generate PWM from.
 * @Return:
 * 			tenuErrorStatus: Returns an error status that indicates if this function executed correctly or not.
 **/
tenuErrorStatus HAL_TIM_PMM_DutyCycle( MOTOR_HandleTypeDef *MOTOR_cfg, uint8_t Copy_u8DutyPercentage)
{
	tenuErrorStatus RetStatus = E_OK;
	if(Copy_u8DutyPercentage > 100){RetStatus = E_NOK_PARAM_OUT_OF_RANGE;}
	else
	{
		uint16_t Local_u16Temp;
		if(!MOTOR_POLARITY_AND_PWM_MODE_CONDITION(MOTOR_cfg->sConfigOC->OCPolarity, MOTOR_cfg->sConfigOC->OCMode))
		{
			/* Calculate the Compare value according PWM mode 1*/
			Local_u16Temp = (((uint32_t)Copy_u8DutyPercentage * MOTOR_cfg->htimX->Init.Period)/ 100);
			/* Set the Capture Compare Register value */
			Select_CCRx(MOTOR_cfg, Local_u16Temp);
		}
		else
		{
			/* Calculate the Compare value according PWM mode 2*/
			Local_u16Temp = MOTOR_cfg->htimX->Init.Period - (((uint32_t)Copy_u8DutyPercentage * MOTOR_cfg->htimX->Init.Period)/ 100);
			/* Set the Capture Compare Register value */
			Select_CCRx(MOTOR_cfg, Local_u16Temp);
		}

	}
	return RetStatus;
}



/*
 * Private.......***************************************************************************************************************
 * Private............**********************************************************************************************************
 * Private..................****************************************************************************************************
 */

/**
 * @Function Name: Select_CCRx
 *
 * @Description: Assign the desired compare match value to CCRx register according to channel index.
 *
 * @Arguments:
 * 			1.uint16_t Copy_u16CCRxValue[in]:
 * 					The compare match value.
 * 			2.uint8_t Copy_u8OutChannel[in]:
 * 					Specify the channel u wanna generate PWM from.
 * @Return:
 * 			void: return nothing.
 **/
static void Select_CCRx( MOTOR_HandleTypeDef *MOTOR_cfg, uint16_t Copy_u16CCRxValue)
{
	switch (MOTOR_cfg->Motor_Channel)
	{
		case TIM_CHANNEL_1:
			MOTOR_cfg->htimX->Instance->CCR1 = Copy_u16CCRxValue;
			break;
		case TIM_CHANNEL_2:
			MOTOR_cfg->htimX->Instance->CCR2 = Copy_u16CCRxValue;
			break;
		case TIM_CHANNEL_3:
			MOTOR_cfg->htimX->Instance->CCR3 = Copy_u16CCRxValue;
			break;
		case TIM_CHANNEL_4:
			MOTOR_cfg->htimX->Instance->CCR4 = Copy_u16CCRxValue;
			break;
	}

}

/*---------------------------------------------------------------------------------------------------------------------------*/
