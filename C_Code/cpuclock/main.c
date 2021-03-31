#include "regs.h"
#include "pll.h"
#include "clkroot.h"

struct ccm_regs *ccm = (struct ccm_regs*)CCM_BASE_ADDR;
#define LOOPS 100000
// static void busy_wait(void){
//     for(u32 i = 0;i <LOOPS; i++);//æ�ȴ�������ʱ
// }

//led�ƵĽӿں���
extern void led_init(void);
extern void led_toggle(void);
void led_on(void);

extern void setup_arm_podf(u32 podf);
extern void sel_pll1_sw_clk(int sel_pll1);

static void busy_wait(void){
    __asm__ __volatile__(
        "ldr r0,=3000000\n"
        "1:\n"
        "subs r0, r0, #1\n"
        "bne 1b\n"
        :::"r0");
}

void main(){
    //���ȳ�ʼ��������LED��
    int blinks = 0;
    led_init();
    led_on();

    //��ARM_ROOTʱ���л���OSC
    sel_pll1_sw_clk(0);
    //ARM_ROOT�ķ�Ƶ��������Ϊ8
    setup_arm_podf(8);
    //����ARM_PLL:24*54/2 = 648MHz,ARM_ROOT:81MHz
    set_pll(ARM_PLL,54);
    //��ARM_ROOT�л���ARM_PLL,��ʱCPUƵ��Ϊ81MHz
    sel_pll1_sw_clk(1);

    //ѭ��������Ϩ��LED�ƹ�10��,�۲�led��˸
    for(blinks = 10; blinks > 0; blinks --){
        busy_wait();
        led_toggle();
    }

    //��ARM_ROOTʱ���л���OSC
    sel_pll1_sw_clk(0);
    //ARM_ROOT�ķ�Ƶ��������Ϊ2
    setup_arm_podf(2);
    //����ARM_PLL:24*108/2 = 1296MHz,ARM_ROOT:648MHz
    set_pll(ARM_PLL,108);
    //��ARM_ROOT�л���ARM_PLL
    sel_pll1_sw_clk(1);

    //����ѭ��������Ϩ��LED,�۲��ʱLED��˸Ƶ�����Ա��
    while(1){
        busy_wait();
        led_toggle();
    }
}

//������ĳ�������ʹ����gcc�ṩ�ĺ���,��Ҫ�ṩraise��������������
void raise(void){
}