/********************************************************************************
 * @file           : MPU.c														*
 * @author         : Salem&Omar  15/12/2023	 												*
 * @brief          : Contains the static code to control the MPU sensor.		*
 *******************************************************************************/

#include "MPU_Lcfg.h"
#include <stdlib.h>


extern void MPU_SetCfg(void);


/* Private define ------------------------------------------------------------*/
/** @defgroup MPU_Register_Addresses_Private_Define MPU Private Define
  * @{
  */
#define SMPLRT_DIV_REG_ADDR						((uint8_t)0X19)
#define CONFIG_REG_ADDR							((uint8_t)0X1A)
#define GYRO_CONFIG_REG_ADDR					((uint8_t)0X1B)
#define ACCEL_CONFIG_REG_ADDR					((uint8_t)0X1C)
#define INT_PIN_CFG_REG_ADDR					((uint8_t)0X37)
#define INT_ENABLE_REG_ADDR						((uint8_t)0X38)
#define INT_STATUS_REG_ADDR						((uint8_t)0X3A)
#define ACCEL_XOUT_H_REG_ADDR					((uint8_t)0X3B)
#define GYRO_XOUT_H_REG_ADDR					((uint8_t)0X43)
#define WHO_AM_I								((uint8_t)0X75)
#define PWR_MGMT_1								((uint8_t)0X6B)


#define DLPF_CFG_REG_BITS						((uint8_t)0X00)

#define TIMEOUT_100_MS							((uint32_t)100)

#define INT_PIN_CFG								((uint8_t)0b00000000)
#define INT_DATA_READY_ENABLE					((uint8_t)0b00000001)
#define INT_DATA_READY_DISABLE					((uint8_t)0b00000000)

#define READ_6_BYTE								((uint8_t)0X06)
#define READ_14_BYTE							((uint8_t)0X0E)



/** @defgroup MPU_Private_Functions MPU Private Functions
  * @{
  */
static MPU_Error_Status MPU_enuGetAccelGyro(MPU_HandleTypeDef *hMPU);

static void Gyro_Calculations (MPU_HandleTypeDef *hMPU);
static void Accel_Calculations(MPU_HandleTypeDef *hMPU);




/**
 * @Function Name: MPU_enuInit
 *
 * @Description: Initializes the MPU (Motion Processing Unit) module.
 *
 * @Arguments:
 *          1. MPU_HandleTypeDef *hMPU [in]:
 *              Pointer to the MPU handle structure containing MPU configuration and state.
 *
 * @Return:
 *          MPU_Error_Status: Returns an MPU error status indicating whether the initialization
 *                            executed correctly or encountered an error.
 **/
MPU_Error_Status MPU_enuInit(MPU_HandleTypeDef *hMPU)
{
	uint8_t Local_u8Check;
	hMPU->state = MPU_STATE_RESET;
	hMPU->dataState = MPU_DATA_STATE_NOT_REQUESTED;
	//hMPU->RegistersBuffer = (uint8_t*)malloc(14 * sizeof(uint8_t));

	/* Set the handler with the MPU Init configurations. */
	MPU_SetCfg();

	/* Fill the temp array with the MPU necessary configurations. */
	uint8_t Local_u8Temp[4] = {hMPU->GyroSampleRate, DLPF_CFG_REG_BITS, hMPU->GyroFullScale, hMPU->AccelFullScale};

	if(hMPU->hi2c != NULL)
	{
		/* Verify the identity of the device */
		if(HAL_I2C_Mem_Read(hMPU->hi2c, (hMPU->MPU_Address << 1), WHO_AM_I, 1, &Local_u8Check, sizeof(Local_u8Check), TIMEOUT_100_MS) != HAL_OK)
		{
			return TRANSMIT_NOT_CMPT;
		}
		if(Local_u8Check != 0x68)
		{
			return MPU_NOT_OK;
		}

		/* Set the MPU Init configurations */
		if(HAL_I2C_Mem_Write(hMPU->hi2c, (hMPU->MPU_Address << 1), SMPLRT_DIV_REG_ADDR, 1, Local_u8Temp, sizeof(Local_u8Temp), TIMEOUT_100_MS) != HAL_OK)
		{
			return TRANSMIT_NOT_CMPT;
		}

		/* Disables the temperature sensor */
		Local_u8Temp[0] = 0b00001000;
		if(HAL_I2C_Mem_Write(hMPU->hi2c, (hMPU->MPU_Address << 1), PWR_MGMT_1, 1, Local_u8Temp, 1, TIMEOUT_100_MS) != HAL_OK)
		{
			return TRANSMIT_NOT_CMPT;
		}

		/* MPU Initialized and ready for use */
		hMPU->state = MPU_STATE_READY;
	}
	else
	{
		return NULL_PTR;
	}

	return MPU_OK;
}



/**
* @Function Name: MPU_enuStartFreeRunning_DMA
*
* @Description: Sets up the MPU and starts the process in free running mode.
*               When data is received and ready to use, a callback function will be
*               called automatically.
*               Note: You don't need to use "MPU_enuInit". This function is called
*               only one time in your application.
*
* @Arguments:
*          1. MPU_HandleTypeDef *hMPU [in]:
*              Pointer to the MPU handle structure containing MPU configuration and state.
*          2. float32_t *Copy_pArrAccelGyroData [in]:
*              Pointer to the array where the accelerometer and gyro readings will be stored.
*
* @Return:
*          MPU_Error_Status: Returns an MPU error status indicating whether the operation
*                            executed correctly or encountered an error.
**/
MPU_Error_Status MPU_enuStartFreeRunning_DMA(MPU_HandleTypeDef *hMPU)
{
	uint8_t Local_u8Check;
	hMPU->DataRequestState = FIRST_REQUEST;
	hMPU->state = MPU_STATE_RESET;
	hMPU->dataState = MPU_DATA_STATE_NOT_REQUESTED;
	hMPU->mode = FREE_RUNNING;
	//hMPU->RegistersBuffer = (uint8_t*)malloc(14 * sizeof(uint8_t));

	/* Set the handler with the MPU Init configurations. */
	MPU_SetCfg();

	/* Fill the temp array with the MPU necessary configurations. */
	uint8_t Local_u8Temp[4] = {hMPU->GyroSampleRate, DLPF_CFG_REG_BITS, hMPU->GyroFullScale, hMPU->AccelFullScale};

	if(hMPU->hi2c != NULL)
	{
		/* Verify the identity of the device */
		if(HAL_I2C_Mem_Read(hMPU->hi2c, (hMPU->MPU_Address << 1), WHO_AM_I, 1, &Local_u8Check, sizeof(Local_u8Check), TIMEOUT_100_MS) != HAL_OK)
		{
			return TRANSMIT_NOT_CMPT;
		}
		if(Local_u8Check != 0x68)
		{
			return MPU_NOT_OK;
		}

		/* Set the MPU Init configurations */
		if(HAL_I2C_Mem_Write(hMPU->hi2c, (hMPU->MPU_Address << 1), SMPLRT_DIV_REG_ADDR, 1, Local_u8Temp, sizeof(Local_u8Temp), TIMEOUT_100_MS) != HAL_OK)
		{
			return TRANSMIT_NOT_CMPT;
		}

		/* Disable interrupt from EXTI (mask it). */
		EXTI->IMR &= ~(hMPU->GPIO_INT_PinNum);

		/* Fill the temp array with the MPU interrupt configurations. */
		Local_u8Temp[0] = INT_PIN_CFG;
		Local_u8Temp[1] = INT_DATA_READY_ENABLE;

		/* Set the MPU interrupt configurations */
		if(HAL_I2C_Mem_Write(hMPU->hi2c, (hMPU->MPU_Address << 1), INT_PIN_CFG_REG_ADDR, 1, Local_u8Temp, 2, TIMEOUT_100_MS) != HAL_OK)
		{
			return TRANSMIT_NOT_CMPT;
		}

		/* Disables the temperature sensor */
		Local_u8Temp[0] = 0b00001000;
		if(HAL_I2C_Mem_Write(hMPU->hi2c, (hMPU->MPU_Address << 1), PWR_MGMT_1, 1, Local_u8Temp, 1, TIMEOUT_100_MS) != HAL_OK)
		{
			return TRANSMIT_NOT_CMPT;
		}

		/* MPU Initialized and ready for use */
		hMPU->state = MPU_STATE_READY;

		/* Start the communication and data reading */
		if(MPU_enuGetAccelGyro(hMPU) != MPU_OK)
		{
			return MPU_NOT_OK;
		}

	}
	else
	{
		return NULL_PTR;
	}

	return MPU_OK;
}



/**
 * @Function Name: MPU_enuGetGyroAccelReadings_DMA
 *
 * @Description: Initiates communication to obtain gyro and accelerometer readings
 *               in DMA (Direct Memory Access) mode. Upon reception and availability
 *               of data, a callback function will be automatically invoked for further processing.
 *
 * @Arguments:
 *          1. MPU_HandleTypeDef *hMPU [in]:
 *              Pointer to the MPU handle structure containing MPU configuration and state.
 *          2. float32_t *Copy_pArrAccelGyroData [in]:
 *              Pointer to the array where the accelerometer and gyro readings will be stored.
 *
 * @Return:
 *          MPU_Error_Status: Returns an MPU error status indicating whether the operation
 *                            executed correctly or encountered an error.
 **/
MPU_Error_Status MPU_enuGetGyroAccelReadings_DMA(MPU_HandleTypeDef *hMPU)
{

	hMPU->mode = SINGLE_READ;
	/* Disable interrupt from EXTI (mask it). */
	EXTI->IMR &= ~(hMPU->GPIO_INT_PinNum);

	if(hMPU->hi2c != NULL)
	{
		/* Start the communication and data reading */
		if(MPU_enuGetAccelGyro(hMPU) != MPU_OK)
		{
			return MPU_NOT_OK;
		}
	}
	else
	{
		return NULL_PTR;
	}

	return MPU_OK;

}



/**
 * @Function Name: MPU_enuStopFreeRunning
 *
 * @Description: Stops the free running mode for the MPU.
 *
 * @Arguments:
 *          1. MPU_HandleTypeDef *hMPU [in]:
 *              Pointer to the MPU handle structure containing MPU configuration and state.
 *
 * @Return:
 *          MPU_Error_Status: Returns an MPU error status indicating whether the operation
 *                            executed correctly or encountered an error.
 **/
MPU_Error_Status MPU_enuStopFreeRunning(MPU_HandleTypeDef *hMPU)
{
	hMPU->state = MPU_STATE_STOP;
	uint8_t Local_u8Temp[2];
	/* Disable the MPU data ready Flag */
	Local_u8Temp[0] = INT_PIN_CFG;
	Local_u8Temp[1] = INT_DATA_READY_DISABLE;

	/* Transmit the temp array */
	if(HAL_I2C_Mem_Write(hMPU->hi2c, (hMPU->MPU_Address << 1), INT_PIN_CFG_REG_ADDR, 1, Local_u8Temp, 2, TIMEOUT_100_MS) != HAL_OK)
	{
		return TRANSMIT_NOT_CMPT;
	}

	// Disable interrupt from EXTI (mask it)
	EXTI->IMR &= ~(hMPU->GPIO_INT_PinNum);

	/* free the memory*/
	//free(hMPU->RegistersBuffer);
	return MPU_OK;

}



/**
 * @Function Name: MPU_enuGetAccelGyro
 *
 * @Description: Retrieves accelerometer and gyroscope data from the MPU (Motion Processing Unit).
 *               This function is used to retrieve accelerometer and gyroscope data from the MPU6050 module (helper function).
 *
 * @Arguments:
 *          1. MPU_HandleTypeDef *hMPU [in]:
 *              Pointer to the MPU handle structure containing MPU configuration and state.
 *
 * @Return:
 *          MPU_Error_Status: Returns an MPU error status indicating whether the operation
 *                            executed correctly or encountered an error.
 **/
static MPU_Error_Status MPU_enuGetAccelGyro(MPU_HandleTypeDef *hMPU)
{
	if((hMPU->hi2c != NULL))
	{
		if(hMPU->state == MPU_STATE_READY)
		{
			/* Receive the Gyro data in the temp array */
			if(HAL_I2C_Mem_Read_DMA(hMPU->hi2c, (hMPU->MPU_Address << 1), ACCEL_XOUT_H_REG_ADDR, 1, hMPU->RegistersBuffer, READ_14_BYTE) != HAL_OK)
			{
				return TRANSMIT_NOT_CMPT;
			}

			/* Change the data state to requested*/
			hMPU->dataState = MPU_DATA_STATE_REQUESTED;
		}

	}
	else
	{
		return NULL_PTR;
	}

	return MPU_OK;

}



/**
 * @brief Callback function invoked when I2C memory reception is complete.
 *
 * This function performs the necessary calculations for the accelerometer and gyroscope data,
 * invokes the data ready callback function, and updates the data request state.
 * Additionally, it enables or disables interrupts from EXTI based on the MPU state and mode.
 *
 * @param hi2c Pointer to the I2C handle structure.
 */
void MPU_RxCpltProcess(MPU_HandleTypeDef *hMPU)
{

	/* Update the data request state */
	hMPU->DataRequestState = NEW_DATA_READY;

	if(hMPU->mode == FREE_RUNNING )
	{
		// Enable interrupt from EXTI (mask it)
		EXTI->IMR |= (hMPU->GPIO_INT_PinNum);
	}
	if(hMPU->state == MPU_STATE_STOP)
	{
		// Disable interrupt from EXTI (mask it)
		EXTI->IMR &= ~(hMPU->GPIO_INT_PinNum);
	}

	/* Change the data state to received*/
	hMPU->dataState = MPU_DATA_STATE_RECEIVED;

	/* A callback function indicates that the frame received */
	MPU_RxFrameCallback();

}




void MPU_GetReadings(MPU_HandleTypeDef *hMPU)
{
	/* Apply the Gyro and the Accel calculations to get the analog value */
	Accel_Calculations(hMPU);
	Gyro_Calculations(hMPU);

	/* Change the data state to ready*/
	hMPU->dataState = MPU_DATA_STATE_READY;

	/* Change the data state to data not requested to start request the data again. */
	//hMPU->dataState = MPU_DATA_STATE_NOT_REQUESTED;
}



/**
 * @brief Weakly defined callback function invoked when accelerometer and gyroscope data reception is complete.
 *
 * This function is intended to be overridden by the user to handle the completion of accelerometer and gyroscope data reception.
 * If not overridden, this function does nothing.
 */
__weak void MPU_RxFrameCallback(void)
{

}



/**
 * @brief Perform calculations for gyroscope data.
 *
 * This function performs calculations for gyroscope data received from the MPU.
 * It combines the data from the registers and calculates the gyroscope readings
 * based on the specified full-scale range.
 */
static void Gyro_Calculations (MPU_HandleTypeDef *hMPU)
{
	sint16_t Local_u16Temp =0;

	MPU_COMBINE(Local_u16Temp, hMPU->RegistersBuffer[9], hMPU->RegistersBuffer[8]);
	MPU_GYRO_CALCULATIONS(*(hMPU->DataBuffer    ), hMPU->GyroFullScale , Local_u16Temp);

	MPU_COMBINE(Local_u16Temp, hMPU->RegistersBuffer[11], hMPU->RegistersBuffer[10]);
	MPU_GYRO_CALCULATIONS(*(hMPU->DataBuffer + 1), hMPU->GyroFullScale , Local_u16Temp);

	MPU_COMBINE(Local_u16Temp, hMPU->RegistersBuffer[13], hMPU->RegistersBuffer[12]);
	MPU_GYRO_CALCULATIONS(*(hMPU->DataBuffer + 2), hMPU->GyroFullScale , Local_u16Temp);

}




/**
 * @brief Perform calculations for gyroscope data.
 *
 * This function combines the raw gyro data from the MPU registers and calculates the gyroscope readings.
 * The calculations are performed for each axis (X, Y, Z) and stored in the MPU handle's data buffer.
 */
static void Accel_Calculations(MPU_HandleTypeDef *hMPU)
{
	sint16_t Local_u16Temp =0;

	MPU_COMBINE(Local_u16Temp, hMPU->RegistersBuffer[1], hMPU->RegistersBuffer[0]);
	MPU_ACCEL_CALCULATIONS(*(hMPU->DataBuffer + 3), hMPU->AccelFullScale , Local_u16Temp);

	MPU_COMBINE(Local_u16Temp, hMPU->RegistersBuffer[3], hMPU->RegistersBuffer[2]);
	MPU_ACCEL_CALCULATIONS(*(hMPU->DataBuffer + 4), hMPU->AccelFullScale , Local_u16Temp);

	MPU_COMBINE(Local_u16Temp, hMPU->RegistersBuffer[5], hMPU->RegistersBuffer[4]);
	MPU_ACCEL_CALCULATIONS(*(hMPU->DataBuffer + 5), hMPU->AccelFullScale , Local_u16Temp);

}

//TODO : Create a calculation function for the temperature sensor... and save its value in the handler struct.




/**
 * @brief Handles the data ready interrupt from MPU (Motion Processing Unit).
 *
 * This function is responsible for handling the data ready interrupt from the MPU (in free running mode). It checks
 * if new data is ready and initiates the process to obtain accelerometer and gyroscope readings.
 * If the MPU is busy or not in the ready state, the interrupt from EXTI is disabled(to avoid overloading of interrupts). Once the data
 * is successfully retrieved, the data request state is updated, and the interrupt from EXTI is disabled.
 *
 * @param hMPU Pointer to the MPU handle structure containing MPU configuration and state.
 *
 * @return MPU_Reading_Request Returns the MPU reading request status.
 */
MPU_Reading_Request MPU_DataReadyInterruptHandler(MPU_HandleTypeDef *hMPU)
{
	if((hMPU->DataRequestState == FIRST_REQUEST)||(hMPU->DataRequestState == NEW_DATA_READY))
	{
		if((hMPU->hi2c->State == HAL_I2C_STATE_BUSY) || (hMPU->state != MPU_STATE_READY))
		{
			// Disable interrupt from EXTI (mask it)
			EXTI->IMR &= ~(hMPU->GPIO_INT_PinNum);
		}
		else if(hMPU->state == MPU_STATE_READY)
		{
			//i++; // TODO : Delete this line ( for debugging ).
			// Disable interrupt from EXTI (mask it)
			EXTI->IMR &= ~(hMPU->GPIO_INT_PinNum);
			MPU_enuGetAccelGyro(hMPU);
			hMPU->DataRequestState = NON_REQUEST;
//			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // TODO : Delete this line ( for debugging ).
			return NEW_DATA_READY;
		}

	}
	return NON_REQUEST;
}




