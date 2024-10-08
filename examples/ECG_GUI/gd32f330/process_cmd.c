/*
## LH
#      数据包分类， 数字为字节数
#命令：        帧头1 + 命令ID1 + 命令长度1 + 命令字符 + 帧尾1
#配置：         
#读寄存器操作： 帧头1 + 读寄存器命令ID1 + 寄存器地址4 + 帧尾
#写寄存器操作： 帧头1 + 写寄存器命令ID1 + 寄存器地址4 + 寄存器值4 + 帧尾
*/

#include "process_cmd.h"

static uint32_t data_cnt;
static uint32_t qrs_sample_cnt;

void process_cmd(UART_CMD_t *pCMD)
{
    if( strncmp(pCMD->pCmdContent,CMD_ECG_START,pCMD->contentLen) == 0)
    {
        lh_ecg_init();
        lh_ecg_start();
        data_cnt = 0;
		qrs_sample_cnt = 0;
    }
	  else if( strncmp(pCMD->pCmdContent,CMD_ECG_STOP,pCMD->contentLen) == 0)
    {
        lh_ecg_stop();
        data_cnt = 0;
		qrs_sample_cnt = 0;
    }
		
    pCMD->flag = LH_FRAME_PROC_FLAG_INVALID;
}

void process_adc_data(UART_CMD_t *pCMD,ADC_DATA_NOFIFO_t rawdat)
{
    int32_t iDat;
		int32_t ptFilter;
		uint32_t leadoffStat;
		uint32_t qrs,heart_rate;
    float volt_mv,filt50Hz;
    float hp_flt,lp_flt,avg;
		heart_rate = 0;
    if(rawdat.data & (1<<23))
        iDat = (int)((0xFFu<<24)|(rawdat.data));
    else
        iDat = (int)(rawdat.data);

		iDat = -iDat;		//if the electrode reversed
    if(strncmp(pCMD->pCmdContent,CMD_ECG_START,pCMD->contentLen) == 0)
    {
				leadoffStat = rawdat.loffstat;
        volt_mv = iDat*2.0*ADC_REF_MV/((1<<24)-1)/6;
        //filt50Hz = lh_filter_50Hz(volt_mv);
			  filt50Hz = volt_mv;
			  lp_flt = lh_filter_lowpass((float)filt50Hz);
			  avg = shift_avergage(lp_flt);
        hp_flt = lh_filter_highpass((float)avg);
				
		
				qrs = panTompkins(iDat,(dataType *)(&ptFilter));
				qrs_sample_cnt++;
				if (qrs)
				{
					heart_rate = (uint32_t)(60000.0/qrs_sample_cnt/4+0.5);	//250 Fs, 4ms per sample
					qrs_sample_cnt = 0;
				}
				printf("%d,%d,%f,%f,%d,%f,%d,%d\r\n",data_cnt,iDat,volt_mv,avg,ptFilter,hp_flt,heart_rate,leadoffStat);
						data_cnt++;
    }
		

    

}

