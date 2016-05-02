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
	
#define MPL3115A2_WHO_AM_I      0x0c	//Device Identification Register
#define MPL3115A2_SYSMOD	0x11	//System Mode Register || Current system mode
#define MPL3115A2_CTRL_REG1	0x26	//Control Register 1 || Modes, Oversampling
#define MPL3115A2_CTRL_REG2	0x27	//Control Register 2 ||	Acquisition time step	 
#define MPL3115A2_CTRL_REG3	0x28	//Control Register 3 || Interrupt pin configuration
#define MPL3115A2_CTRL_REG4	0x29	//Control Register 4 || Interrupt enables
#define MPL3115A2_CTRL_REG5	0x2A	//Control Register 5 || Interrupt output pin assignment
#define MPL3115A2_STATUS	0x00	//Sensor Status Register 
#define MPL3115A2_OFF_T		0x2C	//Temperature Data Offset Register
#define MPL3115A2_BUS		0x01	//I2C bus where the device is connected
#define MPL3115A2_SLAVE		0x60	//I2C slave address of the device
#define MPL3115A2_OUT_T_MSB	0x04
#define MPL3115A2_OUT_T_LSB	0x05
#define MPL3115A2_DR_STATUS	0x06	//
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

__s32 writeregister(int file, __u8 command, __u16 value)
{
	__s32 res = -1;

	res = i2c_smbus_write_word_data(file, command, value);
	if (res < 0)
	{
	    /* ERROR HANDLING: i2c transaction failed */
		printf("Error writing reg: 0x%x, (errno:%d),%s",
				command,errno,strerror(errno));
	}
	/*
	else
	{
		printf("result: 0x%x\n",res);
	}
	*/
	return res;

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
		printf("Error reading reg: 0x%x, (errno:%d),%s",
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
void getTemp(int file)
{
	float temperature = 0.0;
	__s32 res = readRegister(MPL3115A2_DR_STATUS, file);
	printf("DR_STATUS: 0x%x",res);
	printf("DR_STATUS | 0x02: 0x%x",res | (1<<1));
	/*
	if(res & (1<<1)==0)
	{
		printf("Doing oneShot");
		__s32 ctrl_reg1=readRegister(MPL3115A2_CTRL_REG1,file);
		ctrl_reg1 &= ~(1<<1);
		writeregister(file, MPL3115A2_CTRL_REG1, ctrl_reg1);
		ctrl_reg1=readRegister(MPL3115A2_CTRL_REG1,file);
		ctrl_reg1 |= (1<<1);
		writeregister(file, MPL3115A2_CTRL_REG1, ctrl_reg1);
	}
	int count = 0;
	while(count < 600)
	{ 
		res = readRegister(MPL3115A2_DR_STATUS, file);
		printf("DR_STATUS: 0x%x",res);
		if(res & (1<<1)==0)
		{
			printf("waiting...");
			count++;
			sleep(1);
		}
		else
		{
			printf("MAU!");
			count=600;
		}
	}
*/	

}
int main()
{

	int addr = MPL3115A2_SLAVE; /* The I2C address */
	int file;
	int adapter_nr = MPL3115A2_BUS; /* probably dynamically determined */
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
	getTemp(file);
	printf("\nDONE!\n");
	return 0;
}
