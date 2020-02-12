/*
 * WS28withASM.cpp
 *
 * Created: 10/11/2019 20:02:16
 * Author : Delaite
 */ 


#define F_CPU 16000000

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "ledMatrix.h"

#define lum 10

#define R 50,0,0
#define G 0,50,0
#define B 0,0,50
#define F 0x0A,0x0A,0x0A
#define W lum,lum,lum
#define b W
#define a W
#define z 0,0,0

	uint8_t fleche[]={
		z,z,z,z,a,z,z,z,
		z,z,z,z,a,a,z,z,
		z,z,z,z,a,a,a,z,
		b,b,a,a,a,a,a,a,
		a,a,a,a,a,a,a,a,
		z,z,z,z,a,a,a,z,
		z,z,z,z,a,a,z,z,
		z,z,z,z,a,z,z,z
	};
	uint8_t tab[] = {
		F,z,z,z,b,z,z,z,
		z,z,z,b,z,b,z,z,
		z,z,z,b,b,b,z,z,
		z,z,z,b,z,b,z,z,
		z,z,z,b,z,b,z,z,
		z,z,z,b,z,b,z,z,
		z,z,z,b,z,b,z,z,
		z,z,b,b,b,b,b,F
	};
	uint8_t tab2[] = {
		F,z,z,z,b,z,z,z,
		z,z,z,b,z,b,z,z,
		z,z,z,b,b,b,z,z,
		z,z,z,b,z,b,z,z,
		z,z,z,b,z,b,z,z,
		z,z,z,b,z,b,z,z,
		z,z,b,b,b,b,b,z,
		z,z,z,z,z,z,z,F
	};
	uint8_t tab3[] = {
		z,z,z,b,z,z,z,z,
		z,z,z,b,z,z,z,z,
		z,z,z,b,z,z,z,z,
		z,z,z,b,z,z,z,z,
		z,z,z,b,z,z,z,z,
		z,z,z,b,z,z,z,z,
		z,z,z,b,z,z,z,z,
		z,z,z,b,z,z,z,z
	};			
	
	 
int main(void)
{
	DDRD |= 0b10000001;
	
	uint8_t heigth(8);
	uint8_t width(8);
	uint8_t *RGB = fleche;
	
	ledMatrix ledMat(heigth,width,0,RGB);
	ledMat.show();

	while(1){
		//_delay_ms(200);
		ledMat.mooveLeftSmooth();
		ledMat.show();
	}
	return 0;
}