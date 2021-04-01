#include "uart.h"

static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA;

void Uart_Init(void){
    //由于时钟的默认情形已经是满足要求了,所以这里没有设置相关的寄存器
    IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA = (volatile unsigned int *)0x20E0084;
    IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA = (volatile unsigned int *)0x20E0088;

    //设置脚位复用寄存器的功能为uart1
    *IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA = 0;
    *IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA = 0;

    //UART Control Register 1 (UART1_UCR1)
    //Uart使能,在操作UTXD和URXD寄存器之前必须设置UARTEN=1
    UART1->UCR1 |= (1 << 0);

    //设置uart的传输格式:
	/* 
	 *  设置UART传输格式：
	 *  UART1中的UCR2寄存器关键bit如下
	 *  [14]:	1：忽略RTS引脚
	 *  [8] :	0: 关闭奇偶校验 默认为0，无需设置
	 *  [6] :	0: 停止位1位	    默认为0，无需设置
	 *  [5] :	1: 数据长度8位
	 *  [2] :	1: 发送数据使能
	 *  [1] :	1: 接收数据使能
	 */
    UART1->UCR2 |= (1<<14) | (1<<5) | (1<<2) | (1<<1);
	/*
	 *  UART1中的UCR3寄存器关键bit如下
	 *  [2]:  1:根据官方文档表示，IM6ULL的UART用了这个MUXED模型，提示要设置	
	 */
    UART1->UCR3 |= (1<<2);
	/*
	 * 设置波特率
	 * 根据芯片手册得知波特率计算公式:
	 * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1))
	 * 当我们需要设置 115200的波特率
	 * UART1_UFCR [9:7]=101，表示不分频，得到当前UART参考频率Ref Freq ：80M ，
	 * 带入公式：115200 = 80000000 /(16*(UBMR + 1)/(UBIR+1))
	 * 
	 * 选取一组满足上式的参数：UBMR、UBIR即可
	 *	
	 * UART1_UBIR    = 71
	 * UART1_UBMR = 3124  
	 */
    UART1->UFCR = 5<<7;

    UART1->UBIR = 71;

    UART1->UBMR = 3124;

    UART1->UCR1 |= (1 << 0);
}

void PutChar(int c){
    while(!((UART1->USR2) & (1<<3)));
    UART1->UTXD = (unsigned char)c;
}

unsigned char GetChar(void){
	while(!(UART1->USR2 & (1<<0)));
	return (unsigned char)UART1->URXD;
}

void PutStr(const char *s){
	while(*s){
		PutChar(*s);
		s++;
	}
}
