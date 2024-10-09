/*

Version:
Author: LH Software Group
Copyright
*/

#ifndef __UART_PRINT_H
#define __UART_PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "gd32f3x0_usart.h"
#include "gd32f3x0_rcu.h"
#include "gd32f3x0_gpio.h"

#define DEBUG_PIN_PORT GPIOA
#define DEBUG_PIN      GPIO_PIN_1
#define DEBUG_PIN_RCC  RCU_GPIOA

// #define  UART_BAUDRATE            115200
#define UART_BAUDRATE 1500000


void debug_pin_init(void);
void debug_pin_set(void);
void debug_pin_clr(void);
void debug_pin_toggle(void);

void uart_print_init(void);

#ifdef __cplusplus
}
#endif
#endif
