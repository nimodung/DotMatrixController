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

/* Timer.c 의 내용을 수정
ISR(TIMER0_COMPA_vect) //interrupt 걸리면 실행하는 내용 //Interrupt Service Routine
{
	static int msec = 0; //static -> 처음 할당될때 메모리 받아서 반납하지 않음
	static char i = 0;
	msec++;
	i++;
	
	if(i >= 8) i = 0;
	if(i < 4)
	{
		dot_matrix_comm_low_PORT &= 0b11110000;
		dot_matrix_comm_high_PORT &= 0b11110000;
		dot_matrix_comm_low_PORT |= 1 <<i;
		dot_matrix_data_PORT = dotmatrix_row[i];
	}
	else
	{
		dot_matrix_comm_low_PORT &= 0b11110000;
		dot_matrix_comm_high_PORT &= 0b11110000;
		dot_matrix_comm_high_PORT |= 1 << (i-4);
		dot_matrix_data_PORT = dotmatrix_row[i];
	}
	
	if(!(msec % 500))
	PORTB ^= (1<<PORTB5); // (1<<PORTB5) == 0b00100000 //토글 켜져있으면 끄고 꺼져있으면 켠다
}
*/

char dotmatrix_row[8]; //줄 수
char dotmatrix_buffer[8]; //연산 결과를 넣고~
/*
const char KIM[8] = {
	0b10001101, 0b11101101, 0b11011101, 0b10111101, 0b11111111, 0b11000011, 0b11011011, 0b11000011 
}; //Timer.c에서 사용하기위해 전역변수 선언해줌
const char HEE[8] = {
	0b11001111, 0b10000101, 0b11111101, 0b11001101, 0b10110101, 0b11001101, 0b11111101, 0b10000111
}; 
const char RAM[8] = {
	0b10001011, 0b11101001, 0b10001011, 0b10111011, 0b10001111, 0b11110001, 0b11110101, 0b11110001
};
const char WON[8] = {
	0b11001111, 0b10110101, 0b11001101, 0b11111001, 0b10000101, 0b11101101, 0b10111111, 0b10000001
};
const char MO[8] = {
	0b10000011, 0b10111011, 0b10111011, 0b10000011, 0b11111111, 0b11101111, 0b11101111, 0b10000011
};
const char HEART[8] = {
	0b11111111, 0b11111111, 0b11010111, 0b10101011, 0b10111011, 0b11010111, 0b11101111, 0b11111111
};
	
	*/
char name[3][8] = {
	{0b10001101, 0b11101101, 0b11011101, 0b10111101, 0b11111111, 0b11000011, 0b11011011, 0b11000011},
	{0b11001111, 0b10000101, 0b11111101, 0b11001101, 0b10110101, 0b11001101, 0b11111101, 0b10000111},
	{0b10001011, 0b11101001, 0b10001011, 0b10111011, 0b10001111, 0b11110001, 0b11110101, 0b11110001}
};
/*
// 
// char name[5][8] = {
// 	{0b11001111, 0b10000101, 0b11111101, 0b11001101, 0b10110101, 0b11001101, 0b11111101, 0b10000111},
// 	{0b10001011, 0b11101001, 0b10001011, 0b10111011, 0b10001111, 0b11110001, 0b11110101, 0b11110001},
// 	{0b11111111, 0b11111111, 0b11010111, 0b10101011, 0b10111011, 0b11010111, 0b11101111, 0b11111111},
// 	{0b11001111, 0b10110101, 0b11001101, 0b11111001, 0b10000101, 0b11101101, 0b10111111, 0b10000001},
// 	{0b10000011, 0b10111011, 0b10111011, 0b10000011, 0b11111111, 0b11101111, 0b11101111, 0b10000011}		
// };*/
/*
//저항이 없어도 문제 없는 이유 => PORT에서 전원을 주기 때문에 이정도는 ㄱㅊ
int Dot_matrix_main(void)
{
	//int msec = 0;
	//char pattern1 = 0, pattern2 = 0;
	//char char_num = 0;
	//char tmp[8];
	
	//const -> 상수, 바꾸려고하면 에러남
	
	for(int j = 0; j < 8; j++)
	{
		name[0][j] = KIM[j];
	}
	for(int j = 0; j < 8; j++)
	{
		name[1][j] = HEE[j];
	}
	for(int j = 0; j < 8; j++)
	{
		name[2][j] = RAM[j];
	}
// 	for(int j = 0; j < 8; j++)
// 	{
// 		name[2][j] = HEART[j];
// 	}
// 	for(int j = 0; j < 8; j++)
// 	{
// 		name[3][j] = WON[j];
// 	}
// 	for(int j = 0; j < 8; j++)
// 	{
// 		name[4][j] = MO[j];
// 	}
	
	dotmatrix_init();
	
	
	while(1)
	{
		
		dotmatrix_test();
		//dotmatrix_flow(name, 3, 5);
		
		//msec
		/*
		msec += 16;
		if(msec >= 500)
		{
			msec = 0;
			char_num++;
			if(char_num >= 3) char_num = 0;			
		}
		*/
		//이름 세글자 띄우기		
		/* 이름 세글자 띄우기
		dot_matrix_data_PORT = 0b11111111;
		//dot_matrix_data_PORT = 0b00000000;
		
		for(int i = 0; i < 4; i++)
		{
			dot_matrix_comm_low_PORT = 1 <<i;
			dot_matrix_data_PORT = name[char_num][i];
				
			_delay_ms(2);
		}
		dot_matrix_comm_low_PORT = 0;
		for(int i = 0; i < 4; i++)
		{
			dot_matrix_comm_high_PORT = 1 <<i;
			dot_matrix_data_PORT = name[char_num][i+4];
				
			_delay_ms(2);
		}
		dot_matrix_comm_high_PORT = 0;
		*/
		//글자 줄줄이 출력
		/*for(int l = 0; l <5; l++) //name[l]
 		{
 			//글자가 오른쪽에서 흘러 들어오게
 			for(int j = 0; j <8; j++) //font 미는 for문
 			{
 				for(int k = 0; k < 15; k++) //시간 보내는 for문 16msec * 10 = 160msec
 				{							//아래 연산을 계속해서 해야함 -> 비효율적
 					for(int i = 0; i < 4; i++) 
					{
						dot_matrix_comm_low_PORT = 1 <<i;
						dot_matrix_data_PORT = name[(l+1)%3][i] >>(8-j) | name[l][i] << j;
						
						if(l == 4) //name[2] 다음의 쓰레기값 처리 (name[2(l)+1] == name[3] <=없음)
						{
							dot_matrix_data_PORT = dotmatrix_row[i];
							//(name[0][i] >> (8-j)) | (name[l][i]<< j);
						}
						else
						{
							dot_matrix_data_PORT = (name[l+1][i] >> (8-j)) | (name[l][i]<< j);
							//dot_matrix_data_PORT = (name[l][i] >> (7-j)) | ~(0b11111111 >> (7-j));
							//글자 출력 후 뒷부분 1로 채워서 끄기
						}
						
						_delay_ms(2);
		
					}
					dot_matrix_comm_low_PORT = 0;
	
					for(int i = 0; i < 4; i++)
					{
						dot_matrix_comm_high_PORT = 1 <<i;
						dot_matrix_data_PORT = name[(l+1)%3][i+4] >>(8-j) | name[l][i+4] << j;
						_delay_ms(2);
					}
					dot_matrix_comm_high_PORT = 0;
					
					return;
 				}
 			}
		*/
		//글자 왼쪽으로 흘러나가게
 		/*
 			//글자가 왼쪽으로 흘러 나가게
 			for(int j = 0; j <8; j++)
 			{
 				for(int k = 0; k < 5; k++)
 				{
 					for(int i = 0; i < 4; i++)
 					{
 						dot_matrix_comm_low_PORT = 1 <<i;
 						dot_matrix_data_PORT = (name[l][i]<< j) | ~(0b11111111 << j);
 																//글자 출력 후 뒷부분 1로 채워서 끄기
 						_delay_ms(2);
 					}
 					dot_matrix_comm_low_PORT = 0;
 					for(int i = 0; i < 4; i++)
 					{
 						dot_matrix_comm_high_PORT = 1 <<i;
 						dot_matrix_data_PORT = name[l][i+4]<< j  | ~(0b11111111 << j);
 					
 						_delay_ms(2);
 					}
 					dot_matrix_comm_high_PORT = 0;
 				}
 			
 			}
		
		
	}
	
	return 0;
}
*/
void dotmatrix_init(void)
{
	dot_matrix_comm_low_DDR |= 0b00001111; //출력으로 초기화
	dot_matrix_comm_low_PORT = 0;
	dot_matrix_comm_high_DDR |= 0b00001111;
	dot_matrix_comm_high_PORT = 0;
	dot_matrix_data_DDR = 0b11111111;
	dot_matrix_data_PORT = 0b11111111;
	//공통단자에 1 데이터단자에 0 을 줘야 불 켜짐
	//port 꺼지는걸로 초기화
	
	for(int i = 0; i < 8; i++)
	{
		dotmatrix_row[i] = 255; //= 0b11111111 or 0xff
	}
	
	return;
}

void dotmatrix_test(void)
{
	for(int j = 0; j < 4; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			dot_matrix_comm_low_PORT = 1 << j;
			dot_matrix_data_PORT = ~(1 << i);
			_delay_ms(200);
			
		}
		dot_matrix_comm_low_PORT = 0;
		
	}
	for(int j = 0; j < 4; j++)
	{
		for(int i = 0; i < 8; i++)
		{
			dot_matrix_comm_high_PORT = 1 << j;
			dot_matrix_data_PORT = ~(1 << i);
			_delay_ms(200);
		}
		dot_matrix_comm_high_PORT = 0;
	}
	
	
	return;
}

void dotmatrix_operator(void)
{
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_low_PORT = 1 <<i;
		dot_matrix_data_PORT = dotmatrix_row[i];
		/*
		if(l == 4) //name[2] 다음의 쓰레기값 처리 (name[2(l)+1] == name[3] <=없음)
		{
			dot_matrix_data_PORT = dotmatrix_row[i];
			//(name[0][i] >> (8-j)) | (name[l][i]<< j);
		}
		else
		{
			dot_matrix_data_PORT = (name[l+1][i] >> (8-j)) | (name[l][i]<< j);
			//dot_matrix_data_PORT = (name[l][i] >> (7-j)) | ~(0b11111111 >> (7-j));
			//글자 출력 후 뒷부분 1로 채워서 끄기
		}
		*/
		_delay_ms(2);
		
	}
	dot_matrix_comm_low_PORT = 0;
	
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_high_PORT = 1 <<i;
		dot_matrix_data_PORT = dotmatrix_row[i+4];
		_delay_ms(2);
	}
	dot_matrix_comm_high_PORT = 0;
	
	return;
}

void dotmatrix_update(char *pattern)
{
	for(int i = 0; i < 8; i++)	
	{
		dotmatrix_row[i] = pattern[i];
	}
	
	return;
}

void dotmatrix_flow(char (*data)[8], char char_len, char interval) //interval이 커지면 천천히 지나감
{
	for(int k = 0; k < char_len; k++)
	{
		for(int j = 0; j <8; j++)
		{
			for(int i = 0; i < 8; i++)
			{
				dotmatrix_row[i] = data[(k+1)%char_len][i] >>(8-j) | data[k][i] << j;
			}
			for(int i = 0; i < interval; i++)
			{
				dotmatrix_operator(); //출력함수
			}
		}
	}
	
	return;
}

void dotmatrix_flow_buffer(char (*data)[8], char char_len)
{
	for(int k = 0; k < char_len; k++)
	{
		for(int j = 0; j <8; j++)
		{
			for(int i = 0; i < 8; i++)
			{
				dotmatrix_buffer[i] = data[(k+1)%char_len][i] >>(8-j) | data[k][i] << j;
			}
			dotmatrix_update(dotmatrix_buffer); //한줄씩 보내면 밀리는 현상 발생하기 때문에 한번에 업데이트
			_delay_ms(200);  
		}
	}
	
	return;
}

void name_char(char ch[])
{
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_low_PORT = 1 <<i;
		dot_matrix_data_PORT = ch[i];
		_delay_ms(2);
	}
	dot_matrix_comm_low_PORT = 0;
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_high_PORT = 1 <<i;
		dot_matrix_data_PORT = ch[i+4];
		_delay_ms(2);
	}
	dot_matrix_comm_high_PORT = 0;

}
void left_up_tri()
{
	dot_matrix_data_PORT = 0b00000000;
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_low_PORT = 1 << i; //portb => dot_matrix 의 1~4번째 줄까지
		//dot_matrix_data_PORT &= ~(1 << i); // 1개, 2개, 3개, 4개 on
		dot_matrix_data_PORT |= (1 << i);
		_delay_ms(2);
	}	
		
	/*
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_low_PORT = 1 << i;
		dot_matrix_data_PORT =  ~(0b11111111 << (i+1));
		//~(0b11111110 << i);
		_delay_ms(2);
	}
	*/
	dot_matrix_comm_low_PORT = 0; //초기화 안하면 다음 줄들이 같이 실행된다. => delay 2이기 때문에 다 켜진걸로 보임.
		
	for(int j = 0; j < 4; j++)
	{
		dot_matrix_comm_high_PORT = 1 << j; //PORT => dot_matrix 의 5~8번째 줄까지
		dot_matrix_data_PORT |= (0b00010000 <<j); //5개, 6개, 7개, 8개 on
		_delay_ms(2);
	}
	/*
	for(int j = 0; j < 4; j++)
	{
		dot_matrix_comm_high_PORT = 1 << j;
		dot_matrix_data_PORT = ~(0b11100000 << j);
		_delay_ms(2);
	}
		
	*/
	dot_matrix_comm_high_PORT = 0;
		
	return;
}
void right_up_tri()
{
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_low_PORT = 1 << i;
		dot_matrix_data_PORT = ~(0b01111111 >> i);
		//dot_matrix_data_PORT |= 0b10000000 >> i;
		_delay_ms(2);
	}
	dot_matrix_comm_low_PORT = 0; //초기화 안하면 다음 줄들이 같이 실행된다. => delay 2이기 때문에 다 켜진걸로 보임.
	
	for(int j = 0; j < 4; j++)
	{
		dot_matrix_comm_high_PORT = 1 << j; //PORT => dot_matrix 의 5~8번째 줄까지
		dot_matrix_data_PORT = ~(0b00000111 >> j); //5개, 6개, 7개, 8개 on
		//dot_matrix_data_PORT |= 0b10000000 >> (j+4);
		_delay_ms(2);
	}
	dot_matrix_comm_high_PORT = 0;
	
	return;
}
void and_left_right_up_tri()
{
	char pattern1 = 0, pattern2 = 0;
	dot_matrix_data_PORT = 0b00000000;
	pattern1 = 0;
	pattern2 = 0;
	
	for(int i = 0; i < 4; i++)
	{
		dot_matrix_comm_low_PORT = 1 << i;
		//dot_matrix_data_PORT = (~(0b11111110 << i))&(~(0b01111111 >> i));
		pattern1 |= 0b10000000 >> i;
		pattern2 |= 0b00000001 << i;
		dot_matrix_data_PORT = ( pattern1 & pattern2);
		//
		_delay_ms(2);
	}
	
	dot_matrix_comm_low_PORT = 0; //초기화 안하면 다음 줄들이 같이 실행된다. => delay 2이기 때문에 다 켜진걸로 보임.
	
	for(int j = 0; j < 4; j++)
	{
		dot_matrix_comm_high_PORT = 1 << j; //PORT => dot_matrix 의 5~8번째 줄까지
		//dot_matrix_data_PORT = (~(0b11100000 << j))&(~(0b00000111 >> j));
		pattern1 |= 0b10000000 >> (j+4);
		pattern2 |= 0b00000001 << (j+4);
		dot_matrix_data_PORT = (pattern1 & pattern2);
		_delay_ms(2);
	}
	dot_matrix_comm_high_PORT = 0;


	return;
}