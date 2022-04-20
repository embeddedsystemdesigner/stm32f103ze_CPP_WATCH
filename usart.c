#include "stm32f10x.h"



void usart2_putchar(unsigned char c)
{

	while((USART2->SR&0X40)==0){}
		
  USART2->DR = (u8) c;     

}
//////////////////////////////////////////////////////////////////////////////////////////////

void usart2_puts( char *data)
{
	
	while(*data)
		{
		usart2_putchar(*data);
		data++;
		}	

}
//////////////////////////////////////////////////////////////////////////////////////////////


void usart2_putsf(const  char *data)
{
	
	while(*data)
		{
		usart2_putchar(*data);
		data++;
		}	

}
//////////////////////////////////////////////////////////////////////////////////////////////

void usart2_init(u32 Baud)
{

	int i;

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* Configure USART1 Tx (PA.2) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



	/* Configure USART1 Rx (PA.3) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	USART_InitStructure.USART_BaudRate = Baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE);



	USART2->CR1|=(   1UL <<  5);       // enable RXNE Interrupt 


	for (i = 0; i < 0x1000; i++) __NOP();
	
	//NVIC_SetPriority(USART2_IRQn,1);	
	//NVIC_EnableIRQ(USART2_IRQn);
                 
	
}
//////////////////////////////////////////////////////////////////////////////////////////////




#ifdef __DBG_ITM
volatile int ITM_RxBuffer = ITM_RXBUFFER_EMPTY;  /*  CMSIS Debug Input        */
#endif


extern void $Super$$__rt_entry(void);

void $Sub$$__rt_entry(void)  {
  
	usart2_init(9600);
	
  $Super$$__rt_entry();
}



/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/
int SER_PutChar (int c) {

#ifdef __DBG_ITM
    ITM_SendChar(c);
#else
  while (!(USART2->SR & USART_SR_TXE));
  USART2->DR = (c & 0x1FF);
#endif
  return (c);
}


/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int SER_GetChar (void) {

#ifdef __DBG_ITM
  while (ITM_CheckChar() != 1) __NOP();
  return (ITM_ReceiveChar());
#else
  while (!(USART2->SR & USART_SR_RXNE));
  return (USART2->DR & 0xFF);
#endif
}















