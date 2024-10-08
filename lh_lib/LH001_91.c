/*

Version:
Author: LH Software Group
Copyright
*/
#include "LH001_91.h"

void lh001_91_hw_reset()
{
	
  LH001_91_PDEXTRST_SET();
  for(uint32_t i=0;i<8000;i++){LH001_91_DELAY_10US();}
  LH001_91_PDEXTRST_CLR();  //reset lh001_91
	for(uint32_t i=0;i<8000;i++){LH001_91_DELAY_10US();}
  LH001_91_PDEXTRST_SET();  //reset lh001_91
  for(uint32_t i=0;i<8000;i++){LH001_91_DELAY_10US();}
	
	lh001_91_adc_stop();	
	lh001_91_rdatac_stop();
	
}

void lh001_91_adc_go()
{
#if ADC_CONV_START_HW
    LH001_91_START_SET();
#else 
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    
    LH001_91_SpiTxRxByte(SPI_CMD_CONV_START);
    LH001_91_DELAY_10US();
    SPI_SET_CS();
    
#endif
}

void lh001_91_adc_stop()
{
#if ADC_CONV_START_HW
    LH001_91_START_CLR();
#else 
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    
    LH001_91_SpiTxRxByte(SPI_CMD_CONV_STOP);
    LH001_91_DELAY_10US();
    SPI_SET_CS();
    
#endif
}

void lh001_91_sw_reset(void)
{
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    //
    LH001_91_SpiTxRxByte(SPI_CMD_RESET);
    LH001_91_DELAY_10US();
    SPI_SET_CS();
    // 
	
		SPI_CLR_CS();
    LH001_91_DELAY_10US();
    //
    LH001_91_SpiTxRxByte(SPI_CMD_RESET);
    LH001_91_DELAY_10US();
    SPI_SET_CS();
	for(uint32_t i=0;i<8000;i++){
		LH001_91_DELAY_10US();
	}
	lh001_91_adc_stop();
	lh001_91_rdatac_stop();
}

void lh001_91_reset_fifo(void)
{
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    
    LH001_91_SpiTxRxByte(SPI_CMD_RST_FIFO);
    LH001_91_DELAY_10US();
    SPI_SET_CS();
     
}

void lh001_91_rdatac_start(void)
{
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    
    LH001_91_SpiTxRxByte(SPI_CMD_RDATAC);
    LH001_91_DELAY_10US();
	
    SPI_SET_CS();
    
}

void lh001_91_rdatac_stop(void)
{
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    
    LH001_91_SpiTxRxByte(SPI_CMD_SDATAC);
    LH001_91_DELAY_10US();
	
    SPI_SET_CS();
    
}


void lh001_91_write_regs(uint8_t addr, uint8_t *pRegs,uint8_t num)
{
    uint8_t *p = pRegs;
    uint8_t reg_addr;
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
	LH001_91_DELAY_10US();

#endif

    reg_addr = addr&0x1F;
    //
    if(addr < 32)
    {
        LH001_91_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
        LH001_91_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            LH001_91_SpiTxRxByte(p[i]);
        }
    }
    else if(addr < 63)
    {
        LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|reg_addr);
        LH001_91_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            LH001_91_SpiTxRxByte(p[i]);
        }
    }
    else if(addr == 63)
    {
        LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|reg_addr);
        LH001_91_SpiTxRxByte(0);
        LH001_91_SpiTxRxByte(0x72);
        LH001_91_SpiTxRxByte(p[0]);
    }
    else
    {
        //extend address mapping
        LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_91_SpiTxRxByte(0);
        LH001_91_SpiTxRxByte(0x72);
        LH001_91_SpiTxRxByte(0x01);
        //
#if SOFTWARE_SPI_CS
	    LH001_91_DELAY_10US();
        SPI_SET_CS();
#endif

#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
		LH001_91_DELAY_10US();
#endif
        //
		
        if(addr < (64+32))
        {
            LH001_91_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
        }
        else 
        {
            LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|reg_addr);
        }
        LH001_91_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            LH001_91_SpiTxRxByte(p[i]);
        }
        //
#if SOFTWARE_SPI_CS
		LH001_91_DELAY_10US();
        SPI_SET_CS();

#endif
        //
        //clear address extention
#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
		LH001_91_DELAY_10US();
#endif
        
        LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_91_SpiTxRxByte(0);
        LH001_91_SpiTxRxByte(0x72);
        LH001_91_SpiTxRxByte(0x00);
    }

	  //
#if SOFTWARE_SPI_CS
	LH001_91_DELAY_10US();
    SPI_SET_CS();
#endif
}

void lh001_91_read_regs(uint8_t addr, uint8_t *pRegs,uint8_t num)
{
    uint8_t *p = pRegs;
    uint8_t reg_addr;
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
#endif
    reg_addr = addr&0x1F;
	  //

    if(addr < 32)
    {
        LH001_91_SpiTxRxByte(SPI_CMD_RREG_MSK|reg_addr);
        LH001_91_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            p[i] = LH001_91_SpiTxRxByte(LH001_91_SPI_TX_DUMMY);
        }
    }
    else if(addr < 63)
    {
        LH001_91_SpiTxRxByte(SPI_CMD_RREG_BK1_MSK|reg_addr);
        LH001_91_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            p[i] = LH001_91_SpiTxRxByte(LH001_91_SPI_TX_DUMMY);
        }
    }
    else if (addr == 63)
    {
        LH001_91_SpiTxRxByte(SPI_CMD_RREG_BK1_MSK|reg_addr);
        LH001_91_SpiTxRxByte(0);
        LH001_91_SpiTxRxByte(0x72);
        p[0] = LH001_91_SpiTxRxByte(LH001_91_SPI_TX_DUMMY);
    }
    else 
    {
        //extend address mapping
        LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_91_SpiTxRxByte(0);
        LH001_91_SpiTxRxByte(0x72);
        LH001_91_SpiTxRxByte(0x01);
        //
#if SOFTWARE_SPI_CS
        LH001_91_DELAY_10US();
        SPI_SET_CS();
#endif
        //
#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
        LH001_91_DELAY_10US();
#endif
        //
        if(addr < (64+32))
        {
            LH001_91_SpiTxRxByte(SPI_CMD_RREG_MSK|reg_addr);
        }
        else 
        {
            LH001_91_SpiTxRxByte(SPI_CMD_RREG_BK1_MSK|reg_addr);
        }
        LH001_91_SpiTxRxByte(num-1);
        for(uint8_t i=0;i<num;i++)
        {
            p[i] = LH001_91_SpiTxRxByte(LH001_91_SPI_TX_DUMMY);
        }
        //
#if SOFTWARE_SPI_CS
        LH001_91_DELAY_10US();
        SPI_SET_CS();
#endif
        //
        //clear address extention
#if SOFTWARE_SPI_CS
        SPI_CLR_CS();
        LH001_91_DELAY_10US();
#endif
        //
        LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
        LH001_91_SpiTxRxByte(0);
        LH001_91_SpiTxRxByte(0x72);
        LH001_91_SpiTxRxByte(0x00);
    }
    
    //
#if SOFTWARE_SPI_CS
    LH001_91_DELAY_10US();
    SPI_SET_CS();
#endif
}

void lh001_91_read_data(uint8_t *pData,uint8_t num)
{
    uint8_t *p = pData;
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
#endif
	  
    LH001_91_SpiTxRxByte(SPI_CMD_RDATA);
    for(uint8_t i=0;i<num;i++)
    {
        p[i] = LH001_91_SpiTxRxByte(LH001_91_SPI_TX_DUMMY);
    }
#if SOFTWARE_SPI_CS
	LH001_91_DELAY_10US();
    SPI_SET_CS();
#endif
}

void lh001_91_read_data_nofifo(ADC_DATA_NOFIFO_t *pData)
{
    static uint8_t dat[6];
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
#endif
    LH001_91_SpiTxRxByte(SPI_CMD_RDATA);
    for(uint32_t i=0;i<6;i++)
    {
        dat[i] = LH001_91_SpiTxRxByte(LH001_91_SPI_TX_DUMMY);
    }
#if SOFTWARE_SPI_CS
    LH001_91_DELAY_10US();
    SPI_SET_CS();
#endif
    pData->reserved0 = 0;
    pData->start = dat[0]>>4;
    pData->loffstat = ((dat[0]&0x0F)<<1)|(dat[1]>>7);
    pData->gpio = (dat[1]>>5)&0x03;
    pData->reserved1 = ((dat[1]&0x1F)<<8) | dat[2];
    pData->data = (dat[3]<<16) | (dat[4]<<8) |(dat[5]);
}


void fifo_setup(uint32_t thresh_num){
    uint8_t val;
    lh001_91_read_regs(ADDR_LH001_91_SPICTRL,&val,1);
    val |= MSK_LH001_91_SPICTRL_FIFOEN; 
    lh001_91_write_regs(ADDR_LH001_91_SPICTRL,&val,1); 
    val = 0x02;
    lh001_91_write_regs(ADDR_LH001_91_INTOEN,&val,1);   //enable enough interrupt on DRDY pin
    val = thresh_num;
    lh001_91_write_regs(ADDR_LH001_91_FIFOSTA,&val,1);   //number for enough interrupt
}

void lh001_91_read_data_fifo(ADC_DATA_FIFO_t *pData)
{
    uint8_t dat[6];
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
#endif
    LH001_91_SpiTxRxByte(SPI_CMD_RDATA);
    for(uint32_t i=0;i<6;i++)
    {
        dat[i] = LH001_91_SpiTxRxByte(LH001_91_SPI_TX_DUMMY);
    }
#if SOFTWARE_SPI_CS
    LH001_91_DELAY_10US();
    SPI_SET_CS();
#endif
    pData->reserved0 = 0;
    pData->start = dat[0]>>4;
    pData->loffstat = ((dat[0]&0x0F)<<1)|(dat[1]>>7);
    pData->gpio = (dat[1]>>5)&0x03;
    pData->reserved1 = ((dat[1]&0x1F)<<8) | (dat[2]>>2);
    pData->data = ((dat[2]&0x03)<<22) | (dat[3]<<14) | (dat[4]<<6) |(dat[5]>>2);
    pData->tail = dat[5]&0x03;
}


/*!
    \brief initalize ADC

    Related registers: CONFIG1,BUFCON,ADCCTRL, MODCLK
    @param pSetup:
       typedef struct 
        {
            ///Sigma-Delta ADC modulator clock
            ///recommend to use 512K or 128K modulator clock,
            ///hihger modulator has better performance with cost of power
            ///ENUM_LH001_91_ADC_FMODCLK_512K
            ///ENUM_LH001_91_ADC_FMODCLK_128K
            uint32_t Fmodclk;
            ///COFIG1[0]:DR, oversampling rate for sinc3 filter, this is the final data rate
            ///0:Fmodclk/1024
            ///1:Fmodclk/512
            ///2:Fmodclk/256
            ///3:Fmodclk/128
            ///4:Fmodclk/64
            ///5:Fmodclk/32
            ///6:Fmodclk/16
            ///7:Fmodclk/1024
            uint32_t oversample_rate;
            ///ENUM_LH001_91_ADC_SINGLE, single conversion
            ///ENUM_LH001_91_ADC_CONTINOUS, continous conversion
            uint32_t conv_mode;
            ///reference selection
            ///ENUM_LH001_91_ADC_REF_2V, 2v adc internal reference
            ///ENUM_LH001_91_ADC_REF_2V5, 2.5V adc internal reference
            uint32_t ref_sel;
        }LH001_91_ADC_INIT_t; 
*/
void lh001_91_adc_init(LH001_91_ADC_INIT_t *pInit)
{
    uint8_t val;

    lh001_91_read_regs(ADDR_LH001_91_MODCLK,&val,1);
    val &= ~MSK_LH001_91_MODCLK_CD;
    val |= pInit->Fmodclk<<POS_LH001_91_MODCLK_CD;
    lh001_91_write_regs(ADDR_LH001_91_MODCLK,&val,1); 

    lh001_91_read_regs(ADDR_LH001_91_BUFCON,&val,1);
    val &= ~(MSK_LH001_91_BUFCON_EN2P5);
    val |= (pInit->ref_sel<<POS_LH001_91_BUFCON_EN2P5)|MSK_LH001_91_BUFCON_AVDD_DIV2|MSK_LH001_91_BUFCON_ENREF;
    lh001_91_write_regs(ADDR_LH001_91_BUFCON,&val,1); 

    lh001_91_read_regs(ADDR_LH001_91_CONFIG1,&val,1);
    val &= ~(MSK_LH001_91_CONFIG1_DR|MSK_LH001_91_CONFIG1_SGLESHOT);
    val |= (pInit->oversample_rate<<POS_LH001_91_CONFIG1_DR)|(pInit->conv_mode<<POS_LH001_91_CONFIG1_SGLESHOT);
    lh001_91_write_regs(ADDR_LH001_91_CONFIG1,&val,1); 

    lh001_91_read_regs(ADDR_LH001_91_ADCCTRL,&val,1);
    val |= (MSK_LH001_91_ADCCTRL_ADCEN|MSK_LH001_91_ADCCTRL_AMPEN);
    lh001_91_write_regs(ADDR_LH001_91_ADCCTRL,&val,1); 
}

/*!
    \brief PGA initialization

    Related registers: PGAGAIN, PGACTRL, PGACTRL1
    @param pInit 
        typedef struct 
        {
        ///PGA gain setting
        ///ENUM_LH001_91_PGA_PGAGAIN_1 
        ///ENUM_LH001_91_PGA_PGAGAIN_2 
        ///ENUM_LH001_91_PGA_PGAGAIN_3 
        ///ENUM_LH001_91_PGA_PGAGAIN_4 
        ///ENUM_LH001_91_PGA_PGAGAIN_6 
        ///ENUM_LH001_91_PGA_PGAGAIN_8 
        ///ENUM_LH001_91_PGA_PGAGAIN_12
        ///ENUM_LH001_91_PGA_PGAGAIN_24
        ///ENUM_LH001_91_PGA_PGAGAIN_48
        uint32_t gain;
        ///0, do not bypass
        ///1, bypass pga
        uint32_t pga_bypass;
        ///ENUM_LH001_91_PGA_POWER_LP, low power mode
        ///ENUM_LH001_91_PGA_POWER_HP, high power mode
        uint32_t power_mode;
        /// common mode voltage sense function, used for RLD
        ///0, disable
        ///1, enable
        uint32_t comm_sense_en;
        }LH001_91_PGA_INIT_t;
*/
void lh001_91_pga_init(LH001_91_PGA_INIT_t *pInit)
{
    uint8_t val;

    val = (pInit->gain)&MSK_LH001_91_PGAGAIN;
    lh001_91_write_regs(ADDR_LH001_91_PGAGAIN,&val,1); 

    lh001_91_read_regs(ADDR_LH001_91_PGACTRL1,&val,1);
    val &= ~(MSK_LH001_91_PGACTRL1_CHOP|MSK_LH001_91_PGACTRL1_CMSNS);
    val |= (pInit->comm_sense_en<<POS_LH001_91_PGACTRL1_CMSNS)|(pInit->pga_chop<<POS_LH001_91_PGACTRL1_CHOP);
    lh001_91_write_regs(ADDR_LH001_91_PGACTRL1,&val,1); 

    val = (pInit->pga_bypass<<POS_LH001_91_PGACTRL_BYPASS)|(pInit->power_mode<<POS_LH001_91_PGACTRL_LP);
    val &= ~MSK_LH001_91_PGACTRL_PD; //enable PGA
    lh001_91_write_regs(ADDR_LH001_91_PGACTRL,&val,1); 
}

/*!
    @param :LH001_91_LEADOFF_t
        //threshold to determine lead off state
        //LH001_91_LEADOFF_DELTA_1 
        //LH001_91_LEADOFF_DELTA_2 
        //LH001_91_LEADOFF_DELTA_3 
        //LH001_91_LEADOFF_DELTA_4 
        //LH001_91_LEADOFF_DELTA_5 
        //LH001_91_LEADOFF_DELTA_6 
        //LH001_91_LEADOFF_DELTA_7 
        //LH001_91_LEADOFF_DELTA_8 
        //LH001_91_LEADOFF_DELTA_9 
        //LH001_91_LEADOFF_DELTA_10
        //LH001_91_LEADOFF_DELTA_11
        //LH001_91_LEADOFF_DELTA_12
        //LH001_91_LEADOFF_DELTA_13
        //LH001_91_LEADOFF_DELTA_14
        //LH001_91_LEADOFF_DELTA_15
        //LH001_91_LEADOFF_DELTA_16
        uint32_t threshold;
        //current source selection for lead off detection
        //LH001_91_LEADOFF_CURRENT_SOURCE_5nA  
        //LH001_91_LEADOFF_CURRENT_SOURCE_10nA 
        //LH001_91_LEADOFF_CURRENT_SOURCE_25nA 
        //LH001_91_LEADOFF_CURRENT_SOURCE_50nA 
        //LH001_91_LEADOFF_CURRENT_SOURCE_100nA
        uint32_t current;
        //connection for sink current source
        //LH001_91_LEADOFF_SINK_CLOSE 
        //LH001_91_LEADOFF_SINK_AIN0  
        //LH001_91_LEADOFF_SINK_AIN1  
        //LH001_91_LEADOFF_SINK_AIN0_1
        uint32_t sink_cfg;
        //connection for source current source
        //LH001_91_LEADOFF_SOURCE_CLOSE 
        //LH001_91_LEADOFF_SOURCE_AIN0  
        //LH001_91_LEADOFF_SOURCE_AIN1  
        //LH001_91_LEADOFF_SOURCE_AIN0_1
        uint32_t source_cfg;
        //0, disable sink current on RLD
        //1, enable sink current on RLD
        uint32_t rld_sink_en;
        //0, disable leadoff detection on ain0
        //1, enable leadoff detection on ain0
        uint32_t ain0_detect_en;
        //0, disable leadoff detection on ain1
        //1, enable leadoff detection on ain1
        uint32_t ain1_detect_en;
        //0, disable leadoff detection on RLD
        //1, enable leadoff detection on RLD
        uint32_t rld_detect_en; 
*/
void lh001_91_leadoff_init(LH001_91_LEADOFF_t *pInit)
{
    uint8_t val;

    val = ((pInit->threshold)<<POS_LH001_91_LOCON1_THRESHOLD)|(pInit->current<<POS_LH001_91_LOCON1_CURRENT);
    lh001_91_write_regs(ADDR_LH001_91_LOCON1,&val,1); 

    lh001_91_read_regs(ADDR_LH001_91_LOCON2,&val,1);
    val &= ~(MSK_LH001_91_LOCON2_SINKEN|MSK_LH001_91_LOCON2_SOURCEENB|MSK_LH001_91_LOCON2_RLDLOEN);
    val = (pInit->sink_cfg<<POS_LH001_91_LOCON2_SINKEN)\
            |(pInit->source_cfg<<POS_LH001_91_LOCON2_SOURCEENB)\
            |(pInit->rld_sink_en<<POS_LH001_91_LOCON2_RLDLOEN);
    lh001_91_write_regs(ADDR_LH001_91_LOCON2,&val,1); 

    lh001_91_read_regs(ADDR_LH001_91_LOCON3,&val,1);
    val &= ~MSK_LH001_91_LOCON3_DCLOEN; 
    val |= (pInit->ain0_detect_en<<POS_LH001_91_LOCON3_DCLOEN0)\
         |(pInit->ain1_detect_en<<POS_LH001_91_LOCON3_DCLOEN1)\
         |(pInit->rld_detect_en<<POS_LH001_91_LOCON3_DCLOEN2);
    lh001_91_write_regs(ADDR_LH001_91_LOCON3,&val,1); 
}

void lh001_91_reg_dump(REG_DUMP_t *pRegs,uint8_t num)
{
    for(uint32_t i=0;i<num;i++)
    {
        lh001_91_read_regs(pRegs[i].addr,&(pRegs[i].val),1);        
    }
}

/*! @breif: fucntion to setup test signal frequency
    @param: freq
        ENUM_LH001_91_TEST_FREQUENCY_DC   
        ENUM_LH001_91_TEST_FREQUENCY_0P5HZ
        ENUM_LH001_91_TEST_FREQUENCY_1HZ  
        ENUM_LH001_91_TEST_FREQUENCY_2HZ  
*/
void lh001_91_test_signal(uint32_t freq)
{
    uint8_t val;
    lh001_91_read_regs(ADDR_LH001_91_LOCON3,&val,1);
    val &= ~MSK_LH001_91_LOCON3_TESTFREQ; 
    val |= (freq<<POS_LH001_91_LOCON3_TESTFREQ);
    lh001_91_write_regs(ADDR_LH001_91_LOCON3,&val,1); 
}


/*! @breif: setup right leg driver 
    @param enable:
        0 - disable right leg driver
        1 - enabel right leg driver
    @param refsel:
        ENUM_LH001_91_RLD_REF_AVDD_DIV2
        ENUM_LH001_91_RLD_REF_EXT  
    @param chop:
        ENUM_LH001_91_RLD_CHOP_CLOSE      
        ENUM_LH001_91_RLD_CHOP_FMOD_DIV32 
        ENUM_LH001_91_RLD_CHOP_FMOD_DIV64 
        ENUM_LH001_91_RLD_CHOP_FMOD_DIV128
*/
void lh001_91_rld_init(uint32_t enable,uint32_t refsel, uint32_t chop)
{
    uint8_t val;
    val = (enable<<POS_LH001_91_RLDCON_EN)|(refsel<<POS_LH001_91_RLDCON_RLDREFSEL)\
         |(chop<<POS_LH001_91_RLDCON_CHOPFREQ);
    lh001_91_write_regs(ADDR_LH001_91_RLDCON,&val,1); 
}

void lh001_91_spi_daisy_mode(uint32_t enable)
{
    uint8_t val;
    val = (uint8_t)LH001_91_USERKEY;
    lh001_91_write_regs(ADDR_LH001_91_USERKEY,&val,1);
    lh001_91_read_regs(ADDR_LH001_91_CLKCON,&val,1);        
    val &= (~MSK_LH001_91_CLKCON_CLKEN);
    if(enable == LH_ENABLE)
    {
        val |= (ENUM_LH001_91_CLKCON_OSCOUT<<POS_LH001_91_CLKCON_CLKEN); //output clock
    }
    else  //disable daisy chain
    {
        val |= (ENUM_LH001_91_CLKCON_OSCINT<<POS_LH001_91_CLKCON_CLKEN); //internal osc only
    }
    lh001_91_write_regs(ADDR_LH001_91_CLKCON,&val,1); 

    lh001_91_read_regs(ADDR_LH001_91_SPICTRL,&val,1);        
    val &= (~MSK_LH001_91_SPICTRL_DAISYIN);
    if(enable == LH_ENABLE)
    {
        val |= MSK_LH001_91_SPICTRL_DAISYIN/*|MSK_LH001_91_SPICTRL_FIFOEN*/;    //Better use FIFO mode in daisychain
    }    
    lh001_91_write_regs(ADDR_LH001_91_SPICTRL,&val,1); 
}

void lh001_91_adc_channel(uint32_t chP, uint32_t chN)
{
    uint8_t val;
    val = (chP<<POS_LH001_91_ADCCHCON_PSEL)\
            |(chN<<POS_LH001_91_ADCCHCON_NSEL);
    lh001_91_write_regs(ADDR_LH001_91_ADCCHCON,&val,1);
}

/*!
    @param code: adc raw code
    @param ref: adc referece in mv, 2000 or 2500
*/
float lh001_91_adc_code2mv(uint32_t code, uint32_t ref)
{
    int32_t dat;
    float rlt;
    if(code & (1<<23))
        dat = (int)((0xFFu<<24)|code);
    else
        dat = (int)code;
    rlt = dat*2.0*ref/((1<<24)-1);
    return rlt;
}

void lh001_91_userkey_unlock()
{
    uint8_t val;
    val = (uint8_t)LH001_91_USERKEY_F2M;
    lh001_91_write_regs(ADDR_LH001_91_USERKEY,&val,1);
}


/*
    Enter standby mode
    call lhxxx_wakeup function to wakeup.
*/
void lh001_91_standby(void)
{
    uint8_t reg_addr;
	
	//write PD.all to 0
    lh001_91_userkey_unlock();
	lh001_91_userkey1_unlock();
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
#endif
    reg_addr = ADDR_LH001_91_PLTFMPD&0x1F;
	
		//extend address mapping
		LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
		LH001_91_SpiTxRxByte(0);
		LH001_91_SpiTxRxByte(0x72);
		LH001_91_SpiTxRxByte(0x01);
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_CLR_CS();
#endif
		LH001_91_DELAY_10US();

		LH001_91_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
		LH001_91_SpiTxRxByte(0);
    LH001_91_SpiTxRxByte(0);
		
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif


		//write PD.all to 1
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
     SPI_CLR_CS();
#endif
    LH001_91_DELAY_10US();
    LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
    LH001_91_SpiTxRxByte(0);
    LH001_91_SpiTxRxByte(0x72);
    LH001_91_SpiTxRxByte(0x00);
	LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
    SPI_SET_CS();
#endif
		LH001_91_DELAY_10US();
    lh001_91_userkey_unlock();
		
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
#endif
    reg_addr = ADDR_LH001_91_PLTFMPD&0x1F;
    LH001_91_DELAY_10US();
		//extend address mapping
		LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
		LH001_91_SpiTxRxByte(0);
		LH001_91_SpiTxRxByte(0x72);
		LH001_91_SpiTxRxByte(0x01);
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_CLR_CS();
#endif
		LH001_91_DELAY_10US();

		LH001_91_SpiTxRxByte(SPI_CMD_WREG_MSK|reg_addr);
		LH001_91_SpiTxRxByte(0);
    LH001_91_SpiTxRxByte(MSK_LH001_91_PLTFMPD_PDALL);
	//LH001_91_SpiTxRxByte((1<<3)|(1<<6)|(1<<5)|(1<<4));

		
		LH001_91_DELAY_10US();
#if SOFTWARE_SPI_CS
		SPI_SET_CS();
#endif

}

/*
    Any read to LH device will wakeup system
*/
void lh001_91_wakeup(void)
{
    uint8_t val;
    lh001_91_read_regs(ADDR_LH001_91_CHIPID,&val,1);	//read any register to wake up system
    for(uint32_t i=0;i<100;i++);
	
    
    //clear address extention
#if SOFTWARE_SPI_CS
    SPI_CLR_CS();
    LH001_91_DELAY_10US();
#endif
    
    LH001_91_SpiTxRxByte(SPI_CMD_WREG_BK1_MSK|31);
    LH001_91_SpiTxRxByte(0);
    LH001_91_SpiTxRxByte(0x72);
    LH001_91_SpiTxRxByte(0x00);

	  
#if SOFTWARE_SPI_CS
    LH001_91_DELAY_10US();
    SPI_SET_CS();
#endif
		
}


 void lh001_91_userkey1_unlock()
{

    uint8_t RegAddr;

    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    LH001_91_SpiTxRxByte(31 | 0xc0);
    LH001_91_SpiTxRxByte(0x00);
    LH001_91_SpiTxRxByte(0x72);
    LH001_91_SpiTxRxByte(0x01);
    LH001_91_DELAY_10US();
    SPI_SET_CS();

    LH001_91_DELAY_10US();

    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    RegAddr = ADDR_LH001_91_KEY0 & 0x1F;
    LH001_91_SpiTxRxByte(RegAddr | 0xc0);
    LH001_91_SpiTxRxByte(0x01);
    LH001_91_SpiTxRxByte(0xac);
    LH001_91_SpiTxRxByte(0xec);
    LH001_91_DELAY_10US();
    SPI_SET_CS();

    LH001_91_DELAY_10US();

    SPI_CLR_CS();
    LH001_91_DELAY_10US();
    LH001_91_SpiTxRxByte(31 | 0xc0);
    LH001_91_SpiTxRxByte(0x00);
    LH001_91_SpiTxRxByte(0x72);
    LH001_91_SpiTxRxByte(0x00);
    LH001_91_DELAY_10US();
    SPI_SET_CS();
}

/*
    @param clkSrc: 
        ENUM_LH001_91_OUTCLK_0       
        ENUM_LH001_91_OUTCLK_OSC     
        ENUM_LH001_91_OUTCLK_SYSCLK  
        ENUM_LH001_91_OUTCLK_MODCLK  
        ENUM_LH001_91_OUTCLK_LEADOFF 
        ENUM_LH001_91_OUTCLK_CHOP    
    @param pin:
        ENUM_LH001_91_OUTCLK_DRDY
        ENUM_LH001_91_OUTCLK_INTB
*/
void lh001_91_output_clk(uint32_t clkSrc, uint32_t pin)
{
    uint8_t val;
    val = (clkSrc<<POS_LH001_91_OUTCLK_SEL) | (pin<<POS_LH001_91_OUTCLK_PIN);
    lh001_91_write_regs(ADDR_LH001_91_OUTCLK,&val,1);
}


/*
    set current source to AIN4 or AIN5
    example: lh001_91_Isource_cfg(1,CURRENT_SOURCE_MAG_50uA,MSK_LH001_91_IEXECON_AIN4)
    @param Isrc:
        typedef enum{
        CURRENT_SOURCE_MAG_100nA = 0,
        CURRENT_SOURCE_MAG_50uA,
        CURRENT_SOURCE_MAG_100uA,
        CURRENT_SOURCE_MAG_250uA,
        CURRENT_SOURCE_MAG_500uA,
        CURRENT_SOURCE_MAG_750uA,
        CURRENT_SOURCE_MAG_1mA,
        }CURRENT_SRC_MAG_t;
    @param channel: 
        - MSK_LH001_91_IEXECON_AIN4, current source connect to AIN4
        - MSK_LH001_91_IEXECON_AIN5, current source connect to AIN5

*/
void lh001_91_Isource_cfg(uint32_t enable,CURRENT_SRC_MAG_t Isrc,uint32_t channel)
{
    uint8_t val;
    if(enable > 0)
    {
        lh001_91_read_regs(ADDR_LH001_91_IEXEMAG,&val,1);
        if (channel == MSK_LH001_91_IEXECON_AIN4)
        {
            val &= ~MSK_LH001_91_IEXEMAG_AIN4;
            val |= (Isrc<<POS_LH001_91_IEXEMAG_AIN4);
        }
        else if(channel == MSK_LH001_91_IEXECON_AIN5)
        {
            val &= ~MSK_LH001_91_IEXEMAG_AIN5;
            val |= (Isrc<<POS_LH001_91_IEXEMAG_AIN5);
        }
        lh001_91_write_regs(ADDR_LH001_91_IEXEMAG,&val,1);
        

        val = MSK_LH001_91_IEXECON_EN | (channel);
        if (Isrc == CURRENT_SOURCE_MAG_100nA)
        {
            val |= MSK_LH001_91_IEXECON_EN100N;
        }
        lh001_91_write_regs(ADDR_LH001_91_IEXECON,&val,1);

    }
    else
    {
        val = 0;
        lh001_91_write_regs(ADDR_LH001_91_IEXECON,&val,1);
        lh001_91_write_regs(ADDR_LH001_91_IEXEMAG,&val,1);
    }
    
}




