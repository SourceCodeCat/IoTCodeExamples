all: temperature lcdtest lcd_temp

temperature:
	g++ -lmraa -lupm-grove -I/usr/include/upm/ temperature.cpp -o temperature
lcdtest:
	g++ -lmraa -lupm-i2clcd -I/usr/include/upm/ lcdtest.cpp -o lcdtest
lcd_temp:
	g++ -lmraa -lupm-i2clcd -lupm-mpl3115a2 -I/usr/include/upm/ lcd_temp.cpp -o lcd_temp
clean:
	rm temperature lcdtest lcd_temp *.*~ .*~

