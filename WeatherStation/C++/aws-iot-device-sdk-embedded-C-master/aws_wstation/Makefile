CC = gcc

#remove @ for no make command prints
DEBUG= @

APP_DIR = .
WRAPPER_NAME=test
APP_NAME=aws_wstation
APP_INCLUDE_DIRS += -I $(APP_DIR)
APP_SRC_FILES=$(APP_NAME).c
WRAPPER_SRC_FILES=$(WRAPPER_NAME).cpp
WRAPPER_INCLUDE_DIRS = 

#IoT client directory


IOT_CLIENT_DIR=../aws_iot_src

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
MQTT_DIR = ../aws_mqtt_embedded_client_lib
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
WRAPPER_INCLUDE_DIRS = $(INCLUDE_ALL_DIRS)
INCLUDE_ALL_DIRS += $(APP_INCLUDE_DIRS)
 
SRC_FILES += $(MQTT_SRC_FILES)
SRC_FILES += $(APP_SRC_FILES)
SRC_FILES += $(IOT_SRC_FILES)

# Logging level control
LOG_FLAGS += -DIOT_DEBUG
LOG_FLAGS += -DIOT_INFO
LOG_FLAGS += -DIOT_WARN
LOG_FLAGS += -DIOT_ERROR

COMPILER_FLAGS += -c -fPIC 
COMPILER_FLAGS += $(LOG_FLAGS)

MAKE_CMD = $(CC) $(SRC_FILES) $(COMPILER_FLAGS) $(EXTERNAL_LIBS) $(LD_FLAG) $(INCLUDE_ALL_DIRS)  
#MAKE_CMD = $(CC) $(SRC_FILES) $(COMPILER_FLAGS) -o $(APP_NAME) $(EXTERNAL_LIBS) $(LD_FLAG) $(INCLUDE_ALL_DIRS)

#we've gotta check if the object with the c code is already generated, if not generated first...
all: $(APP_NAME).o

	#-----------------------------------------
	#  Linking all objects...
	#-----------------------------------------
	$(eval TEMP:= $(shell find $(APP_DIR)/ -name '*.o'))
	$(eval $(shell ld -r $(TEMP) -o $(APP_NAME)))
	$(DEBUG)rm -rf $(APP_DIR)/*.o 
	$(DEBUG)mv $(APP_NAME) $(APP_NAME).o
	#-----------------------------------------
	#  Done
	#-----------------------------------------
	$(DEBUG)#g++ $(WRAPPER_SRC_FILES) -o $(WRAPPER_NAME) $(APP_NAME).o $(EXTERNAL_LIBS) $(LD_FLAG) $(WRAPPER_INCLUDE_DIRS)

#this recipe compiles the objects needed for the C objects for the aws methods
$(APP_NAME).o:

	#-----------------------------------------
	#  Starting to compile the  AWS Wrapper
	#-----------------------------------------
	$(DEBUG)$(MAKE_CMD)
	#-----------------------------------------
	#  Done
	#-----------------------------------------
	
clean:
	rm -rf $(APP_DIR)/$(APP_NAME)	
	rm -rf $(APP_DIR)/*.o	
	rm -rf $(APP_DIR)/$(WRAPPER_NAME)
