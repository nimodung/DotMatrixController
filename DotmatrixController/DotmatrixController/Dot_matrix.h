/*
 * Dot_matrix.h
 *
 * Created: 2019-04-09 오후 5:07:43
 *  Author: hee ram
 */ 


#ifndef DOT_MATRIX_H_
#define DOT_MATRIX_H_


#define Dot_DDR DDRC
#define Dot_PORT PORTC
#define RClk PORTC4
#define SRClk PORTC5
#define SER PORTC3

void Dotmatrix_init_shiftR(void);
void Dotmatrix_shift_out(uint8_t data, uint8_t comm);


#endif /* DOT_MATRIX_H_ */
