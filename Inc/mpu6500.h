#ifndef __MPU6500_H
#define __MPU6500_H

#include "sys.h"

#define spi1ncs PAout(4)

typedef struct
{
    s16 x;
    s16 y;
    s16 z;
}S16_XYZ;

#define BYTE16(Type, ByteH, ByteL)  ((Type)((((u16)(ByteH))<<8) | ((u16)(ByteL))))

#define SELF_TEST_X_GYRO		0X00
#define SELF_TEST_Y_GYRO		0X01
#define SELF_TEST_Z_GYRO		0X02

#define SELF_TEST_X_ACCEL		0X0D
#define SELF_TEST_Y_ACCEL		0X0E
#define SELF_TEST_Z_ACCEL		0X0F

#define XG_OFFSET_H					0X13
#define XG_OFFSET_L					0X14
#define YG_OFFSET_H					0X15
#define YG_OFFSET_L					0X16
#define ZG_OFFSET_H					0X17
#define ZG_OFFSET_L					0X18

#define SMPLRT_DIV					0X19 //�����ǲ�����
#define CONFIG						0X1A //��ͨ�˲���  ����ֵ0x06 5hz
#define GYRO_CONFIG					0X1B //�����ǲ�����Χ 0X18 ����2000��
#define ACCEL_CONFIG				0X1C //���ٶȼƲ�����Χ 0X18 ����16g
#define ACCEL_CONFIG2				0X1D //���ٶȼƵ�ͨ�˲��� 0x06 5hz

#define LP_ACCEL_ODR				0X1E
#define WOM_THR						0X1F
#define FIFO_EN						0X23

#define ACCEL_XOUT_H				0X3B  //���ٶȼ���������
#define ACCEL_XOUT_L				0X3C
#define ACCEL_YOUT_H				0X3D
#define ACCEL_YOUT_L				0X3E
#define ACCEL_ZOUT_H				0X3F
#define ACCEL_ZOUT_L				0X40

#define TEMP_OUT_H					0X41  //�¶ȼ���������
#define TEMP_OUT_L					0X42

#define GYRO_XOUT_H					0X43  //��������������
#define GYRO_XOUT_L					0X44
#define GYRO_YOUT_H					0X45
#define GYRO_YOUT_L					0X46
#define GYRO_ZOUT_H					0X47
#define GYRO_ZOUT_L					0X48

#define SIGNAL_PATH_RESET           0X68 //�����ǡ����ٶȼơ��¶ȴ������źŸ�λ
#define USER_CTRL					0X6A //�û����� ��Ϊ0X10ʱʹ��SPIģʽ
#define PWR_MGMT_1					0X6B //��Դ����1 ����ֵΪ0x00
#define PWR_MGMT_2					0X6C //��Դ����2 ����ֵΪ0X00

#define WHO_AM_I					0X75 //����ID MPU9250Ĭ��IDΪ0X71
#define WHO_AM_MAG					0X00 //����ID MPU9250Ĭ��IDΪ0X71

u8 MPU6500_Read_Reg(u8 reg);
void mpu6500_init(void);
void mpu6500_ReadValue(void);
void mpu6500_ReadtoUSB(void);

#endif

