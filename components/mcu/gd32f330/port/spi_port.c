/*

Version:
Author: LH Software Group
Copyright
*/

#include "spi_port.h"


void stm_lh_spi_init()
{

    //PDEXTRST pin Init
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_1);
    stm_lh_pdextrst_set();

    //START PIN init
    rcu_periph_clock_enable(RCU_GPIOA);
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
    stm_lh_start_clr();
  //DRDY PIN INIT
    rcu_periph_clock_enable(RCU_CFGCMP);
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO_PIN_10);
 /* enable and set key wakeup EXTI interrupt to the higher priority */
    nvic_irq_enable(EXTI4_15_IRQn, 2U, 0U);
    /* connect key wakeup EXTI line to key GPIO pin */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN10);
    /* configure key wakeup EXTI line */
    exti_init(EXTI_10, EXTI_INTERRUPT, EXTI_TRIG_FALLING);
    exti_interrupt_flag_clear(EXTI_10);


    //-------SPI PORT INIT
  /*!< Enable the SPI clock */
  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  /*!< Enable GPIO clocks */
    rcu_periph_clock_enable(RCU_SPI0);
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_4);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4);
    SPI_SET_CS();
    /* SPI0 GPIO config: SCK/PA5, MISO/PA6, MOSI/PA7 */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
	gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

  
  /*!< SPI pins configuration *************************************************/
  /*!< Connect SPI pins to AF5 */  
  spi_parameter_struct spi_init_struct;
    /* deinitilize SPI and the parameters */
    spi_i2s_deinit(SPI0);
    spi_struct_para_init(&spi_init_struct);
    
    /* SPI0 parameter config */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_2EDGE;
	 //   spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_8
	;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(SPI0, &spi_init_struct);

    spi_enable(SPI0);


}


uint8_t stm_lh_spi_txrx8bit(uint8_t tx_byte)
{
     /*!< Loop while DR register in not empty */
  while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE));

  /*!< Send byte through the SPI1 peripheral */
  spi_i2s_data_transmit(SPI0, tx_byte);

  /*!< Wait to receive a byte */
  while(RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE));

  /*!< Return the byte read from the SPI bus */
  return spi_i2s_data_receive(SPI0);

}



#ifdef SYS_TICK_DELAY
#define SYS_TICK_CTRL   (*((volatile uint32_t *)0xE000E010))
#define SYS_TICK_RELOAD (*((volatile uint32_t *)0xE000E014))
#define SYS_TICK_CURRENT (*((volatile uint32_t *)0xE000E018))
#endif
void stm_lh_delay_10us()
{
#ifdef SYS_TICK_DELAY
    uint32_t t,sta;
    t = 10*(SystemCoreClock/1000000);
		SYS_TICK_RELOAD = t;
    SYS_TICK_CURRENT = 0;
    SYS_TICK_CTRL = (1<<2)|(1<<0);  //Core clock, enable
    do{
      sta = SYS_TICK_CTRL;
    }while((sta&(1<<16))==0); //wait for counting down to 0
#else 
    for(uint32_t i=0;i<100;i++);
#endif
}

