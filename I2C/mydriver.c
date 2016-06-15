/*
 * Tiny I2C Chip Driver
 *
 * Copyright (C) 2003 Greg Kroah-Hartman (greg@kroah.com)
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, version 2 of the License.
 *
 * This driver shows how to create a minimal I2C bus and algorithm driver.
 *
 * Compile this driver with:

	echo "obj-m := tiny_i2c_chip.o" > Makefile
	make -C <path/to/kernel/src> SUBDIRS=$PWD modules
 */

#define DEBUG 1

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>


#include <linux/stddef.h>

//static struct i2c_client * theclient;
/*
static int tiny_chip_detect(struct i2c_client *client, struct i2c_board_info * bip)
{
	printk("tiny_chip: trying to detect the device...\n");
	return 0;
}
*/
static s32 tiny_access(struct i2c_adapter *adap, u16 addr,
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
	case I2C_SMBUS_PROC_CALL:
		dev_info(&adap->dev, "size = I2C_SMBUS_PROC_CALL\n");
		break;
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
	case I2C_SMBUS_BLOCK_DATA:
		dev_info(&adap->dev, "size = I2C_SMBUS_BLOCK_DATA\n");
		if (read_write == I2C_SMBUS_WRITE) {
			dev_info(&adap->dev, "data = %.4x\n", data->word);
			len = data->block[0];
			if (len < 0)
				len = 0;
			if (len > 32)
				len = 32;
			for (i = 1; i <= len; i++)
				dev_info(&adap->dev, "data->block[%d] = %.2x\n",
					 i, data->block[i]);
		}
		break;
	}

	return 0;
}

static int tiny_chip_probe(struct i2c_client *client, const struct i2c_device_id *idp)
{
	printk("tiny_chip: trying to probe the device (%s)...\n",client->name);
	return 0;
}

static int tiny_chip_remove(struct i2c_client *client)
{
	printk("tiny_chip: trying to remove the device...\n");
	return 0;
}

/**/static struct i2c_device_id tiny_chip_idtable[] = {
	{ "mydriver", 0 },
	{ "my_other_driver", 1 },	
	{ }
};

/*
static struct i2c_board_info tiny_chip_info[] = {
	{
		I2C_BOARD_INFO("mydriver", 0x60),		
	},
};
*/
struct i2c_board_info tiny_chip_info = {
    .type = "mydriver",
    .addr = 0x60,
  };

/* This is the driver that will be inserted */
static struct i2c_driver chip_driver = {

	.driver = {
		.name ="mydriver",
		.owner=THIS_MODULE,
		
	},
	//.owner		= THIS_MODULE,
	//.name		= "tiny_chip",
	//.flags		= I2C_DF_NOTIFY,
	//.attach_adapter	= chip_attach_adapter,
	//.detach_client	= chip_detach_client,
	.id_table = tiny_chip_idtable,
	.probe = tiny_chip_probe,
	.remove = tiny_chip_remove,
	//.detect = tiny_chip_detect,
};
static u32 tiny_func(struct i2c_adapter *adapter)
{
	return I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA;
}
static struct i2c_algorithm tiny_algorithm = {

	.smbus_xfer	= tiny_access,
	.functionality	= tiny_func,
};

static struct i2c_adapter tiny_adapter = {
	.owner		= THIS_MODULE,
	//.class		= I2C_ADAP_CLASS_SMBUS,
	.algo		= &tiny_algorithm,
	.name		= "tiny adapter",
};

static int __init tiny_init(void)
{

	printk("tiny chip: Adding adapter, result=%d\n",i2c_add_adapter(&tiny_adapter));
	printk("tiny_chip: creating new device...\n");
	i2c_new_device(&tiny_adapter,&tiny_chip_info);
	printk("tiny_chip: trying to add the device driver...\n");	
	return i2c_add_driver(&chip_driver);
}

static void __exit tiny_exit(void)
{
	printk("tiny_chip: trying to delete the device driver...\n");
	i2c_del_driver(&chip_driver);
}


MODULE_AUTHOR("Greg Kroah-Hartman <greg@kroah.com>");
MODULE_DESCRIPTION("Tiny i2c chip");
MODULE_LICENSE("GPL");

module_init(tiny_init);
module_exit(tiny_exit);
