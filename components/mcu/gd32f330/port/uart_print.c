/*

Version:
Author: LH Software Group
Copyright
*/

#include "uart_print.h"


void debug_pin_init()
{
    rcu_periph_clock_enable(DEBUG_PIN_RCC);
    gpio_mode_set(DEBUG_PIN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, DEBUG_PIN);
    gpio_output_options_set(DEBUG_PIN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, DEBUG_PIN);

}

void debug_pin_set()
{
    GPIO_BOP(DEBUG_PIN_PORT) = DEBUG_PIN;
}
void debug_pin_clr()
{
    GPIO_BC(DEBUG_PIN_PORT) = DEBUG_PIN;
}
void debug_pin_toggle()
{
    GPIO_TG(DEBUG_PIN_PORT) = DEBUG_PIN;
}


/*!
    Initialization for debug functions like uart print and toggle GPIO
*/
void uart_print_init()
{
    //-----------  DEBUG GPIO Init  ----------------
/* enable COM GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);
	/* connect port to USARTx_Tx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_2);

    /* connect port to USARTx_Rx */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_3);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_2);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, GPIO_PIN_3);
	
	 

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART1);

    /* USART configure */
    usart_deinit(USART1);
    usart_word_length_set(USART1, USART_WL_8BIT);
    usart_stop_bit_set(USART1, USART_STB_1BIT);
    usart_parity_config(USART1, USART_PM_NONE);
    usart_baudrate_set(USART1, UART_BAUDRATE);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);

    usart_enable(USART1);

}

#ifdef __ICCARM__
int putc(char c)
{
    usart_data_transmit(USART1,c);
    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
    return c;
}
#else 
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART1,ch);
    while(RESET == usart_flag_get(USART1, USART_FLAG_TBE));
    return ch;

}
#endif

