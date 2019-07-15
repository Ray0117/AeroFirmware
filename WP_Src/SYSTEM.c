
#include "Headfile.h"
#include "SYSTEM.h"

/***********************************************************
@��������HardWave_Init
@��ڲ�������
@���ڲ�������
������������ϵͳоƬ��Դ����Ӳ����Դ����һϵ�г�ʼ���������
����ʼ�����ע��
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void HardWave_Init(void)
{
	WP_Init();//�ɿس�ʼ��
  Butterworth_Parameter_Init();//�˲���������ʼ��
  PPM_Init();//PPM������ʼ��
  Init_PWM();//PWM��ʼ��
  Bling_Init();//LED״ָ̬ʾ�Ƴ�ʼ��
  Quad_Start_Bling();//����LEDԤ��ʾ
  Key_Init();//���ذ�����ʼ��
  RC_Calibration_Trigger();//ң�����г̱궨���
  Horizontal_Calibration_Init();//����ˮƽ�궨��ʼ��
  PID_Paramter_Init_With_Flash();//PID������ʼ��
  Init_I2C();//Ӳ��I2C��ʼ��
  Init_MPU6050();//MPU6050�����ǡ����ٶȼ����ó�ʼ��
//  Compass_Init();//���������ó�ʼ��
  SPL06_Init();//SPL06��ѹ�����ó�ʼ��
  Parameter_Init();//���ٶȼơ�������У׼������ʼ��
  WP_Quad_Init();//���ݹ۲⴫�������ٶȼơ������ƶ���̬��Ԫ����ʼ��
  ConfigureUART1();//����1��ʼ������������վ
  ConfigureUART3();//����3��ʼ����OPENMV����ݮ���Ӿ�ģ�顢SDKģʽ����
  ConfigureUART2();//����2��ʼ������OPENMV
//  Set_GPS_USART();//����2��ʼ����ʹ��UBLOXЭ������GPSģ��
  ConfigureUART7();//����7��ʼ��.������ģ��/TOF��������	
  ConfigureUART6();//����6��ʼ��������ģ��LC306���ݽ���
  SDK_Init();//SDKģʽ��ʼ��
	Temperature_Ctrl_Init();
  Time_init();//�ɿص��ȶ�ʱ����ʼ��
  delay_ms(200);//��ʼ����ʱ	
}

