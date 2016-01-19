#include "mraa.hpp"
#define RAIN_MM 0.2794
#define RAIN_INCHES 0.011
#define TIME_LIMIT_SECS 1 
float Total= 0.0;
int Time = 0;

void myEvent(void * args)
{
    Total++;
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
    response = gpio->isr(mraa::EDGE_RISING,&myEvent,NULL);
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
            printf("rainfall per Min %fmm\n", Total*RAIN_MM);
            printf("rainfall per Min %fin\n", Total*RAIN_INCHES);
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

