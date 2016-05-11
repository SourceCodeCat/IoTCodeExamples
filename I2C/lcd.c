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
//////////////////////////////////////////////////////////
I2CCONTEXT lcd, rgb;
/////////////////////////////////////////////////////////

void setRGBColor(I2CCONTEXT *rgb, int r, int g, int b)
{
    	writebyteregister(rgb->file, REG_RED, r);
	writebyteregister(rgb->file, REG_GREEN, g);
    	writebyteregister(rgb->file, REG_BLUE, b);    
	i2cRead(rgb->file, 0x04);
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
	initRGB(&rgb);	
	printf("\nDONE!\n");
	
	return 0;
}
