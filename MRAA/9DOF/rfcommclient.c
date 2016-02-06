#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

struct sockaddr_rc addr = { 0 };
int s, status;
char dest[18] = "28:B2:BD:A8:39:F4";

void setupClientConnection(const char * baddr)
{
    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );
   
}

void sentMessageToBluetoothServer(const char *message)
{
    // connect to server
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
    // send a message
    if( status == 0 ) {
        status = write(s, message, 6);
    }
    if( status < 0 ) perror("uh oh");

    close(s);

}
