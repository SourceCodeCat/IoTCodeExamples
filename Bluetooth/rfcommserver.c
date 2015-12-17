#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>


    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    char baddr[50] = {0}; //to store bluetooth address
    int s, client, bytes_read;
    socklen_t opt;
    int keepListening = 1;
    pthread_t tid;
    int err;

void* bluetoothListeningLoop(void *arg)
{
    //int i = 0;
    //pthread_t id = pthread_self();

    while(keepListening == 1)
    {

    	// put socket into listening mode
    	listen(s, 1);
    	// accept one connection
    	client = accept(s, (struct sockaddr *)&rem_addr, &opt);
    	ba2str( &rem_addr.rc_bdaddr, baddr );
    	//fprintf(stderr, "accepted connection from %s\n", buf);
    	memset(buf, 0, sizeof(buf));

    	// read data from the client
     	bytes_read = read(client, buf, sizeof(buf));
	if( bytes_read > 0 ) 
	{
		printf("received: %s | from : %s\n", buf,baddr);
	}
    }
    printf("\nBYE! from thread bluetoothListeningLoop..\n");
    return NULL;
}

void initBindRfcomm()
{

    opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));
}
void startRfcomm()
{

    err = pthread_create(&(tid), NULL, &bluetoothListeningLoop, NULL);
    if (err != 0)
        printf("\ncan't create thread :[%s]", strerror(err));
    else
        printf("\n bluetoothListeningLoop Thread created successfully\n");

}
void stopRfcomm()
{
  keepListening = 0;
  //sleep(2);
  // close connection
  close(client);
  close(s);
}

