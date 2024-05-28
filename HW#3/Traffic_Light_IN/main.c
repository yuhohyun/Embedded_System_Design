#define F_CPU 3333333

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define _PORTA			(uint8_t *)			(0x0600)
#define _PORTA_DIR		(PORTA)->DIR
#define _PORTA_DIRSET	(PORTA)->DIRSET
#define _PORTA_DIRCLR	(PORTA)->DIRCLR
#define _PORTA_OUT		(PORTA)->OUT
#define _PORTA_OUTSET	(PORTA)->OUTSET
#define _PORTA_OUTCLR	(PORTA)->OUTCLR
#define _PORTA_IN		(PORTA)->IN
#define _PORTA_INTFLAGS (PORTA)->INTFLAGS


#define _PORTC			(uint8_t *)			(0x0440)
#define _PORTC_DIR		(PORTC)->DIR
#define _PORTC_DIRSET	(PORTC)->DIRSET
#define _PORTC_DIRCLR	(PORTC)->DIRCLR
#define _PORTC_OUT		(PORTC)->OUT
#define _PORTC_OUTSET	(PORTC)->OUTSET
#define _PORTC_OUTCLR	(PORTC)->OUTCLR

#define _PORTD			(uint8_t *)			(0x0460)
#define _PORTD_DIR		(PORTD)->DIR
#define _PORTD_DIRSET	(PORTD)->DIRSET
#define _PORTD_DIRCLR	(PORTD)->DIRCLR
#define _PORTD_OUT		(PORTD)->OUT
#define _PORTD_OUTSET	(PORTD)->OUTSET
#define _PORTD_OUTCLR	(PORTD)->OUTCLR

#define PIN_ON(N)		(1<<N)
#define PORT_PULL_UP	(1<<3)

static volatile uint8_t prevButtonState = 0;
static volatile uint8_t delayIndex = 0;

void LED_A_1s(void) {
	PORTA.OUT |= PIN_ON(7);
	_delay_ms(1000);
	PORTC.OUT &= ~PIN_ON(7);
	PORTD.OUT &= ~PIN_ON(7);
}

void LED_A_3s(void) {
	PORTA.OUT |= PIN_ON(7);
	_delay_ms(3000);
	PORTC.OUT &= ~PIN_ON(7);
	PORTD.OUT &= ~PIN_ON(7);
}

void LED_A_5s(void) {
	PORTA.OUT |= PIN_ON(7);
	_delay_ms(5000);
	PORTC.OUT &= ~PIN_ON(7);
	PORTD.OUT &= ~PIN_ON(7);
}

void LED_C_1s(void) {
	PORTC.OUT |= PIN_ON(7);
	_delay_ms(1000);
	PORTA.OUT &= ~PIN_ON(7);
	PORTD.OUT &= ~PIN_ON(7);
}

void LED_C_3s(void) {
	PORTC.OUT |= PIN_ON(7);
	_delay_ms(3000);
	PORTA.OUT &= ~PIN_ON(7);
	PORTD.OUT &= ~PIN_ON(7);
}

void LED_C_5s(void) {
	PORTC.OUT |= PIN_ON(7);
	_delay_ms(5000);
	PORTA.OUT &= ~PIN_ON(7);
	PORTD.OUT &= ~PIN_ON(7);
}

void LED_D_1s(void) {
	PORTD.OUT |= PIN_ON(7);
	_delay_ms(1000);
	PORTA.OUT &= ~PIN_ON(7);
	PORTC.OUT &= ~PIN_ON(7);
}

void LED_D_3s(void) {
	PORTD.OUT |= PIN_ON(7);
	_delay_ms(3000);
	PORTA.OUT &= ~PIN_ON(7);
	PORTC.OUT &= ~PIN_ON(7);
}

void LED_D_5s(void) {
	PORTD.OUT |= PIN_ON(7);
	_delay_ms(5000);
	PORTA.OUT &= ~PIN_ON(7);
	PORTC.OUT &= ~PIN_ON(7);
}


ISR(PORTA_PORT_vect) {
	static volatile uint8_t prevButtonState = 0;
	uint8_t buttonState = (PORTA.IN & PIN_ON(6));
	
	if (buttonState && !prevButtonState) {
		// 버튼이 눌렸을 때
		if (delayIndex == 0) {
			// 현재 딜레이가 1초인 경우
			delayIndex = 1; // 딜레이를 3초로 변경
			} else if (delayIndex == 1) {
			// 현재 딜레이가 3초인 경우
			delayIndex = 2; // 딜레이를 5초로 변경
			} else {
			// 현재 딜레이가 5초인 경우
			delayIndex = 0; // 딜레이를 1초로 변경
		}
	}
	
	prevButtonState = buttonState;
	_delay_ms(100);
}


void init_interrupt(void) {
	PORTA.PIN6CTRL |= PORT_ISC_FALLING_gc | PORT_PULLUPEN_bm; // 기존의 PIN6CTRL 값을 유지하면서 필요한 비트를 추가로 설정함
	PORTA.INTFLAGS = PORT_INT6_bm;  // 인터럽트 플래그 클리어
	PORTA.PIN6CTRL |= PORT_INT6_bm;  // 인터럽트 활성화
}


int main(void)
{
	PORTA.DIR = 0x80;
	PORTC.DIR = 0x80;
	PORTD.DIR = 0x80;
	PORTA.DIRCLR = PIN_ON(6); // PA6은 입력

	init_interrupt();
	
	sei();

	while (1) {
		switch(delayIndex) {
			case 0:
			LED_A_1s();
			LED_D_1s();
			LED_C_1s();
			break;
			case 1:
			LED_A_3s();
			LED_D_3s();
			LED_C_3s();
			break;
			case 2:
			LED_A_5s();
			LED_D_5s();
			LED_C_5s();
			break;
			default:
			break;
		}
	}

	return 0;
}
