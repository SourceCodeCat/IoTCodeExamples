all: weatherStation

weatherStation: weatherStation.cpp
	        g++ weatherStation.cpp SparkFunADS1015.cpp -I/usr/include/upm/ -lmraa -lupm-tsl2561  -o weatherStation
clean:
	rm weatherStation
