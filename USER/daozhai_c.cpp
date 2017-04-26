#include "daozhai_c.h"
#include "stm32f10x_conf.h"
#include "SysTick.h"
#include <new>
daozhai_abs_c::daozhai_abs_c()
{
    tim=400;//4
    m_jiaodu=0;
    err=0;
}

int daozhai_abs_c::jiaodu()
{
    return m_jiaodu;
}

//10ms 调用一次
void *daozhai_abs_c::run(void *arg)
{
    (void*)arg;
    static int t=0,ts=0;
    static unsigned int i=0;
    static bool kai_s=false;
    static bool guan_s=false;

    static bool kai_r,guan_r;
    ts=(tim/90)+1;

    // while(1)
    {
        //OSTimeDlyHMSM(0,0,0,10);
        if(!time_after(SysTick_GetTick(),i+20))
            return 0;
        i=SysTick_GetTick();

        kai_r=sig_kai();
        guan_r=sig_guan();

        if(kai_r&&guan_r)
        {

        }
        else if(kai_r)
        {
            kai_s=true;
        }else if(guan_r)
        {
            guan_s=true;
        }
        if( sig_ting() )
        {
            guan_s=false;
            kai_s=false;
        }

        if(kai_s)
        {
            if(++t>ts)
            {

                if(m_jiaodu<100)
                    m_jiaodu+=3;
                t=0;
            }
        }
        if(guan_s)
        {
            if(++t>ts)
            {
                if(m_jiaodu>-10)
                    m_jiaodu-=3;
                t=0;
            }
        }

        if(m_jiaodu>=90)
        {
            set_kai_xw(true);
            kai_s=false;
        }
        else
        {
            set_kai_xw(false);
        }

        if(m_jiaodu<=0)
        {
            set_guan_xw(true);
            guan_s=false;
        }
        else
        {
            set_guan_xw(false);
        }
        
    }
    return 0;

}

daozhai_c::daozhai_c():daozhai_abs_c()
{
    GPIO_InitTypeDef  gpio_init;

    //开关停信号输入 PA0 1 2
    GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2);
    gpio_init.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
    gpio_init.GPIO_Mode  = GPIO_Mode_IPU;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);


    //开限位 关限位 输出信号 PB12 PB13
    GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13);
    gpio_init.GPIO_Pin   = GPIO_Pin_12|GPIO_Pin_13;
    gpio_init.GPIO_Mode  = GPIO_Mode_Out_OD;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio_init);

}

daozhai_c *daozhai_c::get_intance()
{
    static uint32_t mem_buf[(sizeof(daozhai_c)+sizeof(uint32_t)-1)/sizeof(uint32_t)];
    static daozhai_c *p=0;
    if(!p)
        p=new(mem_buf) daozhai_c();
    return p;
}

//低电平为有效
bool daozhai_c::sig_kai()
{
    if( Bit_RESET==GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) )
    {
    	int i=20;
	int s=0;
	for(s=0;i>0;--i)
	{
		s+=(int)GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) ;
	}
	if(s<15)
		return true;
	else
		return false;
	
	
    }
    return false;
}

bool daozhai_c::sig_guan()
{

    if( Bit_RESET==GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) )
    {
    	int i=20;
	int s=0;
	for(s=0;i>0;--i)
	{
		s+=(int)GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) ;
	}
	if(s<15)
		return true;
	else
		return false;
	
	
    }
    return false;
}

bool daozhai_c::sig_ting()
{
    if( Bit_RESET==GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2))
    {
    	int i=20;
	int s=0;
	for(s=0;i>0;--i)
	{
		s+=(int)GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) ;
	}
	if(s<15)
		return true;
	else
		return false;
	
	
    }
    return false;
}

//低电平有效
void daozhai_c::set_kai_xw(bool status)
{
    if(!status)
        GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
    else
        GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
}

void daozhai_c::set_guan_xw(bool status)
{
    if(!status)
        GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_SET);
    else
        GPIO_WriteBit(GPIOB,GPIO_Pin_13,Bit_RESET);
}
