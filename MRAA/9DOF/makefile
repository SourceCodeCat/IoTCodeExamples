all: rfcommclient.o Sparkfun

rfcommclient.so: rfcommclient.o
         gcc -shared -o librfcommclient.so rfcommclient.o

rfcommclient.o: rfcommclient.c
         gcc -c -Wall -Werror -fPIC rfcommclient.c -lbluetooth

Sparkfun:Sparkfun.cpp
	g++ -lmraa -lupm-lsm9ds0 -I/usr/include/upm/ Sparkfun.cpp SFE_LSM9DS0.cpp -o Sparkfun

clean:
	rm Sparkfun rfcommclient.o

clean_all:
	rm Sparkfun librfcommclient.so rfcommclient.o
