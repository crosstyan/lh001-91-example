/*
## LH
#      数据包分类， 数字为字节数
#命令：        帧头1 + 命令ID1 + 命令长度1 + 命令字符 + 帧尾1
#配置：         
#读寄存器操作： 帧头1 + 读寄存器命令ID1 + 寄存器地址4 + 帧尾
#写寄存器操作： 帧头1 + 写寄存器命令ID1 + 寄存器地址4 + 寄存器值4 + 帧尾
*/

#ifndef __UART_FRAME_H__
#define __UART_FRAME_H__

#include <stdint.h>

#define FIFO_LENGTH  64

typedef struct 
{
    uint32_t num;
    uint8_t *pRd;
    uint8_t *pWr;
    uint8_t *pFIFO;
}UART_FIFO_t;

#define LH_FRAME_PROC_STATE_IDLE   0
#define LH_FRAME_PROC_STATE_SYNC   1
#define LH_FRAME_PROC_STATE_CMD    2
#define LH_FRAME_PROC_STATE_IDLE   0
#define LH_FRAME_PROC_STATE_IDLE   0
#define LH_FRAME_PROC_FLAG_VALID   1
#define LH_FRAME_PROC_FLAG_INVALID 0


#define LH_COMM_FREME_HEAD   0x7E
#define LH_COMM_CMD_ID       0
#define LH_COMM_WRITEREG_ID  1
#define LH_COMM_READREG_ID   2
#define LH_COMM_FREME_END    0x7D

typedef struct 
{
    uint8_t cmdID;
    char  *pCmdContent;
    uint8_t contentLen;
    uint8_t flag;
}UART_CMD_t;


void uart_frame_process(UART_CMD_t *pCMD);

void uart_fifo_init(void);
void uart_fifo_write(uint8_t byte);
uint8_t uart_fifo_read(void);
uint32_t uart_fifo_getnum(void);



#endif 
