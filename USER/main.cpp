
/**************************************
 * 文件名  ：main.c
 * 描述    ：通过串口调试软件，向板子发送数据，板子接收到数据后，立即回传给电脑。         
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 库版本  ：ST3.0.0  																										  

*********************************************************/
#include <stdarg.h>
#include <string.h>

#include "stm32f10x.h"
#include "usart1.h"
#include "SysTick.h"
#include "daozhai_c.h"


int printf_com(const char *_format, ...)
{
        va_list ap;
        static  char buf[200]={0};
        int len;
	 uint32_t CCR;
	 FlagStatus tc;
	 int i;
	 unsigned int t=0;
	 
	va_start(ap, _format);
        len = vsnprintf(buf, sizeof(buf), _format, ap);
        va_end(ap);
        if((!buf[0])||(0==len))
        	return 0;
        
         for(i=0;i<len;i++)
         {
	        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
	         USART_SendData(USART1,buf[i]);
         }

        
	
        return len;
}

  daozhai_abs_c * daozha;
int main(void)
{  
    unsigned int i=0;
    static char disp_dat[50]={0};
    static char tx_dat[50]={0};
  
    SystemInit();	//配置系统时钟为 72M 
	/* 配置SysTick 为10us中断一次 */
   SysTick_Init(); 
   USART1_Config(); //USART1 配置 		
   i=SysTick_GetTick();
   daozha=daozhai_c::get_intance();
   sprintf(disp_dat," 道闸:%03d 开:%01d 关:%01d 停:%01d   \r\n",daozha->jiaodu(),(int)daozha->sig_kai(),(int)daozha->sig_guan(),(int)daozha->sig_ting());
  while (1)
  {	
      sprintf(tx_dat," 道闸:%03d 开:%01d 关:%01d 停:%01d   ",daozha->jiaodu(),(int)daozha->sig_kai(),(int)daozha->sig_guan(),(int)daozha->sig_ting());   
      if(time_after(SysTick_GetTick(),i+2000)||(0!=strcmp(disp_dat,tx_dat)))
      {
       if (0!=strcmp(disp_dat,tx_dat))
       	{
        	strcpy(disp_dat,tx_dat);
		printf_com("\r\n");
		printf_com(disp_dat);	
		printf_com("%06u ",SysTick_GetTick());		
       	}
	else
	{
		printf_com("\r");
		printf_com(disp_dat);	
		printf_com("%06u ",SysTick_GetTick());		
	}
		
        
     	i=SysTick_GetTick();       
      }
	daozha->run((void * )0);
  }
}




