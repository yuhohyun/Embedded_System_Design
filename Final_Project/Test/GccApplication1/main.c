
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define TRIGGER_PIN  PIN4_bm
#define ECHO_PIN     PIN6_bm

#define F_CPU 3333333
#define BAUD_RATE 9600

#define USART_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64/ (16 * (float)BAUD_RATE)) + 0.5)
#define PIN(N)  (1 << N)

void initialize() {
	// 초음파 센서의 트리거 핀을 출력으로 설정
	PORTB_DIR |= TRIGGER_PIN;

	// 초음파 센서의 에코 핀을 입력으로 설정
	PORTB_DIR &= ~ECHO_PIN;

	TCB0_CTRLB = TCB_CNTMODE_INT_gc;  // Interval mode
	TCB0_CTRLA = TCB_ENABLE_bm;  // Enable TCB
}

float measureDistance() {
	// 트리거 핀을 LOW로 설정하여 초기화
	PORTA_OUT &= ~TRIGGER_PIN;
	_delay_us(2);

	// 10us 동안 트리거 핀을 HIGH로 설정
	PORTA_OUT |= TRIGGER_PIN;
	_delay_us(10);
	PORTA_OUT &= ~TRIGGER_PIN;

	// 에코 핀이 HIGH가 될 때까지 기다림
	while(!(PORTA_IN & ECHO_PIN));

	// 에코 핀이 HIGH인 동안의 시간을 측정
	TCB0_CNT = 0;  // 타이머 카운터를 0으로 초기화
	while(PORTA_IN & ECHO_PIN);

	// 초음파가 왕복하는데 걸린 시간을 계산
	// (타이머 카운트 값 / 클럭 주파수) * 초음파 속도(340.29 m/s) * 100 (cm로 변환) / 2 (왕복 거리이므로 2로 나눔)
	float distance = ((float)TCB0_CNT / F_CPU) * 340.29 * 100 / 2;
	//float distance = (float)TCB0.CNT * 340.0 * 0.000001 / 2.0 * 100.0;
	
	return distance;
}

void USART3_init(void){
	PORTB_DIR |= PIN(0);
	PORTB_DIR &= ~PIN(1);
	// UART 통신 초기화
	USART3_BAUD = (uint16_t)USART_BAUD_RATE(BAUD_RATE);
	USART3_CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
}

void USART3_Transmit(unsigned char data){
	while (!((USART3_STATUS) & USART_DREIF_bm));
	USART3_TXDATAL = data;
	//while (!(USART0.STATUS & USART_TXCIF_bm));
}

int USART3_printChar(char c, FILE *stream){
	USART3_Transmit(c);
	return 0;
}

FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

int main(void) {
	initialize();
	USART3_init();
	stdout = &USART_stream;

	while (1) {
		float distance = measureDistance();

		printf("Distance: %.2f cm\n\r", distance);

		_delay_ms(1000);
	}
}