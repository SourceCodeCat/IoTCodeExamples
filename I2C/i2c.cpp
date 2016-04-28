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
#include <linux/i2c-dev-user.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
	
#define MPL3115A2_WHO_AM_I      0x0c
#define MPL3115A2_SYSMOD	0x11
#define MPL3115A2_CTRL_REG1	0x26

//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_
//#define MPL3115A2_

__s32 readregister(int file, __u8 command, __u16 value)
{
	i2c_smbus_write_word_data(int file, __u8 command, __u16 value);
}
__s32 readRegister(int r, int file)
{
	/* Using SMBus commands */
	__u8 reg = r; /* Device register to access */
	__s32 res = -1;
	char buf[10];  
	res = i2c_smbus_read_word_data(file, reg);
	if (res < 0)
	{
	    /* ERROR HANDLING: i2c transaction failed */
		printf("Error reading reg: %d, (errno:%d),%s",
				reg,errno,strerror(errno));
	}
	/*
	else
	{
		printf("result: 0x%x\n",res);
	}
	*/
	return res;
}
int main()
{

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

	////////////////////////////////////////////////////////////
	__s32 res;	
	res=readRegister(MPL3115A2_WHO_AM_I,file);
	printf("MPL3115A2_WHO_AM_I: 0x%x\n",res);
	res=readRegister(MPL3115A2_SYSMOD,file);
	printf("MPL3115A2_SYSMOD: 0x%x\n",res);
	printf("DONE!\n");
	return 0;
}
