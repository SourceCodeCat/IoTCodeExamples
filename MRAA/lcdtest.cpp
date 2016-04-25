#include <unistd.h>
#include <iostream>
#include "jhd1313m1.h"

int
main(int argc, char **argv)
{
 
    // 0x62 RGB_ADDRESS, 0x3E LCD_ADDRESS
        upm::Jhd1313m1 *lcd = new upm::Jhd1313m1(0, 0x3E, 0x62);
            lcd->setCursor(0,0);
	     lcd->setColor(0, 255, 0);
                lcd->write("Hello World");
                    lcd->setCursor(1,2);
                        lcd->write("Hello World");

                            printf("Sleeping for 5 seconds\n");
                               sleep(5);
                                  delete lcd;
                                        return 0;     
}	
