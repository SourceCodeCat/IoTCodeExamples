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

extern "C"
{
	#include "aws_iot_log.h"
	#include "aws_iot_version.h"
	#include "aws_iot_shadow_interface.h"
	#include "aws_iot_shadow_json_data.h"
	#include "aws_iot_config.h"
	#include "aws_iot_mqtt_interface.h"
	void superduper();
	void probando();
}



int main()
{
  std::cout << "Hello World!"<<std::endl;
  superduper();
}
