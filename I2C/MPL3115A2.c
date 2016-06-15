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
 * This driver shows how to implement a minimal driver for the I2C MPL3115A2
 * barometric chip.
 */
#include "MPL3115A2.h"

s32 readWordRegister(const struct i2c_client *client, u8 reg)
{
	
	s32 res;
	res = i2c_smbus_read_word_data(client, reg);
	if (res < 0)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printk("%s: Error reading reg: 0x%x, code:%d \n",TAG,reg,res);
	}
	return res;
	
}

static int MPL3115A2_probe(struct i2c_client *client, const struct i2c_device_id *idp)
{
//	printk("%s: trying to probe the device (%s)...\n",__FUNCTION__,client->name);
/**/
	s32 id;
	printk("%s: trying to probe the device (%s)...\n",
		__FUNCTION__,client->name);
	id = readWordRegister(client, MPL3115A2_WHO_AM_I);
	printk("%s: device id: %d \n",TAG,id);
	printk("%s: device %s \n",__FUNCTION__, (id == MPL3115A2_ID)?"SUCCESSFULLY identified":"FAILED to be identified");
	return 0;
}
static int MPL3115A2_remove(struct i2c_client *client)
{
	printk("%s: trying to remove the device...\n",__FUNCTION__);
	i2c_unregister_device(MPL3115A2_client);
	//i2c_del_adapter(MPL3115A2_adapter);
	return 0;
}
static struct i2c_driver MPL3115A2_driver = {

	.driver = {
		.name ="MPL3115A2",
		.owner=THIS_MODULE,
		
	},
	.id_table = device_idtable,
	.probe = MPL3115A2_probe,
	.remove = MPL3115A2_remove,
};

static int __init MPL3115A2_init(void)
{

	printk("%s: Obtaining adapter from bus 1\n",__FUNCTION__);	
	MPL3115A2_adapter = i2c_get_adapter(1);
	printk("%s: creating new device...\n",__FUNCTION__);
	MPL3115A2_client = i2c_new_device(MPL3115A2_adapter,&board_info);
	printk("%s: trying to add the device driver...\n",__FUNCTION__);	
	return i2c_add_driver(&MPL3115A2_driver);
}

static void __exit MPL3115A2_exit(void)
{
	printk("%s: trying to delete the device driver...\n",__FUNCTION__);
	i2c_del_driver(&MPL3115A2_driver);	
}


MODULE_AUTHOR("Marco A Salgado Mtz <ing.marco@gmail.com>");
MODULE_DESCRIPTION("I2C MPL3115A2 Barometer");
MODULE_LICENSE("GPL");

module_init(MPL3115A2_init);
module_exit(MPL3115A2_exit);
