//#include<stdio.h>
//#include<errno.h>
//#include<fcntl.h>
//#include <string.h>
//#include"linux/i2c-dev.h"
////#include <stdlib.h>
////#include <unistd.h>
////#include <inttypes.h>
////#include <sys/types.h>
////#include <sys/errno.h>
//#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	#define MPL3115A2_WHO_AM_I      0x0c

	int addr = 0x60; /* The I2C address */
	int file;
	int adapter_nr = 1; /* probably dynamically determined */
	char filename[20];
	snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
	file = open(filename, O_RDWR);
	if (file < 0) 
	{
	   /* ERROR HANDLING; you can check errno 2 c what went wrong */
		printf("Error ocurred @ opening BUS: (errno:%d) %s\n",
				errno,
				strerror(errno));
		return 1;	

	}

	
	if (ioctl(file, I2C_SLAVE, addr) < 0)
	{
      	  /* ERROR HANDLING; you can check errno 2 c what went wrong */
		printf("Error ocurred @ accessing slave: (errno:%d) %s\n",
					errno,
					strerror(errno));
	}

	/* Using SMBus commands */
	__u8 reg = 0x0c; /* Device register to access */
	__s32 res;
	char buf[10];  
	res = i2c_smbus_read_word_data(file, reg);
	if (res < 0)
	{
	    /* ERROR HANDLING: i2c transaction failed */
		printf("Error reading reg: %d, (errno:%d),%s",
				reg,errno,strerror(errno));
	}
	else
	{
	    /* res contains the read word */
		printf("result: %s",res);	
	}


	printf("Hello, DONE! %d\n",50);
	return 0;
}
