/*----------------------------------------------------------------------------
 * Name:    Main.c
 * Purpose: Computation and User Interface main c file
 *----------------------------------------------------------------------------
 * Author: 	Joel W Webb
 * Date: 		20/12/2017
 *----------------------------------------------------------------------------*/

#include "MK64F12.h"
#include "Math.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "lcd.h"
#include "Main.h"
#include "Planetary_Positioning.h"

// DEFINES
#define MechAddr 			0x12
#define InternetAddr 	0x14
#define CompUIAddr 		0x16

// Function Pointer to Draw States
void (*Menu[]) (void) =	{
	Menu_StartScreen,				// 0
	Menu_SelectDate,				// 1
	Menu_EngineeringMode,		// 2
	Menu_WifiSettings,			// 3
	Menu_Settings,					// 4
	Menu_ChangeDate,				// 5
	Menu_ChangeAngle				// 6
};

// Delay functions
void wait_clock(int x){
	PIT_LDVAL0 = x;		// Set timer value
	PIT_TCTRL0 = 0x1;	// Enable Timer
	while(!(PIT_TFLG0)){}
	PIT_TFLG0 = 0x1;	// Clear Timout flag
	PIT_TCTRL0 = 0x0;	// Disable Timer
}
void wait_ms(int t){
	int x = t*60E3;	// PIT Timers run at 60MHz bus 
	wait_clock(x);
}
void wait_us(int t){
	int x = t*60;		// PIT Timers run at 60MHz bus 
	wait_clock(x);
}
void sleep(void){
	
}
// Initialisation Function
void init(void){
	
	// Gate Clock Setup
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;	// Enable Port B Gate Clock
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;	// Enable Port C Gate Clock
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;	// Enable Port D Gate Clock
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;	// Enable Port E Gate Clock
	SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;		// Enable ADC1 Gate Clock
	SIM_SCGC6 |= SIM_SCGC6_SPI0_MASK;		// Enable SPI0 Gate Clock
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;		// Enable I2C Gate Clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;		// Enable Timer Gate CLock
	
	// Timer setup
	PIT_MCR = 0x00;		// Allow access to general purpose timers
	
	// Analogue to Digital Converter Setup
	ADC1_CFG1 |= 0x8; 	// 10 bit ADC
	ADC1_SC1A |= 0x1F;	// Disable the module for now, ADCH = 1111
	ADC1_CFG2 |= 0x10;	// MUXSEL set to ADxxb channels selected
	ADC1_SC3  = 0x7;		// Hardware averaging Enabled with 32 samples
	
	// Interrupt Setup
	PORTC_ISFR = PORT_ISFR_ISF(0x400);	// Clear interrupt status flag for PC10
	NVIC_EnableIRQ(PORTC_IRQn);					// Enable Port C Interrupt
	enableTouchInterrupt();							// Enable Interrupts
	
	// SPI Interface Setup
	PORTD_PCR0 = 0x200;		// PTD0 as PCS0
	PORTD_PCR1 = 0x200;		// PTD1 as SCK
	PORTD_PCR2 = 0x200;		// PTD2 as SDO
	PORTD_PCR3 = 0x200;		// PTD3 as SDI
	PORTC_PCR4 =	0x100;	// PTC4 as GPIO (Reset pin)
	GPIOC_PDDR |= 0x10;		// PTC4 as output (Reset pin)
	GPIOC_PDOR |= 0x10;		// Set Reset High
	
	SPI0_MCR |= SPI_MCR_HALT_MASK;	// Disable the module while configuring
	SPI0_SR = 0x9A0A0000;						// Clear all Status Flags
	SPI0_TCR = 0;
	SPI0_RSER = 0;
	SPI0_PUSHR = 0;
	SPI0_MCR = 0x80013000;					// Master Mode (0x80000000), CS active low (0x10000), Disable FIFO (0x3000)
	SPI0_CTAR0 = 0x40011110;				// Frame size = 9 bits & Specify Baud rate and other various timing quantities specific to LCD display
	SPI0_CTAR1 = 0x48011110;				// Frame size = 10 bits for dummy cycle when reading 32-bits
	SPI0_MCR &= ~SPI_MCR_HALT_MASK;	// Enable the module after configuring
	
	// I2C Interface Setup
	PORTE_PCR24 = 0x500;						// PTE24 as I2C_SCK (Alt 2 MUX)
	PORTE_PCR25 = 0x500;						// PTE25 as I2C_SDA (Alt 2 MUX)
	I2C0_A1 = CompUIAddr;						// Set Slave address
	I2C0_F = 0x2C;									// I2C baud rate selection (Divider = 576: Baud rate = Bus clock/576 = 60MHz/576 = 104.17kHz)
	I2C0_C1 = I2C_C1_IICEN_MASK;		// Enable I2C Module operation
	
	// LCD Display Setup
	lcdReset();
}


/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	SystemCoreClockUpdate();	// Update system clock (120MHz)
  init(); 									// Initialise all startup routines
	uint8_t bytearray[33];		// Angle array
	PosComp(2000,1,01,0);
	format_I2C(bytearray);
	I2CSendAngles(bytearray);
	
	
	uint8_t state = 0;
	int settings = 0x00000000;
  while (1) {
		
		/*	MENU STRUCTURE
		During Menu Displays where user input will directly take you to another state, the MCU can poll Internet Module for information
		During Menu Displays where user input is interpreted such as Menu_ChangeAngle, Menu_ChangeDate and Wifi_Settings then polling is post-poned.		
		*/
		
		sleep();
		
		// If a touch event is detected then call stateChange() function and if change occurs then update
		if(pos.flag){
			pos.flag = 0;
			uint8_t temp = state;
			state = stateChange(state);
			if(temp != state){
				(*Menu[state])();
			}
			
		}
		
		// Poll Internet Controller for information on every wake-up
		/* POLLING INTERNET CONTROLLER HERE */
		
	}
}

uint8_t stateChange(uint8_t state){
	/*	STATES
	0 - Main Menu
	1 - Date Selection
	2 - Engineering Mode
	3 - Wifi Settings
	4 - Settings
	5 - Change Date
	6 - Change Angle
	*/
	switch (state){
		case 0:	// Main menu
			if			(pos.x>20 && pos.x<220 && pos.y>50  && pos.y<90) 	{			state = 1;			}		// Time&Date Selection Button
			else if (pos.x>20 && pos.x<220 && pos.y>100 && pos.y<140)	{			state = 2;			}		// Engineering Mode Button
			else if (pos.x>20 && pos.x<220 && pos.y>150 && pos.y<190)	{			state = 3;			}		// Wifi Settings Button
			else if (pos.x>20 && pos.x<220 && pos.y>200 && pos.y<240)	{			state = 4;			}		// Settings Button
			break;
		case 1:	// Date selection
			if			(pos.x>0 && pos.x<50 && pos.y>0 && pos.y<30)			{			state = 0;			}	// Back Button
			else if	(pos.x>20 && pos.x<220 && pos.y>50 && pos.y<90)		{			state = 5;			}	// Change Date selection (Busy State)
			break;
		case 2:	// Engineering Mode
			if			(pos.x>0 && pos.x<50 && pos.y>0 && pos.y<30)			{			state = 0;			} // Back Button
			else if (pos.x>125 && pos.x<225 && pos.y>50 && pos.y<260)	{			state = 6;			}	// Change Angle Button (Busy State)
			break;
		case 3:	// Wifi Settings
			if			(pos.x>0 && pos.x<50 && pos.y>0 && pos.y<30)			{			state = 0;			}	// Back Button
			break;
		case 4:	// Settings
			if			(pos.x>0 && pos.x<50 && pos.y>0 && pos.y<30)			{			state = 0;			} // Back Button
			break;
	}
	return state;
}

// State 0
void Menu_StartScreen(){
	lcdClear();
	Menu_Topbar();
	lcdPrintString(50,5,"Electronic Orrery",arial_14pt,Black);	// Title
	lcdDrawRect(20,50,220,90,Green,1);													// Option 1 - Select Date
	lcdPrintString(75,62,"Select Date",arial_14pt,Black);
	lcdDrawRect(20,100,220,140,Green,1);												// Option 2 - Engineering Mode
	lcdPrintString(55,112,"Engineering Mode",arial_14pt,Black);
	lcdDrawRect(20,150,220,190,Green,1);												// Option 3 - Wifi Settings
	lcdPrintString(70,165,"Wifi Settings",arial_14pt,Black);
	lcdDrawRect(20,200,220,240,Green,1);												// Option 4 - Settings
	lcdPrintString(90,212,"Settings",arial_14pt,Black);
}

// State 1
void Menu_SelectDate(){
	lcdClear();
	Menu_Topbar();
	Menu_Back();
	lcdPrintString(50,5,"Date Selection",arial_14pt,Black);			// Title
	lcdDrawRect(20,50,220,90,Green,1);													// Date Box
	lcdDrawRect(20,100,220,300,LightGrey,1);										// Planet Stats Box
	lcdPrintString(25,145,"Planet   Long(°)    Lat(°)   Dist(AU)",arial_10pt,Black);
	lcdPrintString(25,155,"Mercury",arial_10pt,Black);					// Text
	lcdPrintString(25,165,"Venus",arial_10pt,Black);
	lcdPrintString(25,175,"Earth",arial_10pt,Black);
	lcdPrintString(25,185,"Mars",arial_10pt,Black);
	lcdPrintString(25,195,"Jupiter",arial_10pt,Black);
	lcdPrintString(25,205,"Saturn",arial_10pt,Black);
	lcdPrintString(25,155,"Uranus",arial_10pt,Black);
	lcdPrintString(25,155,"Neptune",arial_10pt,Black);
}

// State 2
void Menu_EngineeringMode(){
	lcdClear();
	Menu_Topbar();
	Menu_Back();
	lcdPrintString(40,5,"Engineering Mode",arial_14pt,Black);		// Title
	lcdDrawRect(20,50,115,260,LightGrey,1);											// Planet Box
	lcdDrawRect(125,50,220,260,Green,1);												// Angle Box
	lcdDrawRect(20,270,220,310,Green,1);												// Demo Mode Button
	lcdPrintString(25,60,"Planet",arial_14pt,Black);
	lcdPrintString(25,80,"Mercury",arial_10pt,Black);						// Text
	lcdPrintString(25,100,"Venus",arial_10pt,Black);
	lcdPrintString(25,120,"Earth",arial_10pt,Black);
	lcdPrintString(25,140,"Mars",arial_10pt,Black);
	lcdPrintString(25,160,"Jupiter",arial_10pt,Black);
	lcdPrintString(25,180,"Saturn",arial_10pt,Black);
	lcdPrintString(25,200,"Uranus",arial_10pt,Black);
	lcdPrintString(25,220,"Neptune",arial_10pt,Black);
	
	lcdPrintString(80,280,"Demo Mode",arial_14pt,Black);
}

// State 3
void Menu_WifiSettings(){

}

// State 4
void Menu_Settings(){

}

// State 5
void Menu_ChangeDate(){
	lcdClear();
	Menu_Topbar();
	Menu_Back();
	lcdPrintString(50,5,"Change Date",arial_14pt,Black);		// Title
	Menu_Numpad();
	uint8_t datenum = 0;
	uint8_t loop = 1;
	char dateFormat[] = "YYYY/MM/DD hh:mm";
	char str[] = "_YYY/MM/DD hh:mm";
	while(loop){
		sleep();
		if(pos.flag){
			pos.flag = 0;
			if(pos.x>20 && pos.x<80){
				if			(pos.y>100 && pos.y<140){	str[datenum] = 7;	}
				else if	(pos.y>150 && pos.y<190){	str[datenum] = 4;	}
				else if (pos.y>200 && pos.y<240){	str[datenum] = 1;	}
				else if (pos.y>250 && pos.y<300){	
					str[datenum] = dateFormat[datenum]; 
					if(datenum == 5 || datenum == 8 || datenum == 11 || datenum == 14){
						datenum-=2;
					} else{
						datenum--;
					}
					str[datenum] = '_';
				}
			}
			if(pos.x>90 && pos.x<150){
				if			(pos.y>100 && pos.y<140){	str[datenum] = 8;	}
				else if	(pos.y>150 && pos.y<190){	str[datenum] = 5;	}
				else if (pos.y>200 && pos.y<240){	str[datenum] = 2;	}
				else if (pos.y>250 && pos.y<300){	str[datenum] = 0;	}
			}
			if(pos.x>160 && pos.x<220){
				if			(pos.y>100 && pos.y<140){	str[datenum] = 9;	}
				else if	(pos.y>150 && pos.y<190){	str[datenum] = 6;	}
				else if (pos.y>200 && pos.y<240){	str[datenum] = 3;	}
				else if (pos.y>250 && pos.y<300){
					if(datenum == 15){	// Complete Date
						char* endptr;
						int YY = strtol(str,&endptr,10);		// Store Year
						int MM = strtol(endptr,&endptr,10);	// Store Month
						int DD = strtol(endptr,&endptr,10);	// Store Day
						int hh = strtol(endptr,&endptr,10);	// Store Hour
						int mm = strtol(endptr,&endptr,10);	// Store Minute
						if(checkDate(YY,MM,DD,hh,mm)){
							/* ############## WORKING HERE ############## */
						}	else{	// Wrongly Formatted Date
							lcdDrawRect(20,35,220,49,White,1);
							lcdPrintString(20,35,"NOT VALID DATE",arial_10pt,Red);
						}
					} else{		// Incomplete Date
						lcdDrawRect(20,35,220,49,White,1);
						lcdPrintString(20,35,"INCOMPLETE DATE",arial_10pt,Red);
					}
				}
			}
			if(str[datenum]>('0'-1) && str[datenum]<('9'+1)){
				if(datenum == 3 || datenum == 6 || datenum == 9 || datenum == 12){
					datenum+=2;
				} else if(datenum == 15){
					// Do nothing if at end
				} else{
					datenum++;
				}
			}
		}
	}
}

// State 6
void Menu_ChangeAngle(){
	lcdClear();
	Menu_Topbar();
	Menu_Back();
	lcdPrintString(50,5,"Change Angle",arial_14pt,Black);		// Title
	lcdDrawRect(20,50,220,90,LightGrey,1);									// Date + Time
	Menu_Numpad();
}


/* ---------- Bitmaps and Common Drawing Functions ----------*/
void Menu_Topbar(){
	lcdDrawRect(0,0,240,30,Blue,1);
}

void Menu_Wifi(int colour){
	const uint16_t WifiBitmap[] =
	{	8,13,		7,12,		8,12,		9,12,		8,11,		6,10,		7,9,		8,9,
		9,9,		10,10,	4,8, 		5,7,		6,6, 		7,6,	 	8,6,	 	9,6,
		10,6, 	11,7, 	12,8, 	2,6,	 	3,5, 		4,4, 		5,3, 		6,3,
		7,3, 		8,3, 		9,3, 		10,3, 	11,3, 	12,4, 	13,5,		14,6,
		0,4,		1,3, 		2,2, 		3,1, 		4,0, 		5,0, 		6,0, 		7,0,
		8,0, 		9,0, 		10,0, 	11,0, 	12,0, 	13,1, 	14,2, 	15,3,
		16,4};
	for(int i=0; i<98; i+=2){
		lcdSetPixel(WifiBitmap[i]+215,WifiBitmap[i+1]+7,colour);
	}
}

void Menu_Data(int colour){
	const uint16_t DataBitmap[] = 
	{	3,14, 	3,13, 	3,12, 	3,11, 	3,10, 	3,9, 		3,8, 		3,7,
		3,6, 		3,5, 		3,4, 		0,3, 		1,3, 		2,3, 		3,3, 		4,3, 
		5,3, 		6,3, 		1,2, 		2,2, 		3,2, 		4,2, 		5,2, 		2,1, 
		3,1, 		4,1, 		3,0, 		9,0, 		9,1, 		9,2, 		9,3, 		9,4, 
		9,5, 		9,6, 		9,7, 		9,8, 		9,9, 		9,10, 	6,11, 	7,11, 
		8,11, 	9,11, 	10,11, 	11,11, 	12,11, 	7,12, 	8,12, 	9,12, 
		10,12, 	11,12, 	8,13, 	9,13, 	10,13, 	9,14};
	for(int i=0; i<108; i+=2){
		lcdSetPixel(DataBitmap[i]+195,DataBitmap[i+1]+7,colour);
	}
}

void Menu_Back(){
	lcdDrawRect(0,0,50,30,Green,1);
	lcdPrintString(5,5,"Back",arial_10pt,White);
}

void Menu_Numpad(void){
	lcdDrawRect(20,100,80,140,Green,1);
	lcdDrawRect(90,100,150,140,Green,1);
	lcdDrawRect(160,100,220,140,Green,1);
	lcdDrawRect(20,150,80,190,Green,1);
	lcdDrawRect(90,150,150,190,Green,1);
	lcdDrawRect(160,150,220,190,Green,1);
	lcdDrawRect(20,200,80,240,Green,1);
	lcdDrawRect(90,200,150,240,Green,1);
	lcdDrawRect(160,200,220,240,Green,1);
	lcdDrawRect(20,250,80,300,Green,1);
	lcdDrawRect(90,250,150,300,Green,1);
	lcdDrawRect(160,250,220,300,Green,1);
	lcdPrintChar(50,110,'7',Black,arial_14pt);
	lcdPrintChar(120,110,'8',Black,arial_14pt);
	lcdPrintChar(190,110,'9',Black,arial_14pt);
	lcdPrintChar(50,160,'4',Black,arial_14pt);
	lcdPrintChar(120,160,'5',Black,arial_14pt);
	lcdPrintChar(190,160,'6',Black,arial_14pt);
	lcdPrintChar(50,210,'1',Black,arial_14pt);
	lcdPrintChar(120,210,'2',Black,arial_14pt);
	lcdPrintChar(190,210,'3',Black,arial_14pt);
	lcdPrintString(45,270,"<--",arial_14pt,Black);
	lcdPrintChar(120,270,'0',Black,arial_14pt);
	lcdPrintString(170,270,"Confirm",arial_10pt,Black);
}

// Date checking function
uint8_t checkDate(int year, int month, int day, int hour, int minute){
	if(year>=0 && year<=9999){
		if(month>=1 && month<=12){
			if		 ((day>0 && day<=31) && (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)){}
			else if((day>0 && day<=30) && (month==4 || month==6 || month==9 || month==11)){}
			else if((day>0 && day<=28) && (month==2)){}
			else if( day==29 && month==2 && (year%400==0 ||(year%4==0 && year%100!=0))){}	// Leap years every 4 years but not every 100 years except for every 400 years
			else return 0;	// Not a valid date
		}else	return 0; // Not a valid month
	}else	return 0; // Not a valid year
	
	if(hour>=0 && hour<=24){
		if(minute>=0 && minute<60){
			return 1;		// All conditions met, return success
		}
	}
	return 0; // Not a valid hour
}

// I2CSendAngles takes bytearray as input and sends it to Mechatronics module
// Returns 1 if successful, 0 if failed
uint8_t I2CSendAngles(uint8_t *bytearray){
	I2C0_C1 |= I2C_C1_TX_MASK;						// Set transmit mode
	I2C0_C1 |= I2C_C1_MST_MASK;						// Send START signal
	I2C0_D = MechAddr;										// Send Mechatronics Slave Address with R/!W as 0
	while((I2C0_S & I2C_S_TCF_MASK) == 0){}
	if(I2C0_S & I2C_S_RXAK_MASK){					// If no acknoledgement received then return failure (0)
		I2C0_C1 &= ~I2C_C1_MST_MASK;				// Send STOP signal
		return 0;
	}
		
	if(bytearray[0]){											// Rotate planets by angles
		for(int i=0; i<33; i++){						// 32 bytes to be transmitted (8x4 bytes planet angles)
			I2C0_D = bytearray[i];						// Send Data
			while((I2C0_S & I2C_S_TCF_MASK) == 0){}
			if(I2C0_S & I2C_S_RXAK_MASK){			// If no acknoledgement received then return failure (0)
				I2C0_C1 &= ~I2C_C1_MST_MASK;		// Send STOP signal
				return 0;
			}
		}
		I2C0_C1 &= ~I2C_C1_MST_MASK;				// Send STOP signal
		return 1;
	}
	
	else{																	// Demo Mode
		for(int i=0; i<2; i++){							// 2 bytes to be transmitted (Configuration byte and speed byte)
			I2C0_D = bytearray[i];						// Send Data
			while((I2C0_S & I2C_S_TCF_MASK) == 0){}
			if(I2C0_S & I2C_S_RXAK_MASK){			// If no acknoledgement received then return failure (0)
				I2C0_C1 &= ~I2C_C1_MST_MASK;		// Send STOP signal
				return 0;
			}
		}
		I2C0_C1 &= ~I2C_C1_MST_MASK;	// Send STOP signal
		return 1;
	}
}
