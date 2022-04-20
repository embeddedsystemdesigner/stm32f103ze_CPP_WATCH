#include "stm32f10x.h"
#include <stdio.h>
#include <iostream>
#include <limits>


// telegram id --->    @eneeir
// github --->  https://github.com/embeddedsystemdesigner
// website  ---> www.enee.ir





using namespace std;

void delay_us(unsigned int time);
void delay_ms(unsigned int time);



void TIM1_Init (void);
void timer1_enable(void);
void timer1_disable(void);


class Time
{
	public:
		  Time(int h,int m,int s): hour(h),minute(m),second(s) {}
			int get_second(void){ return second;   }
			int get_minute(void){ return minute;   }
			int get_hour(void){ return hour;   }
			void get_clock(int *h,int *m,int *s){ *h = hour; *m = minute; *s = second;     }
			void set_second(void){ second++;   if(second==60){second=0; minute++;}  if(minute==60){minute=0; hour++;}  if(hour==24) hour=0; }
			void print_clock(void){cout<<"clock : "<<hour<<":"<<minute<<":"<<second<<endl;}
	private:
		int hour,minute,second;
	
	
};



int hour=0,minute=0,second=0;
volatile int flag=0;

Time mytime(11,43,0);

int main()
{
TIM1_Init();
timer1_enable();
cout<<"welcome to program"<<endl;

	
while(1)
{

if(flag)
{
mytime.print_clock();	
flag=0;
}
	
	
}


	
}




void delay_us(unsigned int time)
{
	
	while(time--)	
		{
			
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();	
    __NOP();__NOP();	

		}
	
}
/////////////////////////////////////////////////////////////
void delay_ms(unsigned int time)
{
	
	while(time--)	
		{
			
delay_us(1000);
			
		}

}



void TIM1_Init (void)
{
  RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;              /* enable clock for TIM1    */

  TIM1->PSC   = ( 7200 - 1);                       /* set prescaler   = 10KHz  */
  TIM1->ARR   = ( 10000 - 1);                       /* set auto-reload = 500ms */
  TIM1->RCR   =  0;;                               /* set repetition counter   */

  TIM1->DIER = TIM_DIER_UIE;                       /* Update Interrupt enable  */
  TIM1->CR1  &=~ TIM_CR1_CEN;                      /* timer1 disable             */	
  NVIC_DisableIRQ(TIM1_UP_IRQn);                   /* TIM1   Interrupt disable  */	

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void timer1_enable(void)
{

	TIM1->CR1  |= TIM_CR1_CEN; 
	NVIC_SetPriority(TIM1_UP_IRQn,1);		/* timer enable             */	
	NVIC_EnableIRQ(TIM1_UP_IRQn);                    /* TIM1   Interrupt enable  */
		
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void timer1_disable(void)
{
		
	TIM1->CR1  &=~ TIM_CR1_CEN;                      /* timer disable             */	
	TIM1->CNT=0;	
	NVIC_DisableIRQ(TIM1_UP_IRQn);                   /* TIM1   Interrupt disable  */	
		
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern "C"
{
void TIM1_UP_IRQHandler (void)
{

  if (TIM1->SR & (TIM_SR_UIF))
		{       

     
		mytime.set_second();
		flag=1;
			
    TIM1->SR &= ~(TIM_SR_UIF);           
    }
		
		
}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







