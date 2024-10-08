#include "uart_frame.h"

uint8_t uart_fifo[FIFO_LENGTH];
UART_FIFO_t fifo;
uint32_t state = LH_FRAME_PROC_STATE_IDLE;

char cmd_content[32];
char *pDat =cmd_content; 

void uart_frame_process(UART_CMD_t *pCMD)
{
    uint32_t rx_num,i;
    uint8_t rx_byte;
    rx_num = uart_fifo_getnum();
    if(rx_num != 0)
    {
        for(i=0;i<rx_num;i++)
        {
            if(state == LH_FRAME_PROC_STATE_IDLE)
            {
                if(uart_fifo_read()==LH_COMM_FREME_HEAD)
                {
                    state = LH_FRAME_PROC_STATE_SYNC;
                }
            }
            else if (state == LH_FRAME_PROC_STATE_SYNC)
            {
                pCMD->cmdID = uart_fifo_read();
                state = LH_FRAME_PROC_STATE_CMD;
            }
            else if (state == LH_FRAME_PROC_STATE_CMD)
            {
                if(pCMD->cmdID == LH_COMM_CMD_ID)
                {
                    rx_byte = uart_fifo_read();
                    if(rx_byte == LH_COMM_FREME_END)
                    {
						pCMD->contentLen = cmd_content[0];
                        pCMD->pCmdContent = &(cmd_content[1]);
                        pCMD->flag = LH_FRAME_PROC_FLAG_VALID;
                        state = LH_FRAME_PROC_STATE_IDLE;
						pDat = cmd_content;
                        break;
                    }
                    else
                    {
                        *pDat++ = rx_byte;
                    }
                    
                }
                else if(pCMD->cmdID == LH_COMM_WRITEREG_ID)
                {

                }
                else if(pCMD->cmdID == LH_COMM_READREG_ID)
                {

                }
                else 
                {
                    state = LH_FRAME_PROC_STATE_IDLE;
                }
            }
			else
			{
				state = LH_FRAME_PROC_STATE_IDLE;
			}
            
            
        }
    }
}


void uart_fifo_init()
{
    fifo.num = 0;
    fifo.pFIFO = uart_fifo;
    fifo.pRd=fifo.pFIFO;
    fifo.pWr=fifo.pFIFO;
}

void uart_fifo_write(uint8_t byte)
{
    if(fifo.num < FIFO_LENGTH)
    {
        *(fifo.pWr) = byte;
        fifo.num++;
        if(fifo.pWr == (uint8_t *)(fifo.pFIFO + FIFO_LENGTH - 1))   
        {
            fifo.pWr = fifo.pFIFO;
        }
        else
        {
            fifo.pWr++;
        }
    }
    else
    {
        /*FIFO full*/
    }  
}

uint8_t uart_fifo_read()
{
    uint8_t rdbyte;
    if(fifo.num != 0)
    {
        fifo.num--;
        rdbyte = *(fifo.pRd);
        if(fifo.pRd == (uint8_t *)(fifo.pFIFO + FIFO_LENGTH - 1))   
        {
            fifo.pRd = fifo.pFIFO;
        }
        else
        {
            fifo.pRd++;
        }
    }
    else
    {
        /*FIFO Empty*/
    }  
	
	return rdbyte;
}

uint32_t uart_fifo_getnum()
{
    return fifo.num;
}

