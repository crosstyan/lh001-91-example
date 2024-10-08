/*

Version:
Author: LH Software Group
Copyright
*/

#ifndef __STM_LH_SPI_H
#define __STM_LH_SPI_H

#include "LH001_91.h"
#include "gd32f3x0_spi.h"
#include "gd32f3x0_rcu.h"
#include "gd32f3x0_gpio.h"
#include "gd32f3x0_syscfg.h"
#include "gd32f3x0_exti.h"
#include "gd32f3x0_misc.h"

#define GPIO_EMULATE_SPI 0

//some LDO has enable pin, If an ldo used for LHxxx,
//this macro will set a GPIO from host to control this LDO enable pin
//#define LDO_ENABLE_PIN_EN

//setup GPIO for drdy interrupt
#define DRDY_INT_ENABLE 1

/*
Connection between GD32  and LH001_91 

 GD32F330         |     LH001_91
 ------------------------------------
 PA4/SPI0_CS      |     LH_CS
 PA5/SPI0_SCLK    |     LH_SCLK
 PA6/SPI0_MISO    |     LH_DOUT
 PA7/SPI0_MOSI    |     LH_DIN
 PB1              |     PWDN
 PA9              |     START
 PA10             |     DRDY
 #ifdef LDO_ENABLE_PIN_EN
 PG6              |     AFE_EN(P2-7)  //used when user has ldo enable pin
 #endif
*/

/*
    1 - Use GPIO control SPI cs
    0 - Use SPI CS pin
*/
#ifndef SOFTWARE_SPI_CS
#define SOFTWARE_SPI_CS      1
#endif

#if SOFTWARE_SPI_CS
#define SPI_SET_CS()  GPIO_BOP(GPIOA)=GPIO_PIN_4
#define SPI_CLR_CS()  GPIO_BC(GPIOA)=GPIO_PIN_4
#endif
#if GPIO_EMULATE_SPI
#define SPI_SET_SCLK()  GPIOB->BSRRL=GPIO_Pin_13
#define SPI_CLR_SCLK()  GPIOB->BSRRH=GPIO_Pin_13
#define SPI_SET_MOSI()  GPIOB->BSRRL=GPIO_Pin_15
#define SPI_CLR_MOSI()  GPIOB->BSRRH=GPIO_Pin_15
#endif

#define stm_lh_pdextrst_set() GPIO_BOP(GPIOB)=GPIO_PIN_1
#define stm_lh_pdextrst_clr() GPIO_BC(GPIOB)=GPIO_PIN_1
#define stm_lh_start_set()    GPIO_BOP(GPIOA)=GPIO_PIN_9
#define stm_lh_start_clr()    GPIO_BC(GPIOA)=GPIO_PIN_9
#ifdef LDO_ENABLE_PIN_EN
#define stm_giga_afeen_set()    GPIOG->BSRRL=GPIO_Pin_6
#endif

void stm_lh_spi_init(void);
uint8_t stm_lh_spi_txrx8bit(uint8_t tx_byte);
void stm_lh_delay_10us(void);

#endif
