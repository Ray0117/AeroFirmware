
#ifndef _CONTROL_ALTHOLD_H
#define _CONTROL_ALTHOLD_H


void Thr_Scale_Set(Vector_RC *rc_date);
void ncq_control_althold(void);
float get_stopping_point_z(Vector3f *stopping_point);
uint8_t Thr_Push_Over_Deadband(void);


extern float Yaw_Vel_Feedforward_Output;//��ֱ�ٶ�ǰ�����������;
extern float Yaw_Vel_Feedforward_Rate;//��ֱ�ٶ�ǰ����������APM����Ϊ1��0.45;
extern float Yaw_Vel_Feedforward_Delta;//��ֱ�����ٶȱ仯��;
extern float Last_Yaw_Vel_Target;
extern float Yaw_Vel_Target;
extern Vector3f UAV_Cushion_Stop_Point;

extern uint16_t  Deadband;//������λ����
extern uint16_t  Deadzone_Min;
extern uint16_t  Deadzone_Max;
extern uint16_t  Thr_Top;//����������г�
extern uint16_t  Thr_Buttom;//����������г�
extern uint8_t Thr_Push_Over_State;
#endif

