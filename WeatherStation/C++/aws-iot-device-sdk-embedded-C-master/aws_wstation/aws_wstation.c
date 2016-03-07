#include "aws_wstation.h"

#define ROOMTEMPERATURE_UPPERLIMIT 32.0f
#define ROOMTEMPERATURE_LOWERLIMIT 25.0f
#define STARTING_ROOMTEMPERATURE ROOMTEMPERATURE_LOWERLIMIT
#define MAX_LENGTH_OF_UPDATE_JSON_BUFFER 200
char JsonDocumentBuffer[MAX_LENGTH_OF_UPDATE_JSON_BUFFER];
size_t sizeOfJsonDocumentBuffer = sizeof(JsonDocumentBuffer) / sizeof(JsonDocumentBuffer[0]);

char certDirectory[PATH_MAX + 1] = "aws-iot-device-sdk-embedded-C-master/certs";
char HostAddress[255] = AWS_IOT_MQTT_HOST;
uint32_t port = AWS_IOT_MQTT_PORT;
uint8_t numPubs = 5;
char rootCA[PATH_MAX + 1];
char clientCRT[PATH_MAX + 1];
char clientKey[PATH_MAX + 1];
char CurrentWD[PATH_MAX + 1];
char cafileName[] = AWS_IOT_ROOT_CA_FILENAME;
char clientCRTName[] = AWS_IOT_CERTIFICATE_FILENAME;
char clientKeyName[] = AWS_IOT_PRIVATE_KEY_FILENAME;
MQTTClient_t mqttClient;

void ShadowUpdateStatusCallback(const char *pThingName, ShadowActions_t action, Shadow_Ack_Status_t status,
		const char *pReceivedJsonDocument, void *pContextData) {

	if (status == SHADOW_ACK_TIMEOUT) {
		INFO("Update Timeout--");
	} else if (status == SHADOW_ACK_REJECTED) {
		INFO("Update RejectedXX");
	} else if (status == SHADOW_ACK_ACCEPTED) {
		INFO("Update Accepted !!");
	}
}
void sendData()
{

/*
	aws_iot_shadow_init_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
	
	aws_iot_shadow_add_reported(JsonDocumentBuffer, sizeOfJsonDocumentBuffer, 4, 
	&awsSensorData[HUMIDITY],	
	&awsSensorData[LUX], 
	&awsSensorData[WSPEED_MPH], 
	&awsSensorData[WSPEED_KM]);
	
	aws_iot_finalize_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
	INFO("\nUpdate Shadow: %s", JsonDocumentBuffer);

*/

	IoT_Error_t rc = NONE_ERROR;
	rc = aws_iot_shadow_init_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
	if (rc == NONE_ERROR) {
		rc = aws_iot_shadow_add_reported(JsonDocumentBuffer, sizeOfJsonDocumentBuffer, 4,
									&awsSensorData[HUMIDITY],	
									&awsSensorData[LUX], 
									&awsSensorData[WSPEED_MPH], 
									&awsSensorData[WSPEED_KM]);

		if (rc == NONE_ERROR){
			rc = aws_iot_finalize_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
			if (rc == NONE_ERROR) {
				INFO("Update Shadow: %s", JsonDocumentBuffer);
			}
			rc = aws_iot_shadow_update(&mqttClient, AWS_IOT_MY_THING_NAME, JsonDocumentBuffer, ShadowUpdateStatusCallback,NULL, 4, true);//INFO("Update Shadow: %s", JsonDocumentBuffer);//
		}
	}

}

void initAWS_Wrapper()
{
	
	initSensorStruct();
	initWrapper();
}
void initWrapper()
{
	IoT_Error_t rc = NONE_ERROR;
	aws_iot_mqtt_init(&mqttClient);
	INFO("\nAWS IoT SDK Version(dev) %d.%d.%d-%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

	getcwd(CurrentWD, sizeof(CurrentWD));
	sprintf(rootCA, "%s/%s/%s", CurrentWD, certDirectory, cafileName);
	sprintf(clientCRT, "%s/%s/%s", CurrentWD, certDirectory, clientCRTName);
	sprintf(clientKey, "%s/%s/%s", CurrentWD, certDirectory, clientKeyName);

	DEBUG("Using rootCA %s", rootCA);
	DEBUG("Using clientCRT %s", clientCRT);
	DEBUG("Using clientKey %s", clientKey);

	ShadowParameters_t sp = ShadowParametersDefault;
	sp.pMyThingName = AWS_IOT_MY_THING_NAME;
	sp.pMqttClientId = AWS_IOT_MQTT_CLIENT_ID;
	sp.pHost = HostAddress;
	sp.port = port;
	sp.pClientCRT = clientCRT;
	sp.pClientKey = clientKey;
	sp.pRootCA = rootCA;

	INFO("Shadow Init");
	rc = aws_iot_shadow_init(&mqttClient);

	INFO("Shadow Connect");
	rc = aws_iot_shadow_connect(&mqttClient, &sp);

	if (NONE_ERROR != rc) {
		ERROR("Shadow Connection Error %d", rc);
	}
/*
	rc = aws_iot_shadow_register_delta(&mqttClient);

	if (NONE_ERROR != rc) {
		ERROR("Shadow Register Delta Error");
	}
*/
}
void initSensorStruct()
{


	awsSensorData[TEMPERATURE].pKey="TEMPERATURE";
	awsSensorData[TEMPERATURE].pData=NULL;
	awsSensorData[TEMPERATURE].type=SHADOW_JSON_FLOAT;
	awsSensorData[TEMPERATURE].cb=NULL;

        awsSensorData[PRESSURE].pKey="PRESSURE";
        awsSensorData[PRESSURE].pData=NULL;
        awsSensorData[PRESSURE].type=SHADOW_JSON_FLOAT;
        awsSensorData[PRESSURE].cb=NULL;

        awsSensorData[ALTITUDE].pKey="ALTITUDE";
        awsSensorData[ALTITUDE].pData=NULL;
        awsSensorData[ALTITUDE].type=SHADOW_JSON_FLOAT;
        awsSensorData[ALTITUDE].cb=NULL;

        awsSensorData[LUX].pKey="LUX";
        awsSensorData[LUX].pData=NULL;
        awsSensorData[LUX].type=SHADOW_JSON_FLOAT;
        awsSensorData[LUX].cb=NULL;

        awsSensorData[WSPEED_MPH].pKey="WSPEED_MPH";
        awsSensorData[WSPEED_MPH].pData=NULL;
        awsSensorData[WSPEED_MPH].type=SHADOW_JSON_FLOAT;
        awsSensorData[WSPEED_MPH].cb=NULL;

        awsSensorData[WSPEED_KM].pKey="WSPEED_KM";
        awsSensorData[WSPEED_KM].pData=NULL;
        awsSensorData[WSPEED_KM].type=SHADOW_JSON_FLOAT;
        awsSensorData[WSPEED_KM].cb=NULL;

        awsSensorData[WDIRECTION_DEG].pKey="WDIRECTION_DEG";
        awsSensorData[WDIRECTION_DEG].pData=NULL;
        awsSensorData[WDIRECTION_DEG].type=SHADOW_JSON_FLOAT;
        awsSensorData[WDIRECTION_DEG].cb=NULL;

        awsSensorData[RAINLVL_MM].pKey="RAINLVL_MM";
        awsSensorData[RAINLVL_MM].pData=NULL;
        awsSensorData[RAINLVL_MM].type=SHADOW_JSON_FLOAT;
        awsSensorData[RAINLVL_MM].cb=NULL;

        awsSensorData[RAINLVL_IN].pKey="RAINLVL_IN";
        awsSensorData[RAINLVL_IN].pData=NULL;
        awsSensorData[RAINLVL_IN].type=SHADOW_JSON_FLOAT;
        awsSensorData[RAINLVL_IN].cb=NULL;

        awsSensorData[HUMIDITY].pKey="HUMIDITY";
        awsSensorData[HUMIDITY].pData=NULL;
        awsSensorData[HUMIDITY].type=SHADOW_JSON_FLOAT;
        awsSensorData[HUMIDITY].cb=NULL;



}























