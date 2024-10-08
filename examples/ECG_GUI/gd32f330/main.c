/*

Version:
Author: LH Software Group
Copyright
*/

#include "LH001_91.h"
#include <stdio.h>
#include "uart_print.h"
#include "uart_frame.h"
#include "process_cmd.h"

uint32_t data_cnt;

volatile ADC_DATA_NOFIFO_t dat;
volatile uint32_t data_ready_flag;

void delay(uint32_t t)
{
    for(uint32_t i=0;i<t;i++);
}

void uart_rx_int_en()
{
    usart_interrupt_disable(USART1,USART_INT_TBE);
    usart_interrupt_enable(USART1,USART_INT_RBNE);
    nvic_irq_enable(USART1_IRQn, 2U, 0U);

}

/*check below registers for configuration*/
REG_DUMP_t reg[] =
{
  {ADDR_LH001_91_PGAGAIN,0,"ADDR_LH001_91_PGAGAIN"},
  {ADDR_LH001_91_PGACTRL,0,"ADDR_LH001_91_PGACTRL"},
  {ADDR_LH001_91_PGACTRL1,0,"ADDR_LH001_91_PGACTRL1"},
  {ADDR_LH001_91_ADCCTRL,0,"ADDR_LH001_91_ADCCTRL"},
  {ADDR_LH001_91_ADCCHCON,0,"ADDR_LH001_91_ADCCHCON"},
  {ADDR_LH001_91_BUFCON,0,"ADDR_LH001_91_BUFCON"},
  {ADDR_LH001_91_CLKCON,0,"ADDR_LH001_91_CLKCON"},
	{ADDR_LH001_91_LOCON1,0,"ADDR_LH001_91_LOCON1"},
  {ADDR_LH001_91_LOCON2,0,"ADDR_LH001_91_LOCON2"},
  {ADDR_LH001_91_LOCON3,0,"ADDR_LH001_91_LOCON3"},
  {ADDR_LH001_91_LOFFSTAT,0,"ADDR_LH001_91_LOFFSTAT"},
  {ADDR_LH001_91_RLDCON,0,"ADDR_LH001_91_RLDCON"},
};



int main()
{
	uint8_t val;
	UART_CMD_t uart_proc;
    uart_proc.flag = LH_FRAME_PROC_FLAG_INVALID;

	data_ready_flag = 0;
	
	uart_print_init();
    debug_pin_init();
    LH001_91_Spi_Init();
	lh001_91_sw_reset();
	
	lh001_91_read_regs(ADDR_LH001_91_BUFCON,&val,1);
    val &= ~(MSK_LH001_91_BUFCON_EN2P5|MSK_LH001_91_BUFCON_ENREF);
    lh001_91_write_regs(ADDR_LH001_91_BUFCON,&val,1); 

    uart_rx_int_en();
    uart_fifo_init();
	data_ready_flag = 0;

    while(1)
    {

        uart_frame_process(&uart_proc);
        if(uart_proc.flag == LH_FRAME_PROC_FLAG_VALID)
        {
            process_cmd(&uart_proc);
        }
			
		if(data_ready_flag>0)
		{
			data_ready_flag = 0;
            process_adc_data(&uart_proc,dat);
		}		 
    }
}


void EXTI4_15_IRQHandler()
{
  if(exti_interrupt_flag_get(EXTI_10) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    exti_interrupt_flag_clear(EXTI_10);
    
    //read ADC data
    lh001_91_read_data_nofifo(&dat);
    data_ready_flag++;
  }
    
}

void USART1_IRQHandler()
{
    /* USART in Receiver mode */
	if(usart_flag_get(USART1,USART_FLAG_RBNE)!= RESET)
  {
      uart_fifo_write( usart_data_receive(USART1) );
  }
}
