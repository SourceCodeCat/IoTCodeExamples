all: librfcommserver.so test

librfcommserver.so: rfcommserver.o
	 gcc -shared -o librfcommserver.so rfcommserver.o

rfcommserver.o: rfcommserver.c 
	 gcc -c -Wall -Werror -fPIC rfcommserver.c -lpthread -lbluetooth         

test:   rfcommserver.o
	g++ -Wall test.cpp -o test rfcommserver.o -lbluetooth -lpthread

threadtest: threadtest.c
	gcc threadtest.c -o threadtest -lpthread	     
clean:
	 rm librfcommserver.so rfcommserver.o test

clean_threadtest:
	rm threadtest
