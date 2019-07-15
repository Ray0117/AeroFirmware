
#ifndef _CONTROL_CONFIG_H
#define _CONTROL_CONFIG_H

#include "control_althold.h"
#include "control_poshold.h"
#include "control_land.h"


#define Self_Balance_Mode 1//���ȡ�����̬�����Ų���
#define High_Hold_Mode    2//����ģʽ
#define Pos_Free_Mode 1//ˮƽλ��no fixed
#define Pos_Hold_Mode 2//����ģʽ
//GPS�����´�˿���ģʽ��ֱ����̬��
#define Speed_Mode 0  //GPS����ģʽ�£���˿���
#define Angle_Mode 1  //GPS����ģʽ�£����ֱ�Ӹ���̬������

/*****************ң�����г�����**********************/
#define  Climb_Up_Speed_Max    300//������������ٶȣ�cm/s  400  300
#define  Climb_Down_Speed_Max  200//��������½��ٶȣ�cm/s  200  150

/****************************************************************
���������رȽ�Сʱ���������½��������ٶȱȽϴ�
�ᵼ�����ӳ����������̬�������ò�����������
ʹ�ÿ��������½�ʱ����̬��ƽ�ȣ����˹��̳���ʱ�䳤��
�ᵼ����̬���ڵò���������ֱ�����ը���������رȽ�
Сʱ���ɽ��������ٶ���Сһ�㣬���������������ȼ�����
*******************************************************************/
#define  Climb_Up_Acceleration_Max     400//��������������ٶȣ�cm/s^2  400  250
#define  Climb_Down_Acceleration_Max   250//��������½����ٶȣ�cm/s^2  300  150



#define  Thr_Start  1050//��ת��������������ǲ����ã�̫��ᵼ�¹�����
#define  Thr_Fly_Start  1150//��������� 1250
#define  Thr_Hover_Default 1500//Ĭ����ͣ���ţ�ֱ�Ӷ������ʱ��1500
#define  Thr_Min 1000
#define  Thr_Idle 1100//���ŵ��٣�ȡ�ӽ���ת����ֵ����1150
#define  Nav_Speed_Max  500//�������ˮƽ�ٶ�Ϊ5m/s


/*****************һ����ɸ߶����ã���λΪcm������100��ʾԭ����ɵ���Գ�ʼλ��1�׸ߵ�λ��**********************/
#define  Auto_Launch_Target 75//һ����ɵ�Ŀ��߶ȣ������ɸ߶ȣ�ʹ�ó�����ʱ�����𳬹������������̣��Ƽ�200����



#endif

