all: adcTest adcTestNames rainGaugeTest anemometerTest humidityTest freeboard

freeboard: testFreeboard.cpp
		g++ `curl-config --libs` testFreeboard.cpp -o testFreeboard


humidityTest: humidityTest.cpp
	      g++ humidityTest.cpp -lmraa -o humidityTest

adcTestNames: adcTestNames.cpp
	      g++ -lmraa -o adcTestNames adcTestNames.cpp

adcTest: adcTest.cpp
	 g++ -lmraa -o adcTest adcTest.cpp

rainGaugeTest: rainGaugeTest.cpp
	    g++ -lmraa rainGaugeTest.cpp -o rainGaugeTest

anemometerTest: anemometerTest.cpp
		g++ -lmraa anemometerTest.cpp -o anemometerTest	   


clean:
	rm adcTest adcTestNames rainGaugeTest anemometerTest humidityTest testFreeboard
