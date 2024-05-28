#include <avr/io.h>
#include <stdio.h>
#include <avr/delay.h>

#define F_CPU 3333333
#define BAUD_RATE 9600

#define _ADC0_CTRLA				(unsigned char *)(0x0600)
#define _ADC0_CTRLA				(unsigned char *)(0x0600)
#define _ADC0_MUXPOS			(unsigned char *)(0x0606)
#define _ADC0_COMMAND			(unsigned char *)(0x0608)
#define _ADC0_RES				(unsigned char *)(0x0610)
#define _ADC_RESSEL_10BIT_gc	(0x01<<0)
#define _ADC_ENABLE_bm			(0x01)
#define _ADC_STCONV_bm			(0x01)

#define PORTC					(unsigned char *)(0x0440)
#define PORTC_DIR				(unsigned char *)(0x0440)
#define PORTC_DIRSET			(unsigned char *)(0x0441)
#define PORTC_DIRCLR			(unsigned char *)(0x0442)
#define PORTC_OUT				(unsigned char *)(0x0444)
#define PORTC_OUTSET			(unsigned char *)(0x0445)
#define PORTC_OUTCLR			(unsigned char *)(0x0446)
#define PORTC_IN				(unsigned char *)(0x0448)

#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
#define PIN(N)	(1<<N)

void ADC_init(void);
uint16_t ADC_read(int ch);

void USART3_init(void);
void USART3_Transmit(unsigned char);
int USART3_printChar(char, FILE *stream);

FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

void USART3_init(void){
	PORTB_DIR |= PIN(0);
	PORTB_DIR &= ~PIN(1);
	
	USART3_BAUD = (uint16_t)USART0_BAUD_RATE(BAUD_RATE);
	USART3_CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
}

int USART3_printChar(char c, FILE *stream){
	USART3_Transmit(c);
	
	return 0;
}

void USART3_Transmit(unsigned char data){
	while(!((USART3_STATUS)&USART_DREIF_bm));
	USART3_TXDATAL = data;
}

void ADC_init(void){
	PORTD_PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc;

	ADC0_CTRLA = ADC_RESSEL_10BIT_gc;
	ADC0_CTRLC |= ADC_REFSEL_VDDREF_gc;
	ADC0_CTRLA |= ADC_ENABLE_bm | ADC_FREERUN_bm;
}

uint16_t ADC_read(int ch){
	ADC0_MUXPOS = ch;
	ADC0_COMMAND |= ADC_STCONV_bm;
	
	while(!(ADC0_COMMAND) & ADC_STCONV_bm);
	
	return (uint16_t)ADC0_RES;
}

uint8_t motor_speed(int Y){
	if(Y >= 492 && Y <= 532){
		TCB0_CCMPH = 0;
	}
	else if((Y >= 533 && Y <= 631) || (Y >= 394 && Y <= 492)){
		TCB0_CCMPH = 32;
	}
	else if((Y >= 632 && Y <= 730) || (Y >= 295 && Y <= 393)){
		TCB0_CCMPH = 64;
	}
	else if((Y >= 731 && Y <= 829) || (Y >= 196 && Y <= 294)){
		TCB0_CCMPH = 128;
	}
	else if((Y >= 830 && Y <= 928) || (Y >= 98 && Y <= 195)){
		TCB0_CCMPH = 192;
	}
	else if((Y >= 929 && Y <= 1023) || (Y >= 0 && Y <= 97)){
		TCB0_CCMPH = 255;
	}
	return TCB0_CCMPH;
}



int main(void)
{
	USART3_init();
	ADC_init();
	stdout = &USART_stream;
	
	// 포트A의 2번 핀을 출력 핀으로 설정
	PORTA_DIR |= PIN2_bm;
	PORTA_OUT |= PIN2_bm;
	
	TCB0_CTRLA |= TCB_ENABLE_bm // TCB enable
	| TCB_CLKSEL_CLKDIV2_gc; // (Clock 속도 / 2)
	
	TCB0_CTRLB |= TCB_CCMPEN_bm	// Compare mode enable
	| TCB_CNTMODE_PWM8_gc; // 8bit PWM Mode
	
	TCB0_CCMPL = 0xFF; // Period 설정
	TCB0_CCMPH = 0xFF; // Duty 설정
	
	*PORTC_DIRSET = PIN(2) | PIN(3) | PIN(4) | PIN(5);

	int X_value = ADC_read(0);
	_delay_ms(10);
	int Y_value = ADC_read(1);

	while (1)
	{
		int X_value = ADC_read(0);
		_delay_ms(10);
		int Y_value = ADC_read(1);
		printf("X value : %d \t Y value : %d \n\r", X_value, Y_value);
		
		// 좌측 모터 순방향 : PIN5 , 좌측 모터 역방향 : PIN4 
		// 우측 모터 순방향 : PIN2 , 우측 모터 역방향 : PIN3
		if(Y_value >= 492 && Y_value <= 532){
			if(X_value >= 467 && X_value <= 506){
				motor_speed(Y_value);
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5)));
				printf("stop\n\r");
			}
			else if(X_value >= 507 ){
				TCB0_CCMPH = 192;
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(3) | PIN(4);
				printf("Right\n\r");
			}
			else if(X_value <= 466 ){
				TCB0_CCMPH = 192;
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(2) | PIN(5);
				printf("Left\n\r");
			}
			_delay_ms(10);
		}
		else if(Y_value >= 533){
			if(X_value >= 467 && X_value <= 506){
				motor_speed(Y_value);				
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(2) | PIN(4);
				printf("drive\n\r");
			}
			else if(X_value >= 507 ){
				TCB0_CCMPH = 192;
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(3) | PIN(4);
				printf("Right\n\r");
			}
			else if(X_value <= 466 ){
				TCB0_CCMPH = 192;
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(2) | PIN(5);
				printf("Left\n\r");
				
			}
			_delay_ms(10);
		}
		else if(Y_value <= 491){
			if(X_value >= 467 && X_value <= 506){
				motor_speed(Y_value);
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(3) | PIN(5);
				printf("reverse\n\r");
			}
			else if(X_value >= 507 ){
				TCB0_CCMPH = 192;
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(3) | PIN(4);
				printf("Right\n\r");
			}
			else if(X_value <= 466 ){
				TCB0_CCMPH = 192;
				*PORTC_OUT = (*PORTC_OUT & ~(PIN(2) | PIN(3) | PIN(4) | PIN(5))) | PIN(2) | PIN(5);
				printf("Left\n\r");
			}
			_delay_ms(10);
		}
		
		_delay_ms(300);
	}
}

