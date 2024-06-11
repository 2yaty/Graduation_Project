/*
 * Ras_TX_Task.c
 *
 *  Created on: Apr 27, 2024
 *      Author: moham
 */


#include "Ras_TX_task.h"

#define HEADER_BYTE_1 				0xAA
#define HEADER_BYTE_2 				0x55
#define MAX_PACKET_LENGTH 			250


typedef struct{
	char data[MAX_PACKET_LENGTH];
	uint8_t length;

}Ras_TX_Data_st;


osMessageQueueId_t* ras_tx_MsgQueue ;
UART_HandleTypeDef* ras_huart;
osSemaphoreId_t* ras_Semaphore;

uint8_t calculate_checksum(uint8_t *data, uint8_t length) ;



void Ras_TX_task_init(osMessageQueueId_t* ras_Tx_MsgQueue ,osSemaphoreId_t* uart_Semaphore, UART_HandleTypeDef *huart){
	ras_tx_MsgQueue = ras_Tx_MsgQueue;
	ras_huart = huart;
	ras_Semaphore = uart_Semaphore;
	logs_init(Ras_TX_add_to_q);
}



void Ras_TX_Task(void *argument){

	Ras_TX_Data_st packet ;

	for(;;)
	  {

//		static uint32_t count =0;
//		logs_debg("ras","{'times':'%d'}",count++);

	    osSemaphoreAcquire(*ras_Semaphore,osWaitForever);

		if(osOK == osMessageQueueGet(*ras_tx_MsgQueue, &packet, NULL, osWaitForever )){

//			send_data_packet(msg.data);
			 HAL_UART_Transmit_DMA(ras_huart, packet.data, packet.length);
		}


		//osThreadYield();
	  }
}


void Ras_UART_Callback(){
	osSemaphoreRelease(*ras_Semaphore);
}


uint8_t calculate_checksum(uint8_t *data, uint8_t length) {
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum;
}


void Ras_TX_add_to_q(uint8_t* str){

    uint8_t payload_length = strlen(str);
    uint8_t packet_length = 2 + 1 + payload_length + 1; // Header + Length + Payload + Checksum

    Ras_TX_Data_st packet;
    packet.length = packet_length;
    packet.data[0] = HEADER_BYTE_1;
    packet.data[1] = HEADER_BYTE_2;
    packet.data[2] = payload_length;
    memcpy(&packet.data[3], str, payload_length);
    packet.data[packet_length - 1] = calculate_checksum((uint8_t *)str, payload_length);

    osMessageQueuePut(*ras_tx_MsgQueue, &packet, 0U, 0U);

}
