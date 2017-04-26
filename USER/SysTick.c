/**************************************
 * 文件名  ：SysTick.c
 * 描述    ：SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
 *           常用的有 1us 10us 1ms 中断。         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：无
 * 库版本  ：ST3.0.0  

*********************************************************/

#include "SysTick.h"

static __IO u32 TimingDelay=0;

/*初始化  SysTick*/
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
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



/* 获取节拍程序，在 SysTick 中断函数 SysTick_Handler()调用	 */  
void TimingDelay_Decrement(void)
{
  	TimingDelay++;
}

