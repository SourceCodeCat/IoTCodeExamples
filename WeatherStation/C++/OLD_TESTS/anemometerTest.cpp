#include "mraa.hpp"
#define WIND_SPEED_MPH 1.492  
#define WIND_SPEED_KM_H 2.4 
#define TIME_LIMIT_SECS 5 
int Total= 0;
int Time = 0;

void myEvent(void * args)
{
    Total++;
	//printf("testing wind %d \n", Total);
}

int
main()
{

    mraa::Gpio* gpio = new mraa::Gpio(7);
    if (gpio == NULL) {
        return mraa::ERROR_UNSPECIFIED;
    }
    mraa::Result response = gpio->dir(mraa::DIR_IN);
    if (response != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }
    response = gpio->mode(mraa::MODE_PULLDOWN);
    if (response != mraa::SUCCESS) {                      
        mraa::printError(response);                       
        return 1;                                         
    } 
    response = gpio->isr(mraa::EDGE_BOTH,&myEvent,NULL);
    if (response != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }
    for (;;) 
    {
        /*OldValue = NewValue;
        NewValue = gpio->read();
        printf("%d\n", NewValue);
        */
        if(Time > TIME_LIMIT_SECS)
        {
            printf("Wind speed %f MPH \n", Total*WIND_SPEED_MPH );
            printf("Wind speed %f KM/H \n", Total*WIND_SPEED_KM_H );
            Total = 0;
            Time = 0;
        }
        //else
        //{
        //
        //}   
         sleep(1);
         Time++;
      
    }
    delete gpio;
    return 0;
}

