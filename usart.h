#include "stm32f10x.h"


void usart2_init(u32 Baud);
void usart2_puts( char *data);
void usart2_putsf(const  char *data);
void usart2_putchar(unsigned char c);
int SER_GetChar (void);
int SER_PutChar (int c);




