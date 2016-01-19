#include "mraa.hpp"
#include "cmath"

int
main()
{
    uint16_t adc_value;
    float adc_value_float;
    float ADC_10BIT_RESOLUTION = 0.004887586;
    //float ADC_12BIT_RESOLUTION = 0.001154785;//0.001220703;
    mraa::Aio* a0;
    a0 = new mraa::Aio(0);
    if (a0 == NULL) {
        return MRAA_ERROR_UNSPECIFIED;
    }
    //a0->setBit(12);
    for (;;) 
    {
        adc_value = a0->read();
        adc_value_float = ADC_10BIT_RESOLUTION*adc_value;
        //fprintf(stdout, "ADC A0 value: %.2f\n", adc_value_float);
	
	if(adc_value_float > 3.36 && adc_value_float < 3.82)
	{
	    printf("NORTH\n");
	}

        else if(adc_value_float > 1.95 && adc_value_float < 2.28)
	{
	    printf("NORTH EAST\n");
	}

        else if(adc_value_float > 0.40 && adc_value_float < 0.48)  
        {                                                          
            printf("EAST\n");                                
        }
        else if(adc_value_float > 0.32  && adc_value_float < 0.93)
        {                                                        
            printf("SOUTH EAST\n");                                      
        }
        else if(adc_value_float > 1.19  && adc_value_float < 1.44)
        {                                                        
            printf("SOUTH\n");                                
        }
        else if(adc_value_float > 2.87  && adc_value_float < 3.09)
        {                                                        
            printf("SOUTH WEST\n");                                     
        }
        else if(adc_value_float >4.46  && adc_value_float < 4.64)
        {                                                        
            printf("WEST\n");                                
        }    
        else if(adc_value_float >3.90  && adc_value_float < 4.31)    
        {                                                         
            printf("NORTH WEST\n");                                     
        }
	else
	{
	   // fprintf(stdout, "ADC A0 value: %.2f\n", adc_value_float);
	}


//        fprintf(stdout, "ADC A0 value: %.2f\n", adc_value_float);
        sleep(0.99);
    }
    return MRAA_SUCCESS;
}
