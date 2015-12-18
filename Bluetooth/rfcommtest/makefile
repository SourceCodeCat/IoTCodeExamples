
all: rfcommClient rfcommServer

rfcommClient: rfcommClient.c
	gcc rfcommClient.c -o rfcommClient -lbluetooth

rfcommServer: rfcommServer.c
	gcc rfcommServer.c -o rfcommServer -lbluetooth

clean: 
	rm rfcommClient rfcommServer
