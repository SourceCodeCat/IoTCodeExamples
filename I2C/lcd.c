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
    	writeByteRegister(rgb->file, REG_RED, r);
	writeByteRegister(rgb->file, REG_GREEN, g);
    	writeByteRegister(rgb->file, REG_BLUE, b);    
	i2cRead(rgb->file, 0x04);
}
void initLCD(I2CCONTEXT *lcd)
{

	writeByteRegister(lcd->file, 0x00, LCD_FUNCTIONSET | LCD_2LINE );
	usleep(100);
	writeByteRegister(lcd->file, 0x00,LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKON );
	usleep(100);
	writeByteRegister(lcd->file, 0x00, LCD_CLEARDISPLAY );
	usleep(4000);
	writeByteRegister(lcd->file, 0x00,LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT );



}

void initRGB(I2CCONTEXT *rgb)
{
    	// backlight init
    	writeByteRegister(rgb->file, REG_MODE1, 0);
    	// set LEDs controllable by both PWM and GRPPWM registers
    	writeByteRegister(rgb->file, REG_OUTPUT, 0xFF);
    	// set MODE2 values
    	// 0010 0000 -> 0x20  (DMBLNK to 1, ie blinky mode)
	writeByteRegister(rgb->file, REG_MODE2, 0x20);
	// set the baklight Color to white :)
	setRGBColor(rgb, 0xFF, 0xFF, 0xFF);//	
}
void turnOffRGB(I2CCONTEXT *rgb)
{
	setRGBColor(rgb, 0x00, 0x00, 0x00);	
}
void turnOffLCD(I2CCONTEXT *lcd)
{
	
	writeByteRegister(lcd->file, 0x00, LCD_DISPLAYCONTROL );
	writeByteRegister(lcd->file, 0x00, LCD_CLEARDISPLAY );

}
void writeToLCD(I2CCONTEXT *lcd, char *c)
{

	//writeByteRegister(lcd->file, 0x80, 0x48);
	//usleep(4000);
	
	uint ascii_val=0;
	int i;
	int s = strlen(c);
	for(i = 0 ; i < s; i++)
	{
		ascii_val = toascii(c[i]);
		writeByteRegister(lcd->file, 0x40, ascii_val);
	}
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

	writeToLCD(&lcd, ":) HOLO!");
	/*sleep for 5 secs before turning off*/
    	sleep(5);
    	/*turn off RGB LEDS*/
    	turnOffRGB(&rgb);
    	turnOffLCD(&lcd);
    	printf("\nDONE!\n");


	return 0;
}
