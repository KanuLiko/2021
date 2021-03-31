#include "regs.h"
#include "pll.h"
extern struct ccm_regs *ccm;

void sel_pll1_sw_clk(int sel_pll1){
    if(sel_pll1)
        clr_bit(&ccm->ccsr, 2);
    else{
        clr_bit(&ccm->ccsr, 8);
        set_bit(&ccm->ccsr, 2);
    }
}

u32 get_pll1_sw_clk(void){
    u32 reg = read32(&ccm->ccsr);
    if (reg & (1u << 2)){
        if(reg & (1u<<8)){
            if(reg & (1u<<3))
                return get_pll(SYS_PLL);
            else    
                return get_pll_pfd(SYS_PLL, PFD2);
        }else   
            return CKIH;
    }else
        return get_pll(ARM_PLL);
}

u32 get_pll3_sw_clk(void){
    u32 reg = read32(&ccm->ccsr);
    if (reg & 1)
        return get_pll(USB1_PLL);
    else    
        return CKIH;
}

extern struct anadig_regs * anadig;
u32 get_pll4_main_clk(void){
    u32 reg, audio_div;
    reg = read32(&anadig->pmu_misc2);
    audio_div = reg & (1u << 15) ? (reg & (1u << 23) ? 4 : 2) : 1;
    return get_pll(AUDIO_PLL) / audio_div;
}

u32 get_pll5_main_clk(void){
    u32 reg, video_div;
    reg = read32(&anadig->pmu_misc2);
    video_div = reg & (1u << 30) ? (reg & (1u << 31) ? 4 : 2) : 1;
    return get_pll(VIDEO_PLL) /video_div;
}
