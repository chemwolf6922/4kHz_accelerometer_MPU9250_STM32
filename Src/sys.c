#include "sys.h"

void delay_init(void){
	SysTick->CTRL &= (uint32_t)0xFFFFFFFB;
	fac_us=SystemCoreClock/8000000;	
	fac_ms=(u16)fac_us*1000; 
}

void delay_us(u32 nus){		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;   		 
	SysTick->VAL=0x00;      
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;        
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;     
	SysTick->VAL =0X00;     
}

void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;       
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;      
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;    
	SysTick->VAL =0X00;     
} 


//printf
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);  
  USART1->DR = (u8) ch; 
	return ch;
}

