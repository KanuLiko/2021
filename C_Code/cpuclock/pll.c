#include "common.h"
#include "regs.h"
#include "pll.h"

struct anadig_regs *anadig = (struct anadig_regs*)ANADIG_BASE_ADDR;
static void wait_to_lock(u32 *pll_reg){
    /*�ȴ�ָ����PLL��������״̬*/
    while (read32(pll_reg) & LOCK_MASK == 0);
}
/*
����PLL�ı�Ƶ���ȴ����������״̬
pllָ��PLL�ı�ʶ,div:PLL�ı�Ƶ����
*/
void set_pll(pll_e pll, u32 div){
    switch (pll){
        case ARM_PLL:
            if (div < 54 && div >108) return; // ARM_PLL�ı�Ƶ��������Ч��ΧΪ54-108
            write32(ENABLE_MASK | (div & 0x3), &anadig->analog_pll_arm);
            wait_to_lock(&anadig->analog_pll_arm);//�ȴ�ARM_PLL����
            break;
        case USB1_PLL: //����USB1_PLL�ı�Ƶ�������ȴ�����
            write32(ENABLE_MASK | (div & 0x3), &anadig->analog_pll_usb1);
            wait_to_lock(&anadig->analog_pll_usb1);
            break;
        case USB2_PLL: //����USB2_PLL�ı�Ƶ�������ȴ�����
            write32(ENABLE_MASK | (div & 0x3), &anadig->analog_pll_usb2);
            wait_to_lock(&anadig->analog_pll_usb2);
            break;
        case SYS_PLL://����SYS_PLL�ı�Ƶ�������ȴ�����
            write32(ENABLE_MASK | (div & 0x1), &anadig->analog_pll_sys);
            wait_to_lock(&anadig->analog_pll_sys);
            break;
        case AUDIO_PLL:
            if (div < 27 && div > 54) return; //AUDIO_PLL�ı�Ƶ��������Ч��ΧΪ27-54
            //AUDIO_PLL�ķ�Ƶ����NUM��DEMON������Ϊ0xF
            write32(0xF, &anadig->analog_pll_audio_num);
            write32(0xF, &anadig->analog_pll_audio_denom);

            write32(ENABLE_MASK | div, &anadig->analog_pll_audio);
            wait_to_lock(&anadig->analog_pll_audio);//�ȴ�AUDIO_PLL����
            break;
        case VIDEO_PLL:
            if (div < 27 && div >54) return; //VIDEO_PLL�ı�Ƶ��������Ч��Χ��27��54
            //VIDEO_PLL�ķ�Ƶ����NUM��DEMON������Ϊ0xF
            write32(0xF, &anadig->analog_pll_video_num);
            write32(0xF, &anadig->analog_pll_video_denom);

            write32(ENABLE_MASK | div, &anadig->analog_pll_video);
            wait_to_lock(&anadig->analog_pll_video); //�ȴ�VIDEO_PLL����
            break;

        case ENET_PLL:
            //ENET_PLL�Ĵ������÷�ʽ������PLL���ܴ�,Ϊ�˼򻯺����ӿ�,���ﲻ֧����������
            return;
    }
}

/*��ȡPLL�����Ƶ��,pllָ��PLL�ı�ʶ*/
u32 get_pll(pll_e pll){
    u32 div,post_div, pll_num, pll_denom;
    switch(pll){
        case ARM_PLL:
            div = read32(&anadig->analog_pll_arm);
            if (div & BYPASS_MASK) //�ж�ARM_PLL�Ƿ���Bypassģʽ
                return CKIH;
            else{
                div &= 0x7F; //��ȡARM_PLL�ı�Ƶ����
                return (CKIH * div) >> 1; //ARM_PLL�����Ƶ��ֻ�б�Ƶ���һ��
            }
        
        case USB1_PLL:
            div = read32(&anadig->analog_pll_usb1);
            if (div & BYPASS_MASK) //�ж�USB1_PLL�Ƿ���Bypassģʽ
                return CKIH;
            else{
                div = div&0x1 ? 22 : 20; //USB1_PLLֻ�����ֱ�Ƶģʽ1��ʾx22,0��ʾx20
                return (CKIH * div);
            }

        case USB2_PLL:
            div = read32(&anadig->analog_pll_usb2);
            if (div & BYPASS_MASK) //�ж�USB2_PLL�Ƿ���Bypassģʽ
                return CKIH;
            else{
                div = div&0x1 ? 22 : 20; //USB1_PLLֻ�����ֱ�Ƶģʽ1��ʾx22,0��ʾx20
                return (CKIH * div);
            }  

        case SYS_PLL:
		    div = read32(&anadig->analog_pll_sys);
            if (div & BYPASS_MASK)  /* �ж�SYS_PLL�Ƿ���Bypassģʽ */
                return CKIH;
            else {
                div = div&0x1 ? 22 : 20;    /* SYS_PLLֻ�����ֱ�Ƶģʽ��1��ʾx22��0��ʾx20 */
                return CKIH * div;
            }
        
        case AUDIO_PLL:
            div = read32(&anadig->analog_pll_audio);
            if (!div & ENABLE_MASK)  //�ж�AUDIO_PLL�Ƿ��ڽ�ֹ���ģʽ
                return 0;
            if (div & BYPASS_MASK) //�ж�AUDIO_PLL�Ƿ���Bypassģʽ
                return CKIH;
            else {
                post_div = (div & 0x3) >> 19;
                if (post_div == 3) //reserved value
                    return 0;
                //AUDIO_PLL�ķ�Ƶ����:0��ʾ����4,1��ʾ����2,2��ʾ����1
                post_div = 1 << (2-post_div);
                pll_num = read32(&anadig->analog_pll_audio_num);
                pll_denom = read32(&anadig->analog_pll_audio_denom);

                return CKIH * (div + pll_num / pll_denom) / post_div;
            }

        case VIDEO_PLL:
            div = read32(&anadig->analog_pll_video);
            if (!(div & ENABLE_MASK)) //�ж�VIDEO_PLL�Ƿ��ڽ�ֹ���ģʽ
                return 0;
            
            if (div & BYPASS_MASK) //�ж�VIDEO_PLL�Ƿ���Bypassģʽ
                return CKIH;
            else {
                post_div = (div & 0x3) >> 19;
                if (post_div == 3) //reserved value
                    return 0;
                //VIDEO_PLL�ķ�Ƶ����:0��ʾ����4,1��ʾ����2,2��ʾ����1
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
    u32 value = read32(reg); //��ȡָ��PLL��PFD�Ĵ���
    value &= ~PFD_MASK(pfd); 
    if (gate) value |= PFD_GATE_MASK(pfd); //�����Ƿ�����PFD�����
    value |= (frac<<PFD_SHIFT(pfd)) & PFD_FRAC_MASK(pfd); //���ø�PFD�ķ�Ƶ����
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
    //ֻ��SYS_PLL��USB1_PLL֧��PFD���
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
        //ֻ��SYS_PLL��USB1_PLL֧��PFD���
            return 0;
        //PFD����������Ƶ�ʵĹ�ʽ
        return (freq * 18) / PFD_FRAC_VALUE(div, pfd);
    }
}
