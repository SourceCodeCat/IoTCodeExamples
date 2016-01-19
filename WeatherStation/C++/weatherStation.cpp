#include "mraa.hpp"

#include <iostream>
#include <unistd.h>
#include "SparkFunADS1015.h"
#include <cmath>
#include <string.h>
using namespace std;

// Declare a variable for our i2c object. You can create an
//  arbitrary number of these, and pass them to however many
//  slave devices you wish.
mraa::I2c* adc_i2c;
ads1015 *adc;
float adc_float = 0;
#define WIND_SPEED_MPH 1.492  
#define WIND_SPEED_KM_H 2.4 
#define TIME_LIMIT_SECS 5 
#define ANEMOMETER_GPIO 48
#define RAINGAUGE_GPIO 36
#define RAIN_MM 0.2794
#define RAIN_INCHES 0.011
int anemometerTotal= 0;
int Time = 0;
float raingaugeTotal= 0.0;
mraa::Gpio* gpioAnemometer;
mraa::Gpio* gpioRainGauge;
void anemometerEvent(void * args)
{
    anemometerTotal++;
	//printf("testing wind %d \n", Total);
}
void raingaugeEvent(void * args)
{
    raingaugeTotal++;
}
int setupRainGauge()
{
    gpioRainGauge = new mraa::Gpio(RAINGAUGE_GPIO);
    if (gpioRainGauge == NULL) {
        return mraa::ERROR_UNSPECIFIED;
    }
    mraa::Result response = gpioRainGauge->dir(mraa::DIR_IN);
    if (response != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }
    response = gpioRainGauge->mode(mraa::MODE_PULLDOWN);
    if (response != mraa::SUCCESS) {                      
        mraa::printError(response);                       
        return 1;                                         
    } 
    response = gpioRainGauge->isr(mraa::EDGE_RISING,&raingaugeEvent,NULL);
    if (response != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }
    return mraa::SUCCESS;
}
int setupAnemometer()
{
    gpioAnemometer = new mraa::Gpio(ANEMOMETER_GPIO);
    if (gpioAnemometer == NULL) {
        return mraa::ERROR_UNSPECIFIED;
    }
    mraa::Result response = gpioAnemometer->dir(mraa::DIR_IN);
    if (response != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }
    response = gpioAnemometer->mode(mraa::MODE_PULLDOWN);
    if (response != mraa::SUCCESS) {                      
        mraa::printError(response);                       
        return 1;                                         
    } 
    response = gpioAnemometer->isr(mraa::EDGE_BOTH,&anemometerEvent,NULL);
    if (response != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }
    return mraa::SUCCESS;
}
int setupADC()
{
    adc_i2c = new mraa::I2c(1);
    adc = new ads1015(adc_i2c, 0x48);
    adc->setRange(_6_144V);
    return MRAA_SUCCESS;	
}

string getWindDirection() 
{
	adc_float = adc->getResult(0);
	if(abs(adc_float-0.801)<0.1 || abs(adc_float-2.076)<0.1)
	{return "NORTH\n";//cout<<"NORTH\n";
	}
	else if(abs(adc_float-1.89)<0.1 || abs(adc_float-3.165)<0.01)
	{return "NORTH EAST\n";//cout<<"NORTH EAST\n";
	}
        else if(abs(adc_float-3.132)<0.01 || abs(adc_float-3.222)<0.01)       
        {return "EAST\n";//cout<<"EAST\n";
	}  
        else if(abs(adc_float-2.825)<0.1 || abs(adc_float-3.021)<0.1)
	{return "SOUTH EAST\n";//cout<<"SOUTH EAST\n";
	}  
        else if(abs(adc_float-2.481)<0.1 ||  abs(adc_float-2.625)<0.1)       
        {return"SOUTH\n";//cout<<"SOUTH\n";
	}  
        else if(abs(adc_float-1.323)<0.1 || abs(adc_float-1.425)<0.1)       
        {return "SOUTH WEST\n";//cout<<"SOUTH WEST\n";
        }  
        else if(abs(adc_float-0.261)<0.1 || abs(adc_float-0.65)<0.1)       
        {return"WEST\n";//cout<<"WEST\n";
        }  
        else if(abs(adc_float-0.455)<0.1 || abs(adc_float-1.077)<0.1)       
        {return "NORTH WEST\n";//cout<<"NORTH WEST\n";
	}
	//else
	//{  
		//cout<<"Ch 0: "<<adc_float<<endl;
		//usleep(500);
	//}

}



int main()
{


	setupADC();
	setupAnemometer();
	setupRainGauge();
	for(;;)
	{
		cout<<getWindDirection();
		if(Time > TIME_LIMIT_SECS)
		{
		    printf("Wind speed %f MPH \n", (anemometerTotal/Time)*WIND_SPEED_MPH );
		    printf("Wind speed %f KM/H \n", (anemometerTotal/Time)*WIND_SPEED_KM_H );
            	    printf("rainfall per Min %fmm\n", (raingaugeTotal/Time)*RAIN_MM);
            	    printf("rainfall per Min %fin\n", (raingaugeTotal/Time)*RAIN_INCHES);
		    anemometerTotal = 0;
		    raingaugeTotal = 0.0;
		    Time = 0;
		}
		sleep(1);
		Time++;	
	}
	return 0;
}
