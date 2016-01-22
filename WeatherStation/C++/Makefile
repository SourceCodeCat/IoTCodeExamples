all: WeatherStation

WeatherStation: WeatherStation.cpp
	        @g++ `curl-config --libs` WeatherStation.cpp SparkFunADS1015.cpp -I/usr/include/upm/ -lmraa -lupm-tsl2561  -o WeatherStation
		@if [ -d "bin" ]; then echo "Yes there's bin dir"; else echo "creating bin dir"; mkdir bin ; fi
		@mv WeatherStation bin/ 
		
clean:
	@rm bin/WeatherStation
        
