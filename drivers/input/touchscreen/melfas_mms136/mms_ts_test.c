#include "mms_ts_test.h"

 int get_cm_test_init(struct mms_ts_test *test)
{
	struct i2c_client *client = test->client;
	int ret = 0;
	u8 sz = 0;
	
	disable_irq(test->irq);
	memset(test->get_data,0,4096);
	sprintf(test->get_data,"start cm test\n");
	if(i2c_smbus_write_byte_data(test->client, MMS_UNIVERSAL_CMD, MMS_UNIV_ENTER_TEST)){
		dev_err(&client->dev,"i2c failed\n");
	}
	do{
		udelay(100);
	}while (gpio_get_value(test->pdata->gpio_resetb));
	sz = i2c_smbus_read_byte_data(test->client, MMS_EVENT_PKT_SZ);
	sz = i2c_smbus_read_byte_data(test->client, MMS_INPUT_EVENT);
	if(sz!=0x0C){
		dev_err(&client->dev,"maker\n");
		return -1;
	}
	sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
	sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT);
	return ret;
}

 int get_cm_test_exit(struct mms_ts_test *test)
{

	struct i2c_client *client = test->client;
	int ret = 0;
	if(i2c_smbus_write_byte_data(test->client, MMS_UNIVERSAL_CMD, MMS_UNIV_EXIT_TEST)){
		dev_err(&client->dev,"i2c failed\n");
		return -1;
	}
	enable_irq(test->irq);
	return ret;
	
}

 int get_cm_test_delta(struct mms_ts_test *test)
{
	struct i2c_client *client = test->client;
	int r, t;
	int ret = 0;
	int result = 1;
	u8 sz = 0;
	u8 buf[256]={0, };
	u8 reg[4]={ 0, };
	s16 cmdata;
	char data[6];
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = reg,
		},{
			.addr = client->addr,
			.flags = I2C_M_RD,
		},
	};
	printk("cm-delta\n");
	strcat(test->get_data,"\ncm-delta\n\n");
	
	if(i2c_smbus_write_byte_data(test->client, MMS_UNIVERSAL_CMD, MMS_UNIV_TEST_CM)){
		dev_err(&client->dev,"i2c failed\n");
	}

	do{
		udelay(100);
	}while (gpio_get_value(test->pdata->gpio_resetb));

	sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);

	result = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT);

	if( result == 1 ){
	 	dev_info(&client->dev, "Cm delta test pass\n");
		strcat(test->get_data,"\nCm delta test pass\n\n");
	}else{
		dev_err(&client->dev, "Cm delta test failed\n");
		strcat(test->get_data,"\nCm delta test failed\n");
		ret = -1;
		return ret;
	}
	msleep(1);
	
	printk("\t");

	for(t = 0; t < test->tx_num ; t++){
		printk("[%2d] ",t);
	}
		printk("\n");
	for(r = 0 ; r < test->rx_num; r++)
	{
		printk("[%2d]",r);
		sprintf(data,"[%2d]",r);
		strcat(test->get_data,data);
		memset(data,0,5);

		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = MMS_UNIV_GET_CM;
		reg[2] = 0xFF;
		reg[3] = r;
		msg[0].len = 4;
		
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "Cm delta i2c transfer failed\n");
			ret = -1;
			return ret;
		}
			
		while (gpio_get_value(test->pdata->gpio_resetb)){
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;			
			return ret;
		}
		for(t = 0; t< test->tx_num; t++){
			cmdata = (s16)(buf[2*t] | (buf[2*t+1] << 8));
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);
		

	}
	if (test->key_num)
	{
		printk("---key cm delta---\n");
		strcat(test->get_data,"key cm delta\n");
		memset(data,0,5);
		
		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = 0x4A;
		reg[2] = 0xFF;
		reg[3] = 0x00;
		msg[0].len = 4;
		
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "Cm delta i2c transfer failed\n");
			ret = -1;
			return ret;
		}
			
		while (gpio_get_value(test->pdata->gpio_resetb)){
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;			
			return ret;
		}
		for(t = 0; t< test->key_num; t++){
			cmdata = (s16)(buf[2*t] | (buf[2*t+1] << 8));
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);
		
	}
	
	return ret;
}

 int get_cm_test_abs(struct mms_ts_test *test)
{
	struct i2c_client *client = test->client;
	int r, t;
	int ret = 0;
	int result = 1;
	u8 sz = 0;
	u8 buf[256]={0, };
	u8 reg[4]={ 0, };
	s16 cmdata;
	char data[6];
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = reg,
		},{
			.addr = client->addr,
			.flags = I2C_M_RD,
		},
	};
	printk("cm-abs\n");
	strcat(test->get_data,"\ncm-abs\n\n");
	
	
	if(i2c_smbus_write_byte_data(test->client, MMS_UNIVERSAL_CMD, 0x43)){
		dev_err(&client->dev,"i2c failed\n");
	}
	do{
		udelay(100);
	}while (gpio_get_value(test->pdata->gpio_resetb));

	sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
	result = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT);

	if( result == 1 ){
	 	dev_info(&client->dev, "Cm abs test pass\n");
		strcat(test->get_data,"\nCm abs test pass\n\n");
	}else{
		dev_err(&client->dev, "Cm abs test failed\n");
		strcat(test->get_data,"\nCm abs test failed\n");
		ret = -1;
		return ret;
	}
	msleep(1);
	
	printk("\t");

	for(t = 0; t < test->tx_num ; t++){
		printk("[%2d] ",t);
	}
		printk("\n");
	for(r = 0 ; r < test->rx_num; r++)
	{
		printk("[%2d]",r);
		sprintf(data,"[%2d]",r);
		strcat(test->get_data,data);
		memset(data,0,5);

		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = 0x44;
		reg[2] = 0xFF;
		reg[3] = r;
		msg[0].len = 4;
		
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "Cm abs i2c transfer failed\n");
			ret = -1;
			return ret;
		}
			
		while (gpio_get_value(test->pdata->gpio_resetb)){
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;			
			return ret;
		}
		for(t = 0; t< test->tx_num; t++){
			cmdata = (s16)(buf[2*t] | (buf[2*t+1] << 8));
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);
		memset(data,0,5);

	}
	if (test->key_num)
	{
		printk("---key cm abs---\n");
		strcat(test->get_data,"key cm abs\n");
		memset(data,0,5);
		
		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = 0x4B;
		reg[2] = 0xFF;
		reg[3] = 0x00;
		msg[0].len = 4;
		
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "Cm delta i2c transfer failed\n");
			ret = -1;
			return ret;
		}
			
		while (gpio_get_value(test->pdata->gpio_resetb)){
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;			
			return ret;
		}
		for(t = 0; t< test->key_num; t++){
			cmdata = (s16)(buf[2*t] | (buf[2*t+1] << 8));
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);
		
	}
	return ret;
}

 int get_cm_test_jitter(struct mms_ts_test *test)
{
	struct i2c_client *client = test->client;
	int r, t;
	int ret = 0;
	int result = 1;
	u8 sz = 0;
	u8 buf[256]={0, };
	u8 reg[4]={ 0, };
	s16 cmdata;
	char data[6];
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = reg,
		},{
			.addr = client->addr,
			.flags = I2C_M_RD,
		},
	};
	printk("cm-jitter\n");
	strcat(test->get_data,"\ncm-jitter\n\n");
	
	
	if(i2c_smbus_write_byte_data(test->client, MMS_UNIVERSAL_CMD, 0x45)){
		dev_err(&client->dev,"i2c failed\n");
	}

	do{
		udelay(100);
	}while (gpio_get_value(test->pdata->gpio_resetb));

	sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);

	result = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT);

	if( result == 1 ){
	 	dev_info(&client->dev, "Cm jitter test pass\n");
		strcat(test->get_data,"\nCm jitter test pass\n\n");
	}else{
		dev_err(&client->dev, "Cm jitter test failed\n");
		strcat(test->get_data,"\nCm jitter test failed\n");
		ret = -1;
		return ret;
	}
	msleep(1);
	
	printk("\t");

	for(t = 0; t < test->tx_num ; t++){
		printk("[%2d] ",t);
	}
		printk("\n");
	for(r = 0 ; r < test->rx_num; r++)
	{
		printk("[%2d]",r);
		sprintf(data,"[%2d]",r);
		strcat(test->get_data,data);
		memset(data,0,5);

		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = 0x46;
		reg[2] = 0xFF;
		reg[3] = r;
		msg[0].len = 4;
		
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "Cm jitter i2c transfer failed\n");
			ret = -1;
			return ret;
		}
			
		while (gpio_get_value(test->pdata->gpio_resetb)){
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;			
			return ret;
		}
		for(t = 0; t< test->tx_num; t++){
			cmdata = buf[t];
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);
		memset(data,0,5);

	}
	if (test->key_num)
	{
		printk("---key cm delta---\n");
		strcat(test->get_data,"key cm jitter\n");
		memset(data,0,5);
		
		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = 0x4C;
		reg[2] = 0xFF;
		reg[3] = 0x00;
		msg[0].len = 4;
		
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "Cm delta i2c transfer failed\n");
			ret = -1;
			return ret;
		}
			
		while (gpio_get_value(test->pdata->gpio_resetb)){
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;			
			return ret;
		}
		for(t = 0; t< test->key_num; t++){
			cmdata = (buf[t]);
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);
		
	}
	return ret;
}

 int get_test_intensity(struct mms_ts_test *test)
{
	struct i2c_client *client = test->client;
	int r, t;
	int ret = 0;
	u8 sz = 0;
	u8 buf[42]={0, };
	u8 reg[4]={ 0, };
	s16 cmdata;
	char data[6];
	struct i2c_msg msg[] = {
		{
			.addr = client->addr,
			.flags = 0,
			.buf = reg,
		},{
			.addr = client->addr,
			.flags = I2C_M_RD,
		},
	};
	
	disable_irq(test->irq);
	memset(test->get_data,0,4096);
	sprintf(test->get_data,"start intensity\n");
	for(r = 0 ; r < test->rx_num ; r++)
	{

		printk("[%2d]",r);
		sprintf(data,"[%2d]",r);
		strcat(test->get_data,data);
		memset(data,0,5);

		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = MMS_UNIV_INTENSITY;
		reg[2] = 0xFF;
		reg[3] = r;
		msg[0].len = 4;
		
		msleep(1);
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "intensity i2c transfer failed\n");
			ret = -1;
			enable_irq(test->irq);
			return ret;
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		

		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;
			enable_irq(test->irq);
			return ret;
		}
		
		sz >>=1;
		for(t = 0 ; t <sz ; t++){		
			cmdata = (s16)(buf[2*t] | (buf[2*t+1] << 8));
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);

	}

	if (test->key_num)
	{
		printk("---key cm delta---\n");
		strcat(test->get_data,"key intensity\n");
		memset(data,0,5);
		
		reg[0] = MMS_UNIVERSAL_CMD;
		reg[1] = 0x71;
		reg[2] = 0xFF;
		reg[3] = 0x00;
		msg[0].len = 4;
		
		if(i2c_transfer(client->adapter, &msg[0],1)!=1){
			dev_err(&client->dev, "Cm delta i2c transfer failed\n");
			ret = -1;
			return ret;
		}
			
		while (gpio_get_value(test->pdata->gpio_resetb)){
		}
		
		sz = i2c_smbus_read_byte_data(test->client, MMS_UNIVERSAL_RESULT_LENGTH);
		
		reg[0] =MMS_UNIVERSAL_RESULT;
		msg[0].len = 1;
		msg[1].len = sz;
		msg[1].buf = buf;
		if(i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg))!=ARRAY_SIZE(msg)){
			ret = -1;			
			return ret;
		}
		for(t = 0; t< test->key_num; t++){
			cmdata = (s16)(buf[2*t] | (buf[2*t+1] << 8));
			printk("%5d",cmdata);
			sprintf(data,"%5d",cmdata);
			strcat(test->get_data,data);
			memset(data,0,5);
		}
		printk("\n");
		sprintf(data,"\n");
		strcat(test->get_data,data);
		memset(data,0,5);
		
	}
	enable_irq(test->irq);

	return 0;
}
