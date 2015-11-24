#include <unistd.h>                                                             
#include "grove.h"                                                              
#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <sstream>                                                              
#include <iostream>                                                             
#include <cstring>                                                              
#include <mosquitto.h>                                                          
#include <mosquittopp.h>
                   
class myMosq : public mosqpp::mosquittopp
{                  
private:          
 const char     *     host;
 const char    *     id;
 const char    *     topic;
 int                port;                
 int                keepalive;
        
void on_disconnect(int rc) 
{
	std::cout << ">> myMosq - disconnection(" << rc << ")" << std::endl;
}                         
void on_connect(int rc)  
{
	if ( rc == 0 ) 
	{
 		std::cout << ">> myMosq - connected with server" << std::endl;
	} 
	else 
	{                                                            
		std::cout << ">> myMosq - Impossible to connect with server(" << rc << ")" << s
	}
}                                                                              
void on_publish(int mid)                                                        
{                                                                              
	std::cout << ">> myMosq - Message (" << mid << ") succeed to be published " << 
}                                                                              
public:                                                                         
myMosq(const char * _id,const char * _topic, const char * _host, int _port) : m
{                                                                              
	mosqpp::lib_init();        // Mandatory initialization for mosquitto library   
	this->keepalive = 60;    // Basic configuration setup for myMosq class         
	this->id = _id;                                                                
	this->port = _port;                                                            
	this->host = _host;                                                            
	this->topic = _topic;                                                          
	connect_async(host,     // non blocking connection to broker request           
	port,                                                                          
	keepalive);                                                                    
	loop_start();            // Start thread managing connection / publish / subscr
};                                                                             
~myMosq()                                                                      
{
	loop_stop();            // Kill the thread                                     
	mosqpp::lib_cleanup();    // Mosquitto library cleanup                         
}                                                                              
                                                                                
bool send_message(const  char * _message)                                       
{                                                                              
	// Send message - depending on QoS, mosquitto lib managed re-submission this th
	//                                                                             
	// * NULL : Message Id (int *) this allow to latter get status of each message 
	// * topic : topic to be used                                                  
	// * lenght of the message                                                     
	// * message                                                                   
	// * qos (0,1,2)                                                               
	// * retain (boolean) - indicates if message is retained on broker or not      
	// Should return MOSQ_ERR_SUCCESS                                              
	int ret = publish(NULL,this->topic,8,_message,1,false);                        
	return ( ret == MOSQ_ERR_SUCCESS );                                            
}                                                                              
};                                                                              
                                                                                
int main(int argc, char *argv[])                                                
{   
       //char * id = "123456789";                                              
        char *host = "localhost";                                               
        char * topic = "temperature";                                           
        int port = 1884;                                                        
        //int keepalive = 60;                                                   
        //bool clean_session = true;                                            
        myMosq *mymosq=new myMosq("12345",topic, host, port);                   
                                                                                
    // Create the temperature sensor object using AIO pin 0                     
    upm::GroveTemp* temp = new upm::GroveTemp(0);                               
    std::cout << temp->name() << std::endl;                                     
    // Read the temperature ten times, printing both the Celsius and            
    // equivalent Fahrenheit temperature, waiting one second between readings   
    char buffer [3];                                                            
    std::stringstream celsius_ss;                                               
                                                                                
    for (int i=0; i < 1000; i++) {                                              
        int celsius = temp->value();                                            
        celsius_ss.str("");                                                     
        celsius_ss<<celsius;                                                    
        int fahrenheit = (int) (celsius * 9.0/5.0 + 32.0);                      
        printf("%d degrees Celsius, or %d degrees Fahrenheit\n",                
                celsius, fahrenheit); 
        mymosq->send_message(celsius_ss.str().c_str());                         
        sleep(1);                                                               
    }                                                                           
                                    
                                                                                
        delete mymosq;                                                          
                                                                                
        return 0;                                                               
}                                                                               
   
