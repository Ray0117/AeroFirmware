
#include "Headfile.h"
#include "Temperature_Ctrl.h"

#define Temperature_Ctrl_Enable   1

#define Temperature_Setpoint   50
const float Temp_Control_Unit[20]=
{1  ,1 ,1 ,0 ,0 ,0 , 0 ,50    ,30  ,0 ,80,  20.00  ,3.0   ,100.0  ,0    ,0 ,100 , 1 ,  1 ,  1 };//ˮƽά�ȷ�����ٶȿ����� 20 3 50  //  10  3  80
/*
1ƫ���޷���־��  2�����޷���־��3���ַ����־��   4������
5����            6ƫ�        7�ϴ�ƫ�       8ƫ���޷�ֵ��
9���ַ���ƫ��ֵ��10����ֵ       11�����޷�ֵ��    12���Ʋ���Kp��
13���Ʋ���Ki��   14���Ʋ���Kd�� 15�������������  16�ϴο����������
17������޷��ȣ� 18����ֿ���ʱ�Ļ�������
*/		
void Temperature_Ctrl_Init(void)
{
  Total_Controller.IMU_Temperature_Control.Err_Limit_Flag=(uint8)(Temp_Control_Unit[0]);//1ƫ���޷���־
  Total_Controller.IMU_Temperature_Control.Integrate_Limit_Flag=(uint8)(Temp_Control_Unit[1]);//2�����޷���־
  Total_Controller.IMU_Temperature_Control.Integrate_Separation_Flag=(uint8)(Temp_Control_Unit[2]);//3���ַ����־
  Total_Controller.IMU_Temperature_Control.Expect=Temp_Control_Unit[3];//4����
  Total_Controller.IMU_Temperature_Control.FeedBack=Temp_Control_Unit[4];//5����ֵ
  Total_Controller.IMU_Temperature_Control.Err=Temp_Control_Unit[5];//6ƫ��
  Total_Controller.IMU_Temperature_Control.Last_Err=Temp_Control_Unit[6];//7�ϴ�ƫ��
  Total_Controller.IMU_Temperature_Control.Err_Max=Temp_Control_Unit[7];//8ƫ���޷�ֵ
  Total_Controller.IMU_Temperature_Control.Integrate_Separation_Err=Temp_Control_Unit[8];//9���ַ���ƫ��ֵ
  Total_Controller.IMU_Temperature_Control.Integrate=Temp_Control_Unit[9];//10����ֵ
  Total_Controller.IMU_Temperature_Control.Integrate_Max=Temp_Control_Unit[10];//11�����޷�ֵ
  Total_Controller.IMU_Temperature_Control.Kp=Temp_Control_Unit[11];//12���Ʋ���Kp
  Total_Controller.IMU_Temperature_Control.Ki=Temp_Control_Unit[12];//13���Ʋ���Ki
  Total_Controller.IMU_Temperature_Control.Kd=Temp_Control_Unit[13];//14���Ʋ���Ki
  Total_Controller.IMU_Temperature_Control.Control_OutPut=Temp_Control_Unit[14];//15�����������
  Total_Controller.IMU_Temperature_Control.Last_Control_OutPut=Temp_Control_Unit[15];//16�ϴο����������
  Total_Controller.IMU_Temperature_Control.Control_OutPut_Limit=Temp_Control_Unit[16];//17�ϴο����������
  Total_Controller.IMU_Temperature_Control.Scale_Kp=Temp_Control_Unit[17];
  Total_Controller.IMU_Temperature_Control.Scale_Ki=Temp_Control_Unit[18];
  Total_Controller.IMU_Temperature_Control.Scale_Kd=Temp_Control_Unit[19];  
}

void Simulation_PWM_Init(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; 
  HWREG(GPIO_PORTC_BASE + GPIO_O_CR) = 0x000000FF;
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);
}

#define Simulation_PWM_Period_MAX  100//100*1ms=0.1S
void Simulation_PWM_Output(uint16_t width)
{
#if Temperature_Ctrl_Enable
	uint16_t static cnt=0;
	cnt++;
	if(cnt>=Simulation_PWM_Period_MAX)  cnt=0;
  if(cnt<=width) GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,GPIO_PIN_2);
	else GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);
#else
	GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_2,0);
#endif
	
}


void Temperature_Ctrl(void)
{
#if Temperature_Ctrl_Enable
 uint16_t static cnt=0;
 cnt++;
 Total_Controller.IMU_Temperature_Control.Expect=Temperature_Setpoint;
 Total_Controller.IMU_Temperature_Control.FeedBack=WP_Sensor.temperature;
 if(cnt>=10)  //10*1ms=0.01S
 {
	 PID_Control(&Total_Controller.IMU_Temperature_Control);
	 Total_Controller.IMU_Temperature_Control.Control_OutPut=constrain_float(Total_Controller.IMU_Temperature_Control.Control_OutPut,0,Simulation_PWM_Period_MAX);
	 cnt=0;
 }
#else
	Total_Controller.IMU_Temperature_Control.Control_OutPut=0;
#endif
}

uint8_t Temperature_State_Check(void)
{
#if Temperature_Ctrl_Enable
  return (ABS(Total_Controller.IMU_Temperature_Control.Err))<=0.5f?1:0;
#else
	return 1;
#endif	
}
