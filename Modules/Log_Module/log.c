/*
 * log.c
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */
#include <stdarg.h>
#include <stdio.h>
#include "log.h"

ptrFunction logs_send;

void logs_init(Logs_ptrFunction send_func){


	logs_send = send_func;
}



void log(const int8_t *from, const int8_t *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[LOG_BUFF_SIZE]; // Adjust size as needed
    vsnprintf(buffer, buffer, format, args);
    va_end(args);
    // Enclose the message and 'from' field in JSON-like format
    // char json_buffer[256]; // Adjust size as needed
	#if LOG_FORMAT_JSON
    snprintf(buffer, LOG_BUFF_SIZE, "{\"from\": \"%s\", \"data\": \"%s\"}\n", from, buffer);
	#else
    snprintf(buffer, LOG_BUFF_SIZE, "from: %s, data: %s\n", from, buffer);
	#endif
    // Now send json_buffer over UART
    logs_send(buffer);
}


void log_debg(const int8_t *from, const int8_t *format, ...){

#if LOG_ENV_DEBUG
    va_list args;
    va_start(args, format);
    char buffer[LOG_BUFF_SIZE]; // Adjust size as needed
    vsnprintf(buffer, buffer, format, args);
    va_end(args);
    // Enclose the message and 'from' field in JSON-like format
    // char json_buffer[256]; // Adjust size as needed
	#if LOG_FORMAT_JSON
    snprintf(buffer, LOG_BUFF_SIZE, "{\"from\": \"%s\", \"data\": \"%s\"}\n", from, buffer);
	#else
    snprintf(buffer, LOG_BUFF_SIZE, "from: %s, data: %s\n", from, buffer);
	#endif
    // Now send json_buffer over UART
    logs_send(buffer);
#endif

}
