#include "mraa.hpp"
int
main()
{
    uint16_t adc_value;
    float adc_value_float;
    mraa::Aio* a0;
    a0 = new mraa::Aio(0);
    if (a0 == NULL) {
        return MRAA_ERROR_UNSPECIFIED;
    }
    for (;;) {
        adc_value = a0->read();
        adc_value_float = 0.004887586*adc_value;
        //adc_value_float = a0->readFloat();
        //fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
        //#fprintf(stdout, "ADC A0 read float - %.5f\n", adc_value_float);
        fprintf(stdout, "ADC A0 value: %.2f\n", adc_value_float);
        usleep(1000);
    }
    return MRAA_SUCCESS;
}
