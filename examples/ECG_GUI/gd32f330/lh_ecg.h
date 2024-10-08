#ifndef __LH_ECG_H__
#define __LH_ECG_H__

#include "LH001_91.h"
#include "panTompkins.h"
#include "adaptive_lms.h"

void lh_ecg_init(void);
void lh_ecg_start(void);
void lh_ecg_stop(void);

float lh_filter_highpass(float input);
float lh_filter_50Hz(float input); 
float lh_filter_lowpass(float input);
float lh_filter_50notch(float input);
float shift_avergage(float input);

#endif

