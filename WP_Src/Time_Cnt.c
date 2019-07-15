
#include "Headfile.h"
#include "Time_Cnt.h"
/***********************************************************
@��������Time_init
@��ڲ�������
@���ڲ�������
@����������ϵͳ���ȶ�ʱ����ʼ��
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void Time_init(void)//ϵͳ���ȶ�ʱ����ʼ��
{
	Schedule_init();//��ʱ��ʹ��
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);							//��ʱ��0ʹ��				
  TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);						//32λ���ڶ�ʱ��				
  TimerLoadSet(TIMER0_BASE,TIMER_A,SysCtlClockGet()/200);		//�趨װ��ֵ,��80M/200��*1/80M=5ms				
  IntEnable(INT_TIMER0A);																		//���ж�ʹ��				
  TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT); 					//�ж����, ����ģʽ;			
  TimerIntRegister(TIMER0_BASE,TIMER_A,TIMER0A_Handler);		//�жϺ���ע��
  IntMasterEnable();			
  TimerEnable(TIMER0_BASE,TIMER_A); 												//��ʱ��ʹ�ܿ�ʼ����
  IntPrioritySet(INT_TIMER0A,USER_INT7);
}

Sensor WP_Sensor;
Testime Time0_Delta;
/***********************************************************
@��������TIMER0A_Handler
@��ڲ�������
@���ڲ�������
@����������ϵͳ���ȶ�ʱ���жϷ���������Ҫ����ң����������
�������ݲɼ��������˲�����̬���㡢���Ե��������Ƶȶ�������
�ϸ�Ҫ��ĺ���
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void TIMER0A_Handler(void)				//ϵͳ�����жϺ���
{
  Test_Period(&Time0_Delta);
  Remote_Control();								//ң�������ݽ���
  Get_Status_Feedback();					//��ȡ��̬���ݡ�ˮƽ����ֱ����ߵ�����
  US_100_Statemachine();					//������������״̬������
  Optflow_Statemachine();					//����״̬������ʼ��ʱ���ڹ�������
  SDK_Data_Prase();								//SDK���ݽ���
  SDK_Data_Prase_Front();         //ǰ��openmvSDK���ݽ���
//GPS_Data_Prase();								//GPS���ݽ���
//KalmanFilter_Horizontal();			//ˮƽλ��GPS˫�۲���Kalman�˲��ں�	
  CarryPilot_Control();						//�ܿ�����
	Accel_Calibration_Check();			//���ٶ�У׼���
  Mag_Calibration_Check();				//������У׼���
  ESC_Calibration_Check();				//����г�У׼���
  Horizontal_Calibration_Check();	//����ˮƽУ׼���
  Bling_Working(Bling_Mode);			//״ָ̬ʾ������
  TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
}

