obj-m += MPL3115A2.o

all:i2ctest lcdtest example MPL3115A2

i2ctest:i2c.c
		gcc -O i2c.c -o i2ctest
lcdtest:lcd.c
		gcc -O lcd.c -o lcdtest
example:example.c
		gcc -O example.c -o example
MPL3115A2:MPL3115A2.c
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
		-rm i2ctest lcdtest example *.*~ .*~
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
