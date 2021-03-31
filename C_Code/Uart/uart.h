#ifndef _UART_H_
#define _UART_H_
/*UART1�ļĴ����Ļ���ַ*/
#define UART1_BASE (0x2020000u)

#define UART1    ((UART_Type *)UART1_BASE)

/*����IMX6uLLоƬ�ֲᶨ��UART�Ľṹ��*/
typedef struct {
    volatile unsigned int UXRD;
             unsigned char RESERVED_0[60];
    volatile unsigned int UTXD;
             unsigned char RESERVED_1[60];
    volatile unsigned int  UCR1;               /**< UART Control Register 1, offset: 0x80 	       ���ڿ��ƼĴ���1��ƫ�Ƶ�ַ0x80*/
    volatile unsigned int  UCR2;               /**< UART Control Register 2, offset: 0x84 	       ���ڿ��ƼĴ���2��ƫ�Ƶ�ַ0x84*/
    volatile unsigned int  UCR3;               /**< UART Control Register 3, offset: 0x88            ���ڿ��ƼĴ���3��ƫ�Ƶ�ַ0x88*/
    volatile unsigned int  UCR4;               /**< UART Control Register 4, offset: 0x8C            ���ڿ��ƼĴ���4��ƫ�Ƶ�ַ0x8C*/
    volatile unsigned int  UFCR;               /**< UART FIFO Control Register, offset: 0x90         ����FIFO���ƼĴ�����ƫ�Ƶ�ַ0x90*/
    volatile unsigned int  USR1;               /**< UART Status Register 1, offset: 0x94             ����״̬�Ĵ���1��ƫ�Ƶ�ַ0x94*/
    volatile unsigned int  USR2;               /**< UART Status Register 2, offset: 0x98             ����״̬�Ĵ���2��ƫ�Ƶ�ַ0x98*/
    volatile unsigned int  UESC;               /**< UART Escape Character Register, offset: 0x9C     ����ת���ַ��Ĵ�����ƫ�Ƶ�ַ0x9C*/
    volatile unsigned int  UTIM;               /**< UART Escape Timer Register, offset: 0xA0         ����ת�嶨ʱ���Ĵ��� ƫ�Ƶ�ַ0xA0*/
    volatile unsigned int  UBIR;               /**< UART BRM Incremental Register, offset: 0xA4      ���ڶ����Ʊ������ӼĴ��� ƫ�Ƶ�ַ0xA4*/
    volatile unsigned int  UBMR;               /**< UART BRM Modulator Register, offset: 0xA8 	   ���ڶ����Ʊ��ʵ��ڼĴ��� ƫ�Ƶ�ַ0xA8*/
    volatile unsigned int  UBRC;               /**< UART Baud Rate Count Register, offset: 0xAC      ���ڲ����ʼ����Ĵ��� ƫ�Ƶ�ַ0xAC*/
    volatile unsigned int  ONEMS;              /**< UART One Millisecond Register, offset: 0xB0      ����һ����Ĵ��� ƫ�Ƶ�ַ0xB0*/
    volatile unsigned int  UTS;                /**< UART Test Register, offset: 0xB4                 ���ڲ��ԼĴ��� ƫ�Ƶ�ַ0xB4*/		
    volatile unsigned int  UMCR;               /**< UART RS-485 Mode Control Register, offset: 0xB8  ����485ģʽ���ƼĴ��� ƫ�Ƶ�ַ0xB8*/
}UART_Type;

void Uart_Init(void);
void PutChar(int c);

#endif