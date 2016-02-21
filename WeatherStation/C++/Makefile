#remove @ for no make command prints
DEBUG= @

AWS_SDK_BASEDIR = aws-iot-device-sdk-embedded-C-master
AWS_WRAPPER_DIR = $(AWS_SDK_BASEDIR)/aws_wstation
AWS_WRAPPER_FILE = aws_wstation.o
APP_INCLUDE_DIRS = -I $(AWS_WRAPPER_DIR)
APP_NAME = test
APP_SRC_FILES=$(APP_NAME).cpp



#IoT client directory
IOT_CLIENT_DIR= $(AWS_SDK_BASEDIR)/aws_iot_src

PLATFORM_DIR = $(IOT_CLIENT_DIR)/protocol/mqtt/aws_iot_embedded_client_wrapper/platform_linux/openssl
PLATFORM_COMMON_DIR = $(IOT_CLIENT_DIR)/protocol/mqtt/aws_iot_embedded_client_wrapper/platform_linux/common
SHADOW_SRC_DIR= $(IOT_CLIENT_DIR)/shadow


IOT_INCLUDE_DIRS += -I $(IOT_CLIENT_DIR)/protocol/mqtt
IOT_INCLUDE_DIRS += -I $(IOT_CLIENT_DIR)/protocol/mqtt/aws_iot_embedded_client_wrapper
IOT_INCLUDE_DIRS += -I $(IOT_CLIENT_DIR)/protocol/mqtt/aws_iot_embedded_client_wrapper/platform_linux
IOT_INCLUDE_DIRS += -I $(PLATFORM_COMMON_DIR)
IOT_INCLUDE_DIRS += -I $(PLATFORM_DIR)
IOT_INCLUDE_DIRS += -I $(SHADOW_SRC_DIR)
IOT_INCLUDE_DIRS += -I $(IOT_CLIENT_DIR)/utils
IOT_INCLUDE_DIRS += -I $(IOT_CLIENT_DIR)/shadow

IOT_SRC_FILES += $(IOT_CLIENT_DIR)/protocol/mqtt/aws_iot_embedded_client_wrapper/aws_iot_mqtt_embedded_client_wrapper.c
IOT_SRC_FILES += $(IOT_CLIENT_DIR)/utils/jsmn.c
IOT_SRC_FILES += $(IOT_CLIENT_DIR)/utils/aws_iot_json_utils.c
IOT_SRC_FILES += $(shell find $(SHADOW_SRC_DIR)/ -name '*.c')
IOT_SRC_FILES += $(shell find $(PLATFORM_DIR)/ -name '*.c')
IOT_SRC_FILES += $(shell find $(PLATFORM_COMMON_DIR)/ -name '*.c')

#MQTT Paho Embedded C client directory
MQTT_DIR = $(AWS_SDK_BASEDIR)/aws_mqtt_embedded_client_lib
MQTT_C_DIR = $(MQTT_DIR)/MQTTClient-C/src
MQTT_EMB_DIR = $(MQTT_DIR)/MQTTPacket/src

MQTT_INCLUDE_DIR += -I $(MQTT_EMB_DIR)
MQTT_INCLUDE_DIR += -I $(MQTT_C_DIR)

MQTT_SRC_FILES += $(shell find $(MQTT_EMB_DIR)/ -name '*.c')
MQTT_SRC_FILES += $(MQTT_C_DIR)/MQTTClient.c

#TLS - openSSL
TLS_LIB_DIR = /usr/lib/
TLS_INCLUDE_DIR = -I /usr/include/openssl
EXTERNAL_LIBS += -L$(TLS_LIB_DIR)
LD_FLAG := -ldl -lssl -lcrypto
LD_FLAG += -Wl,-rpath,$(TLS_LIB_DIR)

#Aggregate all include and src directories
INCLUDE_ALL_DIRS += $(IOT_INCLUDE_DIRS) 
INCLUDE_ALL_DIRS += $(MQTT_INCLUDE_DIR) 
INCLUDE_ALL_DIRS += $(TLS_INCLUDE_DIR)
INCLUDE_ALL_DIRS += $(APP_INCLUDE_DIRS)
 
#SRC_FILES += $(MQTT_SRC_FILES)
#SRC_FILES += $(APP_SRC_FILES)
#SRC_FILES += $(IOT_SRC_FILES)

# Logging level control
LOG_FLAGS += -DIOT_DEBUG
LOG_FLAGS += -DIOT_INFO
LOG_FLAGS += -DIOT_WARN
LOG_FLAGS += -DIOT_ERROR

COMPILER_FLAGS += -c -fPIC 
COMPILER_FLAGS += $(LOG_FLAGS)
all: $(AWS_WRAPPER_DIR)/aws_wstation.o WeatherStation

WeatherStation:  test.cpp #WeatherStation.cpp
		
	#-----------------------------------------
	# Compiling the WeatherStation-ware
	#-----------------------------------------
	$(DEBUG)g++ $(APP_SRC_FILES) -o $(APP_NAME) $(AWS_WRAPPER_DIR$)/$(AWS_WRAPPER_FILE) $(EXTERNAL_LIBS) $(LD_FLAG) $(INCLUDE_ALL_DIRS) 
	@#g++ `curl-config --libs` WeatherStation.cpp SparkFunADS1015.cpp -I/usr/include/upm/ -lmraa -lupm-tsl2561  -o WeatherStation
	$(DEBUG)if [ -d "bin" ]; then echo "Yes there's bin dir"; else echo "creating bin dir"; mkdir bin ; fi
	$(DEBUG)mv $(APP_NAME) bin/ 
	#-----------------------------------------
	# Done
	#-----------------------------------------

$(AWS_WRAPPER_DIR)/aws_wstation.o:		
	$(MAKE) -C aws-iot-device-sdk-embedded-C-master/aws_wstation/
clean:

	#-----------------------------------------
	# Deleting AWS wrapper
	#-----------------------------------------
	$(MAKE) -C aws-iot-device-sdk-embedded-C-master/aws_wstation/ clean
	#-----------------------------------------
	# Deleting the WeatherStation-ware
	#-----------------------------------------
	$(DEBUG)rm -rf bin/
 	#-----------------------------------------
	# Done
	#-----------------------------------------
