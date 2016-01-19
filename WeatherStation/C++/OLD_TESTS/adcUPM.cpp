#include "mraa.hpp"
#include <iostream>
#include <unistd.h>
#include "ads1015.h"
#include "ads1115.h"
int
main()
{

     using namespace std;
     using namespace upm;
     int command;
     //Select the device you are testing here and adjust case 6 for the correct sample rates.
     //upm::ADS1015 *ads = new upm::ADS1015(1);
     upm::ADS1115 *ads = new upm::ADS1115(1, 0x49);
     float inputVoltage;
     int ans;

     do
     {

          cout << endl;
          cout << "1 - get Conversion \t" ;
          cout << "2 - get last conversion" << endl;
          cout << "3 - get Gain \t\t";
          cout << "4 - set Gain"  << endl;;
          cout << "5 - get Data Rate \t";
          cout << "6 - set Data Rate" << endl;
          cout << "7 - Set Upper Threshold \t" ;
          cout << "8 - Set Lower Threshold \t";
          cout << "9 - Display Thresholds \t";
          cout << "10 - Set Default Thresholds \t";
          cout << "11 - Set conversion ready" << endl;
          cout << "12 - get Comp Que \t" ;
          cout << "13 - set Comp Que" << endl;
          cout << "1et Comp Pol \t";
          cout << "15 - set Comp Pol" << endl;
          cout << "16 - get Comp mode \t";
          cout << "17 - set Comp mode " << endl;
          cout << "18 - get Comp Latch\t";
          cout << "19 - set Comp Latch " << endl;
    e 9:
               cout << "Upper " << ads->getThresh(ADS1X15::THRESH_HIGH) << endl;
               cout << "Lower " << ads->getThresh(ADS1X15::THRESH_LOW) << endl;
               break;
          case 10:
               ads->setThresh(ADS1115::THRESH_
}
