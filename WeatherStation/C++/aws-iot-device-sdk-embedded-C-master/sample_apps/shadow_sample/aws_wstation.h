#ifndef AWS_WSTATION_H_
#define AWS_WSTATION_H_

#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include <signal.h>
#include <memory.h>
#include <sys/time.h>
#include <limits.h>

#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_shadow_interface.h"
#include "aws_iot_shadow_json_data.h"
#include "aws_iot_config.h"
#include "aws_iot_mqtt_interface.h"

typedef enum {
   TEMPERATURE,
   PRESSURE,
   ALTITUDE,
   LUX,
   WSPEED_MPH,
   WSPEED_KM,
   WDIRECTION_NM, //Wind direction name..like NORTH, SOUTH,etc..
   WDIRECTION_DEG,//Wind direction degree relative to the anemometer, i.e NORTH = 90  or SOUTH = 180.
   RAINLVL_MM,
   RAINLVL_IN,
   HUMIDITY
}WEATHER_VARS;

//This struct is meant to be accessible
// from the C++ code....
//that's why it is here...
jsonStruct_t awsSensorData[11];





#endif
