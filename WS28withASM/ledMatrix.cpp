#include "ledMatrix.h"

// default constructor
ledMatrix::ledMatrix()
{
} //ledMatrix

// default destructor
ledMatrix::~ledMatrix()
{
} //~ledMatrix

ledMatrix::ledMatrix(uint16_t n, uint16_t p): nPixels(n),pin(p)
{	
}

ledMatrix::ledMatrix(uint16_t n, uint16_t p, uint8_t *tab): nPixels(n),pin(p),RGB(tab)
{
}

ledMatrix::ledMatrix(uint8_t w, uint8_t h, uint16_t p, uint8_t *tab): width(w), heigth(h), nPixels(w*h), pin(p), RGB(tab)
{
}

void ledMatrix::show(){
	updateLeds(this->RGB, 3*this->nPixels);
}

void ledMatrix::updateTab(uint8_t *newTab){
	RGB = newTab;
}

void ledMatrix::mooveLeft(){
	for(int y=0; y<heigth; y++){
		uint8_t tempR = RGB[3*(y*width)];
		uint8_t tempG = RGB[3*(y*width)+1];
		uint8_t tempB = RGB[3*(y*width)+2];
		for(int x=0; x < (width-1); x++){
			RGB[3*(x+y*width)] = RGB[3*(x+y*width+1)];
			RGB[3*(x+y*width)+1] = RGB[3*(x+y*width+1)+1];
			RGB[3*(x+y*width)+2] = RGB[3*(x+y*width+1)+2];
		}
		RGB[3*((y+1)*width-1)  ] = tempR;
		RGB[3*((y+1)*width-1)+1] = tempG;
		RGB[3*((y+1)*width-1)+2] = tempB;
	}
}


void ledMatrix::mooveRigth(){
	for(int y=0; y<heigth; y++){
		uint8_t tempR = RGB[3*((y+1)*width-1)];
		uint8_t tempG = RGB[3*((y+1)*width-1)+1];
		uint8_t tempB = RGB[3*((y+1)*width-1)+2];
		for(int x=width; x > 0; x--){
			RGB[3*(x+y*width)  ] = RGB[3*(x+y*width+1)  ];
			RGB[3*(x+y*width)+1] = RGB[3*(x+y*width+1)+1];
			RGB[3*(x+y*width)+2] = RGB[3*(x+y*width+1)+2];
		}
		RGB[3*((y+1)*width-1)  ] = tempR;
		RGB[3*((y+1)*width-1)+1] = tempG;
		RGB[3*((y+1)*width-1)+2] = tempB;
	}
}

void ledMatrix::mooveLeftSmooth(){
	for(int y=0; y<heigth; y++){
		uint8_t tempR = RGB[3*y*width];
		for(int x=0; x < 3*width - 1 ; x++){
			RGB[3*y*width +x] = RGB[3*y*width +x +1];
		}
		RGB[3*((y+1)*width-1)] = tempR;
	}
}

void ledMatrix::updateLeds(uint8_t volatile *tab, uint8_t indexByte){
	// sent as R G B
	//volatile uint8_t port = PORTB; // Have to find a way to put it in the inline asm
	//volatile uint8_t pin = 0;      // SBI/CBI only take constant as second operand so it's not trivial to choose the pin at runtime
	
	cli(); // Prevent any interruption
	
	uint8_t indexBit = 8;

	// Comments on the right of each asm line are :
	//[Nb clk cycles for this line] - [Total number of clock cycle since first bit sent, after the instruction]
	
	asm volatile(
	"ld __tmp_reg__,%a[tab]+" "\n\t" // load first byte in r0						//2
	
	"nextBit:"
	"nop"					"\n\t"								//1		(16)
	"nop"					"\n\t"								//1		(17)
	"nop"					"\n\t"								//1		(18)
	"nop"					"\n\t"								//1		(19)
	"nop"					"\n\t"								//1		(20)	
	// Start of the loop
	"nextBit0:"
	"SBI %[port],7"			"\n\t"	// Set the pin HIGH						//1-2		(1) (This takes 1 or 2 cycles, not clear why. Let say it's really one)
	"LSL __tmp_reg__"		"\n\t"	// load High bit in C flag					//1 		(2)
	"BRCS one"			"\n\t"	// If Carry set then branch to one 				//1-2		(3 or 4 if branch)
		
	// Else sent zero without branch
	// ZERO CODE - start at 3 clock cycle high (need 6 to send a zero))							(3)
	"nop"					"\n\t"								//1		(4)
	"nop"					"\n\t"								//1		(5)
	"nop"					"\n\t"								//1		(6)
	"CBI %[port],7"			"\n\t"	//clear pin							//2(really 2)   (7)
	"nop"					"\n\t"								//1		(8)
	"nop"					"\n\t"								//1		(9)
	"nop"					"\n\t"								//2		(10)
	"nop"					"\n\t"								//1		(11)
	"dec %[indexBit]"		"\t\n"	//decrement compteurBit	   					//1		(12)
	"BRNE nextBit"			"\n\t"	//nextbit or nextByte						//1-2		(14 si branch)
	"RJMP loadByte"			"\n\t"									//2		(15)
	

	// ONE code after branch - start at 4 clock high (need 12)								(4)
	"one:"
	"nop"					"\n\t"								//1		(5)
	"nop"					"\n\t"								//1		(6)
	"nop"					"\n\t"								//1		(7)
	"nop"					"\n\t"								//1		(8)
	"nop"					"\n\t"								//1		(9)
	"nop"					"\n\t"								//1		(10)
	"dec %[indexBit]"		"\n\t"	//decremente compteurBit					//1		(11)
	"CBI %[port],7"			"\n\t"									//2		(13)
	"BRNE nextBit"			"\n\t"	//Branch if indexBit<8						//1-2		(15)
	"nop"				"\n\t"									//1		(15)
	
	"loadByte:"
	"ld __tmp_reg__,%a[tab]+" "\n\t"	// load byte in r0						//2		(17)
	"ldi %[indexBit],8"		  "\n\t"	// indexBit = 7						//1		(18)
	"dec %[indexByte]"		  "\n\t"	// indexByte--						//1		(19)
	"BRNE nextBit0"					//Branch if indexByte!=0	 			//2		(21)
	://output
	://input :
	[tab] "e" (tab),
	[indexBit] "d" (indexBit),
	[port] "I" (_SFR_IO_ADDR(PORTD)),
	[indexByte] "d" (indexByte)
	://clobbered (none as we use temp_reg for data)
	);
	
	sei(); // enable interruptions
}
