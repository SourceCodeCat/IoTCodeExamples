
all: TempMosquitto

TempMosquitto: TempMosquitto.cpp
	g++ -lmraa -lupm-grove -lmosquittopp -I/usr/include/upm/ TempMosquitto.cpp -o TempMosquitto

clean: 
	rm TempMosquitto
