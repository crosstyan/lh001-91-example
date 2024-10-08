#ifndef __PROCESS_CMD_H__
#define __PROCESS_CMD_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "uart_frame.h"
#include "lh_ecg.h"

#define CMD_ECG_START  "ECG_START"
#define CMD_ECG_STOP  "ECG_STOP"


#define DEFUALT_ECG_DATA_LENGTH   7500




void process_cmd(UART_CMD_t *pCMD);
void process_adc_data(UART_CMD_t *pCMD,ADC_DATA_NOFIFO_t rawdat);


#endif 

