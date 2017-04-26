/**************************************
 * �ļ���  ��SysTick.c
 * ����    ��SysTick ϵͳ�δ�ʱ��10us�жϺ�����,�ж�ʱ����������ã�
 *           ���õ��� 1us 10us 1ms �жϡ�         
 * ʵ��ƽ̨��MINI STM32������ ����STM32F103C8T6
 * Ӳ�����ӣ���
 * ��汾  ��ST3.0.0  

*********************************************************/

#include "SysTick.h"

static __IO u32 TimingDelay=0;

/*��ʼ��  SysTick*/
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemFrequency / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
}

unsigned int SysTick_GetTick(void)
{
	return TimingDelay;
}



/* ��ȡ���ĳ����� SysTick �жϺ��� SysTick_Handler()����	 */  
void TimingDelay_Decrement(void)
{
  	TimingDelay++;
}

