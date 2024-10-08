#include "lh_temp.h"


void lh_temp_init(uint32_t sensor_type)
{
    LH001_91_ADC_INIT_t adc_init;
    LH001_91_PGA_INIT_t pga_init;
    uint8_t val;

    lh001_91_adc_stop();
	lh001_91_rdatac_stop(); 
	
	lh001_91_userkey1_unlock();
    lh001_91_read_regs(ADDR_LH001_91_MODCFG,&val,1);
    val &= ~(0x3);  //clear MODCFG.MD to 0
    val |= 1;
    lh001_91_write_regs(ADDR_LH001_91_MODCFG,&val,1);
    //val = ENUM_LH001_91_ADC_AVG_50<<POS_LH001_91_CONFIG1_AVG;  //50/4=12.5 sps
    //lh001_91_write_regs(ADDR_LH001_91_CONFIG1,&val,1);

    pga_init.gain = ENUM_LH001_91_PGA_PGAGAIN_8;
    pga_init.pga_bypass = 0;
    pga_init.power_mode = ENUM_LH001_91_PGA_POWER_HP;
    pga_init.comm_sense_en = 1;
	pga_init.pga_chop = ENUM_LH001_91_PGA_CHOP_DIV32;
    lh001_91_pga_init(&pga_init);

    //adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_512K;
	adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_128K;
    adc_init.oversample_rate = ENUM_LH001_91_ADC_DR_DIV1024; //update rate = Fmodclk/oversample_rate
    adc_init.conv_mode = ENUM_LH001_91_ADC_CONTINOUS;
    adc_init.ref_sel = ENUM_LH001_91_ADC_REF_2V5;
    lh001_91_adc_init(&adc_init);
    //lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_VCM,ENUM_LH001_91_ADCCHN_GND);	//FOR NOISE TEST
	if (sensor_type == TEMP_SENSOR_TYPE_RTD)
    {
        //exitaion current
        //100uA x 2K x PGA_8 = 1.6V DC
        lh001_91_Isource_cfg(1,CURRENT_SOURCE_MAG_100uA,MSK_LH001_91_IEXECON_AIN4);
        lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_RLDIN,ENUM_LH001_91_ADCCHN_AIN7);   //measure RCAL	

    }   
    else if(sensor_type == TEMP_SENSOR_TYPE_TC)
    {
        //exitaion current
        //100uA x 2K x PGA_8 = 1.6V DC
        lh001_91_Isource_cfg(1,CURRENT_SOURCE_MAG_100uA,MSK_LH001_91_IEXECON_AIN4);
        lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_RLDIN,ENUM_LH001_91_ADCCHN_AIN7);  
        
    }
    else if (sensor_type == TEMP_SENSOR_TYPE_IR)
    {

    }
    else
    {
        /* code */
    }
    
    
	

}


void lh_temp_start(void)
{
	lh001_91_rdatac_start();
	lh001_91_adc_go();
}

void lh_temp_stop(void)
{
	uint8_t val=0;
	lh001_91_adc_stop();
	lh001_91_rdatac_stop(); 
	
}

