#ifndef __LH_RESP_H__
#define __LH_RESP_H__

#include "LH001_91.h"

void lh_resp_init(void);
void lh_resp_start(void);
void lh_resp_stop(void);

float resp_filter_lowpass(float input);


#endif

