#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev-user.h>
//#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>



typedef struct
{
	int addr; //i2c address of device
	int file; //reprsents a place to do the i2c read & write
	int adapter_nr; //the bus number of the device
	char filename[20]; //the name of the device
}I2CCONTEXT;
/////////////////////////////////////////////////////////

int initContext(I2CCONTEXT *ctx, int addr_,int bus)
{
	ctx->addr = addr_;
	ctx->adapter_nr = bus;
	snprintf(ctx->filename, 19, "/dev/i2c-%d", ctx->adapter_nr);
	ctx->file = open(ctx->filename, O_RDWR);
	if (ctx->file < 0) 
	{
	   /* ERROR HANDLING; you can check errno 2 c what went wrong */
		printf("Error ocurred @ opening BUS: (errno:%d) %s\n",
				errno,
				strerror(errno));
		return -errno;	

	}
	
	if (ioctl(ctx->file, I2C_SLAVE, ctx->addr) < 0)
	{
      	  /* ERROR HANDLING; you can check errno 2 c what went wrong */
		printf("Error ocurred @ accessing slave: (errno:%d) %s\n",
					errno,
					strerror(errno));
		return -errno;
	}

}
/////////////////////////////////////////////////////////
int i2cRead(int file, int reg)
{
	int buf[1]={reg}; 
	if(read(file, buf, 1) != 1)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Error ocurred @ reading from slave: (errno:%d) %s\n",
					errno,
					strerror(errno));
		return -errno;
	}
	else
	{
    		/* buf[0] contains the read byte */
  		printf("Value from reg 0x%x : 0x%x\n", reg , buf[0]);
		return 0;
	}	
}
int i2cWrite(int file, int reg, int data)
{
	int buf[2]={reg , data};
        if (write(file, buf, 2) != 2)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Error ocurred @ writing to slave: (errno:%d) %s\n",
					errno,
					strerror(errno));
		return -errno;

	}
	else
	{
		printf("Success writing to: 0x%x\n",buf[0]);
		return 1;
	}
}
__s32 writebyteregister(int file, __u8 command, __u8 value)
{
	__s32 res = -1;
	res = i2c_smbus_write_byte_data(file, command, value);
	if (res < 0)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Error writing byte, (errno:%d),%s",errno,
				strerror(errno));
	}
}
