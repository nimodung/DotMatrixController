/*
 * Uart.h
 *
 * Created: 2019-04-17 오전 9:49:14
 *  Author: user
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdio.h>

#define BUFFER_MAX 100 // 한 명령어의 최대 글자 수
#define COMMAND_MAX 10 //명령어 갯수
//명령어 처리 중에 다른 딜레이가 생겨 명령어를 놓치는 일이 없게 하기위해 명령어 저장해서 실행



void UART0_init(unsigned long baud);
void TX0_char(char data);


#endif /* UART_H_ */
