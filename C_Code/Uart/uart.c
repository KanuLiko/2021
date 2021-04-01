#include "uart.h"

static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA;

void Uart_Init(void){
    //����ʱ�ӵ�Ĭ�������Ѿ�������Ҫ����,��������û��������صļĴ���
    IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA = (volatile unsigned int *)0x20E0084;
    IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA = (volatile unsigned int *)0x20E0088;

    //���ý�λ���üĴ����Ĺ���Ϊuart1
    *IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA = 0;
    *IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA = 0;

    //UART Control Register 1 (UART1_UCR1)
    //Uartʹ��,�ڲ���UTXD��URXD�Ĵ���֮ǰ��������UARTEN=1
    UART1->UCR1 |= (1 << 0);

    //����uart�Ĵ����ʽ:
	/* 
	 *  ����UART�����ʽ��
	 *  UART1�е�UCR2�Ĵ����ؼ�bit����
	 *  [14]:	1������RTS����
	 *  [8] :	0: �ر���żУ�� Ĭ��Ϊ0����������
	 *  [6] :	0: ֹͣλ1λ	    Ĭ��Ϊ0����������
	 *  [5] :	1: ���ݳ���8λ
	 *  [2] :	1: ��������ʹ��
	 *  [1] :	1: ��������ʹ��
	 */
    UART1->UCR2 |= (1<<14) | (1<<5) | (1<<2) | (1<<1);
	/*
	 *  UART1�е�UCR3�Ĵ����ؼ�bit����
	 *  [2]:  1:���ݹٷ��ĵ���ʾ��IM6ULL��UART�������MUXEDģ�ͣ���ʾҪ����	
	 */
    UART1->UCR3 |= (1<<2);
	/*
	 * ���ò�����
	 * ����оƬ�ֲ��֪�����ʼ��㹫ʽ:
	 * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1))
	 * ��������Ҫ���� 115200�Ĳ�����
	 * UART1_UFCR [9:7]=101����ʾ����Ƶ���õ���ǰUART�ο�Ƶ��Ref Freq ��80M ��
	 * ���빫ʽ��115200 = 80000000 /(16*(UBMR + 1)/(UBIR+1))
	 * 
	 * ѡȡһ��������ʽ�Ĳ�����UBMR��UBIR����
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
	return (unsigned char)UART1->UXRD;
}
