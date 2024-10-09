/*
Author: LH Software Group
Copyright
*/

#ifndef __LH001_91_H
#define __LH001_91_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
/*!
	spi_def header file
*/
#include "spi_def.h"

/*
	0 - Send SPI command to trigger ADC conversion
	1 - Set START pin to high to trigger ADC conversion
*/
#define ADC_CONV_START_HW 0


#define REG_VALUE_TBD     0x00

#define ADC_REF_MV        2500
// #define ADC_REF_MV  2000

/*********************************************************
	Register Definition
*********************************************************/
/*MISC registers*/
#define ADDR_LH001_91_SYSCLK  0x14
#define ADDR_LH001_91_MODCLK  0x15
#define ADDR_LH001_91_CLKCON  0x16
#define ADDR_LH001_91_SPICTRL 0x17
#define ADDR_LH001_91_INTOEN  0x18
#define ADDR_LH001_91_FIFOSTA 0x19
#define ADDR_LH001_91_USERKEY 0x1E
// #define ADDR_LH001_91_CHIPID                0x00
#define ADDR_LH001_91_CHIPID 0x40
#define ADDR_LH001_91_OUTCLK 0x1C
/*ADC registers*/
#define ADDR_LH001_91_CONFIG1  0x01
#define ADDR_LH001_91_ADCCHOP  0x4B
#define ADDR_LH001_91_ADCCTRL  0x0C
#define ADDR_LH001_91_ADCCHCON 0x0B
#define ADDR_LH001_91_BUFCON   0x0A
#define ADDR_LH001_91_RWAB     0x10
#define ADDR_LH001_91_GAIN     0x11
#define ADDR_LH001_91_OFFSET   0x12
/*PGA registers*/
#define ADDR_LH001_91_PGAGAIN  0x0D
#define ADDR_LH001_91_PGACTRL  0x0E
#define ADDR_LH001_91_PGACTRL1 0x0F
/*ECG Registers*/
#define ADDR_LH001_91_LOCON1   0x03
#define ADDR_LH001_91_LOCON2   0x04
#define ADDR_LH001_91_LOCON3   0x05
#define ADDR_LH001_91_LOFFSTAT 0x06
#define ADDR_LH001_91_RLDCON   0x07
#define ADDR_LH001_91_IEXECON  0x08
#define ADDR_LH001_91_IEXEMAG  0x09
/*GPIO Registers*/
#define ADDR_LH001_91_GPIO0 0x1F
#define ADDR_LH001_91_GPIO1 0x20
/*KEYS*/
#define ADDR_LH001_91_KEY0 0x70
#define ADDR_LH001_91_KEY1 0x71
/*PLATFORM*/
#define ADDR_LH001_91_PLTFMPD 0x55
#define ADDR_LH001_91_MODCFG  0x64


/*********************************************************
	Register bit mask and bit position definition
*********************************************************/
/*MISC*/
#define MSK_LH001_91_SYSCLK_CD          0xFF
#define MSK_LH001_91_MODCLK_CD          0xFF
#define POS_LH001_91_MODCLK_CD          0x00
#define POS_LH001_91_MODCFG_ACIMPEN     2
#define MSK_LH001_91_MODCFG_ACIMPEN     (1 << POS_LH001_91_MODCFG_ACIMPEN)
#define MSK_LH001_91_CLKCON_CLKEN       0x01
#define POS_LH001_91_CLKCON_CLKEN       0
#define MSK_LH001_91_CLKCON_F2M         0x02
#define POS_LH001_91_CLKCON_F2M         1
#define MSK_LH001_91_CLKCON_PU          0x04
#define POS_LH001_91_CLKCON_PU          2
#define MSK_LH001_91_SPICTRL_DAISYIN    0x01
#define POS_LH001_91_SPICTRL_DAISYIN    0
#define MSK_LH001_91_SPICTRL_FIFOEN     0x02
#define POS_LH001_91_SPICTRL_FIFOEN     1
#define MSK_LH001_91_SPICTRL_DCMODE     0x04
#define POS_LH001_91_SPICTRL_DCMODE     2
#define MSK_LH001_91_INTOEN_INTEN       0x0F
#define POS_LH001_91_INTOEN_INTEN       0
#define MSK_LH001_91_INTOEN_INTBEN      (0x0F << 4)
#define POS_LH001_91_INTOEN_INTBEN      (4)
#define MSK_LH001_91_INTOEN_DRDY        (0x01 << 0)
#define MSK_LH001_91_INTOEN_ENOUGH      (0x01 << 1)
#define MSK_LH001_91_INTOEN_FULL        (0x01 << 2)
#define MSK_LH001_91_INTOEN_OVERFLOW    (0x01 << 3)
#define MSK_LH001_91_FIFOSTA_ENOUGHCNT  (0x1F << 0)
#define POS_LH001_91_FIFOSTA_ENOUGHCNT  (0)
#define MSK_LH001_91_FIFOSTA_ENOUGHTINT (0x01 << 5)
#define MSK_LH001_91_FIFOSTA_FULL       (0x01 << 6)
#define MSK_LH001_91_FIFOSTA_OVERFLOW   (0x01 << 7)
#define POS_LH001_91_OUTCLK_SEL         (0x00)
#define MSK_LH001_91_OUTCLK_SEL         (0x07 << POS_LH001_91_OUTCLK_SEL)
#define POS_LH001_91_OUTCLK_PIN         (0x3)
#define MSK_LH001_91_OUTCLK_PIN         (0x3 << POS_LH001_91_OUTCLK_PIN)

/*ADC*/
#define MSK_LH001_91_ADCCTRL_ADCEN    (0x01 << 0)
#define POS_LH001_91_ADCCTRL_ADCEN    (0)
#define MSK_LH001_91_ADCCTRL_AMPEN    (0x01 << 1)
#define POS_LH001_91_ADCCTRL_AMPEN    (1)
#define MSK_LH001_91_CONFIG1_DR       (0x07 << 0)
#define MSK_LH001_91_CONFIG1_SGLESHOT (0x01 << 3)
#define MSK_LH001_91_CONFIG1_AVG      (0x0F << 4)
#define POS_LH001_91_CONFIG1_DR       (0)
#define POS_LH001_91_CONFIG1_SGLESHOT (3)
#define POS_LH001_91_CONFIG1_AVG      (4)
#define POS_LH001_91_BUFCON_TEMPEN    (1)
#define MSK_LH001_91_BUFCON_TEMPEN    (1 << POS_LH001_91_BUFCON_TEMPEN)
#define POS_LH001_91_BUFCON_AVDD_DIV2 (2)
#define MSK_LH001_91_BUFCON_AVDD_DIV2 (1 << POS_LH001_91_BUFCON_AVDD_DIV2)
#define POS_LH001_91_BUFCON_ENREF     (4)
#define MSK_LH001_91_BUFCON_ENREF     (1 << POS_LH001_91_BUFCON_ENREF)
#define POS_LH001_91_BUFCON_EN2P5     (5)
#define MSK_LH001_91_BUFCON_EN2P5     (0x01 << POS_LH001_91_BUFCON_EN2P5)
#define POS_LH001_91_ADCCHCON_PSEL    (0)
#define POS_LH001_91_ADCCHCON_NSEL    (4)
/*PGA*/
#define MSK_LH001_91_PGACTRL_PD     (1 << 0)
#define POS_LH001_91_PGACTRL_PD     (1 << 0)
#define MSK_LH001_91_PGACTRL_BYPASS (1 << 1)
#define POS_LH001_91_PGACTRL_BYPASS (1 << 1)
#define MSK_LH001_91_PGACTRL_RESET  (1 << 2)
#define POS_LH001_91_PGACTRL_RESET  (1 << 2)
#define MSK_LH001_91_PGACTRL_LP     (1 << 3)
#define POS_LH001_91_PGACTRL_LP     (3)
#define MSK_LH001_91_PGACTRL_AC     (1 << 4)
#define MSK_LH001_91_PGACTRL1_CMSNS (1 << 2)
#define POS_LH001_91_PGACTRL1_CMSNS (2)
#define POS_LH001_91_PGACTRL1_CHOP  (0)
#define MSK_LH001_91_PGACTRL1_CHOP  (3 << POS_LH001_91_PGACTRL1_CHOP)
#define POS_LH001_91_PGACTRL1_ACMUX (5)
#define MSK_LH001_91_PGACTRL1_ACMUX (7 << POS_LH001_91_PGACTRL1_ACMUX)
#define POS_LH001_91_PGAGAIN        0
#define MSK_LH001_91_PGAGAIN        0x3F
#define POS_LH001_91_PGACTRL_ACEN   (4)
#define MSK_LH001_91_PGACTRL_ACEN   (1 << POS_LH001_91_PGACTRL_ACEN)
#define POS_LH001_91_PGACTRL_ACGAIN (5)
#define MSK_LH001_91_PGACTRL_ACGAIN (7 << POS_LH001_91_PGACTRL_ACGAIN)
/*ECG*/
#define POS_LH001_91_LOCON1_THRESHOLD (0)
#define MSK_LH001_91_LOCON1_THRESHOLD (0x0F)
#define POS_LH001_91_LOCON1_CURRENT   (4)
#define MSK_LH001_91_LOCON1_CURRENT   (0x07 << POS_LH001_91_LOCON1_CURRENT)
#define POS_LH001_91_LOCON2_ACLOEN    (0)
#define MSK_LH001_91_LOCON2_ACLOEN    (1 << POS_LH001_91_LOCON2_ACLOEN)
#define POS_LH001_91_LOCON2_SINKEN    (1)
#define MSK_LH001_91_LOCON2_SINKEN    (3 << POS_LH001_91_LOCON2_SINKEN)
#define POS_LH001_91_LOCON2_SOURCEENB (3)
#define MSK_LH001_91_LOCON2_SOURCEENB (3 << POS_LH001_91_LOCON2_SOURCEENB)
#define POS_LH001_91_LOCON2_RLDLOEN   (5)
#define MSK_LH001_91_LOCON2_RLDLOEN   (1 << POS_LH001_91_LOCON2_RLDLOEN)
#define POS_LH001_91_LOCON3_DCLOEN    (0)
#define MSK_LH001_91_LOCON3_DCLOEN    (7 << POS_LH001_91_LOCON3_DCLOEN)
#define POS_LH001_91_LOCON3_TESTFREQ  (4)
#define MSK_LH001_91_LOCON3_TESTFREQ  (0xF << POS_LH001_91_LOCON3_TESTFREQ)
#define POS_LH001_91_LOCON3_DCLOEN0   (0)
#define POS_LH001_91_LOCON3_DCLOEN1   (1)
#define POS_LH001_91_LOCON3_DCLOEN2   (2)
#define POS_LH001_91_RLDCON_CHOPFREQ  (0)
#define MSK_LH001_91_RLDCON_CHOPFREQ  (3 << POS_LH001_91_RLDCON_CHOPFREQ)
#define POS_LH001_91_RLDCON_EN        (2)
#define MSK_LH001_91_RLDCON_EN        (1 << POS_LH001_91_RLDCON_EN)
#define POS_LH001_91_RLDCON_RLDREFSEL (3)
#define MSK_LH001_91_RLDCON_RLDREFSEL (1 << POS_LH001_91_RLDCON_RLDREFSEL)
/*PLATFORM*/
#define POS_LH001_91_PLTFMPD_PDALL (7)
#define MSK_LH001_91_PLTFMPD_PDALL (1 << POS_LH001_91_PLTFMPD_PDALL)
/*CURRENT SOURCE*/
#define POS_LH001_91_IEXECON_EN     (0)
#define MSK_LH001_91_IEXECON_EN     (1 << POS_LH001_91_IEXECON_EN)
#define POS_LH001_91_IEXECON_AIN4   (1)
#define MSK_LH001_91_IEXECON_AIN4   (1 << POS_LH001_91_IEXECON_AIN4)
#define POS_LH001_91_IEXECON_AIN5   (2)
#define MSK_LH001_91_IEXECON_AIN5   (1 << POS_LH001_91_IEXECON_AIN5)
#define POS_LH001_91_IEXECON_EN100N (3)
#define MSK_LH001_91_IEXECON_EN100N (1 << POS_LH001_91_IEXECON_EN100N)
#define POS_LH001_91_IEXEMAG_AIN4   (0)
#define MSK_LH001_91_IEXEMAG_AIN4   (3 << POS_LH001_91_IEXEMAG_AIN4)
#define POS_LH001_91_IEXEMAG_AIN5   (3)
#define MSK_LH001_91_IEXEMAG_AIN5   (3 << POS_LH001_91_IEXEMAG_AIN5)

/*********************************************************
	enum  definition
*********************************************************/
/*ADC*/
#define ENUM_LH001_91_ADC_SINGLE    0x01
#define ENUM_LH001_91_ADC_CONTINOUS 0x00
#define ENUM_LH001_91_ADC_REF_2V    0x00
#define ENUM_LH001_91_ADC_REF_2V5   0x01
#define ENUM_LH001_91_ADCCHP_AIN0   0X00
#define ENUM_LH001_91_ADCCHP_AIN1   0X01
#define ENUM_LH001_91_ADCCHP_AIN2   0X02
#define ENUM_LH001_91_ADCCHP_AIN3   0X03
#define ENUM_LH001_91_ADCCHP_AIN4   0X04
#define ENUM_LH001_91_ADCCHP_AIN5   0X05
#define ENUM_LH001_91_ADCCHP_AIN6   0X06
#define ENUM_LH001_91_ADCCHP_AIN7   0X07
#define ENUM_LH001_91_ADCCHP_RLDIN  0X08
#define ENUM_LH001_91_ADCCHP_DVDD   0X09
#define ENUM_LH001_91_ADCCHP_AVDD   0X0A
#define ENUM_LH001_91_ADCCHP_VCM    0X0B
#define ENUM_LH001_91_ADCCHP_TEMP   0X0C
#define ENUM_LH001_91_ADCCHP_TEST   0X0D
#define ENUM_LH001_91_ADCCHN_AIN0   0X00
#define ENUM_LH001_91_ADCCHN_AIN1   0X01
#define ENUM_LH001_91_ADCCHN_AIN2   0X02
#define ENUM_LH001_91_ADCCHN_AIN3   0X03
#define ENUM_LH001_91_ADCCHN_AIN4   0X04
#define ENUM_LH001_91_ADCCHN_AIN5   0X05
#define ENUM_LH001_91_ADCCHN_AIN6   0X06
#define ENUM_LH001_91_ADCCHN_AIN7   0X07
#define ENUM_LH001_91_ADCCHN_RLDIN  0X08
#define ENUM_LH001_91_ADCCHN_GND    0X0F
/*PGA*/
#define ENUM_LH001_91_PGA_PGAGAIN_1  0x00
#define ENUM_LH001_91_PGA_PGAGAIN_2  0x01
#define ENUM_LH001_91_PGA_PGAGAIN_3  0x02
#define ENUM_LH001_91_PGA_PGAGAIN_4  0x03
#define ENUM_LH001_91_PGA_PGAGAIN_6  0x04
#define ENUM_LH001_91_PGA_PGAGAIN_8  0x05
#define ENUM_LH001_91_PGA_PGAGAIN_12 0x06
#define ENUM_LH001_91_PGA_PGAGAIN_24 0x07
#define ENUM_LH001_91_PGA_PGAGAIN_48 0x08
#define ENUM_LH001_91_PGA_POWER_LP   0x01
#define ENUM_LH001_91_PGA_POWER_HP   0x00
#define ENUM_LH001_91_PGA_CHOP_DIV64 0
#define ENUM_LH001_91_PGA_CHOP_DIV32 1
#define ENUM_LH001_91_PGA_CHOP_DIV16 2
#define ENUM_LH001_91_PGA_CHOP_DIV8  3
/*MISC*/
#define ENUM_LH001_91_CLKCON_OSCINT  0x00
#define ENUM_LH001_91_CLKCON_OSCOUT  0x01
#define ENUM_LH001_91_CLKCON_OSC2M   0x00
#define ENUM_LH001_91_CLKCON_OSC16M  0x01
#define ENUM_LH001_91_CLKCON_PULLUP  (0 << 2)
#define ENUM_LH001_91_CLKCON_NOPULL  (1 << 2)
#define LH001_91_USERKEY             0x86
#define LH001_91_USERKEY_F2M         0x58
#define ENUM_LH001_91_OUTCLK_0       0x00
#define ENUM_LH001_91_OUTCLK_OSC     0x01
#define ENUM_LH001_91_OUTCLK_SYSCLK  0x02
#define ENUM_LH001_91_OUTCLK_MODCLK  0x03
#define ENUM_LH001_91_OUTCLK_LEADOFF 0x04
#define ENUM_LH001_91_OUTCLK_CHOP    0x05
#define ENUM_LH001_91_OUTCLK_DRDY    0x01
#define ENUM_LH001_91_OUTCLK_INTB    0x02


/*ECG*/
#define ENUM_LH001_91_TEST_FREQUENCY_DC    0
#define ENUM_LH001_91_TEST_FREQUENCY_0P5HZ 1
#define ENUM_LH001_91_TEST_FREQUENCY_1HZ   2
#define ENUM_LH001_91_TEST_FREQUENCY_2HZ   3
#define ENUM_LH001_91_RLD_CHOP_CLOSE       0
#define ENUM_LH001_91_RLD_CHOP_FMOD_DIV32  1
#define ENUM_LH001_91_RLD_CHOP_FMOD_DIV64  2
#define ENUM_LH001_91_RLD_CHOP_FMOD_DIV128 3
#define ENUM_LH001_91_RLD_REF_AVDD_DIV2    0
#define ENUM_LH001_91_RLD_REF_EXT          1


/*********************************************************
 *SPI command
 *********************************************************/
#define SPI_CMD_RESET        0x06 // reset device
#define SPI_CMD_CONV_START   0x08 // start conversion
#define SPI_CMD_CONV_STOP    0x0A // stop conversion
#define SPI_CMD_RST_FIFO     0x0C // reset data fifo
#define SPI_CMD_RDATAC       0x10 // start continous read
#define SPI_CMD_SDATAC       0x11 // stop continouse read
#define SPI_CMD_RDATA        0x12 // read data command
#define SPI_CMD_RREG_MSK     0x20 // read register from specified address, followed by register number to be read
#define SPI_CMD_WREG_MSK     0x40 // write register to specified address, followed by register number to be write
#define SPI_CMD_RREG_BK1_MSK 0xA0 // read register from specified address +32,followed by register number to be read
#define SPI_CMD_WREG_BK1_MSK 0xC0 // write register to specified address +32,followed by register number to be write

/*********************************************************
	Register reset value definition
*********************************************************/
#define RST_VAL_LH001_91_GPIO0    0x00
#define RST_VAL_LH001_91_LOCON1   0x0F
#define RST_VAL_LH001_91_LOCON2   0x18
#define RST_VAL_LH001_91_BUFCON   0x11
#define RST_VAL_LH001_91_ADCCHCON 0x10
#define RST_VAL_LH001_91_CHIPID   0x01
#define RST_VAL_LH001_91_CONFIG1  0x06
#define RST_VAL_LH001_91_PGACTRL  0x0D
#define RST_VAL_LH001_91_SYSCLK   0x08
#define RST_VAL_LH001_91_CLKCON   0x06
#define RST_VAL_LH001_91_INTOEN   0x21
#define RST_VAL_LH001_91_FIFOSTA  0x0F

/*********************************************************
 Init structure
*********************************************************/
#define ENUM_LH001_91_ADC_FMODCLK_512K    4   // 2048KHz/4
#define ENUM_LH001_91_ADC_FMODCLK_128K    16  // 2048KHz/16
#define ENUM_LH001_91_ADC_FMODCLK_32K     64  // 2048KHz/32
#define ENUM_LH001_91_ADC_FMODCLK_16K     128 // 2048KHz/128

#define ENUM_LH001_91_ADC_FMODCLK_IMP1M   16  // 16MHz/16
#define ENUM_LH001_91_ADC_FMODCLK_IMP512K 32  // 16MHz/32
#define ENUM_LH001_91_ADC_FMODCLK_IMP128K 128 // 16MHz/128

/*! DR definition for MODCFG.MD=1*/
#define ENUM_LH001_91_ADC_DR_DIV1024 0
#define ENUM_LH001_91_ADC_DR_DIV512  1
#define ENUM_LH001_91_ADC_DR_DIV256  2
#define ENUM_LH001_91_ADC_DR_DIV128  3
#define ENUM_LH001_91_ADC_DR_DIV64   4
#define ENUM_LH001_91_ADC_DR_DIV32   5
#define ENUM_LH001_91_ADC_DR_DIV16   6
#define ENUM_LH001_91_ADC_AVG_30K    0
#define ENUM_LH001_91_ADC_AVG_15K    1
#define ENUM_LH001_91_ADC_AVG_7K5    2
#define ENUM_LH001_91_ADC_AVG_3K75   3
#define ENUM_LH001_91_ADC_AVG_2K     4
#define ENUM_LH001_91_ADC_AVG_1K     5
#define ENUM_LH001_91_ADC_AVG_500    6
#define ENUM_LH001_91_ADC_AVG_100    7
#define ENUM_LH001_91_ADC_AVG_60     8
#define ENUM_LH001_91_ADC_AVG_50     9
#define ENUM_LH001_91_ADC_AVG_30     10
#define ENUM_LH001_91_ADC_AVG_25     11
#define ENUM_LH001_91_ADC_AVG_15     12
#define ENUM_LH001_91_ADC_AVG_10     13
#define ENUM_LH001_91_ADC_AVG_5      14
#define ENUM_LH001_91_ADC_AVG_2P5    15
typedef struct
{
	/// Sigma-Delta ADC modulator clock
	/// recommend to use 512K or 128K modulator clock,
	/// hihger modulator has better performance with cost of power
	/// ENUM_LH001_91_ADC_FMODCLK_512K
	/// ENUM_LH001_91_ADC_FMODCLK_128K
	uint32_t Fmodclk;
	/// COFIG1[0]:DR, oversampling rate for sinc3 filter, this is the final data rate
	/// 0:Fmodclk/1024
	/// 1:Fmodclk/512
	/// 2:Fmodclk/256
	/// 3:Fmodclk/128
	/// 4:Fmodclk/64
	/// 5:Fmodclk/32
	/// 6:Fmodclk/16
	/// 7:Fmodclk/1024
	uint32_t oversample_rate;
	/// ENUM_LH001_91_ADC_SINGLE, single conversion
	/// ENUM_LH001_91_ADC_CONTINOUS, continous conversion
	uint32_t conv_mode;
	/// reference selection
	/// ENUM_LH001_91_ADC_REF_2V, 2v adc internal reference
	/// ENUM_LH001_91_ADC_REF_2V5, 2.5V adc internal reference
	uint32_t ref_sel;
} LH001_91_ADC_INIT_t;

typedef struct
{
	/// PGA gain setting
	/// ENUM_LH001_91_PGA_PGAGAIN_1
	/// ENUM_LH001_91_PGA_PGAGAIN_2
	/// ENUM_LH001_91_PGA_PGAGAIN_3
	/// ENUM_LH001_91_PGA_PGAGAIN_4
	/// ENUM_LH001_91_PGA_PGAGAIN_6
	/// ENUM_LH001_91_PGA_PGAGAIN_8
	/// ENUM_LH001_91_PGA_PGAGAIN_12
	/// ENUM_LH001_91_PGA_PGAGAIN_24
	/// ENUM_LH001_91_PGA_PGAGAIN_48
	uint32_t gain;
	/// 0, do not bypass
	/// 1, bypass pga
	uint32_t pga_bypass;
	// ENUM_LH001_91_PGA_CHOP_DIV64
	// ENUM_LH001_91_PGA_CHOP_DIV32
	// ENUM_LH001_91_PGA_CHOP_DIV16
	// ENUM_LH001_91_PGA_CHOP_DIV8
	uint32_t pga_chop;
	/// ENUM_LH001_91_PGA_POWER_LP, low power mode
	/// ENUM_LH001_91_PGA_POWER_HP, high power mode
	uint32_t power_mode;
	/// common mode voltage sense function, used for RLD
	/// 0, disable
	/// 1, enable
	uint32_t comm_sense_en;
} LH001_91_PGA_INIT_t;

// Vcm=AVDD/2, delta=0.81*Vcm/16, Hysteresis=0.25*delta
#define LH001_91_LEADOFF_DELTA_1              0 // VTHH = Vcm+1*delta, VTHH=Vcm-1*delta
#define LH001_91_LEADOFF_DELTA_2              1 // VTHH = Vcm+2*delta, VTHH=Vcm-2*delta
#define LH001_91_LEADOFF_DELTA_3              2 // VTHH = Vcm+3*delta, VTHH=Vcm-3*delta
#define LH001_91_LEADOFF_DELTA_4              3 // VTHH = Vcm+4*delta, VTHH=Vcm-4*delta
#define LH001_91_LEADOFF_DELTA_5              4 // VTHH = Vcm+5*delta, VTHH=Vcm-5*delta
#define LH001_91_LEADOFF_DELTA_6              5 // VTHH = Vcm+6*delta, VTHH=Vcm-6*delta
#define LH001_91_LEADOFF_DELTA_7              6 // VTHH = Vcm+7*delta, VTHH=Vcm-7*delta
#define LH001_91_LEADOFF_DELTA_8              7 // VTHH = Vcm+8*delta, VTHH=Vcm-8*delta
#define LH001_91_LEADOFF_DELTA_9              8 // VTHH = Vcm+9*delta, VTHH=Vcm-9*delta
#define LH001_91_LEADOFF_DELTA_10             9 // VTHH = Vcm+10*delta, VTHH=Vcm-10*delta
#define LH001_91_LEADOFF_DELTA_11             A // VTHH = Vcm+11*delta, VTHH=Vcm-11*delta
#define LH001_91_LEADOFF_DELTA_12             B // VTHH = Vcm+12*delta, VTHH=Vcm-12*delta
#define LH001_91_LEADOFF_DELTA_13             C // VTHH = Vcm+13*delta, VTHH=Vcm-13*delta
#define LH001_91_LEADOFF_DELTA_14             D // VTHH = Vcm+14*delta, VTHH=Vcm-14*delta
#define LH001_91_LEADOFF_DELTA_15             E // VTHH = Vcm+15*delta, VTHH=Vcm-15*delta
#define LH001_91_LEADOFF_DELTA_16             F // VTHH = Vcm+16*delta, VTHH=Vcm-16*delta

#define LH001_91_LEADOFF_CURRENT_SOURCE_5nA   0
#define LH001_91_LEADOFF_CURRENT_SOURCE_10nA  1
#define LH001_91_LEADOFF_CURRENT_SOURCE_25nA  2
#define LH001_91_LEADOFF_CURRENT_SOURCE_50nA  3
#define LH001_91_LEADOFF_CURRENT_SOURCE_100nA 4

#define LH001_91_LEADOFF_SINK_CLOSE           0
#define LH001_91_LEADOFF_SINK_AIN0            1
#define LH001_91_LEADOFF_SINK_AIN1            2
#define LH001_91_LEADOFF_SINK_AIN0_1          3

#define LH001_91_LEADOFF_SOURCE_CLOSE         3
#define LH001_91_LEADOFF_SOURCE_AIN0          2
#define LH001_91_LEADOFF_SOURCE_AIN1          1
#define LH001_91_LEADOFF_SOURCE_AIN0_1        0

typedef struct
{
	// threshold to determine lead off state
	// LH001_91_LEADOFF_DELTA_1
	// LH001_91_LEADOFF_DELTA_2
	// LH001_91_LEADOFF_DELTA_3
	// LH001_91_LEADOFF_DELTA_4
	// LH001_91_LEADOFF_DELTA_5
	// LH001_91_LEADOFF_DELTA_6
	// LH001_91_LEADOFF_DELTA_7
	// LH001_91_LEADOFF_DELTA_8
	// LH001_91_LEADOFF_DELTA_9
	// LH001_91_LEADOFF_DELTA_10
	// LH001_91_LEADOFF_DELTA_11
	// LH001_91_LEADOFF_DELTA_12
	// LH001_91_LEADOFF_DELTA_13
	// LH001_91_LEADOFF_DELTA_14
	// LH001_91_LEADOFF_DELTA_15
	// LH001_91_LEADOFF_DELTA_16
	uint32_t threshold;
	// current source selection for lead off detection
	// LH001_91_LEADOFF_CURRENT_SOURCE_5nA
	// LH001_91_LEADOFF_CURRENT_SOURCE_10nA
	// LH001_91_LEADOFF_CURRENT_SOURCE_25nA
	// LH001_91_LEADOFF_CURRENT_SOURCE_50nA
	// LH001_91_LEADOFF_CURRENT_SOURCE_100nA
	uint32_t current;
	// connection for sink current source
	// LH001_91_LEADOFF_SINK_CLOSE
	// LH001_91_LEADOFF_SINK_AIN0
	// LH001_91_LEADOFF_SINK_AIN1
	// LH001_91_LEADOFF_SINK_AIN0_1
	uint32_t sink_cfg;
	// connection for source current source
	// LH001_91_LEADOFF_SOURCE_CLOSE
	// LH001_91_LEADOFF_SOURCE_AIN0
	// LH001_91_LEADOFF_SOURCE_AIN1
	// LH001_91_LEADOFF_SOURCE_AIN0_1
	uint32_t source_cfg;
	// 0, disable sink current on RLD
	// 1, enable sink current on RLD
	uint32_t rld_sink_en;
	// 0, disable leadoff detection on ain0
	// 1, enable leadoff detection on ain0
	uint32_t ain0_detect_en;
	// 0, disable leadoff detection on ain1
	// 1, enable leadoff detection on ain1
	uint32_t ain1_detect_en;
	// 0, disable leadoff detection on RLD
	// 1, enable leadoff detection on RLD
	uint32_t rld_detect_en;
} LH001_91_LEADOFF_t;


typedef enum {
	LH001_91_CLKSRC_EXT = 0, /// use external clock from clk pin
	LH001_91_CLKSRC_INT,     /// use internal 2.048M osc, clken=0
	/// use internal 2.048MHz OSC and output this clock to clk pin
	/// this feature depends on CLKSEL pin setting,
	///  clksel pad    |  clken     | clock source   | CLK pad
	///-----------------------------------------------------------
	///       0        |     x      |  external clock| input clock
	///       1        |     0      |  internal osc  | three-state
	///       1        |     1      |  internal osc  | output clock
	LH001_91_CLKSRC_INT_OUTPUT, /// clken=1
} LH001_91_CLOCK_SOURCE_t;


typedef struct {
	uint8_t addr;
	uint8_t val;
	uint8_t reg_name[48];
} REG_DUMP_t;

typedef struct {
	volatile uint64_t reserved0 : 48;
	volatile uint64_t start : 4;
	volatile uint64_t loffstat : 5;
	volatile uint64_t gpio : 2;
	volatile uint64_t reserved1 : 13;
	volatile uint64_t data : 24;
} ADC_DATA_NOFIFO_t;

typedef struct {
	volatile uint64_t reserved0 : 48;
	volatile uint64_t start : 4;
	volatile uint64_t loffstat : 5;
	volatile uint64_t gpio : 2;
	volatile uint64_t reserved1 : 11;
	volatile uint64_t data : 24;
	volatile uint64_t tail : 2;
} ADC_DATA_FIFO_t;

typedef enum {
	ENUM_TIA_GAIN_RES_NO = 0u,
	ENUM_TIA_GAIN_RES_500,
	ENUM_TIA_GAIN_RES_1K,
	ENUM_TIA_GAIN_RES_2K,
	ENUM_TIA_GAIN_RES_5K,
	ENUM_TIA_GAIN_RES_10K,
	ENUM_TIA_GAIN_RES_20K,
	ENUM_TIA_GAIN_RES_40K,
	ENUM_TIA_GAIN_RES_80K,
	ENUM_TIA_GAIN_RES_160K,
	ENUM_TIA_GAIN_RES_EXT,
} TIA_GAIN_RES_t;

typedef enum {
	CURRENT_SOURCE_MAG_100nA = 0,
	CURRENT_SOURCE_MAG_50uA,
	CURRENT_SOURCE_MAG_100uA,
	CURRENT_SOURCE_MAG_250uA,
	CURRENT_SOURCE_MAG_500uA,
	CURRENT_SOURCE_MAG_750uA,
	CURRENT_SOURCE_MAG_1mA,
} CURRENT_SRC_MAG_t;


#ifndef LH_ENABLE
#define LH_ENABLE 1
#endif
#ifndef LH_DISABLE
#define LH_DISABLE 0
#endif

#define LH_FIFO_ENABLE  1
#define LH_FIFO_DISABLE 0


/*****************************************************************************************
								API
*****************************************************************************************/
void lh001_91_adc_go(void);
void lh001_91_adc_stop(void);
void lh001_91_sw_reset(void);
void lh001_91_reset_fifo(void);
void lh001_91_rdatac_start(void);
void lh001_91_rdatac_stop(void);

void lh001_91_hw_reset(void);
void lh001_91_write_regs(uint8_t addr, uint8_t *pRegs, uint8_t num);
void lh001_91_read_regs(uint8_t addr, uint8_t *pRegs, uint8_t num);
void lh001_91_read_data(uint8_t *pData, uint8_t num);
void lh001_91_read_data_nofifo(ADC_DATA_NOFIFO_t *pData);
void lh001_91_read_data_fifo(ADC_DATA_FIFO_t *pData);
void lh001_91_standby(void);
void lh001_91_wakeup(void);

void lh001_91_adc_init(LH001_91_ADC_INIT_t *pInit);
void lh001_91_adc_channel(uint32_t chP, uint32_t chN);
void lh001_91_pga_init(LH001_91_PGA_INIT_t *pInit);
void lh001_91_leadoff_init(LH001_91_LEADOFF_t *pInit);
void lh001_91_rld_init(uint32_t enable, uint32_t refsel, uint32_t chop);

void lh001_91_test_signal(uint32_t freq);
void lh001_91_spi_daisy_mode(uint32_t enable);
void lh001_91_clock_source(LH001_91_CLOCK_SOURCE_t clksrc);
void lh001_91_userkey_unlock(void);
void lh001_91_userkey1_unlock(void);
float lh001_91_adc_code2mv(uint32_t code, uint32_t ref);

void lh001_91_reg_dump(REG_DUMP_t *pRegs, uint8_t num);
void lh001_91_output_clk(uint32_t clkSrc, uint32_t pin);

#ifdef __cplusplus
}
#endif
#endif // #ifndef __LH001_91_H
