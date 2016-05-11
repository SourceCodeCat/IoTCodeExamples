all:i2ctest lcdtest


i2ctest:i2c.c
		gcc -O i2c.c -o i2ctest

lcdtest:lcd.c
		gcc -O lcd.c -o lcdtest
clean:
		@rm i2ctest lcdtest *~ .*~
