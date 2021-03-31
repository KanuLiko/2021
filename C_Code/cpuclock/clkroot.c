#include "common.h"
#include "pll.h"
#include "regs.h"
#include "clkroot.h"

extern struct ccm_regs *ccm;

void setup_arm_podf(u32 podf){
    if (podf < 1 || podf >8) return ;
    write32(podf-1, &ccm->cacrr);
}

u32 get_arm_clk_root(void){
    u32 reg, freq;

    reg = read32(&ccm->cacrr);
    reg = (reg & 0x7) + 1;
    freq = get_pll(ARM_PLL);

    return freq / reg;
}

static u32 get_periph_clk(void){
    u32 reg, per_clk2_podf = 0, freq = 0;
    reg = read32(&ccm->cbcdr);

    if (reg & (1u << 25)){
        per_clk2_podf = (reg >> 27) & 0x7;
        reg = read32(&ccm->cbcmr);
        reg = (reg >> 12) & 0x3;

        switch(reg) {
            case 0:
                freq = get_pll(USB1_PLL);
                break;
            case 1:
            case 2:
                freq = CKIH;
                break;
            default:
                break;
        }
        freq /= (per_clk2_podf + 1);
    }else{
        reg = read32(&ccm->cbcmr);
        reg = (reg >> 18) & 0x3;
        switch(reg){
            case 0:
                freq = get_pll(SYS_PLL);
                break;
            case 1:
                freq = get_pll_pfd(SYS_PLL,PFD2);
                break;
            case 2:
                freq = get_pll_pfd(SYS_PLL,PFD0);
                break;
            case 3:
                freq = get_pll_pfd(SYS_PLL,PFD2);
                break;
            default:
                break;
        }
    }
    return freq;
}

u32 get_ahb_clk_root(void){
    u32 reg, ahb_podf;
    reg = read32(&ccm->cbcdr);
    ahb_podf = (reg >> 10) & 0x7;
    return get_periph_clk() / (ahb_podf + 1);
}

u32 get_ipg_clk_root(void){
    u32 reg, ipg_podf;
    reg = read32(&ccm->cbcdr);
    ipg_podf = (reg >> 8) & 0x3;
    return get_ahb_clk_root() / (ipg_podf + 1);
}

u32 get_axi_clk_root(void){
    u32 root_freq, axi_podf;
    u32 reg = read32(&ccm->cbcdr);
    axi_podf = (reg >> 6) & 0x7;
    if (reg & (1u << 6)){
        if (reg & (1u << 6))
            root_freq = get_pll_pfd(USB1_PLL,PFD1);
        else    
            root_freq = get_pll_pfd(USB1_PLL,PFD2);            
    }else
        root_freq = get_periph_clk();
    return root_freq / (axi_podf + 1);
}

u32 get_fabric_mmdc_clk_root(void){
    u32 cbcmr = read32(&ccm->cbcmr);
    u32 cbcdr = read32(&ccm->cbcdr);

    u32 freq, podf, per2_clk2_podf;
    podf = (cbcdr >> 3) & 0x7;
    if (cbcdr & (1u << 26)){
        freq = CKIH;
        if(cbcmr & (1u << 20))
            freq = CKIH;
        else    
            freq = get_pll(USB1_PLL);
        freq /= (per2_clk2_podf + 1);
    }else{
        extern u32 get_pll4_main_clk(void);
        switch((cbcmr >> 21) & 0x3){
            case 0:
                freq = get_pll(SYS_PLL);
                break;
            case 1:
                freq = get_pll_pfd(SYS_PLL,PFD2);
                break;
            case 2:
                freq = get_pll_pfd(SYS_PLL,PFD0);
                break;
            case 3:
                freq = get_pll4_main_clk();
                break;
        }
    }
    return freq / (podf + 1);
}
