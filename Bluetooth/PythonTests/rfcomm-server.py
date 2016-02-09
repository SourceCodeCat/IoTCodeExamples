import bluetooth
import signal
import sys

server_sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )

port = 1
server_sock.bind(("",port))
server_sock.listen(1)

#client_sock,address = server_sock.accept()
#print "Accepted connection from ",address
var = 1;
while True:
	client_sock,address = server_sock.accept()
	#print "Accepted connection from ",address
	data = client_sock.recv(1024)
	print "received: {0} from(address, port): {1}".format(data,address)
        client_sock.send("hey!, sup!")
client_sock.close()
server_sock.close()
