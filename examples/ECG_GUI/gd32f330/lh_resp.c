#include "lh_resp.h"

void ac_lead_enable(){
	uint8_t val;
	val = LH001_91_LEADOFF_CURRENT_SOURCE_100nA<<4;
	lh001_91_write_regs(ADDR_LH001_91_LOCON1,&val,1);
	val = MSK_LH001_91_LOCON2_ACLOEN|(2<<POS_LH001_91_LOCON2_SINKEN)|(2<<POS_LH001_91_LOCON2_SOURCEENB);
	lh001_91_write_regs(ADDR_LH001_91_LOCON2,&val,1);
	val = 0;
	lh001_91_write_regs(ADDR_LH001_91_LOCON3,&val,1);
}

void lh_resp_init(void)
{
    LH001_91_ADC_INIT_t adc_init;
    LH001_91_PGA_INIT_t pga_init;
    uint8_t val;

    lh001_91_adc_stop();

	  ac_lead_enable();
    lh001_91_rld_init(1,ENUM_LH001_91_RLD_REF_AVDD_DIV2,ENUM_LH001_91_RLD_CHOP_FMOD_DIV32);

    pga_init.gain = ENUM_LH001_91_PGA_PGAGAIN_6;
    pga_init.pga_bypass = 0;
    pga_init.power_mode = ENUM_LH001_91_PGA_POWER_LP;
    pga_init.comm_sense_en = 1;
	  pga_init.pga_chop = ENUM_LH001_91_PGA_CHOP_DIV16;
    lh001_91_pga_init(&pga_init);

    //adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_512K;
	  adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_128K;
    adc_init.oversample_rate = ENUM_LH001_91_ADC_DR_DIV512; //update rate = Fmodclk/oversample_rate
    adc_init.conv_mode = ENUM_LH001_91_ADC_CONTINOUS;
    adc_init.ref_sel = ENUM_LH001_91_ADC_REF_2V5;
    lh001_91_adc_init(&adc_init);
    //lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_VCM,ENUM_LH001_91_ADCCHN_GND);	//FOR NOISE TEST
	  lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_AIN0,ENUM_LH001_91_ADCCHN_AIN1);

    lh001_91_userkey1_unlock();
    lh001_91_read_regs(ADDR_LH001_91_MODCFG,&val,1);
    val &= ~(0x3);  //clear MODCFG.MD to 0
    val |= 1;
    lh001_91_write_regs(ADDR_LH001_91_MODCFG,&val,1);
}



void lh_resp_start(void)
{
   lh001_91_adc_go();
   lh001_91_rdatac_start(); 
}

void lh_resp_stop(void)
{
   lh001_91_adc_stop();
   lh001_91_rdatac_stop(); 
}

const float lp_bs[7] = {
  0.02297348, -0.0055155,   0.03615661,  0.00371042,  0.03615661, -0.0055155,
  0.02297348,
};
const float lp_as[7] = {
 -2.85638443,  3.90728836, -3.01642343,  1.38819349, -0.3507606,
  0.0390262, 0
};
 
static float lp_xn1[7] = {0};
static float lp_yn1[7] = {0};
float resp_filter_lowpass(float input)
{
    float sum = 0;

    sum += lp_bs[0] * input;
    for(uint32_t i=7-1; i > 0; i--)
    {
        sum += lp_bs[i] * lp_xn1[i-1];
        lp_xn1[i] = lp_xn1[i-1];
        sum -= lp_as[i] * lp_yn1[i];
        lp_yn1[i] = lp_yn1[i-1];
    }
    sum -= lp_as[0]*lp_yn1[0];
    lp_yn1[0] = sum;
    lp_xn1[0] = input;

    return sum;
}


