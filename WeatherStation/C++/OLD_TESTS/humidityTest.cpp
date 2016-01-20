#include "mraa.hpp"
float adc_value_float;
mraa::Aio* a0;
float zeroOffset = 0.0;
float slope = 0.0;
float vSupply = 5.0;

float vout()
{
	uint16_t adc_value = 0; 
	float adc_value_float = 0.0;
        adc_value = a0->read();                 
        adc_value_float = 0.004887586*adc_value;
        return adc_value_float;
}
int setupADC()
{
    a0 = new mraa::Aio(0);                      
    if (a0 == NULL) {                           
        return MRAA_ERROR_UNSPECIFIED;                                   
    }  

    return 0;
}

float getSensorRH() 
{
  return ((vout() - zeroOffset) / slope);
}
float getTrueRH(float temperature) {  
  return getSensorRH() / (1.0546 - (0.00216 * temperature)); 
}
int
main()
{
	setupADC();
	slope = 0.0062 * vSupply;
	zeroOffset = 0.16 * vSupply; 
	for (;;) 
	{
        	fprintf(stdout, "ADC A0 value: %.2f\n", getSensorRH());
        	usleep(1000);
    	}
    return MRAA_SUCCESS;
}
