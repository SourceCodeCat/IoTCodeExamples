all: temperature lcdtest

temperature:
	g++ -lmraa -lupm-grove -I/usr/include/upm/ temperature.cpp -o temperature
lcdtest:
	g++ -lmraa -lupm-i2clcd -I/usr/include/upm/ lcdtest.cpp -o lcdtest
clean:
	rm temperature lcdtest

