/********************************************************************************
 * @file           : Standard types												*
 * @author         : Salem Elfaidy												*
 * @brief          : Standard types 											*
 *******************************************************************************/

 #ifndef   STD_TYPES_H
 #define   STD_TYPES_H
 
 
typedef  unsigned char      uint8_t    ;
typedef  unsigned short int uint16_t   ;
typedef  unsigned long  int uint32_t   ;
typedef  signed char        sint8_t    ;
typedef  signed short  int  sint16_t   ;
typedef  signed long   int  sint32_t   ;
typedef  float              float32_t  ;
typedef  double             float64_t  ;
typedef  long double        float128_t ;


typedef enum {
	E_OK,
	E_NOK,
	E_NOK_PARAM_OUT_OF_RANGE ,
	E_NOK_PARAM_NULL_POINTER  ,
	E_NOK_CONFIG_ERROR,
	E_PROCESS_COMPLETE
}tenuErrorStatus;

#define  NULL	    ((void *)0)

typedef  void (* ptrFunction)(void)	 ;

#endif



