/*----------------------------------------------------------------------------
 * Name:    Main.h
 * Purpose: Computation and User Interface main h file
 *----------------------------------------------------------------------------
 * Author: 	Joel W Webb
 * Date: 		18/01/2018
 *----------------------------------------------------------------------------*/
 
// Delay Functions
// One clock cycle of the MCU is 1/120MHz = 8.3ns long
void wait_clock(int x);
void wait_ms(int t);
void wait_us(int t);

void sleep(void);
uint8_t stateChange(uint8_t);
uint8_t I2CSendAngles(uint8_t *);
uint8_t checkDate(int year, int month, int day, int hour, int minute);

// Menu Function States
void Menu_StartScreen(void);
void Menu_SelectDate(void);
void Menu_EngineeringMode(void);
void Menu_WifiSettings(void);
void Menu_Settings(void);
void Menu_ChangeDate(void);
void Menu_ChangeAngle(void);

// Menu Drawing Functions and bitmaps
void Menu_Topbar(void);
void Menu_Wifi(int);
void Menu_Data(int);
void Menu_Back(void);
void Menu_Numpad(void);
