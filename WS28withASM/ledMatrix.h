
#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

class ledMatrix
{
public:
	ledMatrix();
	ledMatrix(uint16_t n, uint16_t p);
	ledMatrix(uint16_t n, uint16_t p, uint8_t *tab);
	ledMatrix(uint8_t w, uint8_t h, uint16_t p, uint8_t *tab);
	~ledMatrix();

	// Send data to the Leds
	void show();
	// Update the data table
	void updateTab(uint8_t *newTab);
	void mooveLeft();
	void mooveLeftSmooth();
	void mooveRigth();

private:
	uint8_t width;
	uint8_t heigth;
	uint16_t nPixels;
	uint16_t pin;
	uint8_t *RGB;
	
	void updateLeds(uint8_t volatile *tab, uint8_t indexByte);
	ledMatrix( const ledMatrix &c );
	ledMatrix& operator=( const ledMatrix &c );
	
}; //ledMatrix

#endif //__LEDMATRIX_H__
