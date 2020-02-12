
#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

class ledMatrix
{
//variables
public:
protected:
private:
	uint8_t width;
	uint8_t heigth;
	uint16_t nPixels;
	uint16_t pin;
	uint8_t *RGB;
	
//functions
public:
	ledMatrix();
	ledMatrix(uint16_t n, uint16_t p);
	ledMatrix(uint16_t n, uint16_t p, uint8_t *tab);
	ledMatrix(uint8_t w, uint8_t h, uint16_t p, uint8_t *tab);
	~ledMatrix();

	void show();
	void updateTab(uint8_t *newTab);
	void mooveLeft();
	void mooveLeftSmooth();
	void mooveRigth();
	
protected:
private:
	void updateLeds(uint8_t volatile *tab, uint8_t indexByte);
	ledMatrix( const ledMatrix &c );
	ledMatrix& operator=( const ledMatrix &c );

}; //ledMatrix

#endif //__LEDMATRIX_H__
