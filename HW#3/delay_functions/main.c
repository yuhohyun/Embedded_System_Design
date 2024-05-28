#define F_CPU 3333333
#include <avr/io.h>

void delay_ms(uint16_t msec);
void delay_us(uint16_t usec);

#define _TCB0			(TCB_t *)			(0x0A80)
#define _TCB0_CTRLA		(TCB0)->CTRLA
#define _TCB0_INTFLAGS	(TCB0)->INTFLAGS
#define _TCB0_CNT		(TCB0)->CNT
#define _TCB0_CCMP		(TCB0)->CCMP

#define _PORTA			(uint8_t *)			(0x0400)
#define _PORTA_DIR		(unsigned char *)	(0x0400)
#define _PORTA_DIRSET	(unsigned char *)	(0x0401)
#define _PORTA_DIRCLR	(unsigned char *)	(0x0402)
#define _PORTA_OUT		(unsigned char *)	(0x0404)
#define _PORTA_OUTSET	(unsigned char *)	(0x0405)
#define _PORTA_OUTCLR	(unsigned char *)	(0x0406)
#define _PORTA_IN		(unsigned char *)	(0x0408)

#define PIN(N)			(1<<N)

void delay_ms(uint16_t msec) {
	// Ÿ�̸�/ī���� ��� �ʱ�ȭ
	TCB0.CTRLA = F_CPU / 64; // Ŭ�� �ҽ��� CPU Ŭ��/64�� ����
	TCB0.CNT = 0; // ī��Ʈ ���� 0���� �ʱ�ȭ
	
	// msec ��ŭ ī��Ʈ �� ����
	uint16_t count =  F_CPU * msec / 1000UL;
	TCB0.CCMP = count;

	// ī��Ʈ�� �Ϸ�� ������ ���
	while ((TCB0.INTFLAGS & TCB_CAPT_bm) == 0) {
		// do nothing
	}
	
	// ī��Ʈ �Ϸ� �� �÷��� Ŭ����
	TCB0.INTFLAGS = TCB_CAPT_bm;
}


void delay_us(uint16_t usec) {
	// Ÿ�̸�/ī���� ��� �ʱ�ȭ
	TCB0.CTRLA = F_CPU / 64; // Ŭ�� �ҽ��� CPU Ŭ������ ����
	TCB0.CNT = 0; // ī��Ʈ ���� 0���� �ʱ�ȭ
	
	// usec ��ŭ ī��Ʈ �� ����
	uint16_t count = F_CPU * usec / 1000000UL;
	TCB0.CCMP = count;

	// ī��Ʈ�� �Ϸ�� ������ ���
	while ((TCB0.INTFLAGS & TCB_CAPT_bm) == 0) {
		// do nothing
	}
	
	// ī��Ʈ �Ϸ� �� �÷��� Ŭ����
	TCB0.INTFLAGS = TCB_CAPT_bm;
}

int main(void) {
	PORTA.DIR = 0x80; 
	
	while (1) {
		PORTA.OUT |= PIN(7);
		delay_ms(1000);
		PORTA.OUT &= ~PIN(7);
		delay_ms(1000);
	}
}
