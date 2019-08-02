/*
 * Dot_matrix.h
 *
 * Created: 2019-04-09 오후 5:07:43
 *  Author: hee ram
 */ 


#ifndef DOT_MATRIX_H_
#define DOT_MATRIX_H_

#define dot_matrix_comm_low_DDR DDRB
#define dot_matrix_comm_high_DDR DDRC
//공통 단자 : PORTB , PORTC
#define dot_matrix_data_DDR DDRD
//데이터 단자 : PORTD
#define dot_matrix_comm_low_PORT PORTB
#define dot_matrix_comm_high_PORT PORTC
#define dot_matrix_data_PORT PORTD

void dotmatrix_init(void);
void dotmatrix_test(void);
void dotmatrix_operator(void);
void dotmatrix_update(char *pattern);
void dotmatrix_flow(char (*data)[8], char char_len, char interval);
void dotmatrix_flow_buffer(char (*data)[8], char char_len);
int Dot_matrix_main(void);


#endif /* DOT_MATRIX_H_ */