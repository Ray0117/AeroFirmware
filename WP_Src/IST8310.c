
#include "Headfile.h"
#include "I2C.h"
#include "WP_DataType.h"
#include "IST8310.h"



Vector2f magn={0,0};
Vector3f mag_offset;
Butter_Parameter Mag_Parameter;
/***********************************************************
@��������IST8310_Init
@��ڲ�������
@���ڲ�������
���������������Ƴ�ʼ������
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void IST8310_Init(void)//�����Ƴ�ʼ������
{
	Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x41,0x24);//����16x�ڲ�ƽ��
	Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x42,0xC0);//Set/Reset�ڲ�ƽ��
  Set_Cutoff_Frequency(40, 18,&Mag_Parameter);//������У׼�Ӽ��˲�ֵ
}

/***********************************************************
@��������IST8310_Read_Data
@��ڲ�����vector3f *mag
@���ڲ�������
�������������������ݲɼ�״̬��
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
uint8_t IST8310_Read_Data(vector3f *mag)//��ȡ����������״̬��
{
  static uint16_t ist8310_sampling_cnt=0;
  uint8_t buf[6];
  ist8310_sampling_cnt++;
  if(ist8310_sampling_cnt==1)
  {
    Single_WriteI2C(IST8310_SLAVE_ADDRESS,IST8310_REG_CNTRL1,0x01);//Single Measurement Mode	
  }
  else if(ist8310_sampling_cnt==6)
  {
    buf[0]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x03);//OUT_X_L_A
    buf[1]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x04);//OUT_X_H_A
    buf[2]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x05);//OUT_Y_L_A
    buf[3]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x06);//OUT_Y_H_A
    buf[4]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x07);//OUT_Z_L_A
    buf[5]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x08);//OUT_Z_H_A
    mag->x= (int16_t)((buf[1]<<8)|buf[0]);
    mag->y=-(int16_t)((buf[3]<<8)|buf[2]);
    mag->z= (int16_t)((buf[5]<<8)|buf[4]);
    ist8310_sampling_cnt=0;
    return 1;
  }
  return 0;
}



