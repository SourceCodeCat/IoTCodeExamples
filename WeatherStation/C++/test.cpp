// my first program in C++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include <signal.h>
#include <memory.h>
#include <sys/time.h>
#include <limits.h>
#include "aws_wstation.h"

extern "C"
{
	void initAWS_Wrapper();
	void sendData();
}

float temperature = 56.0;


int main()
{
  std::cout << "Hello World!"<<std::endl;
  initAWS_Wrapper();
  awsSensorData[TEMPERATURE].pData=&temperature;
  sendData();
}
