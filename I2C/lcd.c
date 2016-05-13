#include <inttypes.h>
#include "myi2c.h"
//////////////////////////////////////////////////////////
#define RGB_SLAVE	0x62
#define LCD_SLAVE	0x3E
#define BUS		0x01
#define REG_RED         0x04        // pwm2
#define REG_GREEN       0x03        // pwm1
#define REG_BLUE        0x02        // pwm0
#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

// commands
#define LCD_CLEARDISPLAY	0x01
#define LCD_RETURNHOME	0x02
#define LCD_ENTRYMODESET	0x04
#define LCD_DISPLAYCONTROL	0x08
#define LCD_CURSORSHIFT	0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR	0x40
#define LCD_SETDDRAMADDR	0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT	0x00
#define LCD_ENTRYLEFT	0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON	0x04
#define LCD_DISPLAYOFF	0x00
#define LCD_CURSORON	0x02
#define LCD_CURSOROFF	0x00
#define LCD_BLINKON	0x01
#define LCD_BLINKOFF	0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE	0x00
#define LCD_MOVERIGHT	0x04
#define LCD_MOVELEFT	0x00

// flags for function set
#define LCD_8BITMODE	0x10
#define LCD_4BITMODE	0x00
#define LCD_2LINE	0x08
#define LCD_1LINE	0x00
//#define LCD_5x10DOTS	0x04
#define LCD_5x8DOTS	0x00
//////////////////////////////////////////////////////////
uint8_t _displayfunction = 0;
uint8_t _displaycontrol = 0;
uint8_t _displaymode = 0;
uint8_t lines = 2;
I2CCONTEXT lcd, rgb;

/////////////////////////////////////////////////////////

void setRGBColor(I2CCONTEXT *rgb, int r, int g, int b)
{
    	writebyteregister(rgb->file, REG_RED, r);
	writebyteregister(rgb->file, REG_GREEN, g);
    	writebyteregister(rgb->file, REG_BLUE, b);    
	i2cRead(rgb->file, 0x04);
}
void initLCD(I2CCONTEXT *lcd)
{
	writebyteregister(lcd->file, 0x80, LCD_FUNCTIONSET | LCD_2LINE );
	usleep(100);
	_displaycontrol = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON;
	writebyteregister(lcd->file, 0x80,LCD_DISPLAYCONTROL | _displaycontrol );
	usleep(100);
	writebyteregister(lcd->file, 0x80, LCD_CLEARDISPLAY);
	usleep(4000);
	writebyteregister(lcd->file, 0x80,LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
	/*
	writebyteregister(lcd->file, 0x80, LCD_FUNCTIONSET | _displayfunction );
	usleep(4500);
	writebyteregister(lcd->file, 0x80, LCD_FUNCTIONSET | _displayfunction );
	usleep(150);
	writebyteregister(lcd->file, 0x80, LCD_FUNCTIONSET | _displayfunction );
	writebyteregister(lcd->file, 0x80, LCD_FUNCTIONSET | _displayfunction );
	_displaycontrol = LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON | LCD_DISPLAYON;

        writebyteregister(lcd->file, 0x80, LCD_DISPLAYCONTROL | _displaycontrol);
	//clear display
	writebyteregister(lcd->file, 0x80, LCD_CLEARDISPLAY);        // clear display, set cursor position to zero
	usleep(2000);          // this command takes a long time!
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	writebyteregister(lcd->file, 0x80, LCD_ENTRYMODESET | _displaymode);
	*/



}

void initRGB(I2CCONTEXT *rgb)
{
    	// backlight init
    	writebyteregister(rgb->file, REG_MODE1, 0);
    	// set LEDs controllable by both PWM and GRPPWM registers
    	writebyteregister(rgb->file, REG_OUTPUT, 0xFF);
    	// set MODE2 values
    	// 0010 0000 -> 0x20  (DMBLNK to 1, ie blinky mode)
	writebyteregister(rgb->file, REG_MODE2, 0x20);
	// set the baklight Color to white :)
	setRGBColor(rgb, 0xFF, 0xFF, 0xFF);//	
}
int main()
{
	//Grove LCD has two devices one that drives LCD
	//and a second that drives RGB
	initContext(&rgb, RGB_SLAVE , BUS);
	initContext(&lcd, LCD_SLAVE , BUS);
	////////////////////////////////////////////////////////////
   	
	//init RGB device & set White color
	initLCD(&lcd);
	initRGB(&rgb);	
	printf("\nDONE!\n");
	
	return 0;
}
