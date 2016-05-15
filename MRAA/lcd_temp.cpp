#include <unistd.h>
#include <iostream>
#include <signal.h>
#include "jhd1313m1.h"
#include "mpl3115a2.h"

#include <string>       // std::string
#include <sstream>      // std::stringstream

volatile int doWork = 0;



void sig_handler(int signo)
{
    if (signo == SIGINT) {
        printf("\nCtrl-C received.\n");
        doWork = 1;
    }
}
int main(int argc, char **argv)
{

	// Register signal handler
	signal(SIGINT, sig_handler);

	float pressure    = 0.0;
	float temperature = 0.0;
	float altitude    = 0.0;
	float sealevel    = 0.0;	
	 
	// 0x62 RGB_ADDRESS, 0x3E LCD_ADDRESS
 	upm::Jhd1313m1 *lcd = new upm::Jhd1313m1(0, 0x3E, 0x62);
 	upm::MPL3115A2 *barometer = new upm::MPL3115A2(0, MPL3115A2_I2C_ADDRESS);
	lcd->setCursor(0,0);
	lcd->setColor(127, 255, 127);
	lcd->write("Temperature:");	

	std::stringstream ss;

    while (!doWork) 
    {

        temperature = barometer->getTemperature(true);
        pressure    = barometer->getPressure(false);
        altitude    = barometer->getAltitude();
        sealevel    = barometer->getSealevelPressure();
        ss.str(std::string());
        ss<<temperature;
        lcd->setCursor(1,2);
    	lcd->write(ss.str());
        usleep (500000);
    }

    delete lcd;
    delete barometer;
    return 0;     
}	
