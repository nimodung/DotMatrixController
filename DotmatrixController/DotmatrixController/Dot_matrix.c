/*
 * Dot_matrix.c
 *
 * Created: 2019-04-08 오전 10:50:17
 *  Author: hee ram
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Dot_matrix.h"

extern uint8_t dotmatrix[8];

void Dotmatrix_init_shiftR(void)
{
	Dot_DDR |= 1 << RClk | 1 << SRClk | 1 << SER; //595 3bit 연결 // 3, 4,5번 연결
	Dot_PORT |= 1 << RClk; // 0b00010000; //RClk : 1 //RClk을 상승 edge로 둬서 다른 데이터가 들어가지 않게
	
	for(int i = 0; i < 8; i++)
		dotmatrix[i] = 0xff;
	
	return;
}

void Dotmatrix_shift_out(uint8_t data, uint8_t comm)
{
	
	Dot_PORT &= ~(1 << RClk);
	for(int i = 0; i < 8; i++) //data 한개씩 넣는걸 8번
	{
		Dot_PORT &= ~(1 << SRClk);
		Dot_PORT &= ~(1 << SER); //일단 0으로 떨어트려
		Dot_PORT |= ((data >> i) & 1) << SER; //받아온 data 값을 0 아니면 1
		Dot_PORT |= 1 << SRClk;//0b00100000; //상승 edge
	}
	
	for(int i = 0; i < 8; i++) //data 한개씩 넣는걸 8번
	{
		Dot_PORT &= ~(1 << SRClk);
		Dot_PORT &= ~(1 << SER); //일단 0으로 떨어트려
		Dot_PORT |= ((comm >> i) & 1) << SER; //받아온 data 값을 0 아니면 1
		Dot_PORT |= 1 << SRClk;//0b00100000; //상승 edge
	}
	
	Dot_PORT |= 1 << RClk; //RClk 상승 edge
	return;
}
