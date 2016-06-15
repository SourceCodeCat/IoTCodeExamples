/*
 * MPL3115A2 Driver
 *
 * Copyright (C) 2016 Marco Antonio Salgado Martinez
		      (marco.antonio.salgado.martinez@intel.com
		       ing.marco@gmail.com)
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, version 2 of the License.
 *
 * This driver shows how toimplement a minimal driver for the I2C MPL3115A2
 * barometric chip.
 */

#ifndef MPL3115A2_H
#define MPL3115A2_H

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/stddef.h>

#define TAG "MPL3115A2"

#define MPL3115A2_ID		196	//Device id, should be returned by WHO_AM_I register
#define MPL3115A2_WHO_AM_I      0x0c	//Device Identification Register

static struct i2c_client * MPL3115A2_client;
struct i2c_adapter * MPL3115A2_adapter;

/*
static s32 bus_access(struct i2c_adapter *adap, u16 addr,
		       unsigned short flags, char read_write,
		       u8 command, int size, union i2c_smbus_data *data)
{
	int i;
	int len;

	dev_info(&adap->dev, "%s was called with the following parameters:\n",
		 __FUNCTION__);
	dev_info(&adap->dev, "addr = %.4x\n", addr);
	dev_info(&adap->dev, "flags = %.4x\n", flags);
	dev_info(&adap->dev, "read_write = %s\n",
		 read_write == I2C_SMBUS_WRITE ? "write" : "read");
	dev_info(&adap->dev, "command = %d\n", command);
	
	switch (size) {
	case I2C_SMBUS_QUICK:
		dev_info(&adap->dev, "size = I2C_SMBUS_QUICK\n");
		break;
	case I2C_SMBUS_BYTE:
		dev_info(&adap->dev, "size = I2C_SMBUS_BYTE\n");
		break;
	case I2C_SMBUS_BYTE_DATA:
		dev_info(&adap->dev, "size = I2C_SMBUS_BYTE_DATA\n");
		if (read_write == I2C_SMBUS_WRITE)
			dev_info(&adap->dev, "data = %.2x\n", data->byte);
		break;
	case I2C_SMBUS_WORD_DATA:
		dev_info(&adap->dev, "size = I2C_SMBUS_WORD_DATA\n");
		if (read_write == I2C_SMBUS_WRITE)
			dev_info(&adap->dev, "data = %.4x\n", data->word);
		break;
	}

	return 0;
}
*/
static struct i2c_device_id device_idtable[] = {
	{ "MPL3115A2", 0 },
	{ }
};
/**/
static struct i2c_board_info board_info = {
	.type = "MPL3115A2",
	.addr = 0x60,
};

/*
static u32 MPL3115A2_func(struct i2c_adapter *adapter)
{
	return I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA;
}
*/
/*
static struct i2c_algorithm MPL3115A2_algorithm = {

	.smbus_xfer	= bus_access,
	.functionality	= MPL3115A2_func,
};
*/

/*
static struct i2c_adapter MPL3115A2_adapter = {
	.owner		= THIS_MODULE,
	//.class		= I2C_ADAP_CLASS_SMBUS,
	.algo		= &MPL3115A2_algorithm,
	.name		= "MPL3115A2 adapter",
};
*/






#endif
