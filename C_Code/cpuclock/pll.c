#include "common.h"
#include "regs.h"
#include "pll.h"

struct anadig_regs *anadig = (struct anadig_regs*)ANADIG_BASE_ADDR;
static void wait_to_lock(u32 *pll_reg){
    /*等待指定的PLL进入锁定状态*/
    while (read32(pll_reg) & LOCK_MASK == 0);
}
/*
设置PLL的倍频并等待其进入锁定状态
pll指定PLL的标识,div:PLL的倍频参数
*/
void set_pll(pll_e pll, u32 div){
    switch (pll){
        case ARM_PLL:
            if (div < 54 && div >108) return; // ARM_PLL的倍频参数的有效范围为54-108
            write32(ENABLE_MASK | (div & 0x3), &anadig->analog_pll_arm);
            wait_to_lock(&anadig->analog_pll_arm);//等待ARM_PLL锁定
            break;
        case USB1_PLL: //设置USB1_PLL的倍频参数并等待锁定
            write32(ENABLE_MASK | (div & 0x3), &anadig->analog_pll_usb1);
            wait_to_lock(&anadig->analog_pll_usb1);
            break;
        case USB2_PLL: //设置USB2_PLL的倍频参数并等待锁定
            write32(ENABLE_MASK | (div & 0x3), &anadig->analog_pll_usb2);
            wait_to_lock(&anadig->analog_pll_usb2);
            break;
        case SYS_PLL://设置SYS_PLL的倍频参数并等待锁定
            write32(ENABLE_MASK | (div & 0x1), &anadig->analog_pll_sys);
            wait_to_lock(&anadig->analog_pll_sys);
            break;
        case AUDIO_PLL:
            if (div < 27 && div > 54) return; //AUDIO_PLL的倍频参数的有效范围为27-54
            //AUDIO_PLL的分频参数NUM和DEMON都设置为0xF
            write32(0xF, &anadig->analog_pll_audio_num);
            write32(0xF, &anadig->analog_pll_audio_denom);

            write32(ENABLE_MASK | div, &anadig->analog_pll_audio);
            wait_to_lock(&anadig->analog_pll_audio);//等待AUDIO_PLL锁定
            break;
        case VIDEO_PLL:
            if (div < 27 && div >54) return; //VIDEO_PLL的倍频参数的有效范围是27到54
            //VIDEO_PLL的分频参数NUM和DEMON都设置为0xF
            write32(0xF, &anadig->analog_pll_video_num);
            write32(0xF, &anadig->analog_pll_video_denom);

            write32(ENABLE_MASK | div, &anadig->analog_pll_video);
            wait_to_lock(&anadig->analog_pll_video); //等待VIDEO_PLL锁定
            break;

        case ENET_PLL:
            //ENET_PLL寄存器设置方式与其它PLL差别很大,为了简化函数接口,这里不支持它的设置
            return;
    }
}

/*获取PLL的输出频率,pll指定PLL的标识*/
u32 get_pll(pll_e pll){
    u32 div,post_div, pll_num, pll_denom;
    switch(pll){
        case ARM_PLL:
            div = read32(&anadig->analog_pll_arm);
            if (div & BYPASS_MASK) //判断ARM_PLL是否处于Bypass模式
                return CKIH;
            else{
                div &= 0x7F; //获取ARM_PLL的倍频参数
                return (CKIH * div) >> 1; //ARM_PLL的输出频率只有倍频后的一半
            }
        
        case USB1_PLL:
            div = read32(&anadig->analog_pll_usb1);
            if (div & BYPASS_MASK) //判断USB1_PLL是否处于Bypass模式
                return CKIH;
            else{
                div = div&0x1 ? 22 : 20; //USB1_PLL只有两种倍频模式1表示x22,0表示x20
                return (CKIH * div);
            }

        case USB2_PLL:
            div = read32(&anadig->analog_pll_usb2);
            if (div & BYPASS_MASK) //判断USB2_PLL是否处于Bypass模式
                return CKIH;
            else{
                div = div&0x1 ? 22 : 20; //USB1_PLL只有两种倍频模式1表示x22,0表示x20
                return (CKIH * div);
            }  

        case SYS_PLL:
		    div = read32(&anadig->analog_pll_sys);
            if (div & BYPASS_MASK)  /* 判断SYS_PLL是否处于Bypass模式 */
                return CKIH;
            else {
                div = div&0x1 ? 22 : 20;    /* SYS_PLL只有两种倍频模式，1表示x22，0表示x20 */
                return CKIH * div;
            }
        
        case AUDIO_PLL:
            div = read32(&anadig->analog_pll_audio);
            if (!div & ENABLE_MASK)  //判断AUDIO_PLL是否处于禁止输出模式
                return 0;
            if (div & BYPASS_MASK) //判断AUDIO_PLL是否处于Bypass模式
                return CKIH;
            else {
                post_div = (div & 0x3) >> 19;
                if (post_div == 3) //reserved value
                    return 0;
                //AUDIO_PLL的分频参数:0表示除以4,1表示除以2,2表示除以1
                post_div = 1 << (2-post_div);
                pll_num = read32(&anadig->analog_pll_audio_num);
                pll_denom = read32(&anadig->analog_pll_audio_denom);

                return CKIH * (div + pll_num / pll_denom) / post_div;
            }

        case VIDEO_PLL:
            div = read32(&anadig->analog_pll_video);
            if (!(div & ENABLE_MASK)) //判断VIDEO_PLL是否处于禁止输出模式
                return 0;
            
            if (div & BYPASS_MASK) //判断VIDEO_PLL是否处于Bypass模式
                return CKIH;
            else {
                post_div = (div & 0x3) >> 19;
                if (post_div == 3) //reserved value
                    return 0;
                //VIDEO_PLL的分频参数:0表示除以4,1表示除以2,2表示除以1
                post_div = 1 << (2 - post_div);
                
                pll_num = read32(&anadig->analog_pll_video_num);
                pll_denom = read32(&anadig->analog_pll_video_denom);
                
                return CKIH * (div + pll_num / pll_denom) / post_div;
            }

            default:
                return 0;
    }
    /*NOTREACHED*/
}

static void set_pfd(u32 *reg, pfd_e pfd, int gate, u32 frac){
    u32 value = read32(reg); //读取指定PLL的PFD寄存器
    value &= ~PFD_MASK(pfd); 
    if (gate) value |= PFD_GATE_MASK(pfd); //设置是否屏蔽PFD的输出
    value |= (frac<<PFD_SHIFT(pfd)) & PFD_FRAC_MASK(pfd); //设置该PFD的分频参数
    write32(value, reg);

    while(read32(reg) & PFD_STABLE_MASK(pfd));
}

void set_pll_pfd(pll_e pll, pfd_e pfd, int gate, u32 frac){
    u32 *reg;
    if (pll = SYS_PLL)
        reg = &anadig->analog_pfd_528;
    else if (pll = USB1_PLL)
        reg = &anadig->analog_pfd_480;
    else
    //只有SYS_PLL和USB1_PLL支持PFD输出
        return;
    set_pfd(reg, pfd, gate, frac);
}

u32 get_pll_pfd(pll_e pll, pfd_e pfd){
    u32 div;
    u32 freq;
    switch (pll){
        case SYS_PLL:
            div = read32(&anadig->analog_pfd_528);
            freq = (u64)get_pll(SYS_PLL);
            break;
        case USB1_PLL:
            div = read32(&anadig->analog_pfd_480);
            freq = (u64)get_pll(USB1_PLL);
        default:
        //只有SYS_PLL和USB1_PLL支持PFD输出
            return 0;
        //PFD参数对最终频率的公式
        return (freq * 18) / PFD_FRAC_VALUE(div, pfd);
    }
}
