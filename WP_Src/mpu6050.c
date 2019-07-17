
#include "Headfile.h"
#include "myiic.h"
#include "mpu6050.h"
Butter_Parameter Ins_Accel_Parameter;
Butter_Parameter Accel_Parameter;
Butter_Parameter Gyro_Parameter;
Butter_Parameter Calibrate_Parameter;
uint8_t IMU_ID=0x68; 
/***********************************************************
@��������Init_MPU6050
@��ڲ�������
@���ڲ�������
����������MPU6050��ʼ��
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void Init_MPU6050(void)//MPU6050��ʼ��
{
	IMU_ID=Single_ReadI2C(MPU_ADRESS,WHO_AM_I);
  if(IMU_ID==IMU_MPU6050_ID)//MPU6050
	{
		i2cWrite(MPU_ADRESS,PWR_MGMT_1  , 0x00);//�ر������ж�,�������
		i2cWrite(MPU_ADRESS,SMPLRT_DIV  , 0x00); // sample rate.  Fsample= 1Khz/(<this value>+1) = 1000Hz
		//i2cWrite(MPU_ADRESS,MPU_CONFIG  , 0x02); //�ڲ���ͨ�˲�Ƶ�ʣ����ٶȼ�94hz��������98hz
		i2cWrite(MPU_ADRESS,MPU_CONFIG  , 0x03);//�ڲ���ͨ�˲�Ƶ�ʣ����ٶȼ�44hz��������42hz
		i2cWrite(MPU_ADRESS,GYRO_CONFIG , 0x10);//1000deg/s
		i2cWrite(MPU_ADRESS,ACCEL_CONFIG, 0x18);// Accel scale 16g (2048 LSB/g)
	}
	else if(IMU_ID==IMU_ICM20689_ID)//ICM20689
	{	
		i2cWrite(MPU_ADRESS,PWR_MGMT_1  , 0x00);//�ر������ж�,�������
		i2cWrite(MPU_ADRESS,SMPLRT_DIV  , 0x00); // sample rate.  Fsample= 1Khz/(<this value>+1) = 1000Hz	
		i2cWrite(MPU_ADRESS,MPU_CONFIG  , 0x03);//���������ǡ��¶��ڲ���ͨ�˲�Ƶ�ʷ�Χ��������41hz����������59hz���¶�42hz	
		i2cWrite(MPU_ADRESS,GYRO_CONFIG , 0x10);//�������������̣�1000deg/s
		i2cWrite(MPU_ADRESS,ACCEL_CONFIG, 0x18);// Accel scale 16g (2048 LSB/g)	
		i2cWrite(MPU_ADRESS,ACCEL_CONFIG2,0x03);//���ü��ٶȼ��ڲ���ͨ�˲�Ƶ�ʷ�Χ�����ٶ�44.8hz����������61.5hz
	}
}
/***********************************************************
@��������MPU6050_Read_Data
@��ڲ�����vector3f *gyro,vector3f *accel
@���ڲ�������
����������MPU6050���ݲɼ�
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void MPU6050_Read_Data(vector3f *gyro,vector3f *accel)//��ȡMPU6050����
{
  accel->x=Double_ReadI2C(MPU_ADRESS,ACCEL_XOUT_H);
  accel->y=Double_ReadI2C(MPU_ADRESS,ACCEL_YOUT_H);
  accel->z=Double_ReadI2C(MPU_ADRESS,ACCEL_ZOUT_H);
	
  gyro->x=Double_ReadI2C(MPU_ADRESS,GYRO_XOUT_H);
  gyro->y=Double_ReadI2C(MPU_ADRESS,GYRO_YOUT_H);
  gyro->z=Double_ReadI2C(MPU_ADRESS,GYRO_ZOUT_H);
}


/***********************************************************
@MPU6050_Read_Temperature
@��ڲ�����float *temperature
@���ڲ�������
����������MPU6050�¶����ݲɼ�
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void MPU6050_Read_Temperature(float *temperature)
{
	if(IMU_ID==IMU_MPU6050_ID)
	{
		//MPU6050
		//Sensitivity=340 LSB/��C
		//Temperature Offset=35 ��C
		*temperature=36.53+((double)Double_ReadI2C(MPU_ADRESS,TEMP_OUT_H))/340;
	}
	if(IMU_ID==IMU_ICM20689_ID)
	{
		//ICM20689
		//Room Temperature Offset=25 ��C
		//Sensitivity=326.8 LSB/��C
		//TEMP_degC = ((TEMP_OUT �CRoomTemp_Offset)/Temp_Sensitivity) +25degC
		*temperature=25.0f+((double)Double_ReadI2C(MPU_ADRESS,TEMP_OUT_H)-25.0f)/326.8;
	}
	
  //ICM20602
	//Room Temperature Offset=25 ��C
	//Sensitivity=326.8 LSB/��C
	//TEMP_degC =(TEMP_OUT)/Temp_Sensitivity +25degC
	//*temperature=25.0f+(double)Double_ReadI2C(MPU_ADRESS,TEMP_OUT_H)/326.8;
}
Vector3f gyro_offset;
s32 g_Gyro_xoffset = 0, g_Gyro_yoffset = 0, g_Gyro_zoffset = 0;
/***********************************************************
@��������IMU_Calibration
@��ڲ�������
@���ڲ�������
���������������ǿ�����ƫ�궨
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void IMU_Calibration(void)
{
  u8 i;
  delay_ms(500);
  for (i = 0; i < 100; i++)			//��������30�Σ�һ����ʱ30*3=90ms
  {
    g_Gyro_xoffset +=Double_ReadI2C(MPU_ADRESS,GYRO_XOUT_H);
    g_Gyro_yoffset +=Double_ReadI2C(MPU_ADRESS,GYRO_YOUT_H);
    g_Gyro_zoffset +=Double_ReadI2C(MPU_ADRESS,GYRO_ZOUT_H);
    delay_ms(10);
  }
  gyro_offset.x =(g_Gyro_xoffset/100);//�õ��궨ƫ��
  gyro_offset.y =(g_Gyro_yoffset/100);
  gyro_offset.z =(g_Gyro_zoffset/100);
}

