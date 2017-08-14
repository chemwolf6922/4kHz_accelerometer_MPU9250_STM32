/*
MPU6500/9250 driver
*/

#include "mpu6500.h"
#include "usbd_cdc_if.h"


S16_XYZ MPU6500_Acc;
extern SPI_HandleTypeDef hspi1;
u8 spi1txbuffer[15] = {0};
u8 spi1rxbuffer[15] = {0};
u8 usb_enable = 0;


u8 MPU6500_Read_Reg(u8 reg)
{
    spi1txbuffer[0] = reg|0x80;
    spi1txbuffer[1] = 0xFF;
	spi1ncs = 0;
    HAL_SPI_TransmitReceive(&hspi1, spi1txbuffer, spi1rxbuffer, 2, 2);
	spi1ncs = 1;
	return(spi1rxbuffer[1]);
}

void MPU6500_Write_Reg(u8 reg,u8 value)
{
    spi1txbuffer[0] = reg;
    spi1txbuffer[1] = value;
	spi1ncs = 0;
	HAL_SPI_TransmitReceive(&hspi1, spi1txbuffer, spi1rxbuffer, 2, 2);
	spi1ncs = 1;
}

/*
Accelerometer init code
This function sets the sample rate and opration mode of the sensor.
For details please refer to the datasheet and register map.
*/
void mpu6500_init(void){
	MPU6500_Write_Reg(PWR_MGMT_1,0X80); 		//Reset the sensor	
	HAL_Delay(100);
	MPU6500_Write_Reg(SIGNAL_PATH_RESET,0X07);	//Reset all the digital signal path
	HAL_Delay(100);
	MPU6500_Write_Reg(PWR_MGMT_1,0X01);   		//Auto select the best clock source
	#ifdef GYRO
	MPU6500_Write_Reg(PWR_MGMT_2,0X38);			//Enable gyro Disable acc
	#else	
	MPU6500_Write_Reg(PWR_MGMT_2,0X07);			//Enable acc Disable gyro
	#endif
	#ifndef MAX_SPEED
	MPU6500_Write_Reg(PWR_MGMT_2,0X00);			//Enable all sensors
	#endif
	MPU6500_Write_Reg(CONFIG,0X07);				//Only effective using gyro, Set sample rate to 8 kHz
	MPU6500_Write_Reg(SMPLRT_DIV,0X00);			//Only effective using gyro, Set sample rate to 8 kHz	
	MPU6500_Write_Reg(GYRO_CONFIG,0X18);  		//Set gyro full range to +-2000 dps
	MPU6500_Write_Reg(ACCEL_CONFIG,0x10); 		//Set Acc full range to +-8G
	MPU6500_Write_Reg(ACCEL_CONFIG2,0x08);		//Bypass Acc DLPF to get 4k saple rate
	#ifdef MAX_SPEED
	MPU6500_Write_Reg(56,0x01);					//Enable data ready interupt
	#else
	MPU6500_Write_Reg(56,0x00);					//Disable data ready interupt
	#endif
}

void mpu6500_ReadValue(void){
	
	spi1txbuffer[0] = ACCEL_XOUT_H|0x80;
	for(u8 i = 1;i!=15;i++){
		spi1txbuffer[i] = 0xFF;
	}
	spi1ncs = 0;
	HAL_SPI_TransmitReceive(&hspi1, spi1txbuffer, spi1rxbuffer, 7, 10);
	spi1ncs = 1;
	MPU6500_Acc.x = BYTE16(s16, spi1rxbuffer[1] , spi1rxbuffer[2]);
	MPU6500_Acc.y = BYTE16(s16, spi1rxbuffer[3] , spi1rxbuffer[4]);
	MPU6500_Acc.z = BYTE16(s16, spi1rxbuffer[5] , spi1rxbuffer[6]);
}

void mpu6500_ReadtoUSB(void){
	#ifdef GYRO
	spi1txbuffer[0] = GYRO_XOUT_H|0x80;
	#else
	spi1txbuffer[0] = ACCEL_XOUT_H|0x80;
	#endif
	#ifndef MAX_SPEED
	spi1txbuffer[0] = ACCEL_XOUT_H|0x80;
	#endif
	for(u8 i = 1;i!=15;i++){
		spi1txbuffer[i] = 0xFF;
	}
	spi1ncs = 0;
	#ifdef MAX_SPEED
	HAL_SPI_TransmitReceive(&hspi1, spi1txbuffer, spi1rxbuffer, 7, 1);
	#else
	HAL_SPI_TransmitReceive(&hspi1, spi1txbuffer, spi1rxbuffer, 15, 1);
	#endif
	spi1ncs = 1;
	spi1rxbuffer[0] = 0xaa;
	if(usb_enable){
		#ifdef MAX_SPEED
		CDC_Transmit_FS(spi1rxbuffer+1,6);		// 6 bytes acc or gyro
		#else
		CDC_Transmit_FS(spi1rxbuffer+1,14);		// 6 bytes acc + 2 bytes temperature + 6 bytes gyro
		#endif
	}
}

