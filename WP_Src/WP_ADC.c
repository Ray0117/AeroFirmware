
#include "Headfile.h"
#include "WP_ADC.h"
#include "hw_adc.h"
#include "adc.h"

uint32_t value[8];
double value_filter;
/***********************************************************
@��������ADC_Init
@��ڲ�������
@���ڲ�������
������������ѹ�����˿�PE3����ΪADC0��ͨ��0��ʼ�������ж�ʽ�ɼ�
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void ADC_Init(void)//ADC��ʼ������   
{    
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);// Enable the ADC1 module.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));// Wait for the ADC1 module to be ready.	
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);    
  GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
  //ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_3V);
  //Enable the first sample sequencer to capture the value of channel 0 when
  //the processor trigger occurs.  
  ADCSequenceConfigure(ADC0_BASE,0,ADC_TRIGGER_PROCESSOR, 0); 
  //ADCHardwareOversampleConfigure(ADC0_BASE, 8);	
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 |ADC_CTL_END | ADC_CTL_IE);    
	//ADCIntClear(ADC0_BASE, 0);
	ADCSequenceEnable(ADC0_BASE, 0);    
  //ADCIntEnable(ADC0_BASE, 0);   
} 


float Battery_Voltage;
/***********************************************************
@��������Get_Battery_Voltage
@��ڲ�������
@���ڲ�������
����������������ص�ѹ���ɿ�Ĭ�Ϸ�ѹ��λ11���ʲ�����ѹ��Ҫ����
3.3V*11=36.6V����������ĵ�ѹ�����������Ϸ�ѹ������ֵ����
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void Get_Battery_Voltage(void)//ADC��ȡ   
{
	ADCProcessorTrigger(ADC0_BASE, 0);   
	while(!ADCIntStatus(ADC0_BASE, 0, false)) {;}
	ADCIntClear(ADC0_BASE, 0);	
	ADCSequenceDataGet(ADC0_BASE, 0, value);   
	//value[0] =  HWREG(ADC0_BASE+ ADC_SEQ + (ADC_SEQ_STEP*0) + ADC_SSFIFO);
	value_filter=(double)(0.7*value_filter+10.89*value[0]/4095.0f);
	Battery_Voltage=value_filter;		
}

