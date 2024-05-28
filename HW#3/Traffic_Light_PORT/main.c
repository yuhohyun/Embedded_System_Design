#define F_CPU 3333333	// ����ũ����Ʈ�ѷ� Ŭ�� ���ļ� ����

#include <avr/io.h>
#include <util/delay.h>

#define _PORTA			(uint8_t *)			(0x0400)	// ��ƮA�� �����ּҸ� ��Ÿ���� ������
#define _PORTA_DIR		(PORTA)->DIR		// ��ƮA�� DIR�� ��Ÿ��.
#define _PORTA_DIRSET	(PORTA)->DIRSET		// ��ƮA�� DIRSET�� ��Ÿ��.
#define _PORTA_DIRCLR	(PORTA)->DIRCLR		// ��ƮA�� DIRCLR�� ��Ÿ��.
#define _PORTA_OUT		(PORTA)->OUT		// ��ƮA�� OUT�� ��Ÿ��.
#define _PORTA_OUTSET	(PORTA)->OUTSET		// ��ƮA�� OUTSET�� ��Ÿ��.
#define _PORTA_OUTCLR	(PORTA)->OUTCLR		// ��ƮA�� OUTCLR�� ��Ÿ��.

#define _PORTC			(uint8_t *)			(0x0440)	// ��ƮC�� �����ּҸ� ��Ÿ���� ������
#define _PORTC_DIR		(PORTC)->DIR		// ��ƮC�� DIR�� ��Ÿ��.
#define _PORTC_DIRSET	(PORTC)->DIRSET		// ��ƮC�� DIRSET�� ��Ÿ��.
#define _PORTC_DIRCLR	(PORTC)->DIRCLR		// ��ƮC�� DIRCLR�� ��Ÿ��.
#define _PORTC_OUT		(PORTC)->OUT		// ��ƮC�� OUT�� ��Ÿ��
#define _PORTC_OUTSET	(PORTC)->OUTSET		// ��ƮC�� OUTSET�� ��Ÿ��.
#define _PORTC_OUTCLR	(PORTC)->OUTCLR		// ��ƮC�� OUTCLR�� ��Ÿ��.

#define _PORTD			(uint8_t *)			(0x0460)	// ��ƮD�� ���� �ּҸ� ��Ÿ���� ������
#define _PORTD_DIR		(PORTD)->DIR		// ��ƮD�� DIR�� ��Ÿ��.
#define _PORTD_DIRSET	(PORTD)->DIRSET		// ��ƮD�� DIRSET�� ��Ÿ��.
#define _PORTD_DIRCLR	(PORTD)->DIRCLR		// ��ƮD�� DIRCLR�� ��Ÿ��.
#define _PORTD_OUT		(PORTD)->OUT		// ��ƮD�� OUT�� ��Ÿ��
#define _PORTD_OUTSET	(PORTD)->OUTSET		// ��ƮD�� OUTSET�� ��Ÿ��.
#define _PORTD_OUTCLR	(PORTD)->OUTCLR		// ��ƮD�� OUTCLR�� ��Ÿ��.
	
#define PIN_ON(N)			(1<<N)			// �Էµ� N�� �ش��ϴ� ��Ʈ�� 1�� ����

void LED_A(void) {			// LED_A �� �����ϴ� �Լ�.
	PORTA.OUT |= PIN_ON(7);		// PORTA.OUT ���������� 7�� ���� ��
	_delay_ms(3000);			// 3�ʵ��� ���
	PORTC.OUT &= ~PIN_ON(7);	// PORTC.OUT ���������� 7�� ���� ��
	PORTD.OUT &= ~PIN_ON(7);	// PORTD.OUT ���������� 7�� ���� ��
}

void LED_C(void) {
	PORTC.OUT |= PIN_ON(7);		// PORTC.OUT ���������� 7�� ���� ��
	_delay_ms(3000);			// 3�ʵ��� ���
	PORTA.OUT &= ~PIN_ON(7);	// PORTA.OUT ���������� 7�� ���� ��
	PORTD.OUT &= ~PIN_ON(7);	// PORTD.OUT ���������� 7�� ���� ��
}

void LED_D(void) {
	PORTD.OUT |= PIN_ON(7);		// PORTC.OUT ���������� 7�� ���� ��
	_delay_ms(3000);			// 3�ʵ��� ���
	PORTA.OUT &= ~PIN_ON(7);	// PORTA.OUT ���������� 7�� ���� ��
	PORTC.OUT &= ~PIN_ON(7);	// PORTC.OUT ���������� 7�� ���� ��
}


int main(void)
{
	// ��Ʈ A,C,D �� ������� ����
	PORTA.DIR = 0x80;			
	PORTC.DIR = 0x80;
	PORTD.DIR = 0x80;

	while (1)
	{
		LED_A();	// LED_A �Լ� ȣ��
		LED_D();	// LED_C �Լ� ȣ��
		LED_C();	// LED_D �Լ� ȣ��
		
	}
	
	return 0;
}
