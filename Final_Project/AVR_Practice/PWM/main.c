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

int main(void)
{	
	USART3_init();
	ADC_init();
	stdout = &USART_stream;

	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL_MCLKCTRLB = CLKCTRL_PDIV_64X_gc | CLKCTRL_PEN_bm;
	CLKCTRL_MCLKCTRLA = CLKCTRL_CLKSEL_OSCULP32K_gc;
	while(CLKCTRL_MCLKSTATUS & CLKCTRL_SOSC_bm);
	
	PORTC_DIR |= PIN2_bm;
	PORTC_OUT |= PIN2_bm;
	
	TCA0_SINGLE_CTRLA |= TCA_SINGLE_ENABLE_bm
						| TCA_SINGLE_CLKSEL_DIV2_gc;
	
	TCA0_SINGLE_CTRLB |= TCA_SINGLE_CMP0_bm
						| TCA_SINGLE_WGMODE0_bm;
						
	TCA0_SINGLE_PER = 0xFF;		// 8 bit resolution
	TCA0_SINGLE_CMP0 = 0xFF; 
	
	while (1)
	{
		int X_value = ADC_read(0);
		_delay_ms(10);
		int Y_value = ADC_read(1);
		printf("X value : %d \t Y value : %d \n\r", X_value, Y_value);
		
		if(Y_value >= 505 && Y_value <= 521){
			printf("stop\n\r");
			_delay_ms(10);
		}
		else if(Y_value > 521){
			if(Y_value > 901) {
				TCA0_SINGLE_CMP0 = 255;
				printf("drive(Speed : 4, TCA0_CMP0 : %d)\n\r", TCA0_SINGLE_CMP0);
			}
			else if(Y_value > 779 && Y_value <= 901){
				TCA0_SINGLE_CMP0 = 191;
				printf("drive(Speed : 3, TCA0_CMP0 : %d)\n\r", TCA0_SINGLE_CMP0);
			}
			else if(Y_value > 657 && Y_value <= 779){ 
				TCA0_SINGLE_CMP0 = 127;
				printf("drive(Speed : 2, TCA0_CMP0 : %d)\n\r", TCA0_SINGLE_CMP0);
			}
			else {
				TCA0_SINGLE_CMP0 = 63;
				printf("drive(Speed : 1, TCA0_CMP0 : %d)\n\r", TCA0_SINGLE_CMP0);
			}
		
		_delay_ms(300);
		}
	}
}



