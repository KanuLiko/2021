#include "regs.h"
#include "pll.h"
#include "clkroot.h"

struct ccm_regs *ccm = (struct ccm_regs*)CCM_BASE_ADDR;
#define LOOPS 100000
// static void busy_wait(void){
//     for(u32 i = 0;i <LOOPS; i++);//忙等待进行延时
// }

//led灯的接口函数
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
    //首先初始化并点亮LED灯
    int blinks = 0;
    led_init();
    led_on();

    //将ARM_ROOT时钟切换至OSC
    sel_pll1_sw_clk(0);
    //ARM_ROOT的分频参数设置为8
    setup_arm_podf(8);
    //设置ARM_PLL:24*54/2 = 648MHz,ARM_ROOT:81MHz
    set_pll(ARM_PLL,54);
    //将ARM_ROOT切换回ARM_PLL,此时CPU频率为81MHz
    sel_pll1_sw_clk(1);

    //循环点亮和熄灭LED灯共10次,观察led闪烁
    for(blinks = 10; blinks > 0; blinks --){
        busy_wait();
        led_toggle();
    }

    //将ARM_ROOT时钟切换至OSC
    sel_pll1_sw_clk(0);
    //ARM_ROOT的分频参数设置为2
    setup_arm_podf(2);
    //设置ARM_PLL:24*108/2 = 1296MHz,ARM_ROOT:648MHz
    set_pll(ARM_PLL,108);
    //将ARM_ROOT切换回ARM_PLL
    sel_pll1_sw_clk(1);

    //无限循环点亮和熄灭LED,观察此时LED闪烁频率明显变快
    while(1){
        busy_wait();
        led_toggle();
    }
}

//本程序的除法运算使用了gcc提供的函数,需要提供raise函数以正常编译
void raise(void){
}