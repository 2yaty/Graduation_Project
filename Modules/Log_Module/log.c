/*
 * log.c
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */
#include <stdarg.h>
#include <stdio.h>
#include "log.h"

Logs_ptrFunction logs_send;

void logs_init(Logs_ptrFunction send_func){


	logs_send = send_func;
}



void logs(const int8_t *from, const int8_t *format, ...) {
    va_list args;
    va_start(args, format);
    int8_t buffer[LOG_BUFF_SIZE]; // Adjust size as needed
    vsnprintf(buffer, LOG_BUFF_SIZE, format, args);
    va_end(args);
    // Enclose the message and 'from' field in JSON-like format
     char json_buffer[LOG_BUFF_SIZE]; // Adjust size as needed
	#if LOG_FORMAT_JSON
    snprintf(json_buffer, LOG_BUFF_SIZE, "{\"from\": \"%s\", \"data\": \"%s\"}\n", from, buffer);
	#else
    snprintf(json_buffer, LOG_BUFF_SIZE, "from: %s, data: %s\n", from, buffer);
	#endif
    // Now send json_buffer over UART
    logs_send(json_buffer);
}


void logs_debg(const int8_t *from, const int8_t *format, ...){

#if LOG_ENV_DEBUG
    va_list args;
    va_start(args, format);
    int8_t buffer[LOG_BUFF_SIZE]; // Adjust size as needed
    vsnprintf(buffer, LOG_BUFF_SIZE, format, args);
    va_end(args);
    // Enclose the message and 'from' field in JSON-like format
     char json_buffer[LOG_BUFF_SIZE]; // Adjust size as needed
	#if LOG_FORMAT_JSON
    snprintf(json_buffer, LOG_BUFF_SIZE, "{\"from\": \"%s\", \"data\": \"%s\"}\n", from, buffer);
	#else
    snprintf(json_buffer, LOG_BUFF_SIZE, "from: %s, data: %s\n", from, buffer);
	#endif
    // Now send json_buffer over UART
    logs_send(json_buffer);
#endif

}
