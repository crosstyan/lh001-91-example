#include "lh_weight.h"


void lh_weight_init(void)
{
    LH001_91_ADC_INIT_t adc_init;
    LH001_91_PGA_INIT_t pga_init;
    uint8_t val;

    lh001_91_adc_stop();
	lh001_91_rdatac_stop(); 
	
	//trim_write_offset(5740);

    pga_init.gain = ENUM_LH001_91_PGA_PGAGAIN_48;
    pga_init.pga_bypass = 0;
    pga_init.power_mode = ENUM_LH001_91_PGA_POWER_HP;
    pga_init.comm_sense_en = 1;
	pga_init.pga_chop = ENUM_LH001_91_PGA_CHOP_DIV32;
    lh001_91_pga_init(&pga_init);

    adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_512K;
	//adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_128K;
    adc_init.oversample_rate = ENUM_LH001_91_ADC_DR_DIV1024; //update rate = Fmodclk/oversample_rate
    adc_init.conv_mode = ENUM_LH001_91_ADC_CONTINOUS;
    adc_init.ref_sel = ENUM_LH001_91_ADC_REF_2V5;
    lh001_91_adc_init(&adc_init);

//!--------------- Disable Internal reference, use external reference ------
	lh001_91_read_regs(ADDR_LH001_91_BUFCON,&val,1);
    val &= ~(MSK_LH001_91_BUFCON_EN2P5|MSK_LH001_91_BUFCON_ENREF);
    lh001_91_write_regs(ADDR_LH001_91_BUFCON,&val,1);
//---------------------------------------------------------------------------	

    //exitaion current
    lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_AIN2,ENUM_LH001_91_ADCCHN_AIN3);   //measure bridge signal	
	//lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_VCM,ENUM_LH001_91_ADCCHN_GND);
    
    lh001_91_pltformkey_unlock();
    lh001_91_read_regs(ADDR_LH001_91_MODCFG,&val,1);
    val &= ~(0x3);  //clear MODCFG.MD to 0
    lh001_91_write_regs(ADDR_LH001_91_MODCFG,&val,1);
    val = ENUM_LH001_91_ADC_AVG_10<<POS_LH001_91_CONFIG1_AVG;  //50/4=12.5 sps
    lh001_91_write_regs(ADDR_LH001_91_CONFIG1,&val,1);
	

}


void lh_weight_start(void)
{
	uint8_t val;

    val = ENUM_LH001_91_PGA_PGAGAIN_48;
    lh001_91_write_regs(ADDR_LH001_91_PGAGAIN,&val,1); 
	lh001_91_rdatac_start();
	lh001_91_adc_go();
}

void lh_weight_stop(void)
{
	lh001_91_adc_stop();
	lh001_91_rdatac_stop(); 
	
}

