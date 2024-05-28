#define F_CPU 3333333
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void USART1_init(void);
void USART1_Transmit(unsigned char data);
unsigned char USART1_Receive(void);
int USART1_printChar(char c, FILE *stream);

#define BAUD_RATE 9600
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5);

#define PIN(N) (1 << N)

void USART1_init(void)
{
	PORTB_DIR |= PIN(0);
	PORTB_DIR &= ~PIN(1);

	USART3_BAUD = (uint16_t)USART0_BAUD_RATE(BAUD_RATE);
	USART3_CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
}

void USART1_Transmit(unsigned char data)
{
	while (!((USART1_STATUS)&USART_DREIE_bm))
	;

	USART1_TXDATAL = data;
}

unsigned char USART1_Receive(void)
{
	while (!((USART1_STATUS)&USART_RXCIE_bm));

	return USART1_RXDATAL;
}

void USART1_Transmit_Reverse()
{
	int cnt = 0;
	unsigned char buf[10];

	while (1)
	{
		buf[cnt] = USART1_Receive();
		if (buf[cnt] == '\0' || buf[cnt] == '\n' || buf[cnt] == '\r')
		break;
		cnt++;
	}

	USART1_Transmit_String("RECEIVE: ");
	USART1_Transmit_String(buf);

	for (int i = cnt - 1; i >= 0; i--)
	{
		USART1_Transmit(buf[i]);
	}
}

void USART1_Transmit_String(unsigned char data[])
{
	int i = 0;
	while (data[i] != '\0')
	{
		USART1_Transmit(data[i]);
		i++;
		_delay_ms(10);
	}
}

int USART1_printChar(char c, FILE *stream)
{
	USART1_Transmit(c);

	return 0;
}

FILE USART_OUTstream = FDEV_SETUP_STREAM(USART1_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void)
{
	USART1_init();
	stdout = &USART_OUTstream;
	
	char string[10];
	
	while (1)
	{
		scanf("%c",string);
		USART1_printChar(string,&USART_OUTstream);
		USART1_Transmit_Reverse();
	}
	return 0;
}
