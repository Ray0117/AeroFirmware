/* Copyright (c)  2018-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �޸�����:2019/4/12
*               �汾����Ӯ�ߡ���CarryPilot_V1.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2017-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _FILTER_H_
#define _FILTER_H_



typedef struct
{
 float Input_Butter[3];
 float Output_Butter[3];
}Butter_BufferData;


typedef struct
{
 float Output_Butter[3];
}Notch_Filter_BufferData;


typedef struct
{
  float a[3];
  float b[3];
}Butter_Parameter;



//������˹�˲�������
typedef struct
{
    int N;          //������˹�˲�����Сʵ�ֽ���
    int length;     //�˲���ϵͳ����ϵ������ĳ���
    float fc;       //������˹�˲�����ֹƵ��
    float cosW0;    //����Ƶ�ʣ���ͨ����ʱ�õ�
    float fs;       //����Ƶ��
    int filterType; //��Ҫ��Ƶ������˲������� 
	  float pass[2];
	  float stop[2];
	  float rp ;//ͨ��˥��������ֵ2dB
	  float rs ;//���˥��������ֵ20dB
	  float sbvalue[11];
	  float num[11];
	  float den[11];
	  float input[11];
	  float output[11];
	  bool isFOK;
}ButterFilterStruct;


void Tes(void);

extern Butter_Parameter Bandstop_Filter_Parameter_30_98,Bandstop_Filter_Parameter_30_94;

extern Butter_Parameter Butter_80HZ_Parameter_Acce,Butter_60HZ_Parameter_Acce,Butter_51HZ_Parameter_Acce,
                 Butter_30HZ_Parameter_Acce,Butter_20HZ_Parameter_Acce,Butter_15HZ_Parameter_Acce,
                 Butter_10HZ_Parameter_Acce,Butter_5HZ_Parameter_Acce,Butter_2HZ_Parameter_Acce;


float set_lpf_alpha(int16_t cutoff_frequency, float time_step);
void Acce_Control_Filter(void);
float LPButterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter);


void Set_Cutoff_Frequency(float sample_frequent, float cutoff_frequent,Butter_Parameter *LPF);
void Butterworth_Parameter_Init(void);
void Test_Filter(void);
float BPF_Butterworth(float curr_input,Butter_BufferData *Buffer,Butter_Parameter *Parameter);


void pascalTriangle(int N,int symbol,int *vector);
bool filter(ButterFilterStruct butterValue,float *numerator,float *denominator,float *xVector,int length,float *yVector);
bool BTfilter(ButterFilterStruct *butterValue,float data);

extern ButterFilterStruct Gyro_X_Butter_Filter,Gyro_Y_Butter_Filter,Gyro_Z_Butter_Filter;
extern ButterFilterStruct Accel_X_Butter_Filter,Accel_Y_Butter_Filter,Accel_Z_Butter_Filter;
#define N2 3
extern float Data_X_MAG[N2];
extern float Data_Y_MAG[N2];
extern float Data_Z_MAG[N2];
extern Butter_Parameter Bandstop_Filter_Parameter_30_98;
extern Butter_Parameter Bandstop_Filter_Parameter_30_94;
float GildeAverageValueFilter_MAG(float NewValue,float *Data);
#endif


