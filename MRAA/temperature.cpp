#include <unistd.h>
#include <iostream>
#include "grove.h"

int
main(int argc, char **argv)
{

    // Create the temperature sensor object using AIO pin 0
    upm::GroveTemp* temp = new upm::GroveTemp(0);
    std::cout << temp->name() << std::endl;
    // Read the temperature ten times, printing both the Celsius and
    // equivalent Fahrenheit temperature, waiting one second between readings
    for (int i=0; i < 100; i++) {
        int celsius = temp->value();
        int fahrenheit = (int) (celsius * 9.0/5.0 + 32.0);
        printf("%d degrees Celsius, or %d degrees Fahrenheit\n",
                celsius, fahrenheit);
        sleep(1);
    }
    // Delete the temperature sensor object
    delete temp;
    return 0;
}
