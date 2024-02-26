/********************************************************************************
 * @file           : MPU.h														*
 * @author         : Salem&Omar 												*
 * @brief          : Contains  APIs to control MPU sensor.          			*
 *******************************************************************************/


#ifndef MPU6050_MPU_H_
#define MPU6050_MPU_H_

/*------------------------------------ Includes Start --------------------------------------*/
#include "Common/STD_Types.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_dma.h"
#include "stdlib.h"
/*------------------------------------ Includes End ----------------------------------------*/

/*------------------------------- Macro Declarations Start ---------------------------------*/
/** @defgroup MPU_Gyro_Sample_Rate_define Gyro sample rate.
  * @{
  */
#define MPU_GYRO_RATE_1K						((uint8_t)0x07)
#define MPU_GYRO_RATE_2K						((uint8_t)0x03)
#define MPU_GYRO_RATE_4K						((uint8_t)0x01)
#define MPU_GYRO_RATE_8K						((uint8_t)0x00)

/** @defgroup MPU_Gyro_Scale_define Gyro full scale.
  * @{
  */
#define MPU_GYRO_SCALE_250						((uint8_t)0b00000000)
#define MPU_GYRO_SCALE_500						((uint8_t)0b00001000)
#define MPU_GYRO_SCALE_1000						((uint8_t)0b00010000)
#define MPU_GYRO_SCALE_2000						((uint8_t)0b00011000)

/** @defgroup MPU_Accel_Scale_define Accel full scale.
  * @{
  */
#define MPU_ACCEL_SCALE_2g						((uint8_t)0b00000000)
#define MPU_ACCEL_SCALE_4g						((uint8_t)0b00001000)
#define MPU_ACCEL_SCALE_8g						((uint8_t)0b00010000)
#define MPU_ACCEL_SCALE_16g						((uint8_t)0b00011000)

/** @defgroup MPU_Address_define Address of MPU chip.
  * @{
  */
#define MPU_AD0_0								((uint8_t)0b1101000)
#define MPU_AD0_1								((uint8_t)0b1101001)

/** @defgroup GPIO_pins_define GPIO pins define
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */
/*-------------------------- Macro• Functions Declarations Start ---------------------------*/

/*-------------------------- Macro• Functions Declarations End -----------------------------*/

/*------------------------------ Data type Declarations Start ------------------------------*/

/**
  * @brief  MPU Reading Request Enumerated Type
  *
  * This enumerated type defines the possible states of a request for MPU6050 data reading.
  */
typedef enum
{
  NON_REQUEST,        /*!< No data reading request is active */
  FIRST_REQUEST,      /*!< Initial request for MPU6050 data reading */
  NEW_DATA_READY      /*!< New data is ready and available from the MPU6050 */
} MPU_Reading_Request;



/**
  * @brief  MPU State Enumerated Type
  *
  * This enumerated type defines the possible states of the MPU6050 module.
  */
typedef enum
{
  MPU_STATE_RESET,    		/*!< The MPU6050 module is in the reset state */
  MPU_STATE_READY = 0x0A,   /*!< The MPU6050 module is initialized and ready for use */
  MPU_STATE_STOP      		/*!< The MPU6050 module is stopped or inactive */
} MPU_STATE;



/**
  * @brief  MPU Mode Enumerated Type
  *
  * This enumerated type defines the possible modes of operation for the MPU6050 module.
  */
typedef enum
{
  FREE_RUNNING,   /*!< MPU operates in free-running mode */
  SINGLE_READ,    /*!< MPU operates in single-read mode */
  POLLING         /*!< MPU operates in polling mode */
} MPU_MODE;



/**
  * @defgroup MPU_handle_Structure_definition MPU handle Structure definition
  * @brief  MPU handle Structure definition
  * @{
  */

/**
  * @brief  MPU Handle Structure
  *
  * This structure holds the configuration and state information for the MPU6050 module.
  */
typedef struct
{
    I2C_HandleTypeDef *hi2c;               /*!< Pointer to the I2C handle structure. */

    uint8_t GyroSampleRate;                /*!< Specifies the Gyro sample rate that specifies the divider from the gyroscope output rate.
                                                This parameter can be any value of @ref MPU_Gyro_Sample_Rate_define.
                                                Note: The accelerometer output rate is constant --> 1kHz */

    uint8_t GyroFullScale;                 /*!< Specifies the Gyro full scale that configures the gyroscopes’ full scale range.
                                                This parameter can be any value of @ref MPU_Gyro_Scale_define */

    uint8_t AccelFullScale;                /*!< Specifies the Accel full scale that configures the Accelerometer’ full scale range.
                                                This parameter can be any value of @ref MPU_Accel_Scale_define */

    uint8_t MPU_Address;                   /*!< MPU Target device address: The device 7 bits address value in datasheet.
                                                This parameter can be any value of @ref MPU_Address_define */

    MPU_Reading_Request DataRequestState;  /*!< State of MPU reading request */

    MPU_STATE state;                       /*!< Current state of the MPU6050 module */

    MPU_MODE mode;                         /*!< Mode of operation for the MPU6050 module */

    float32_t *DataBuffer;                 /*!< Pointer to data buffer for storing MPU6050 readings */

    uint8_t *RegistersBuffer;              /*!< Pointer to register buffer for MPU6050 register readings */

    uint16_t GPIO_INT_PinNum;              /*!< GPIO pin number for interrupt handling */

} MPU_HandleTypeDef;




/**
  * @brief  MPU Error Status Enumerated Type
  *
  * This enumerated type defines the possible error statuses that can occur during MPU operations.
  */
typedef enum
{
    MPU_OK,                 /*!< Operation completed successfully */
    MPU_NOT_OK,             /*!< Operation failed due to an unspecified reason */
    TRANSMIT_NOT_CMPT,      /*!< Error occurred during data transmission to MPU */
    RECEIVE_NOT_CMPT,       /*!< Error occurred during data reception from MPU */
    NULL_PTR                /*!< Null pointer encountered during operation */
} MPU_Error_Status;



/*------------------------------ Data type Declarations End --------------------------------*/


/*------------------------- Software Interfaces Declarations Start --------------------------*/


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
MPU_Error_Status MPU_enuInit(MPU_HandleTypeDef *hMPU);



/**
 * @Function Name: MPU_enuDeInit
 *
 * @Description: Deinitializes the MPU (Motion Processing Unit) module.
 *
 * @Arguments:
 *          1. MPU_HandleTypeDef *hMPU [in]:
 *              Pointer to the MPU handle structure containing MPU configuration and state.
 *
 * @Return:
 *          MPU_Error_Status: Returns an MPU error status indicating whether the deinitialization
 *                            executed correctly or encountered an error.
 **/
MPU_Error_Status MPU_enuDeInit(MPU_HandleTypeDef *hMPU);






/****************************************************************************************
 * ********************* Normal mode (Single read) (non-blocking) ***********************
 * **************************************************************************************

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
MPU_Error_Status MPU_enuGetGyroAccelReadings_DMA(MPU_HandleTypeDef *hMPU, float32_t *Copy_pArrAccelGyroData);





/****************************************************************************************
 * ********************* Free running mode ( non blocking ) *****************************
 * **************************************************************************************

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
MPU_Error_Status MPU_enuStartFreeRunning_DMA(MPU_HandleTypeDef *hMPU, float32_t *Copy_pArrAccelGyroData);


/**
 * @Function Name: MPU_DataReadyInterruptHandler
 *
 * @Description: In the free running mode, this function must be called in the EXTI callback
 *               ("HAL_GPIO_EXTI_Callback").
 *
 * @Arguments:
 *          1. MPU_HandleTypeDef *hMPU [in]:
 *              Pointer to the MPU handle structure containing MPU configuration and state.
 *
 * @Return:
 *          MPU_Reading_Request: Returns an MPU reading request status.
 **/
MPU_Reading_Request MPU_DataReadyInterruptHandler(MPU_HandleTypeDef *hMPU);


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
MPU_Error_Status MPU_enuStopFreeRunning(MPU_HandleTypeDef *hMPU);




/**
 * @brief Callback function for MPU accelerometer and gyroscope data reception.
 *
 * This callback function is intended to be used with "MPU_enuStartFreeRunning_DMA"
 * and "MPU_enuGetAccelGyroReadings_DMA" functions.
 */
void MPU_AccelGyroRxCpltCallback(void);






/*------------------------- Software Interfaces Declarations End ----------------------------*/



/*
 * Private.....***************************************************************************************************
 * Private.........***********************************************************************************************
 * Private................****************************************************************************************
 */

/** @defgroup MPU_Private_Macros MPU.
  * @{
  */

/**
  * Private macros to switch the order of two consecutively bytes, then combines them.
  */
#define MPU_COMBINE(u16Var, u8VarLow, u8VarHigh)	(u16Var = (((uint16_t)u8VarHigh << (uint8_t) 0x08) | u8VarLow))



/**
  * Private macros to apply specific calculations on the Gyro received data (digital) to get the analog value.
  */
#define MPU_GYRO_CALCULATIONS(Result, Full_Scale, Gyro_Read)\
			 (Result =  (Full_Scale == MPU_GYRO_SCALE_250 ) ? ((float32_t) Gyro_Read/131.0f) :\
						(Full_Scale == MPU_GYRO_SCALE_500 ) ? ((float32_t) Gyro_Read/65.5f ) :\
						(Full_Scale == MPU_GYRO_SCALE_1000) ? ((float32_t) Gyro_Read/32.8f ) :\
						(Full_Scale == MPU_GYRO_SCALE_2000) ? ((float32_t) Gyro_Read/16.4f ) :\
						(1))


/**
  * Private macros to apply specific calculations on the Accel received data (digital) to get the analog value.
  */
#define MPU_ACCEL_CALCULATIONS(Result, Full_Scale, Accel_Read)\
			 (Result =  (Full_Scale == MPU_ACCEL_SCALE_2g ) ? ((float32_t) Accel_Read/16384.0f) :\
						(Full_Scale == MPU_ACCEL_SCALE_4g ) ? ((float32_t) Accel_Read/8192.0f ) :\
						(Full_Scale == MPU_ACCEL_SCALE_8g ) ? ((float32_t) Accel_Read/4096.0f ) :\
						(Full_Scale == MPU_ACCEL_SCALE_16g) ? ((float32_t) Accel_Read/2048.0f ) :\
						(1))

/*---------------------------------------------------------------------------------------------------------------*/


#endif /* MPU6050_MPU_H_ */
