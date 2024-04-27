/*
 * log.h
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */

#ifndef LOG_MODULE_LOG_H_
#define LOG_MODULE_LOG_H_
#include <Common/STD_Types.h>

typedef  void (* Logs_ptrFunction)(sint8_t* str)	 ;

#define LOG_BUFF_SIZE		256
#define LOG_FORMAT_JSON		1
#define LOG_ENV_DEBUG		1


/**
 * @Function Name: logs_init
 *
 * @Description: This function initializes the Logs module depending on logging mechanism you are using
 * 				you can use e.g UART or send it to screen.
 *
 * @Arguments:
 * 			Logs_ptrFunction: function pointer for a function that takes a string pointer and send the string the way you like.
 *
 * @Return:
 * 			void: return nothing.
 **/
void logs_init(Logs_ptrFunction send_func);


/**
 * @Function Name: log
 *
 * @Description: the function that used for logging.
 *
 * @Arguments:
 * 			from: a string just for source identification.
 * 			format: the data formated string.
 * 			...: the rest of data formated parameters.
 *
 * @Return:
 * 			void: return nothing.
 *
 *@Example: log("log module example","Hello, world! %d %f", 42, 3.14);
 *	Result sent in Normal format: " from: log module example , data: Hello, world! 42 3.140000"
 *	Result sent in JSON format: "{
 *									"from": "log module example",
 *									"data": "Hello, world! 42 3.140000"
 *								  }"
 *	(JSON format is easy to handle in Python )
 **/
void log(const sint8_t *from, const sint8_t *format, ...);


/**
 * @Function Name: log_debg
 *
 * @Description: the function that used for logging and debugging BUT in case LOG_ENV_DEBUG = 0 won't send anything
 * 				to save time in removing debugging calls.
 *
 * @Arguments:
 * 			from: a string just for source identification.
 * 			format: the data formated string.
 * 			...: the rest of data formated parameters.
 *
 * @Return:
 * 			void: return nothing.
 *
 *@Example: log("log module example","Hello, world! %d %f", 42, 3.14);
 *	Result sent in Normal format: " from: log module example , data: Hello, world! 42 3.140000"
 *	Result sent in JSON format: "{
 *									"from": "log module example",
 *									"data": "Hello, world! 42 3.140000"
 *								  }"
 *	(JSON format is easy to handle in Python )
 **/
void log_debg(const sint8_t *from, const sint8_t *format, ...);

#endif /* LOG_MODULE_LOG_H_ */
