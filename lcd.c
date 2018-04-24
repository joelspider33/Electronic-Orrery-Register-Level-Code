/*----------------------------------------------------------------------------
 * Name:    lcd.c
 * Purpose: Display Interface Driver
 *----------------------------------------------------------------------------
 * Author: 	Joel W Webb
 * Date: 		17/01/2017
 *----------------------------------------------------------------------------*/
 
#include "MK64F12.h"
#include "Math.h"
#include "stdint.h"
#include "stdlib.h"
#include "lcd.h"
#include "Main.h"


// GLOBAL VARIABLES
COORD pos; 									// Described with origin at top left of display
COORD calibReported[3];			// A set of 3 coords representing read value of 3 points on the touchscreen
COORD calibTrue[3];					// A set of 3 coords representing what calibReported should have been in perfect case
COORD calibBlank[3] = {{100,100,0},{900,500,0},{500,900,0}};				// A set of 3 coords that provides setCalibrationMatrix with a Unity matrix
Calibration_Matrix matrix;	// Calibration matrix for resistive touchscreen

int height = 320; // Globals representing size of display, changes with orientation
int width = 240;


// ################  RESISTIVE TOUCHSCREEN FUNCTIONS  ################

void enableTouchInterrupt(void){

	/* 	PTB10 as Digital Output 0
			PTB11 as Digital Input
			PTC10 as Digital Input Pull up w/ interrupt falling edge
			PTC11 as Digital Input
	*/
	
	PORTB_PCR10 = 0x140;	// PTB10 as GPIO, High Drive strength
  PORTB_PCR11 = 0x100;	// PTB11 as GPIO
	PORTC_PCR10 = 0x103;	// PTC10 as GPIO Pull up "interrupt falling edge configured last"
	PORTC_PCR11	=	0x100;	// PTC11 as GPIO Input
	
	GPIOB_PDDR |= 0x400;	// PTB10 as Output
  GPIOB_PDDR &= ~0x800;	// PTB11 as Input
	GPIOC_PDDR &= ~0x400;	// PTC10 as Input
	GPIOC_PDDR &= ~0x800;	// PTC11 as Input
	
	GPIOB_PDOR &= ~0x400;	// PTB10 Outputs 0V
	
	PORTC_PCR10 = 0xA0103;// PTC10 interrupt Falling Edge
}

void disableTouchInterrupt(void){
	
	// Reset Touch Controller Pins to default
	PORTB_PCR10 = 0;
	PORTB_PCR11 = 0;
	PORTC_PCR10 = 0;
	PORTC_PCR11 = 0;
	GPIOB_PDDR &= ~0x400;	// PTB10 as Input
  GPIOB_PDDR &= ~0x800;	// PTB11 as Input
	GPIOC_PDDR &= ~0x400;	// PTC10 as Input
	GPIOC_PDDR &= ~0x800;	// PTC11 as Input
	
}

void readX(void){
	PORTB_PCR10 = 0x100;	// PTB10 as GPIO
  PORTB_PCR11 = 0x140;	// PTB11 as GPIO, High drive strength
	PORTC_PCR10 = 0x140;	// PTC10 as GPIO, High drive strength
	PORTC_PCR11	=	0x000;	// PTC11 as Analogue
	
	GPIOB_PDDR &= ~0x400;	// PTB10 as Input
  GPIOB_PDDR |= 0x800;	// PTB11 as Output
	GPIOC_PDDR |= 0x400;	// PTC10 as Output
	GPIOC_PDDR &= ~0x800;	// PTC11 as Input
	
	GPIOB_PDOR &= ~0x800;	// PTB11 Outputs 0V
	GPIOC_PDOR |= 0x400;	// PTC10 Outputs 3.3V
	
	// Using ADC 1
	ADC1_SC1A = 0x7 & ADC_SC1_ADCH_MASK; 				// Write to SC1A to start conversion: Input - AD7b (PTC11)
	while(ADC1_SC2 & ADC_SC2_ADACT_MASK); 			// Conversion in progress
	while(!(ADC1_SC1A & ADC_SC1_COCO_MASK)); 		// Wait until conversion complete
	pos.x = ADC1_RA;														// Gives result between 0<x<1024 (10-bit ADC)
}

void readY(void){
	PORTB_PCR10 = 0x100;	// PTB10 as GPIO, High drive strength
  PORTB_PCR11 = 0x100;	// PTB11 as GPIO
	PORTC_PCR10 = 0x000;	// PTC10 as Analogue
	PORTC_PCR11	=	0x100;	// PTC11 as GPIO, High drive strength
	
	GPIOB_PDDR |= 0x400;	// PTB10 as Output
  GPIOB_PDDR &= ~0x800;	// PTB11 as Input
	GPIOC_PDDR &= ~0x400;	// PTC10 as Input
	GPIOC_PDDR |= 0x800;	// PTC11 as Output
	
	GPIOB_PDOR &= ~0x400;	// PTB10 Outputs 0V
	GPIOC_PDOR |= 0x800;	// PTC11 Outputs 3.3V
	
	// Using ADC 1
	ADC1_SC1A = 0x6 & ADC_SC1_ADCH_MASK; 				// Write to SC1A to start conversion: Input - AD6b (PTC10)
	while(ADC1_SC2 & ADC_SC2_ADACT_MASK); 			// Conversion in progress
	while(!(ADC1_SC1A & ADC_SC1_COCO_MASK)); 		// Wait until conversion complete
	pos.y = ADC1_RA;														// Gives result between 0<y<1024 (10-bit ADC)
}

void PORTC_IRQHandler(void){
	if(!(GPIOC_PDIR & 0x400) && pos.flag==0 ){	// Skips if unhandled Touch Event is detected or interrupt triggered wrongly
		wait_ms(10);								// Debounce touch
		readX();										// Read X position of touch
		readY();										// Read Y position of touch
		enableTouchInterrupt();			// Re-enable the interrupt
		pos.flag = 1;								// Set touch flag
		pos = applyCalib();
	}
	PORTC_ISFR = 0x400;	// Clear the interrupt flag
}

// ########## Touchscreen Calibration ##########

void setCalibrationMatrix(void){
    matrix.Divider = ((calibReported[0].x - calibReported[2].x) * (calibReported[1].y - calibReported[2].y)) - 
                     ((calibReported[1].x - calibReported[2].x) * (calibReported[0].y - calibReported[2].y)) ;

		matrix.An = ((calibTrue[0].x - calibTrue[2].x) * (calibReported[1].y - calibReported[2].y)) - 
								((calibTrue[1].x - calibTrue[2].x) * (calibReported[0].y - calibReported[2].y)) ;

		matrix.Bn = ((calibReported[0].x - calibReported[2].x) * (calibTrue[1].x - calibTrue[2].x)) - 
								((calibTrue[0].x - calibTrue[2].x) * (calibReported[1].x - calibReported[2].x)) ;

		matrix.Cn = (calibReported[2].x * calibTrue[1].x - calibReported[1].x * calibTrue[2].x) * calibReported[0].y +
								(calibReported[0].x * calibTrue[2].x - calibReported[2].x * calibTrue[0].x) * calibReported[1].y +
								(calibReported[1].x * calibTrue[0].x - calibReported[0].x * calibTrue[1].x) * calibReported[2].y ;

		matrix.Dn = ((calibTrue[0].y - calibTrue[2].y) * (calibReported[1].y - calibReported[2].y)) - 
								((calibTrue[1].y - calibTrue[2].y) * (calibReported[0].y - calibReported[2].y)) ;

		matrix.En = ((calibReported[0].x - calibReported[2].x) * (calibTrue[1].y - calibTrue[2].y)) - 
								((calibTrue[0].y - calibTrue[2].y) * (calibReported[1].x - calibReported[2].x)) ;

		matrix.Fn = (calibReported[2].x * calibTrue[1].y - calibReported[1].x * calibTrue[2].y) * calibReported[0].y +
								(calibReported[0].x * calibTrue[2].y - calibReported[2].x * calibTrue[0].y) * calibReported[1].y +
								(calibReported[1].x * calibTrue[0].y - calibReported[0].x * calibTrue[1].y) * calibReported[2].y ;
}

void resetCalibrationMatrix(void){
		matrix.Divider = ((calibBlank[0].x - calibBlank[2].x) * (calibBlank[1].y - calibBlank[2].y)) - 
                     ((calibBlank[1].x - calibBlank[2].x) * (calibBlank[0].y - calibBlank[2].y)) ;

		matrix.An = ((calibBlank[0].x - calibBlank[2].x) * (calibBlank[1].y - calibBlank[2].y)) - 
								((calibBlank[1].x - calibBlank[2].x) * (calibBlank[0].y - calibBlank[2].y)) ;

		matrix.Bn = ((calibBlank[0].x - calibBlank[2].x) * (calibBlank[1].x - calibBlank[2].x)) - 
								((calibBlank[0].x - calibBlank[2].x) * (calibBlank[1].x - calibBlank[2].x)) ;

		matrix.Cn = (calibBlank[2].x * calibBlank[1].x - calibBlank[1].x * calibBlank[2].x) * calibBlank[0].y +
								(calibBlank[0].x * calibBlank[2].x - calibBlank[2].x * calibBlank[0].x) * calibBlank[1].y +
								(calibBlank[1].x * calibBlank[0].x - calibBlank[0].x * calibBlank[1].x) * calibBlank[2].y ;

		matrix.Dn = ((calibBlank[0].y - calibBlank[2].y) * (calibBlank[1].y - calibBlank[2].y)) - 
								((calibBlank[1].y - calibBlank[2].y) * (calibBlank[0].y - calibBlank[2].y)) ;

		matrix.En = ((calibBlank[0].x - calibBlank[2].x) * (calibBlank[1].y - calibBlank[2].y)) - 
								((calibBlank[0].y - calibBlank[2].y) * (calibBlank[1].x - calibBlank[2].x)) ;

		matrix.Fn = (calibBlank[2].x * calibBlank[1].y - calibBlank[1].x * calibBlank[2].y) * calibBlank[0].y +
								(calibBlank[0].x * calibBlank[2].y - calibBlank[2].x * calibBlank[0].y) * calibBlank[1].y +
								(calibBlank[1].x * calibBlank[0].y - calibBlank[0].x * calibBlank[1].y) * calibBlank[2].y ;
}

COORD applyCalib(void){
		COORD temp;
		temp.x = ( (matrix.An * pos.x) + (matrix.Bn * pos.y) + matrix.Cn) / matrix.Divider ;
		temp.y = ( (matrix.Dn * pos.x) + (matrix.En * pos.y) + matrix.Fn) / matrix.Divider ;
		temp.flag = pos.flag;
		return temp;
}

void calibration(void){
	resetCalibrationMatrix();
	lcdDrawCircle(36,48,5,Green,1);
	while(pos.flag==0){}
	calibTrue[0].x = 36;
	calibTrue[0].y = 48;
	calibReported[0].x = pos.x;
	calibReported[0].y = pos.y;
	pos.flag = 0;
	lcdDrawCircle(36,48,5,White,1);
	lcdDrawCircle(204,160,5,Green,1);
	while(pos.flag==0){}
	calibTrue[1].x = 204;
	calibTrue[1].y = 160;
	calibReported[1].x = pos.x;
	calibReported[1].y = pos.y;
	pos.flag = 0;
	lcdDrawCircle(204,160,5,White,1);
	lcdDrawCircle(120,272,5,Green,1);
	while(pos.flag==0){}
	calibTrue[2].x = 120;
	calibTrue[2].y = 272;
	calibReported[2].x = pos.x;
	calibReported[2].y = pos.y;
	pos.flag = 0;
	lcdDrawCircle(120,272,5,White,1);
	setCalibrationMatrix();
}



// ################  LCD FUNTIONS  ################

// SPI configuration
	/*	SPI INTERFACE CONFIGURATION
	Module Configuration Register - SPIO_MCR:
	BIT		VALUE		MEANING
	31		1				Master Mode
	30		0				Continuous Clock disabled
	29:28	00			SPI configuration
	27		0				Do not halt serial transfers in Debug mode
	26		0				Modified Timing Format Disabled
	25		0				PCS5 is chip select and not strobe signal
	24		0				FIFO Overflow data is ignored and not overwritten
	23:22	RESERVED
	21:16	000001	PCS0 is active low (Peripheral chip select 0)
	15		0				Doze mode disabled
	14		0				Not power saving mode
	13		1				Disable TX FIFO
	12		1				Disable RX FIFO
	11		0				Do not clear TX FIFO
	10		0				Do not clear RX FIFO
	9:8		00			Not modified Transfer format
	7:1		RESERVED
	0			0				Do not halt transfers
	
	Clock and Transfer Attributes Register - SPI0_CTAR0:
	BIT		VALUE		MEANING
	31		0				Not doubled data rate
	30:27	1000		9 Bits per frame (Value+1)
	26		0				Inactive state of SCK is low
	25		0				Data is captured on leading edge of SCK and changed on following edge
	24		0				MSB first
	23:22	00			PCS to SCK Delay Prescaler (1)
	21:20	00			SCK to PCS off Delay Prescaler (1)
	19:18	00			PCS off to PCS on Delay Prescaler (1)
	17:16	01			Baud Rate Prescaler (3)
	15:12	0001		PCS to SCK Delay Scaler (4)
	11:8	0001		SCK to PCS off Delay Scaler (4)
	7:4		0001		PCS off to PCS on Delay Scaler (4)
	3:0		0000		Baud Rate Scaler (2)
	*/
	
	
// Reset and Initialisation code taken from MI0283QT datasheet
void lcdReset(void){
		
	// Hardware Reset
	GPIOC_PDOR |= 0x10;		// Set Reset High
	wait_us(15);
	GPIOC_PDOR &=	~0x10;	// Set Reset Low (Begin Reset)
	wait_us(50);	// Timing sheet states more than 5us
	GPIOC_PDOR |= 0x10;		// Set Reset High
	wait_ms(125);	// Timing sheet states 120ms in sleep out mode reset
	
	// Software Reset
	lcdcmd(0x01);		// Software reset command
	wait_ms(5);
	lcdcmd(0x28);		// Turn Display off for configuration
	
	// Configuring
	lcdcmd(0xCF);		// Power Control B
  lcddat(0x00);
  lcddat(0x83);
  lcddat(0x30);
     
  lcdcmd(0xED);		// Power on sequence control
  lcddat(0x64);
  lcddat(0x03);
  lcddat(0x12);
  lcddat(0x81);
     
  lcdcmd(0xE8);		// Driver Timing control A
  lcddat(0x85);
  lcddat(0x01);
  lcddat(0x79);
  
  lcdcmd(0xCB);		// Power Control A
  lcddat(0x39);
  lcddat(0x2C);
  lcddat(0x00);
  lcddat(0x34);
  lcddat(0x02);
            
  lcdcmd(0xF7);		// Pump ratio control
  lcddat(0x20);
            
  lcdcmd(0xEA);		// Driver timing control B
  lcddat(0x00);
  lcddat(0x00);
  
	lcdcmd(0xC0);		// Power Control 1
	lcddat(0x26);
	
	lcdcmd(0xC1);		// Power Control 2
  lcddat(0x11);

	lcdcmd(0xC5);		// VCOM Control 1 
	lcddat(0x35);
	lcddat(0x3E);
	
	lcdcmd(0xC7);		// VCOM Control 2
  lcddat(0xBE);

	lcdcmd(0x36);		// Memory Access Control
	lcddat(0x48);
	
	lcdcmd(0x3A);		// Pixel format set  
  lcddat(0x55);		// 16 bit/pixel  

	lcdcmd(0xB1);		// Frame Control  
	lcddat(0x00);
	lcddat(0x1B);		// Default 70Hz
           
	lcdcmd(0xF2);		// 3 Gamma Function Disable  
	lcddat(0x08); 
	
	lcdcmd(0x26);		// Gamma set
	lcddat(0x01);		// Gamma set 4 gamma curve 01/02/04/08

	lcdcmd(0xE0);		// Positive gamma correction  
	lcddat(0x1F);
	lcddat(0x1A);
	lcddat(0x18);
	lcddat(0x0A);
	lcddat(0x0F);
	lcddat(0x06);
	lcddat(0x45);
	lcddat(0x87);
	lcddat(0x32);
	lcddat(0x0A);
	lcddat(0x07);
	lcddat(0x02);
	lcddat(0x07);
	lcddat(0x05);
	lcddat(0x00);
	
	lcdcmd(0xE1);		// Negamma gamma correction  
	lcddat(0x00);
	lcddat(0x25);
	lcddat(0x27);
	lcddat(0x05);
	lcddat(0x10);
	lcddat(0x09);
	lcddat(0x3A);
	lcddat(0x78);
	lcddat(0x4D);
	lcddat(0x05);
	lcddat(0x18);
	lcddat(0x0D);
	lcddat(0x38);
	lcddat(0x3A);
	lcddat(0x1F);
	
	lcdcmd(0x2A);		// Column set  
	lcddat(0x00);
	lcddat(0x00);
	lcddat(0x00);
	lcddat(0xEF);
	
	lcdcmd(0x2B);		// Page address set  
	lcddat(0x00);
	lcddat(0x00);
	lcddat(0x01);
	lcddat(0x3F);
	
	// lcdcmd(0x34);		//  Tearing effect off
	// lcdcmd(0x35);		//  Tearing effect on
	// lcdcmd(0xB4);		//  Display inversion
	// lcddat(0x00);
	
	lcdcmd(0xB7);		// Entry mode set
	lcddat(0x07);  

	lcdcmd(0xB6);		// Display function control
	lcddat(0x0A);
	lcddat(0x82);
	lcddat(0x27);
	lcddat(0x00);
	
	lcdcmd(0x11);		// Sleep out
	wait_ms(100);
	lcdcmd(0x29);		// Display on      
	wait_ms(100);	
	
	lcdSetOrientation(0);
	lcdClear();
	calibration();
}


void lcdcmd(int32_t cmd){
	SPI0_SR = 0x9A0A0000;										// Clear all Status Flags
	SPI0_PUSHR = 0x8010000 | (cmd&0xFF);							// D/CX = 0 for command, Frame is 9 bits long (CTAR0)
	while (!(SPI0_SR & SPI_SR_TCF_MASK)){}	// While transfer is incomplete loop
	SPI0_SR |= SPI_SR_TCF_MASK;							// Clear transfer flag once completed
}


void lcddat(int32_t data){
	SPI0_SR = 0x9A0A0000;										// Clear all Status Flags
	SPI0_PUSHR = 0x8010100 | (data&0xFF);					// D/CX = 1 for data, Frame is 9 bits long (CTAR0)
	while (!(SPI0_SR & SPI_SR_TCF_MASK)){}	// While transfer is incomplete loop
	SPI0_SR |= SPI_SR_TCF_MASK;							// Clear transfer flag once completed
}

int8_t lcdRead8(int32_t cmd){
	SPI0_SR = 0x9A0A0000;										// Clear all Status Flags
	SPI0_PUSHR = 0x80010000 | cmd; 					// Continuous Chip enable for read, D/CX = 0 for command, Frame is 9 bits long (CTAR0)
	while (!(SPI0_SR & SPI_SR_RFDF_MASK)){}	// While transfer is incomplete loop
	SPI0_POPR;															// Dummy read
	SPI0_SR |= SPI_SR_RFDF_MASK;						// Clear reception flag once completed
	SPI0_PUSHR = 0x800100FF;								// Dummy write so LCD has clock to write on
	while (!(SPI0_SR & SPI_SR_RFDF_MASK)){}	// Wait for data to be transfered
	int8_t r = (SPI0_POPR>>1);							// 9 bits are expected but only the first 8 have data hence >>1
	SPI0_SR |= SPI_SR_RFDF_MASK;						// Clear reception flag
	return r;
}

int32_t lcdRead32(int32_t cmd){
	int32_t r = 0x00000000;
	SPI0_MCR |= SPI_MCR_HALT_MASK;					// Disable the module while configuring
	SPI0_CTAR0 = 0x78011110;								// Change CTAR0 for 16-bit frame to receive data in two chunks
	SPI0_SR = 0x9A0A0000;										// Clear all Status Flags
	SPI0_MCR &= ~SPI_MCR_HALT_MASK;					// Enable the module after configuring
	SPI0_PUSHR = 0x90010000 | (cmd<<1);			// Continuous CS enabled for read, D/CX = 0 for command, Frame is 10 bits long (for dummy cycle) (CTAR1)
	while (!(SPI0_SR & SPI_SR_RFDF_MASK)){}	// While transfer is incomplete loop
	SPI0_POPR;															// Dummy read
	SPI0_SR |= SPI_SR_RFDF_MASK;						// Clear reception flag once completed
	SPI0_PUSHR = 0x8001FFFF;								// Dummy write so LCD has clock to write on (CTAR0)
	while (!(SPI0_SR & SPI_SR_RFDF_MASK)){}	// Wait for data to be transfered
	r = SPI0_POPR << 16;										// Read first 16bits (MSB first)
	SPI0_SR |= SPI_SR_RFDF_MASK;						// Clear reception flag
	wait_clock(100);
	SPI0_PUSHR = 0x0001FFFF;								// Dummy write so LCD has clock to write on (CTAR0)
	while (!(SPI0_SR & SPI_SR_RFDF_MASK)){}	// Wait for data to be transfered
	r |= SPI0_POPR;													// Read last 16bits
	SPI0_SR |= SPI_SR_RFDF_MASK;						// Clear reception flag
	SPI0_MCR |= SPI_MCR_HALT_MASK;					// Disable the module while configuring
	SPI0_CTAR0 = 0x40011110;								// Change CTAR0 back to 9-bit frame
	SPI0_MCR &= ~SPI_MCR_HALT_MASK;					// Enable the module while configuring
	return r;
}

void lcdSetOrientation(int a){
    lcdcmd(0x36);						// Memory Access Control Register
		switch (a) {
        case 0:
            lcddat(0x48);		// Default
						width = 240;
						height = 320;
            break;
        case 1:
            lcddat(0x28);		// Default rotated anti-clockwise 90°
						width = 320;
						height = 240;
            break;
        case 2:
            lcddat(0x88);		// Default rotated 180°
						width = 240;
						height = 320;
            break;
        case 3:
            lcddat(0xE8);		// Default rotated anti-clockwise 270° 
						width = 320;
						height = 240;
            break;
    }
}

// Function used to set writable area of LCD memory
void lcdSetMem(int x, int y, int w, int h){
	// 0 < x < 239
	// 0 < y < 319
	// 1 < w < 240
	// 1 < h < 320
	/*
		   x x+w-1
			 |  |
		   V  V
		----------
		|	 |--|	 |<--y
		|	 |**|	 |
		|	 |--|	 |<--y+h-1
		|				 |
	  ----------
	
	** = writable memory in sequence
	*/
	lcdcmd(0x2A);		// Set column addresses
	lcddat(x>>8);
	lcddat(x&0xFF);
	lcddat((x+w-1)>>8);
	lcddat((x+w-1)&0xFF);
	
	lcdcmd(0x2B);		// Set page/row addresses
	lcddat(y>>8);
	lcddat(y&0xFF);
	lcddat((y+h-1)>>8);
	lcddat((y+h-1)&0xFF);
}

void lcdClear(void){
	lcdDrawRect(0,0,width-1,height-1,White,1);
}

void lcdSetPixel(int x,int y,int colour){
	lcdSetMem(x,y,1,1);
	lcdcmd(0x2C);
	lcddat(colour>>8);
	lcddat(colour&0xFF);
}

void lcdDrawLine(int x0, int y0, int x1, int y1, int colour){
	
	// Vertical Line
	if(x0==x1){
		int h;
		if(y0>y1){
			h=y0;
			y0=y1;
			y1=h;
		}
		h = y1-y0+1;
		lcdSetMem(x0,y0,1,h);
		for(int y=y0; y<(h+y0); y++){
			lcdSetPixel(x0,y,colour);
		}
	}
	
	// Horizontal Line
	else if(y0==y1){
		int w;
		if(x0>x1){
			w=x0;
			x0=x1;
			x1=w;
		}
		w = x1-x0+1;
		lcdSetMem(x0,y0,w,1);
		for(int x=x0; x<(w+x0); x++){
			lcdSetPixel(x,y0,colour);
		}
	}
	
	// Diagonal Line
	// Using Bresenham's line algorithm for simplicity
	else{
		if (abs(y1 - y0) < abs(x1 - x0)){
			if (x0 > x1){
				plotLineLow(x1, y1, x0, y0, colour);
			}else{
				plotLineLow(x0, y0, x1, y1, colour);
			}
		}else{
			if (y0 > y1){
				plotLineHigh(x1, y1, x0, y0, colour);
			}else{
				plotLineHigh(x0, y0, x1, y1, colour);
			}
		}
		
	}
}

void plotLineLow(int x0, int y0, int x1, int y1, int colour){
	int dx,dy,x,y,yi,D;
	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;
	if (dy < 0){
		yi = -1;
		dy = -dy;
	}
	D = 2*dy - dx;
	y = y0;
	for (x=x0; x<(x1+1); x++){
		lcdSetPixel(x,y,colour);
		if (D > 0){
			y = y + yi;
			D = D - 2*dx;
		}
		D = D + 2*dy;
	}
}

void plotLineHigh(int x0, int y0, int x1, int y1, int colour){
	int dx,dy,x,y,xi,D;
	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;
	if (dx < 0){
		xi = -1;
		dx = -dx;
	}
	D = 2*dx - dy;
	x = x0;
	for (y=y0; y<(y1+1); y++){
		lcdSetPixel(x,y,colour);
		if (D > 0){
			x = x + xi;
			D = D - 2*dy;
		}
		D = D + 2*dy;
	}
}


void lcdDrawRect(int x0, int y0, int x1, int y1, int colour, int fill){
	
	int h,w;
	if(x0>x1){	// Setup so x1>x0 and y1>y0
		h=x0;
		x0=x1;
		x1=h;
	}
	if(y0>y1){
		h=y0;
		y0=y1;
		y1=h;
	}
	
	if(fill){		// If fill is selected then all pixels within box are drawn
		h = y1 - y0 + 1;
    w = x1 - x0 + 1;
    lcdSetMem(x0,y0,w,h);
    lcdcmd(0x2C);
    for (int a=0; a<(w*h); a++) {
        lcddat(colour >> 8);
        lcddat(colour & 0xFF);
    }
	} else{			// If fill is 0 the just outside box is drawn
		lcdDrawLine(x0,y0,x1,y0,colour);
		lcdDrawLine(x0,y0,x0,y1,colour);
		lcdDrawLine(x1,y0,x1,y1,colour);
		lcdDrawLine(x0,y1,x1,y1,colour);
	}
}

void lcdDrawCircle(int x0,int y0,int r,int colour,int fill){
		int x = r-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (r << 1);

    while (x >= y)
    {
			if(fill){
				lcdDrawLine(x0+x,y0+y,x0-x,y0+y, colour);
				lcdDrawLine(x0+x,y0-y,x0-x,y0-y, colour);
				lcdDrawLine(x0+y,y0+x,x0+y,y0-x, colour);
				lcdDrawLine(x0-y,y0+x,x0-y,y0-x, colour);
			} else{
        lcdSetPixel(x0 + x, y0 + y, colour);	// First Octant
        lcdSetPixel(x0 + y, y0 + x, colour);	// Mirrored Octants
        lcdSetPixel(x0 - y, y0 + x, colour);
        lcdSetPixel(x0 - x, y0 + y, colour);
        lcdSetPixel(x0 - x, y0 - y, colour);
        lcdSetPixel(x0 - y, y0 - x, colour);
        lcdSetPixel(x0 + y, y0 - x, colour);
        lcdSetPixel(x0 + x, y0 - y, colour);
			}
        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        else
        {
            x--;
            dx += 2;
            err += dx - (r << 1);
        }
    }
}


void lcdPrintString(int x, int y, char *string, const FONT_INFO* font, int colour){
	uint8_t i = 0;												// String index
	while(string[i]!='\0'){								// Loops until null character (end of string) is detected
		if(string[i] == 0x20){							// If space character then proceed number of spaces
			x+=font->spacePixels;							// Proceeds number of space pixels
			i++;
		}else{
			lcdPrintChar(x, y, string[i] ,colour, font);			// Print character function
			x+=(font->charInfo[(string[i]-'!')].widthBits)+1;	// Proceed x by width+1 pixels
			i++;																							// Next character
		}
	}
}

void lcdPrintChar(int x, int y, char c, int colour, const FONT_INFO* font){
	uint16_t offset = font->charInfo[c-'!'].offset;									// Get offset from font chracter info array
	uint8_t widthBytes = (int)((font->charInfo[c-'!'].widthBits-1)/8)+1;	// Find # of bytes in character
	for(uint8_t i=0; i<font->heightBits; i++){											// Loop from top to bottom of bitmap
		for(uint8_t j=0; j<font->charInfo[c-'!'].widthBits; j++){			// Loop from left to right of bitmap
			if( ( font->data[offset+(int)(j/8)+(i*widthBytes)]<<(j%8) ) & 0x80 ){		// If bitmap bit set then set pixel
				lcdSetPixel(x+j,y+i,colour);
			}
		}
	}
}






