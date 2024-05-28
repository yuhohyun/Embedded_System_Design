#define F_CPU 3333333	// 마이크로컨트롤러 클럭 주파수 정의

#include <avr/io.h>
#include <util/delay.h>

#define _PORTA			(uint8_t *)			(0x0400)	// 포트A의 시작주소를 나타내는 포인터
#define _PORTA_DIR		(PORTA)->DIR		// 포트A의 DIR을 나타냄.
#define _PORTA_DIRSET	(PORTA)->DIRSET		// 포트A의 DIRSET을 나타냄.
#define _PORTA_DIRCLR	(PORTA)->DIRCLR		// 포트A의 DIRCLR을 나타냄.
#define _PORTA_OUT		(PORTA)->OUT		// 포트A의 OUT을 나타냄.
#define _PORTA_OUTSET	(PORTA)->OUTSET		// 포트A의 OUTSET을 나타냄.
#define _PORTA_OUTCLR	(PORTA)->OUTCLR		// 포트A의 OUTCLR을 나타냄.

#define _PORTC			(uint8_t *)			(0x0440)	// 포트C의 시작주소를 나타내는 포인터
#define _PORTC_DIR		(PORTC)->DIR		// 포트C의 DIR을 나타냄.
#define _PORTC_DIRSET	(PORTC)->DIRSET		// 포트C의 DIRSET을 나타냄.
#define _PORTC_DIRCLR	(PORTC)->DIRCLR		// 포트C의 DIRCLR을 나타냄.
#define _PORTC_OUT		(PORTC)->OUT		// 포트C의 OUT을 나타냄
#define _PORTC_OUTSET	(PORTC)->OUTSET		// 포트C의 OUTSET을 나타냄.
#define _PORTC_OUTCLR	(PORTC)->OUTCLR		// 포트C의 OUTCLR을 나타냄.

#define _PORTD			(uint8_t *)			(0x0460)	// 포트D의 시작 주소를 나타내는 포인터
#define _PORTD_DIR		(PORTD)->DIR		// 포트D의 DIR을 나타냄.
#define _PORTD_DIRSET	(PORTD)->DIRSET		// 포트D의 DIRSET을 나타냄.
#define _PORTD_DIRCLR	(PORTD)->DIRCLR		// 포트D의 DIRCLR을 나타냄.
#define _PORTD_OUT		(PORTD)->OUT		// 포트D의 OUT을 나타냄
#define _PORTD_OUTSET	(PORTD)->OUTSET		// 포트D의 OUTSET을 나타냄.
#define _PORTD_OUTCLR	(PORTD)->OUTCLR		// 포트D의 OUTCLR을 나타냄.
	
#define PIN_ON(N)			(1<<N)			// 입력된 N에 해당하는 비트를 1로 설정

void LED_A(void) {			// LED_A 를 제어하는 함수.
	PORTA.OUT |= PIN_ON(7);		// PORTA.OUT 레지스터의 7번 핀을 켬
	_delay_ms(3000);			// 3초동안 대기
	PORTC.OUT &= ~PIN_ON(7);	// PORTC.OUT 레지스터의 7번 핀을 끔
	PORTD.OUT &= ~PIN_ON(7);	// PORTD.OUT 레지스터의 7번 핀을 끔
}

void LED_C(void) {
	PORTC.OUT |= PIN_ON(7);		// PORTC.OUT 레지스터의 7번 핀을 켬
	_delay_ms(3000);			// 3초동안 대기
	PORTA.OUT &= ~PIN_ON(7);	// PORTA.OUT 레지스터의 7번 핀을 끔
	PORTD.OUT &= ~PIN_ON(7);	// PORTD.OUT 레지스터의 7번 핀을 끔
}

void LED_D(void) {
	PORTD.OUT |= PIN_ON(7);		// PORTC.OUT 레지스터의 7번 핀을 켬
	_delay_ms(3000);			// 3초동안 대기
	PORTA.OUT &= ~PIN_ON(7);	// PORTA.OUT 레지스터의 7번 핀을 끔
	PORTC.OUT &= ~PIN_ON(7);	// PORTC.OUT 레지스터의 7번 핀을 끔
}


int main(void)
{
	// 포트 A,C,D 를 출력으로 설정
	PORTA.DIR = 0x80;			
	PORTC.DIR = 0x80;
	PORTD.DIR = 0x80;

	while (1)
	{
		LED_A();	// LED_A 함수 호출
		LED_D();	// LED_C 함수 호출
		LED_C();	// LED_D 함수 호출
		
	}
	
	return 0;
}
