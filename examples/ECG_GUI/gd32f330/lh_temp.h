#ifndef __LH_TEMP_H__
#define __LH_TEMP_H__

#include "LH001_91.h"

#define TEMP_SENSOR_TYPE_RTD   0
#define TEMP_SENSOR_TYPE_TC    1
#define TEMP_SENSOR_TYPE_IR    2

void lh_temp_init(uint32_t sensor_type);
void lh_temp_start(void);
void lh_temp_stop(void);



#endif

